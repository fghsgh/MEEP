-- lua script for testing drum samples
-- enter a series of hex values, one per line (e.g. 00\n49\n73\nA0\nBA\nD9\n), then ctrl+d to play
-- enter ctrl+d as the first value to exit
-- the script will play it exactly as the sound engine would (modulo a different random number generator), 8 times at 120 bpm
-- (this will probably only work on linux, and it needs mplayer to be installed)

local io = require("io")
local math = require("math")

-- should be roughly MHz / 880
local rate = 18000
-- number of samples per "frame"
local framesize = rate / 100

-- open mplayer to play 16-bit pcm audio
local out = io.popen("mplayer -demuxer rawaudio -rawaudio channels=1:rate=" .. rate .. ":samplesize=2 -really-quiet -","w")
-- alternatively, uncomment this to export to a raw file to be exported into audacity
--local out = io.open("/tmp/a","w")

while true do
  local data = {}
  repeat
    local line = io.read()
    if line then
      data[#data + 1] = tonumber(line,16)
    end
  until not line
  if #data == 0 then
    out:close()
    return
  end

  local phase = 0
  local state = false
  for _ = 1, 8 do
    for i = 1, #data do
      if data[i] == 0 then
        for i = 1, framesize do
          out:write(math.random() < .5 and "\x00\x80" or "\xff\x7f")
        end
      else

        for _ = 1, framesize do
          if phase == 0 then
            state = not state
            phase = data[i]
          end
          phase = phase - 1
          out:write(state and "\x00\x80" or "\xff\x7f")
        end
      end
    end

    for _ = #data + 1, 50 do
      for _ = 1, framesize do
        out:write("\x00\x80")
      end
    end
  end

  for _ = 1, rate do
    out:write("\x00\x80")
  end

  out:flush()
end

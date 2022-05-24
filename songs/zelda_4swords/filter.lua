local io = require("io")
local string = require("string")

local dist = 4
local diff = 9000
local pos = 32767
local high = 32767
local low = -32768
local format = "i2"
local size = 2

local read = io.open(({...})[1],"rb")
local write = io.open(({...})[2],"wb")

local t = {}
for i=1,dist do
  t[i] = 0
end

repeat
--  read:read(2)
  local v = read:read(2)
  if v then
    v = (format):unpack(v)
    table.insert(t,v)
    local p = table.remove(t,1)
    if v - p > diff then
      pos = high
    elseif p - v > diff then
      pos = low
    end
    write:write((format):pack(pos))
  end
until not v

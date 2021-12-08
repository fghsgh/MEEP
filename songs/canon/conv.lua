for line in io.stdin:lines() do
  local len,midi = line:match("(%d+)\t(%d+)")
  midi,len = tonumber(midi),tonumber(len)
  io.write(("  db $%02x,%d\n"):format(midi == 0 and 0x80 or midi % 12 << 4 | midi // 12 - 1,len // 20))
end

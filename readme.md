# MEEP
(Multi-channel EEP Engine Program) (the "EEP" representing the sound of a beep)

My second 1-bit sound engine. Assemble using fasmg. I use fasmg because its macro capabilities are practically required for a project with tons of SMC and dynamically relocated code like this.

See `format.asm` for song data format instructions. See `songs` for song examples. See [my youtube channel](https://www.youtube.com/channel/UCd-hwoM2gHt1Y890qmaZwuQ) for the examples, played back and recorded with oscilloscope visualizations.

Note: this is still in development. There is not yet any interface for playing or selecting songs, and there will be bugs.

## Writing your own songs
I recommend checking out `songs/zelda_4swords`. At some point it'll be able to read from an appvar, but for now I need to assemble to .bin and then include said .bin in the resulting .8xp (see `test/test_zelda.z80`).

## What to assemble
what works:
- `test/test_bitbang.z80` to test `bitbang.z80` (might be broken by now, idk)
- `test/test_canon.z80` to include `songs/canon/canon.z80` and play it as described in [the youtube video](https://youtu.be/590J1vaDna8)
- `test/test_drum.z80` to test a few drum sounds
- `test/test_vib.z80` to test vibrato (I used this to debug vibrato stuff at one point)
- `test/test_zelda.z80` to embed `songs/zelda_4swords/zelda_4swords.bin` in the program and play it, as featured in [this youtube video](https://youtu.be/_XcLONBgVY0)
- `songs/zelda_4swords/zelda_4swords.asm` (make sure to specify `songs/zelda_4swords/zelda_4swords.bin` as the output file) to generate the file needed by `test/test_zelda.z80`

what doesn't work anymore:
- `test/test_driver.z80` at some point I used this to test `driver.z80` but I don't think it works anymore

also, note: all of the `test_*.z80` files are named `prgmA` on-calc

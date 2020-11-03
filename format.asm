; note: throughout this entire document, a "frame" is 1/50th of a second, or 20 ms
; the following is an example note file
; hold down any of the [Y=] [WINDOW] [ZOOM] [TRACE] and [GRAPH] keys during initialization to mute the 4 general-purpose pulse wave channels or the bass wave respectively

include "../tiformat.inc"
format ti appvar

  db "fghbeep2" ; magic number

  org $0000 ; jump offsets are calculated at runtime because position inside memory is unpredictable
  dw ch0,ch1,ch2,ch3,drumbass ; pointers to the start of all channels

; general-purpose pulsewave channels:
; note: $XY,L where L is the note length, Y is the (standard MIDI) octave (X >= 1) and X is the note (0 -> C, B -> B), notes higher than B are undefined but could be set to up to 16-TET with few modifications to the source
;   e.g. C3 is $03, A#5 is $A5
;   more notes can be put between $XY and L for arpeggios (see command $70)
; rest: $ff,L where L is the rest length
; command: $X0 where X is command, optionally with arguments in the following byte(s) (depending on command type)
; commands:
;  $00: set starting pulse width settings
;    1 byte = the pulse width to set at the start of a note ($00 = 0%, $ff = 99.6%, default $00)
;               $00 means "do not change previous value"
;    1 byte = minimum pulse width
;    1 byte = maximum pulse width
;    1 word = offset added to pulse width each time (only MSB is used, LSB is for precision), default $0000
;               an attempt is made at handling overflows
;  $10: set mask
;    1 byte = the mask to set (bit 0 = left, bit 1 = right, other bits ignored)
;  $20: set note length to additive (each note will end after exactly X frames, and will remain silent until the next note starts) (this cancels $07)
;    1 byte = the note length to set (in frames)
;               for notes which are shorter than the additive note length, their length overrides the default one
;  $30: set note length to subtractive (each note will end X frames before the next one starts) (this cancels $06)
;    1 byte = the note length to set (in frames), default $00
;               notes shorter than the subtractive note length will not be played (will be replaced by rests)
;  $40: set note length to fractional (each note will play for a set % of time of the note's length)
;    1 byte = fraction of note that should be played (e.g. $80 = 50% of the note) (rounded down)
;               note length will be rounded down and rest length will be rounded up
;  $50: set glide
;    1 byte = first note, in format $XY as always
;    1 byte = target note, in format $XY as always
;    1 byte = length in frames
;               the glide will overwrite vibrato settings, and enable vibrato (and thus disable arpeggio), be sure to reset it afterwards or else every next note will also be a glide
;               this is because the vibrato code is repurposed for the glide, but detecting each time whether a glide happened and restoring the vibrato state afterwards may not even be preferrable, and would be slow, in any case
;  $60: set vibrato properties
;    1 byte = vibrato delay, in frames (how long the note must have been playing before vibrato takes effect), default $00
;    1 byte = how much the frequency of the playing note can differ from its standard frequency, in 1/512ths of the central frequency, relative, default $00 (both up and down)
;               for example, (2^(1/12)-1)*512 (approximately 30), will result in a vibrato of one semitone up & down
;               unlike with pulse width ramping, carry is NOT handled when oscillating the frequency, because frequencies are expected to fall in a "sane" range
;    1 byte = value added to / subtracted from frequency each frame while vibrato is active, in 1/512ths of the standard frequency, default $00
;               this divided by the previous byte is the number of frames per half oscillation
;    arpeggio length is set to 1 when this command is used!
;  $70: set arpeggio length
;    1 byte = the number of notes in this arpeggio (only bottom 5 bits are considered, and $00 is considered the same as $20, so max = $20), default $01
;               this turns off vibrato! (vib and arp are mutually exclusive because otherwise the vibrato would have to be applied to all arpeggio notes for which there is not enough time)
;  $80: rest (do not play anything for a set number of frames)
;    1 byte = number of frames to rest
;  $90: unconditional jump
;    1 word = address relative to the start of the appvar
;  $a0: decrement value and if not zero, jump to address
;    1 byte = index of value to decrement
;    1 word = address relative to the start of the appvar
;  $b0: set table value
;    1 byte = index of value to set
;    1 byte = value to set it to, all values are initialized to 0 (there is only one table and it is shared between all channels)
;  $c0-$f0: end of this channel (program will terminate when all channels have finished)

; a few notes (pun not intended) about frame timing:
;   not having to read a new note, only advancing pulse width/arpeggio/vibrato is much more economical, especially if there are no new commands to be processed
;   slowdowns may be noticeable if multiple chains of complex commands execute in subsequent frames, and the player will not attempt to catch up if it missed a frame
;   however, even if one channel ends up taking more time, it may still be fine so long as the other channels do not require much further processing

ch0:
  db $00,$80
  db $04,$03
  db $40,250	; C4
  db $30,100
  db $0f

ch1:
  db $00,$80
  db $04,$03
  db $ff,50	; rest
  db $43,200	; Eb4
  db $44,100	; E4
  db $0f

ch2:
  db $00,$80
  db $04,$03
  db $ff,100	; rest
  db $47,250	; G4
  db $0f

ch3:
  db $00,$80
  db $04,$03
  db $ff,150	; rest
  db $50,200	; C5
  db $0f

drumbass:
; drum/bass channel: can play both noise and square waves
;  $XY with X a MIDI note name and Y an octave: play this note on the bass channel (same as general-purpose pulse wave channels)
; commands:
;  $00: play noise/bass sequence
;    1 word: address of noise/bass sequence (explained below)
;  $80: play noise
;    1 byte: number of frames to play noise for (use 0 to simulate a rest)
;    1 byte: number of frames of silence afterwards
;  $10-$40,$70,$90-$f0: identical to general-purpose counterparts

; noise/bass table:
;   this can be used to create complex-sounding drum sounds by rapidly switching between noise and notes of varying pitch
;   at the address pointed to by the word argument of the $00 command, a sequence of bytes is found, where each byte encodes a single frame
;   this byte can be:
;     $00 followed by another $00 to signify the end of the sequence
;     $00 followed by anything else to signify noise (the next byte is ignored)
;     $01-$ff to signify a wavelength for the bass wave, the wavelength is given using the formula H/880/(2^((M-69)/12)*440)/2, where...
;               H is the CPU frequency in Hz
;               M is the MIDI code, where A4 = 69
;               880 is the number of clock cycles per effective sample
;               2 signifies the fact that frequency doubles if the octave goes up by one
;               69 is the MIDI code for the note which has frequency 440 Hz
;               12 is the number of semitones in an octave
;               440 is the frequency in Hz of the note with MIDI code 69
;   the length of the sample is subtracted from the next note, in order to pretend that drums are instantaneous

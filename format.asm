; note: throughout this entire document, a "frame" is 1/50th of a second, or 20 ms
; the following is an example note file
; hold down any of the [Y=] [WINDOW] [ZOOM] [TRACE] and [GRAPH] keys during initialization to mute the 4 general-purpose pulse wave channels or the bass wave respectively

include "../tiformat.inc"
format ti appvar

  db "MEEP" ; magic number

  org $0000 ; jump offsets are calculated at runtime because position inside memory is unpredictable
  dw ch0,ch1,ch2,ch3,drum,bass ; pointers to the start of all channels

; general-purpose pulsewave channels:
; note: $XY,L where L is the note length, Y is the (standard MIDI, with offset 2) octave (must be >= 1, (so MIDI octave -1)) and X is the note (0 -> C, B -> B), notes higher than B are undefined but could be set to up to 16-TET with a few modifications to the source
;   e.g. C3 is $05, A#5 is $A7
;   more notes can be put between $XY and L for arpeggios (see command $70)
; rest: $80,L where L is the rest length
; command: $X0 where X is command, optionally with arguments in the following byte(s) (depending on command type)
; commands:
;  $00: set starting pulse width settings
;    1 byte = the pulse width to set at the start of a note ($00 = 0%, $ff = 99.6%, default $00)
;               $00 means "do not change previous value"
;               this will also cause the min & max to not exist (the values actually aren't stored, not just not read, it immediately goes to the offset 2 bytes later)
;    1 byte = minimum pulse width (only if start != 0)
;    1 byte = maximum pulse width (only if start != 0)
;    1 word = offset added to pulse width each time (only MSB is used, LSB is for precision), default $0000
;               an attempt is made at handling overflows
;  $10: set mask
;    1 byte = the mask to set (bit 0 = left, bit 1 = right, other bits ignored)
;  $20: set note length to ("max length") additive (each note will end after exactly X frames, and will remain silent until the next note starts) (this cancels $07)
;    1 byte = the note length to set (in frames)
;               for notes which are shorter than the additive note length, their length overrides the default one
;  $30: set note length to ("constant gap") subtractive (each note will end X frames before the next one starts) (this cancels $06)
;    1 byte = the note length to set (in frames), default $00
;               notes shorter than the subtractive note length will not be played (will be replaced by rests)
;  $40: set note length to fractional (each note will play for a set % of time of the note's length)
;    1 byte = fraction of note that should be played (e.g. $80 = 50% of the note) (rounded down)
;               note length will be rounded down and rest length will be rounded up
;  $50: set glide
;    1 byte = first note, in format $XY as always
;    1 byte = target note, in format $XY as well
;    1 byte = length in frames
;               the glide will overwrite vibrato settings, and enable vibrato (and thus disable arpeggio), so be sure to restore it afterwards or else every next note will also be a glide
;               this is because the vibrato code is repurposed for the glide, and I didn't feel like writing code to restore the arpeggio/vibrato settings after finishing a glide
;               note that, although it does enable vibrato, the vibrato settings as set by $60 are not changed
;  $60: set vibrato properties
;    1 byte = vibrato delay, in frames (how long the note must have been playing before vibrato takes effect)
;    1 byte = how much the frequency of the playing note can differ from its standard frequency
;               the scaling on this is such that 2048 is one octave up and infinity down (of course, 2048 is out of range)
;               hence, (2^(1/12)-1)*2048, which is approximately 122, will result in one semitone up&down
;               unlike with pulse width modulation, carry is NOT handled when oscillating the frequency, because frequencies are expected to fall in a "sane" range
;    1 byte = value added to / subtracted from frequency each frame while vibrato is active
;               the scaling on this is the same as the previous byte
;               the previous byte divided by this is the number of frames per quarter oscillation
;    this command also disables arpeggio
;  $70: set arpeggio
;    1 byte = the number of notes in all following arpeggios ($00 has undefined behavior)
;    1 byte = the number of frames per note
;    this command also disables vibrato
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
;  $c0: sync oscillator to channel
;    1 byte = channel to sync to
;    this will stop this channel's oscillator and continuously sync it to the given channel
;    the given channel number can be in the range 0-3
;    this will have the effect that two channels will always play the same frequency and will always be in phase (although they can still have a separate pulse width, mask, and timings)
;    set a channel's sync to itself to give it its own oscillator back
;    note: syncing channels like this actually frees up a lot of CPU time, so consider using this for all your general-purpose channels which are currently not playing anything
;  $d0: reserved (as of now, does nothing)
;  $e0: end of this channel (stop playing notes in this channel, still continue all other channels)
;  $f0: end of the song (finish all channels immediately)

; a few comments about frame timing:
;   not having to read a new note, and only advancing pulse width/arpeggio/vibrato is much more economical, especially if there are no new commands to be processed
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
  db $80,50	; rest
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

drum:
; drum channel:
;   <len:byte><sequence:word>: play a drum sequence, <len> is the time in frames before the next command should be parsed, <sequence> is a pointer to the start of the drum sequence
;   if <len> is $00, the next byte specifies a command:
;     $10,<mask:byte>: set mask
;     $80,<length:byte>: rest
;     $90,<pos:word>: unconditional jump
;     $a0,<index:byte><pos:word>: djnz
;     $b0,<index:byte><value:byte>: set table value
;     $e0: finish
;     $f0: stop
;   a sequence has a format of (1) a byte storing the length of the sequence, and (2) a sequence of bytes, (1) long, where any value != 0 is a wavelength to play on the bass channel, and 0 means noise
; NOTE: the drum channel runs at 100 Hz as opposed to 50 Hz

bass:
; bass channel:
;   note that the bass channel will be muted if the drum channel is playing, as they're played on the same bitbang channel
;   the format is the same as for general-purpose pulse wave channels, except vibrato/glissando don't work, and only commands $00-$40,$70-$b0,$e0-$f0 work
;   also note that the bass channel is tuned completely differently from the general-purpose wave channels; higher notes are more out of tune, and lower notes about the same amount, but not exactly the same, which can lead to phasing effects; however, there are no aliasing artifacts (unlike on the general-purpose channels for high notes)
;
; the pwm command works differently
;   the format is $00,<start>[,<lower>,<upper>],<delay>
;   the bass channel's bitbang ISR will decrement its wavelength counter, and if it hits zero, play the next bit of the <start> value (left rotating it)
;   therefore, <start> is an 8-bit value where each bit represents either low or high (low being 1, high being 0)
;     like the general channels, setting this to 0 will make it not get reset at the start of a note
;     this also skips over lower & upper (like, the values actually don't exist, not just that they aren't read)
;   the bass channel's driver can add one bit, or remove one bit, by doing the operations `a | rotl(a,1)` and `a & rotl(a,1)`
;   the delay in frames between these operations is given by <delay>
;   when the state equals <lower> or <upper>, in any rotation, the next state change will reverse the order, <lower> is only checked when the operation is `a & rotl(a,1)`, <upper> when `a | rotl(a,1)`
;   if <lower> and <upper> are equal, the next state change boundary check will not trigger. if you want to disable PWM, set <delay> to 0
;   <delay> specifies how many frames should happen between individual state changes
;   set <delay> to zero to completely avoid PWM (this sets the delay to 256, but notes can be at most 256 frames long)
; examples:
;   $00,$f0,0,0,0: 50%, no pwm (this is the default)
;   $00,$f0,$80,$fe,: pwm between 12.5% and 87.5%, starting at 50%, with 4 frames between switches, meaning it's oscillating at 1 Hz
;   $00,$aa,0,0,0: play 2 octaves higher, no pwm
;   $00,$cc,$88,$ee,6: play 1 octave higher, pwm between 25% and 75%, starting at 75%, with two oscillations per second
;   $00,$e8,0,0,0: weird wave shape 11101000
; the drum channel has its own pulse width

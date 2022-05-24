include "../format.inc"

;format meep "4swords"

  dw ch0,ch1,ch2,ch3,drum,bass

; tempo = 150 bpm (20 frames per quarter, 5 per 16th)

ch0.counter := 0
ch1.counter := 1
ch2.counter := 2
drum.counter := 3



ch0:
  pwm 112,112,144,150
  sub 2
  set .counter, 2
; intro
; 1
  note 50, F5
  note 10, F5
  note 10, F5
  note  5, F5
  note  5, F5
; 2
.i2:
  note 15, F5
  note  5, Eb5
  note 30, F5
  note 10, F5
  note 10, F5
  note  5, F5
  note  5, F5
; 3
  djnz .counter, .i2
; 4
  set .counter, 3
  note 10, F5
  note  5, C5
  note  5, C5
.i4_:
  note 10, C5
  note  5, C5
  note  5, C5
  djnz .counter, .i4_

  pwm 140,128,156,555
  vib 20,30,10

; theme
.t:
; 1
  note 20, Bb4
  note 30, F4
  note 10, Bb4
  note  5, Bb4
  note  5, C5
  note  5, D5
  note  5, Eb5
; 2
  note 50, F5
  note 10, F5
  note 10, F5
  note  5, Gb5
  note  5, Ab5
; 3
  note 50, Bb5
  note 10, Bb5
  note 10, Bb5
  note  5, Ab5
  note  5, Gb5
; 4
  note 15, Ab5
  note  5, Gb5
  note 40, F5
  note 20, F5
; 5
  note 15, Eb5
  note  5, F5
  note 40, Gb5
  note 10, F5
  note 10, Eb5
; 6
  note 15, Db5
  note  5, Eb5
  note 40, F5
  note 10, Eb5
  note 10, Db5
; 7
  note 15, C5
  note  5, Db5
  note 40, Eb5
  note 20, Gb5
; 8
  note 20, F5
  rest 60 + 80
  jump .t



ch1:
  pwm 112,112,144,150
  sub 2
  set .counter, 2
; intro
; 1
  note 50, Bb4
  note 10, Bb4
  note 10, Bb4
  note  5, Bb4
  note  5, Bb4
; 2
.i2:
  note 15, Bb4
  note  5, Ab4
  note 30, Bb4
  note 10, Bb4
  note 10, Bb4
  note  5, Bb4
  note  5, Bb4
; 3
  djnz .counter, .i2
; 4
  set .counter, 3
  note 10, Bb4
  note  5, F4
  note  5, F4
.i4_:
  note 10, F4
  note  5, F4
  note  5, F4
  djnz .counter, .i4_

; add 3
  vib 3,20,7
  pwm 64,64,64,0

; theme
.t:
; 1
  rest 80 + 10
; 2
  mask 1
  note 10, Bb6
  note  5, Bb6
  note  5, C7
  mask 2
  note  5, Db7
  note  5, Eb7
  mask 3
  note 40, F7 ; 40
; 3
  rest 10
  mask 1
  note  5, Db7
  note  5, F7
  mask 2
  note  5, Ab7
  note  5, Bb7
  mask 3
  note 50, Db8
; 4
  rest 30
  mask 1
  note  5, Db7
  note  5, Eb7
  mask 2
  note 10, F7
  note 10, Db7
  mask 3
  note 20, Ab6
; 5
  rest 30
  mask 1
  note  5, Eb7
  note  5, F7
  note 10, Gb7
  mask 2
  note  5, Eb7
  note  5, F7
  note 20, Gb7
; 6
  rest 30
  mask 1
  note  5, Db7
  note  5, Eb7
  note 10, F7
  mask 2
  note  5, Db7
  note  5, Eb7
  note 20, F7
; 7
  rest 30
  mask 1
  note  5, C7
  note  5, Db7
  note 10, Eb7
  mask 2
  note  5, Eb7
  note  5, F7
  mask 3
  note  5, G7
  note  5, A7
  note  5, B7
  note  5, C8
; 8
  note 20, A7
  rest 60 + 80
  jump .t



ch2:
  pwm 112,112,144,150
  sub 2
; intro
; 1
  note 50, D4
  note 10, D4
  note 10, D4
  note  5, D4
  note  5, D4
; 2
  note 15, C4
  note  5, C4
  note 30, C4
  note 10, C4
  note 10, C4
  note  5, C4
  note  5, C4
; 3
  note 15, C#4
  note  5, C#4
  note 30, C#4
  note 10, C#4
  note 10, C#4
  note  5, C#4
  note  5, C#4
; 4
  set .counter, 3
  note 10, C#4
  note  5, A3
  note  5, A3
.i4_:
  note 10, A3
  note  5, A3
  note  5, A3
  djnz .counter, .i4_

  pwm 176,176,192,500

  arp 1,2
; theme
.t:
  rest 10
  sub 10
; 1
  set .counter, 4
.t1_:
  note 20, D4, Bb4
  djnz .counter, .t1_
; 2
  set .counter, 4
.t2_:
  note 20, C4, Ab4
  djnz .counter, .t2_
; 3
  set .counter, 4
.t3_:
  note 20, Bb3, Gb4
  djnz .counter, .t3_
; 4
  set .counter, 4
.t4_:
  note 20, Ab3, F4
  djnz .counter, .t4_
; 5
  set .counter, 4
.t5_:
  note 20, B3, Gb4
  djnz .counter, .t5_
; 6
  set .counter, 4
.t6_:
  note 20, Bb3, F4
  djnz .counter, .t6_
; 7
  set .counter, 4
.t7_:
  note 20, C4, G4
  djnz .counter, .t7_
; 8
  frac 256 * 4 / 5
  note  5, Eb4, Bb4
  note  5, Eb4, Bb4
  note 10, Eb4, Bb4
  note  5, Eb4, Bb4
  note  5, Eb4, Bb4
  note 10, Eb4, Bb4
  rest 10 + 20 + 10
; 9
  note  5, C4, A4
  note  5, C4, A4
  note 10, C4, A4
  note  5, C4, A4
  note  5, C4, A4
  note 10, C4, A4
  rest 30
  jump .t



ch3:
  pwm 77,77,179,816
  note 80, Bb2
  note 80, Ab2
  note 80, Gb2
  note 80, F2
  sub 8
.t:
; 1
  note 40, Bb2
  note 40, Bb2
; 2
  note 40, Ab2
  note 40, Ab2
; 3
  note 40, Gb2
  note 40, Gb2
; 4
  note 40, Db3
  note 40, Db3
; 5
  note 40, Cb3
  note 40, Cb3
; 6
  note 40, Bb2
  note 40, Bb2
; 7
  note 40, C3
  note 40, C3
; 8
  note 40, F2
  rest 40 + 80
  jump .t



drum:
; 1
  sample 60, cymbal
  sample 10, low_drum
  sample 10, low_drum
  sample 80 + 60, low_drum
; 2
  sample 10, low_drum
  sample 10, low_drum
  sample 80 + 60, low_drum
; 3
  sample 10, low_drum
  sample 10, low_drum
  sample 80, low_drum
; 4
  cmd set .counter, 4
.i4_:
  sample 20, low_drum
  sample 10, hihat
  sample 10, hihat
  cmd djnz .counter, .i4_

; theme
.t:
; 1
  sample 20, cymbal
  sample 10, hihat
  sample 10, hihat
  cmd set .counter, 27
.t1_:
  sample 20, hihat
  sample 10, hihat
  sample 10, hihat
  cmd djnz .counter, .t1_
; 8
  sample 20, cymbal
  sample 10, hihat
  sample 10, hihat
  sample 20, hihat
  sample 10, hihat
  sample 10, hihat
  sample 20, hihat
  sample 10, high_drum
  sample 10, high_drum
  sample 20, high_drum
  sample 10, high_drum
  sample 10, high_drum
; 9
  sample 20, cymbal
  sample 10, hihat
  sample 10, hihat
  sample 20, hihat
  sample 10, hihat
  sample 10, hihat
  sample 20, hihat
  sample 10, low_drum
  sample 10, low_drum
  sample 20, low_drum
  sample 10, low_drum
  sample 10, low_drum
  cmd jump .t

cymbal:
  db 20, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
snare:
  db 6, $00,$30,$00,$30,$00,$00
hihat:
  db 1, $00
high_drum:
  db 5, 0,$39,$53,$6a,$82
low_drum:
  db 6, 0,$49,$73,$a0,$ba,$d9


bass:
  finish

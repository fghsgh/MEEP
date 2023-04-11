; note <length>,<list>

; pwm <start>,<min>,<max>,<offset>
; mask <value>
; add <value>
; sub <value>
; frac <value>
; glide <length>,<start>,<end>
; vib <delay>,<range>,<speed>
; arp <delay>,<count>
; rest <length>
; jump <address>
; djnz <counter>,<address>
; set <counter>,<value>
; sync <channel>
; other <channel>,command...
; finish
; stop

; sample <length>,<address>
; cmd <mask|rest|jump|djnz|set|finish|stop>


include "../tiformat.inc"

macro ?!
  local decode_note,notes

  macro format?.meep? clause&
    format ti appvar clause

    db "MEEP"
  end macro

  define notes
  iterate <note,offset>, C,0, D,2, E,4, F,5, G,7, A,9, B,11
    repeat 1, ascii:`note
      notes.ascii := offset
    end repeat
  end iterate


  macro decode_note name,code
    local mod_count,note,octave,midi
    local char,mod_end

    virtual at 0
      mod_count = 0
      db `name

      load char:byte from 0

      if (char >= 'A' & char <= 'G') | (char >= 'a' & char <= 'g')
        repeat 1, ascii:char and not ('A' xor 'a')
          note = notes.ascii
        end repeat
      else
        err "invalid note '", `name, "': first character is not A-G"
      end if

      repeat $ - $$ - 1
        load char:byte from %
        if char = '#'
          mod_count = mod_count + 1
        else if char = 'b'
          mod_count = mod_count - 1
        else if char = '-'
          mod_end := % + 1
        else
          mod_end := %
          break
        end if
      end repeat

      if ~ definite mod_end
        err "invalid note '", `name, "': missing octave"
      end if

      octave = 0
      repeat $ - mod_end, i:mod_end
        load char:byte from i
        if char >= '0' & char <= '9'
          octave = octave * 10 + (char - '0')
        else
          err "invalid note '", `name, "': can't parse octave"
        end if
      end repeat

      load char:byte from mod_end - 1
      if char = '-'
        octave = - octave
      end if
    end virtual

    if note + mod_count < 0
      octave = octave + (note + mod_count - 11) / 12
    end if
    if octave < -1 | octave > 8
      err "invalid note '", `name, "': octave out of range"
    end if
    code = (((note + mod_count) mod 12 + 12) mod 12) shl 4 or (octave + 2)
  end macro

  macro note? length*, notes&
    local value,length_eval
    iterate note, notes
      decode_note note,value
      db value
    end iterate
    length_eval := length
    db length
  end macro

  macro pwm? init*,min*,max*,offset*
    local value
    db $00
    value = init
    db value
    value = min
    db value
    value = max
    db value
    value = offset
    dw value
  end macro

  iterate <name,code>, mask?,$10, add?,$20, sub?,$30, frac?,$40, rest?,$80, sync?,$c0
    macro name value*
      local value_eval
      value_eval := value
      db code,value_eval
    end macro
  end iterate
    
  macro glide? length*,start*,finish*
    local value
    db $50
    decode_note start,value
    db value
    decode_note finish,value
    db value
    value = length
    db value
  end macro

  macro vib? delay*,range*,speed*
    local value
    db $60
    value = delay
    db value
    value = range
    db value
    value = speed
    db value
  end macro

  macro arp? delay*,count*
    local value
    db $70
    value = count
    db value
    value = delay
    db value
  end macro

  macro jump? address*
    local value
    db $90
    value := address
    dw value
  end macro

  macro djnz? counter*,address*
    local value
    db $a0
    value = counter
    db value
    value = address
    dw address
  end macro

  macro set? counter*,value*
    local v
    db $b0
    v = counter
    db v
    v = value
    db v
  end macro

  iterate <name,code>, finish?,$e0, stop?,$f0
    macro name
      db code
    end macro
  end iterate

  macro sample? length*,address*
    local value
    value = length
    db value
    value = address
    dw value
  end macro

  macro cmd? command&
    local success
    success = 0
    iterate name, mask,rest,jump,djnz,set,finish,stop
      match =name args, command
        db $00
        name args
        success = 1
      end match
    end iterate
    if ~ success
      err "command not supported by drum channel: ", `command
    end if
  end macro

  purge ?
end macro


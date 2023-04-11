; RELOCATABLE AND SMCABLE
; this file defines two fasmg macros: relocatable and smcable (and also some things to make it work together with z80.inc)

; relocatable <name>,<length>,<offset>
; this will define an element <name> that other parts of the code can be relative to
; the address of each word which is relative to this element will be written in the location where the macro was called, from first to last
; the length of this table (measured in words) will be stored to the literal constant <length>
; <offset> is an offset that is applied to the address before storing it into the table (for example, for a relocatable origin, this would be equal to the first argument)
; (in other words, it is the value "to be added" to values in the table when relocating code, and an offset of 0 means the addresses will be absolute)
;
; the purpose of this is to generate code that behaves as if a value were known at assembly time, but instead, it is calculated at runtime and substituted into the program using SMC once, after which it becomes a standard static value with fast access
;
; for example:
; >  org origin
; > loop:
; >  jp loop
; > relocatable origin,length,origin
;
; another example:
; > code_start:
; >  ld hl,(variable + 5)
; >  ld de,(variable + 7)
; >  add hl,de
; >  ld (variable + 3),hl
; > relocatable variable,length,code_start

; smcable <identifier>,<address>,[default=0]
; this macro will define an element <identifier> that can be used as an immediate argument in a single instruction
; the address where the immediate argument would have been stored will be stored in <address>
; after this, it is possible to modify the immediate argument using SMC, using <address> as the address
; multiple SMC variables can be in the same location by adding their elements
; "default" is the value that the variable will be initialized to and emitted into the binary, and is either the third argument or the constant term of the linear polynomial (if there are multiple defaults provided, an error is thrown if they mismatch)
;
; the purpose of this is to facilitate the most common type of SMC, where only the immediate argument of an instruction is modified
;
; for example: (here the generated code is identical to "ld a,$0a \ dec a \ ld ($ - 2),a")
; >  ld a,here + $0a
; >  dec a
; >  ld (here_place),a
; > smcable here,here_place

macro ?!
  local relocatable_data,smcable_data,smcable_defaults,scaleelement

  define relocatable_data
  relocatable_data.count = 0
  element scaleelement

  define smcable_data
  smcable_data.count = 0

  define smcable_defaults

  macro @z80.word size*,value*
    local v,init_value
    v := value
    repeat elementsof v,el:1
      repeat 1,index:el metadataof v
        if (defined smcable_data.index) & (el elementof v relativeto smcable_data.index)
          if definite smcable_data.index.addr
            err "smcable element used more than once"
          else
            smcable_data.index.addr := $
            if defined smcable_data.index.default
              if definite init_value
                if init_value <> smcable_data.index.default
                  err "multiple mismatching default values provided"
                end if
              else
                init_value := smcable_data.index.default
              end if
            end if
          end if
        else if (defined relocatable_data.index) & (el elementof v relativeto relocatable_data.index)
          if ~definite relocatable_data.index.count
            relocatable_data.index.count = 0
          end if
          repeat 1,jndex:relocatable_data.index.count + 1
            relocatable_data.index.count = jndex
            relocatable_data.index.jndex := (el scaleof v) * scaleelement + $
          end repeat
        else
          err "variable term used where not expected"
        end if
      end repeat
    end repeat
    if definite init_value
      if (0 scaleof v) <> init_value
        err "multiple mismatching default values provided"
      end if
    else
      init_value := 0 scaleof v
    end if
    emit size:init_value
  end macro
  macro @z80.byte value*
    @z80.word 1,value
  end macro

  macro relocatable name*,length*,offset*
    local offset_

    repeat 1,index:relocatable_data.count + 1
      relocatable_data.count = index
      element relocatable_data.index:index
      name := relocatable_data.index
      offset_ := offset
      repeat relocatable_data.index.count.final,jndex:1
        repeat 1 scaleof relocatable_data.index.jndex
          dw relocatable_data.index.jndex - %% * scaleelement - offset_
        end repeat
      end repeat
      length := relocatable_data.index.count.final
    end repeat
  end macro

  macro smcable name*,address*,default
    repeat 1,index:smcable_data.count + 1
      smcable_data.count = index
      element smcable_data.index:index
      name := smcable_data.index
      if defined smcable_data.index.addr
        address := smcable_data.index.addr
      else
        err `name," was never used"
      end if
    end repeat
  end macro

  postpone
    relocatable_data.count.final := relocatable_data.count
    repeat relocatable_data.count.final,index:1
      relocatable_data.index.count.final := relocatable_data.index.count
    end repeat
  end postpone

  purge ?
end macro


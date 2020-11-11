include "z80.inc"

; RELOCATABLE AND SMCABLE
; this file defines two fasmg macros: relocatable and smcable (and also some things to make it work together with z80.inc)

; relocatable <name>,<length>,<offset>
; this will define an element <name> that other parts of the code can be relative to
; the address of each word which is relative to this element will be written in the location where the macro was called, from first to last
; the length of this table (measured in words) will be stored to the literal constant <length>
; <offset> is an offset that is applied to the address before storing it into the table (for example, for a relocatable origin, this would be equal to the first argument)
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

; smcable <identifier>,<address>
; this macro will define an element <identifier> that can be used as an immediate argument in a single instruction
; the address where the immediate argument would have been stored will be stored in <address>
; after this, it is possible to modify the immediate argument using SMC, using <address> as the address
; the default value which will be emitted into the binary, is the constant term of the linear polynomial
;
; the purpose of this is to facilitate the most common type of SMC, where only the immediate argument of an instruction is modified
;
; for example: (here the generated code is identical to "ld a,$0a \ dec a \ ld ($ - 2),a")
; >  ld a,here + $0a
; >  dec a
; >  ld (here_place),a
; > smcable here,here_place

macro ?!
	local r_count,r_addresses,r_scaleelement,r_elements
	local s_count,s_addresses,s_elements

	r_count = 1
	define r_elements
	define r_addresses
	element r_scaleelement

	s_count = 1
	define s_elements
	define s_addresses
	define s_defaults

	macro @z80.word size*,value*
		local v,e,smc
		v := value
		repeat elementsof v,i:1
			repeat 1,j:i metadataof v
				if (%% eq 1) & (defined s_elements.#j) & (v relativeto s_elements.#j)
					s_addresses.#j := $
				else if (defined r_elements.#j) & (i elementof v relativeto r_elements.#j)
					r_addresses.#j =: (i scaleof v) * r_scaleelement + $
				else
					err "variable term used where not expected."
				end if
			end repeat
		end repeat
		emit size: 0 scaleof v
	end macro

	macro relocatable name*,length*,offset*
		local lengthcount,ofs,el

		repeat 1,c:r_count
			r_count = c + 1
			lengthcount = 0
			element el:c
			r_elements.#c := el
			name := el
			ofs := offset
			irpv address,r_addresses.#c
				repeat 1 scaleof address
					dw address - %% * r_scaleelement - ofs
				end repeat

				lengthcount = lengthcount + 1 scaleof address
			end irpv
		end repeat

		length := lengthcount
	end macro

	macro smcable name*,address*
		local el

		repeat 1,c:s_count
			s_count = c + 1
			element el:c
			s_elements.#c := el
			name := el
			address := s_addresses.#c
		end repeat
	end macro

	purge ?
end macro


; ###############################################################################################
; test
; tests: multiple relocatables, one relative to the other, a relocatable smcable
;
; org origin
;
;	jp exit
;	ld hl,place + $5555
;	ld (variable + 5),hl
;	ld a,len
;	ld b,vlen
;	ld (place_addr),hl
;	ld hl,(variable + 5)
;
;exit:
;	ret
;
;relocatable variable,vlen,0
;relocatable origin,len,origin
;smcable place,place_addr

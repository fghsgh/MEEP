macro format?.ti? clause&
	local all, checkloc, checksum, cplx, data, exec, flag, sign, head, name, nameloc, process, prot, temp, type, ext, var, pagebase, area, curpage, pages, numpages, appsize
	macro process: setting
		match first rest, setting
			process first
			process rest
		else match =ARCHIVED?, setting
			flag = flag or 1 shl 7
		else match =EXECUTABLE?, setting
			define exec
		else match =PROTECTED?, setting
			type = 6
			define prot
		else match =REAL?, setting
			type = 0
			ext = '8xn'
		else match =LIST?, setting
			if defined cplx
				type = 13
			else
				type = 2
			end if
			ext = '8xl'
		else match =MATRIX?, setting
			type = 2
			ext = '8xm'
		else match =EQUATION?, setting
			type = 3
			ext = '8xy'
		else match =STRING?, setting
			type = 4
			ext = '8xs'
		else match =PROGRAM?, setting
			if defined prot
				type = 6
			else
				type = 5
			end if
			ext = '8xp'
		else match =PICTURE?, setting
			type = 7
			ext = '8xi'
		else match =GDB?, setting
			type = 1
			ext = '8xd'
		else match =COMPLEX?, setting
			type = 12
			define cplx
			ext = '8xc'
		else match =APPVAR?, setting
			type = 21
			ext = '8xv'
		else match =GROUP?, setting
			type = 23
			ext = '8xg'
		else match =SIGNED?, setting
			define sign
		else match =APP?, setting
			type = 20
			ext = '8xk'
		else match =APPLICATION?, setting
			type = 20
			ext = '8xk'
		else if setting eqtype 'name'
			name := setting
		else if setting eqtype 0
			type = setting
			ext = '8x'
		end if
	end macro
	type = 6
	ext = '8xp'
	flag = 0
	process clause
	format binary as ext
	assert ~$% & 'Unexpected data before format directive'
	if ~definite name
		name := 'A'
	end if
	if type <> 20
		dq '**TI83F*'
		db 26, 10, 0
		rb 42
		dw sizeof all
		label all: checkloc - $%
		dw sizeof head, sizeof data
		label head: data - $
		db type
		dq name
		db 0, flag
		dw sizeof data
		label data: checkloc - $%
		dw sizeof var
		label var: checkloc - $%
		if defined exec
			dw $6DBB
			org $9D95
		else
			org 0
		end if
		postpone
			label checkloc at $%
		end postpone
		postpone ?
			assert checkloc = $% & 'Unexpected postpone before format directive'
			checksum = 0
			repeat sizeof all
				load temp: byte from: all + %-1
				checksum = (checksum + temp) and $FFFF
			end repeat
			dw checksum
		end postpone
	else
		curpage = 0
		pageof? equ 1 metadataof
		offsetof? equ 0 scaleof
		macro @z80.word size*, value*
			emit size: offsetof? value
		end macro
		macro page
				db $$+$4000-$ dup 0
			end virtual
			local pagebase, area
			curpage = curpage + 1
			element pagebase: curpage
			virtual at pagebase + $4000
			area::
				pages equ area
		end macro
		element pagebase: curpage
		virtual at pagebase + $4000
		area::
			pages equ area
			assert lengthof name <= 8
			db $80,$0F
			dd (appsize - 6) bswap 4
			db $80,$12,1,4
			db $80,$21,1
			db $80,$31,1
			;db $80,$40 or lengthof name,name
			db $80,$48,name,8 - lengthof name dup ' '
			db $80,$81,numpages
			db $80,$90
			db $03,$26,$09,$04,$04,$6F,$1B,$80
			db $02,$0D,$40
			db $A1,$6B,$99,$F6,$59,$BC,$67
			db $F5,$85,$9C,$09,$6C,$0F,$B4,$03,$9B,$C9
			db $03,$32,$2C,$E0,$03,$20,$E3,$2C,$F4,$2D
			db $73,$B4,$27,$C4,$A0,$72,$54,$B9,$EA,$7C
			db $3B,$AA,$16,$F6,$77,$83,$7A,$EE,$1A,$D4
			db $42,$4C,$6B,$8B,$13,$1F,$BB,$93,$8B,$FC
			db $19,$1C,$3C,$EC,$4D,$E5,$75
			db $80,$7F,0,0,0,0
			dw 0,0,0,0,0,0,0,0

		postpone
				appsize := curpage shl 14 + $ - $$
			end virtual
			numpages := curpage + 1
		end postpone
		postpone ?
			local md5, A, B, C, D, block, blocksize, padding, hash
			iterate <name*,   rotate*,              function*, permutation*>, \
			             F, $16110C07, d =xor c =and b =xor d,         1*i+0, \
			             G, $140E0905, c =xor b =and d =xor c,         5*i+1, \
			             H, $17100B04,        d =xor c =xor b,         3*i+5, \
			             I, $150F0A06,    =not d =or b =xor c,         7*i+0
				calminstruction calminstruction?.round#name? K*&
					local a, b, c, d, g, i, k, l, r, t
					arrange a, =a
					arrange b, =b
					arrange c, =c
					arrange d, =d
					compute i, 0
				loop:
					arrange k, K
					match k =, K, K
					compute g, ((permutation) and 15) shl 5
					compute l, rotate shr ((i and 3) shl 3) and 31
					compute r, 32 - l
					arrange t, =compute =t, (function + a + k + =chunk =shr g) =and $FFFFFFFF
					assemble t
					arrange t, =compute a, (b + =t =shl l =or =t =shr r) =and $FFFFFFFF
					assemble t
					arrange t, a
					arrange a, d
					arrange d, c
					arrange c, b
					arrange b, t
					compute i, i + 1
					jyes loop
				end calminstruction
			end iterate
			calminstruction md5 chunk*
				local a, b, c, d, t
				compute a, A
				compute b, B
				compute c, C
				compute d, D
				compute chunk, chunk
				roundF $D76AA478, $E8C7B756, $242070DB, $C1BDCEEE, \
				       $F57C0FAF, $4787C62A, $A8304613, $FD469501, \
				       $698098D8, $8B44F7AF, $FFFF5BB1, $895CD7BE, \
				       $6B901122, $FD987193, $A679438E, $49B40821
				roundG $F61E2562, $C040B340, $265E5A51, $E9B6C7AA, \
				       $D62F105D, $02441453, $D8A1E681, $E7D3FBC8, \
				       $21E1CDE6, $C33707D6, $F4D50D87, $455A14ED, \
				       $A9E3E905, $FCEFA3F8, $676F02D9, $8D2A4C8A
				roundH $FFFA3942, $8771F681, $6D9D6122, $FDE5380C, \
				       $A4BEEA44, $4BDECFA9, $F6BB4B60, $BEBFBC70, \
				       $289B7EC6, $EAA127FA, $D4EF3085, $04881D05, \
				       $D9D4D039, $E6DB99E5, $1FA27CF8, $C4AC5665
				roundI $F4292244, $432AFF97, $AB9423A7, $FC93A039, \
				       $655B59C3, $8F0CCC92, $FFEFF47D, $85845DD1, \
				       $6FA87E4F, $FE2CE6E0, $A3014314, $4E0811A1, \
				       $F7537E82, $BD3AF235, $2AD7D2BB, $EB86D391
				compute A, (A + a) and $FFFFFFFF
				compute B, (B + b) and $FFFFFFFF
				compute C, (C + c) and $FFFFFFFF
				compute D, (D + d) and $FFFFFFFF
			end calminstruction
			iterate name, F, G, H, I
				purge calminstruction?.round#name?
			end iterate

			local jacobi, powmod, p, q, f, lp, lq, r, s, sig, sigbase, sigsize
			calminstruction (return) jacobi n*, k*
				local t, r, temp
				compute k, k
				compute t, 1
				jump enter
			loop:
				compute r, bsf n
				compute temp, n shr r
				compute n, k
				compute k, temp
				compute t, t xor (101000b shr (n and 7) and r and 1) xor (n and k and 3 + 1) shr 2
			enter:
				compute n, n mod k
				check n
				jyes loop
				check k = 1
				jyes done
				compute t, 0
			done:
				publish return, t
			end calminstruction
			calminstruction (return) powmod base*, exponent*, modulus*
				local result
				compute base, base
				compute exponent, exponent
				compute modulus, modulus
				compute result, 1
			loop:
				check exponent and 1
				jno skip
				compute result, (result * base) mod modulus
			skip:
				compute base, (base * base) mod modulus
				compute exponent, exponent shr 1
				check exponent
				jyes loop
				publish return, result
			end calminstruction

			local hexdigits, hexsize, intelhex
			hexdigits := +'0123456789ABCDEF'
			calminstruction calminstruction?.nibble2hex? nibble*
				local line
				arrange line, =compute =digit, '0123456789ABCDEF' =shr ((nibble =and $F) =shl 3) =and $FF
				assemble line
				arrange line, =arrange =line, =line, =digit
				assemble line
			end calminstruction
			calminstruction calminstruction?.byte2hex? byte*
				local line
				arrange line, =nibble2hex byte =shr 4
				assemble line
				arrange line, =nibble2hex byte
				assemble line
				match =check, byte
				jyes nocheck
				arrange line, =compute =check, =check - byte
				assemble line
			nocheck:
			end calminstruction
			calminstruction intelhex length: 0, address: 0, kind: 2, chunk: ''
				local check, line, digit, byte
				compute length, length
				compute address, address
				compute kind, kind
				compute check, 0
				arrange line, =db ':'
				byte2hex length
				byte2hex address shr 8
				byte2hex address
				byte2hex kind
				jump enter
			loop:
				byte2hex chunk
				compute chunk, chunk shr 8
				compute length, length - 1
			enter:
				check length
				jyes loop
				byte2hex check
				check kind = 1
				jyes nonewline
				arrange line, line, 13, 10
			nonewline:
				assemble line
			end calminstruction
			iterate name, nibble2hex, byte2hex
				purge calminstruction?.name?
			end iterate

			A = $01234567 bswap 4
			B = $89ABCDEF bswap 4
			C = $FEDCBA98 bswap 4
			D = $76543210 bswap 4
			blocksize = 64
			padding = 0
			irpv page, pages
				virtual page
					pagebase = $$
					pagesize = $ - $$
					if % <> %%
						repeat pagesize / blocksize, index: 0
							load block: blocksize from page: pagebase + index shl 6
							md5 block
						end repeat
					else
						repeat (pagesize + 1 + 8 + blocksize - 1) shr 6, index: 0
							if (index + 1) shl 6 > pagesize
								if index shl 6 <= pagesize
									blocksize = pagesize and (blocksize - 1)
									padding = $80 shl (blocksize shl 3)
								else
									blocksize = 0
									padding = 0
								end if
								if blocksize <= 56
									padding = padding or appsize shl (512 - 64 + 3)
								end if
							end if
							load block: blocksize from page: pagebase + index shl 6
							md5 block or padding
						end repeat
						hash = 1 or A shl 8 or B shl 40 or C shl 72 or D shl 104

						p = $1CC2C1433A79A5D734F9F5F1FF1BC43F3F87D378142693CE26FEC1B5E9542E5B
						q = $4B697D56EA14013042B11939BBAA1ED3BAB09496DBF208785739B07947B70F797
						lp jacobi hash, p
						lq jacobi hash, q
						f = lp xor 1 or lq shl 1
						hash = hash shl (lp xor lq)
						if ~lq
							hash = $878E894D2CBA39ED8191EFB30A0DF25B4DC3E5E585A80D8AEDBCD73B74167CEA5F19DAFE59BA36FFB70A33DD94571147D8A34F15A361AC5E17E49722DA3124AD - hash
						end if
						r powmod hash, $730B050CE9E6975CD3E7D7C7FC6F10FCFE1F4DE0509A4F389BFB06D7A550B97, p
						s powmod hash, $12DA5F55BA85004C10AC464E6EEA87B4EEAC2525B6FC821E15CE6C1E51EDC3DE6, q
						sig = ((r - s) * $F2BF5471698CD3847DFE4004F7511C9D9CD8BE32C2FA0AE949BDD3DAF9682A3) mod p
						if sig < 0
							sig = sig + p
						end if
						sig = sig * q + s
						siglen := (bsr sig + 8) shr 3
						sigbase db 2, $2D, siglen
						emit siglen: sig
						if f
							db 1
						end if
						db f, sigbase + 96 - $ dup -1
					end if
				end virtual
			end irpv

			db '**TIFL**', 1, 1, 1, $88, $01, $01, $19, $97, 8,name,8 - lengthof name dup ' ', 23 dup 0, $73, $24, 24 dup 0
			; lengthof name, name
			hexsize rd 1
			blocksize = 32
			irpv page, pages
				virtual page
					pagebase = $$
					pagesize = $ - $$
				end virtual
				intelhex 2, , 2, (% - 1) bswap 2
				repeat (pagesize + blocksize - 1) shr 5, index: 0
					if (index + 1) shl 5 > pagesize
						blocksize = pagesize and (blocksize - 1)
					end if
					load block: blocksize from page: pagebase + index shl 5
					intelhex blocksize, offsetof? pagebase + index shl 5, 0, block
				end repeat
			end irpv
			intelhex , , 1
			store $ - hexsize - sizeof hexsize at hexsize
		end postpone
	end if
end macro

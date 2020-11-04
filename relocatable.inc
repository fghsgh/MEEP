macro ?!
	local relocs,addresses,count,lastcount
	count = 0
	define relocs
	define addresses

	macro @z80.word size*, value*
		local elcount
		elcount = 0
		repeat lastcount,i:0
			repeat elementsof value
				if % elementof value eq relocs.#i
					elcount = elcount + 1
					addresses.#i =: $
				end if
			end repeat
		end repeat
		if elementsof value <> elcount
			err "non-constant assignment of word"
		else
			emit size: 0 scaleof value
		end if
	end macro

	macro relocatable el*,len*,org*
		local addr,totallen
		element el
		repeat 1,c:count
			relocs.#c := el
			irpv addr,addresses.#c
				totallen = totallen + 1
				dw addr - org
			end irpv
		end repeat
		count = count + 1
		len := totallen
	end macro

	postpone
		lastcount := count
	end postpone

	purge ?
end macro


GLOBAL throw_opcode_exception

section .text

	throw_opcode_exception:
		;ud2
		rsm
		
		ret

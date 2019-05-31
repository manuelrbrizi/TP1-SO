GLOBAL get_key

section .text

	get_key:
		
		;xor eax, eax

		in al, 0x60
		
		;and RAX,0xFF

	ret
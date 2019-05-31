GLOBAL clock
	section .text


	clock:
		cli
		mov al,0x8B
		out 70h,al

		in al,71h

		or al,0x04
		out 71h,al

		mov rax, rdi
		out 70h, al

		mov rax,0

		in al,71h
		sti
		
	ret

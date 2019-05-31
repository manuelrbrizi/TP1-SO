GLOBAL init_process_stack

extern printEntry

section .text
	init_process_stack:

		mov rax,rsp ;guardo el rsp del proceso

		mov rsp,rdi ;updateo el rsp con el puntero al stack virgen que cree en el scheduler

		;iret hook
		;push qword rsi		;pusheo EntryPoint
		;push qword 0x0008	;push cs
		;push qword 0x0202	;pusheo rflags
	

		;mov rsi,rsp
		;sub rsi,24
		;push qword rsi	;pusheo RSP
		;push qword 0x0000	;push ss
		;push qword 0x0000 	;push base

		push qword 0x0000	;Pusheo Base
		push qword 0x0000	;Pusheo Stack Segment

		mov rdi,rsp
		add rdi,8
		push rdi			;Pusheo dir de Base

		push qword 0x0202	;Pusheo RFlags
		push qword 0x0008	;Pusheo CodeSegment
		push qword rsi		;Pusheo EntryPoint


		push qword 0x0000
		push qword 0x0001
		push qword 0x0002
		push qword 0x0003
		push qword 0x0004
		push qword 0x0005
		push qword 0x0006
		push qword 0x0007
		push qword 0x0008
		push qword 0x0009
		push qword 0x000A
		push qword 0x000B
		push qword 0x000C
		push qword 0x000D
		push qword 0x000E


		mov rdx,rsp


		mov rsp,rax

		mov rax,rdx
	
		ret
;Source: No encuentro la pagina, es una modificacion de uno de internet

GLOBAL beep
GLOBAL stopsound



section .text


beep:	
	MOV CX,600H
	CMP CX, 014H
	JB done
	IN AL, 061H
	OR AL, 003H
	DEC AX
	OUT 061H, AL
	MOV DX, 00012H	
	MOV AX, 034DCH	
	DIV CX
	MOV DX, AX
	MOV AL, 0B6H
	PUSHF
	CLI	
	OUT 043H, AL
	MOV AL, DL
	OUT 042H, AL
	MOV AL, DH
	OUT 042H, AL
	POPF
	IN AL, 061H
	OR AL, 003H
	OUT 061H, AL

done:

RET

stopsound:
	IN AL, 061H	
	AND AL, 0FCH
	OUT 061H, AL
RET



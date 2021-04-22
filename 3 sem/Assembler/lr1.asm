.model small
.stack 100h
.data
	a db 10
	b db 2
	c db 7
	d db 2

.code
start:
	MOV AX, @data
	MOV DS, AX

	MOV AL, a
	MUL c

	MOV BX, AX

	MOV AL, b
	MUL d

	ADD AX, BX
	MOV DX, AX

	MOV AL, a
	MUL d

	MOV BX, AX

	MOV AL, c
	MUL b

	ADD AX, BX

	CMP AX, DX
	JZ frstcond

	MOV AL, c
	MOV AH, a
	CMP AL, AH
	JC scndcond

	XOR AX, AX
	XOR DX, DX
	MOV AX, word ptr a
	MOV DX, word ptr b
	AND DX, word ptr c
	MOV BX, DX
	SUB AX, BX
	JMP finish

	frstcond:
		MUL AX
		JMP finish

	scndcond:
		XOR AX, AX
		MOV AL, c
		AND AL, d
		JMP finish;just like last 'break' in switch-case

	finish:

	MOV AH, 4Ch
	INT 21h
end start
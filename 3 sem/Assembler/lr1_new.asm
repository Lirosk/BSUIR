.8086
.model small
.stack 100h
.data
a dw ?
b dw ?
c dw ?
d dw ?
.code

AXpowerCX PROC; AX = AX to power CX
	CMP CX, word ptr 1
	JZ AXpowerCX_no_need

	PUSH BX CX DX

	MOV BX, AX
	DEC CX

	AXpowerCX_cycle:
		MUL BX
		LOOP AXpowerCX_cycle

	POP DX CX BX

	AXpowerCX_no_need:

	RET
AXpowerCX ENDP

start:
	MOV AX, @data
	MOV DS, AX

	MOV CX, 4
	LEA BX, a

	input_cycle:
		;<read>
		MOV [BX], AX
		ADD BX, word ptr 2
		LOOP input_cycle

	MOV AX, a
	MOV CX, c
	CALL AXpowerCX

	MOV BX, b
	OR BX, d

	CMP AX, BX
	JZ fst_case

	MOV AX, a
	AND AX, b

	MOV BX, a
	ADD BX, c

	CMP AX, BX
	MOV AX, a
	JZ scnd_case

	thrd_case:
		ADD AX, b
		ADD AX, c
		ADD AX, d

		JMP end_prog

	fst_case:
		MOV AX, a
		AND AX, b
		ADD AX, c
		ADD AX, d

		JMP end_prog

	scnd_case:
		OR AX, b
		OR AX, c
		OR AX, d

		JMP end_prog

	end_prog:

	;<print>

	MOV AH, 4Ch
	INT 21h

end start
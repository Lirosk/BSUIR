.8086
.model small
.stack 100h
.data

a dw ?
b dw ?
c dw ?
d dw ?

BadInputMessage db 10, "Bad input", 10 ,"$"

.code

AXoutput PROC
	PUSH AX BX CX DX

	MOV BX, 10
	XOR CX, CX
	XOR DX, DX

	cycleAXoutput:
		DIV BX

		ADD DX, 48
		PUSH DX
		INC CX

		XOR DX, DX

		CMP AX, word ptr 0
		JNZ cycleAXoutput

	outputAXoutput:
		POP DX

		MOV AH, 2h
		INT 21h

		LOOP outputAXoutput

	POP DX CX BX AX

	RET
AXoutput ENDP

backspace PROC
	PUSH AX DX

	MOV DL, 08h
	MOV AH, 02h
	INT 21h

	POP DX AX

	RET
backspace ENDP

read PROC
	PUSH BX CX DX

	XOR AX, AX
	XOR BX, BX
	XOR CX, CX
	XOR DX, DX

	read_cycle:
		MOV AH, 01h; read symbol
		INT 21h

		CMP AL, 0Dh; if Enter pressed
		JZ read_Enter

		CMP AL, 0Ah; if Enter pressed
		JZ read_Enter

		CMP AL, 08h; if Back pressed
		JZ read_Back

		CMP AL, 1Bh; if Esc pressed
		JZ read_Esc

		CMP AL, 48; if AL < '0'
		JC read_BadInput

		CMP AL, 58; if AL > '9'
		JNC read_BadInput

		read_digit:
			CMP CX, 0
			JNZ read_digit_aftercond

			CMP AL, 30h
			JNZ read_digit_aftercond

			CALL backspace

			read_digit_aftercond:

			INC CX
			SUB AL, 30h
			XOR AH, AH
			PUSH AX

			MOV AX, BX
			MOV BX, 10

			MUL BX
			POP BX
			ADD AX, BX

			MOV BX, AX

			JMP read_cycle_next

		read_Enter:
			JMP read_end

		read_Back:
			CMP CX, 0
			JZ read_cycle_next

			MOV AX, BX
			PUSH BX
			MOV BX, 10
			XOR DX, DX
			DIV BX
			POP BX
			MOV BX, AX

			DEC CX

			JMP read_cycle_next

		read_Esc:
			XOR BX, BX

			CALL backspace

			CMP CX, 0
			JZ read_cycle_next

			read_Esc_loop:
				CALL backspace

				LOOP read_Esc_loop

			JMP read_cycle_next

		read_BadInput:
			LEA DX, BadInputMessage
			MOV AH, 09h
			INT 21h

			MOV AL, 1

			MOV AH, 4Ch
			INT 21h

		read_cycle_next:
		MOV AX, 5000
		CMP AX, BX
		JC read_BadInput

		JMP read_cycle

	read_end:

	CMP BX, 0
	JZ read_BadInput

	MOV AX, BX

	POP DX CX BX

	RET
read ENDP

nl PROC
	PUSH AX DX

	MOV DX, 10
	MOV AH, 2h
	INT 21h

	POP DX AX

	RET
nl ENDP

readABCD PROC
	PUSH AX BX CX

	MOV CX, 4
	LEA BX, a

	read_vars_loop:
		CALL read

		MOV [BX], AX
		ADD BX, 2

		LOOP read_vars_loop

	POP CX BX AX

	RET
readABCD ENDP

start:
	MOV AX, @data
	MOV DS, AX

	CALL readABCD

	;AX = a|c
	MOV AX, a
	OR AX, c

	;BX = b ^ d
	MOV BX, b
	XOR BX, d

	CMP AX, BX
	JZ fst_cond

	;AX = a + b
	MOV AX, a
	ADD AX, b

	;BX = c ^ d
	MOV BX, c
	XOR BX, d

	CMP AX, BX
	MOV AX, a
	JZ scnd_cond

	thrd_cond:
		MOV BX, b
		ADD BX, c
		XOR AX, BX
		OR AX, d

		JMP end_cond_op

	fst_cond:
		MOV AX, a
		XOR AX, b
		XOR AX, c
		ADD AX, d

		JMP end_cond_op

	scnd_cond:
		AND AX, d
		MOV BX, b
		MOV BX, c
		OR AX, BX

		JMP end_cond_op

	end_cond_op:

	CALL AXoutput
	CALL nl

	MOV AH, 4Ch
	INT 21h
end start
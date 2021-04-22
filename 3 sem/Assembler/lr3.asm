.8086
.model small
.stack 100h
.data

a dw ?
b dw ?
c dw ?
d dw ?

BadInputMessage db 10, "Bad input", 10 ,"$"
ZeroDivisionMessage db "Zero division", 10, "$"

.code

AXSoutput PROC
	PUSH AX BX CX DX

	TEST AX, 1000000000000000b
	JNS AXoutput_afternegtest
		NEG AX
		PUSH AX
		MOV DL, "-"
		MOV AH, 02h
		INT 21h
		POP AX

	AXoutput_afternegtest:

	MOV BX, 10
	XOR CX, CX

	cycleAXoutput:
		XOR DX, DX
		DIV BX

		ADD DX, 48
		PUSH DX
		INC CX

		XOR DX, DX

		CMP AX, word ptr 0
		JNZ cycleAXoutput

	outputAXoutput:
		POP DX

		MOV AH, 02h
		INT 21h

		LOOP outputAXoutput

	POP DX CX BX AX

	RET
AXSoutput ENDP

backspace PROC
	PUSH AX DX

	MOV DL, 08h
	MOV AH, 02h
	INT 21h

	POP DX AX

	RET
backspace ENDP

read PROC
	PUSH BX CX DX DI

	XOR AX, AX
	XOR BX, BX
	XOR CX, CX
	XOR DX, DX
	XOR DI, DI

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

		CMP AL, "-"
		JZ read_minus

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

		read_minus:
			CMP DI, 1
			JZ read_BadInput

			MOV DI, 1
			JMP read_cycle_next

		read_Enter:
			JMP read_end

		read_Back:
			CMP CX, 0
			JNZ read_Back_afterminuscheck

			CMP DI, 1
			JNZ read_Back_afterminuscheck

			XOR DI, DI

			read_Back_afterminuscheck:

			CMP CX, 0
			JZ read_cycle_next

			MOV AX, BX
			;PUSH BX
			MOV BX, 10
			XOR DX, DX
			DIV BX
			;POP BX
			MOV BX, AX

			;CALL backspace

			DEC CX

			JMP read_cycle_next

		read_Esc:
			XOR BX, BX

			ADD CX, DI

			CALL backspace

			CMP CX, 0
			JZ read_cycle_next

			read_Esc_loop:
				CALL backspace

				LOOP read_Esc_loop

			XOR DI, DI

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

	CMP CX, 0
	JZ read_BadInput

	MOV AX, BX

	CMP DI, 1
	JNZ read_endafterend
		NEG AX

	read_endafterend:

	POP DI DX CX BX

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

ZeroDivision PROC
	LEA DX, ZeroDivisionMessage
	MOV AH, 09h
	INT 21h

	MOV AL, 2
	MOV AH, 4Ch
	INT 21h

	RET
ZeroDivision ENDP

remainder PROC; AX %= BX
	CMP BX, 0
	JNZ remainder_bxnotzero
		CALL ZeroDivision

	remainder_bxnotzero:

	PUSH BX DX DI
	
	XOR DI, DI

	TEST AX, 1000000000000000b
	JNS remainder_axpos
		NEG AX
		XOR DI, 1

	remainder_axpos:

	TEST BX, 1000000000000000b
	JNS remainder_bxpos
		NEG BX
		XOR DI, 1

	remainder_bxpos:

	CWD
	IDIV BX 
	MOV AX, DX

	CMP DI, 1
	JNZ remainder_done
		NEG AX

	remainder_done:

	POP DI DX BX

	RET 
remainder ENDP

start:
	MOV AX, @data
	MOV DS, AX

	CALL readABCD

	; AX = a + b
	MOV AX, a
	ADD AX, b

	; BX = d - c
	MOV BX, d
	SUB BX, c

	CMP AX, BX
	JZ fst_cond

	; AX = a % b
	MOV AX, a
	MOV BX, b
	CALL remainder

	; BX = c + d
	MOV BX, c
	ADD BX, d
	
	CMP AX, BX
	JZ scnd_cond

	thrd_cond:
		MOV AX, a
		ADD AX, d
		SUB AX, b
		SUB AX, c

		JMP afterconds

	fst_cond:
		MOV AX, a
		IMUL b

		MOV BX, AX

		CMP d, 0
		JNZ fst_dnotzero
			CALL ZeroDivision

		fst_dnotzero:

		MOV AX, c
		CWD
		IDIV d
		MOV AX, DX

		ADD AX, BX

		JMP afterconds

	scnd_cond:
		MOV AX, c
		MOV BX, d
		CALL remainder
		MOV BX, AX

		CMP BX, 0
		JNZ scnd_againnotzero
			CALL ZeroDivision

		scnd_againnotzero:

		MOV AX, a
		ADD AX, b
		CWD
		IDIV BX
		MOV AX, DX

		JMP afterconds

	afterconds:

	CALL AXSoutput
	CALL nl

	MOV AL, 0
	MOV AH, 4Ch
	INT 21h
end start
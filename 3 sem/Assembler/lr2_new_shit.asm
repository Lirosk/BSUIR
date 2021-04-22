.8086
.model small
.stack 100h
.data 
BadInputMessage db 10, "Bad input", 10, "$"

m db 10, "Bad input", 10, "$"

a dw ?
b dw ?
c dw ?
d dw ?

InputString db "$$$$$"
numcheck db 35h, 30h, 30h, 30h, "$"

.code

re PROC; s become "$$$$$$"
	PUSH BX CX

	LEA BX, InputString
	MOV CX, 5
	recycle:
		MOV [BX], byte ptr "$"
		INC BX
		LOOP recycle

	POP CX BX

	RET
re ENDP

input PROC
	PUSH AX BX CX

	LEA BX, InputString 
	XOR CX, CX

	input_cycle:
		MOV AH, 1h
		INT 21h

		CMP AL, 0Ah; 0Dh; if Enter
		JZ input_end; input_EnterPressed

		CMP AL, 1Bh; if Esc
		JZ input_EscPressed

		CMP AL, 08h; if Back
		JZ input_BackPressed

		CMP AL, 48; if (AL < '0')
		JC input_BadInput

		CMP AL, 58; if (AL > '9')
		JC input_digit

		JMP input_BadInput

		input_EscPressed:
			CALL re

			MOV DL, 8h
			MOV AH, 2h
			INT 21h

			PUSH CX

			CMP CX, 0
			JZ input_next

			input_EscPressed_cycle:
				MOV BL, 8h
				MOV AH, 2h
				INT 21h
				LOOP input_EscPressed_cycle			

			POP CX

			JMP input_next

		input_BackPressed:
			CMP CX, 0
			JZ input_cycle

			MOV DL, 8h
			MOV AH, 2h
			INT 21h

			JMP input_next

		input_digit:
			CMP CX, 4
			JZ input_BadInput

			MOV [BX], AL
			INC CX
			INC BX

			JMP input_next

		input_next:

		CALL checkstr
		CMP AX, 0
		JZ input_BadInput

		JMP input_cycle

		input_BadInput:
			LEA DX, m; BadInputMessage
			CALL print

			MOV AH, 4Ch
			INT 21h

	input_end:

	POP CX BX AX

	RET
input ENDP

print PROC; print DX
	PUSH AX DX

	print_cycle:
		MOV AH, 2h
		INT 21h

		INC DX

		CMP DL, "$"
		JZ print_end

		JMP print_cycle

	print_end:

	POP DX AX

	RET
print ENDP

strToAX PROC; num from s to AX
	PUSH BX CX DX DI

	XOR AX, AX
	XOR BX, BX
	XOR DX, DX

	MOV DI, 10	
	LEA BX, InputString; CS:s

	strToAXcycle:
		MOV CX, [BX]

		MOV CH, "$"
		CMP CH, CL
		JZ exit

		SUB CL, 48

		MUL word ptr DI
		XOR DX, DX
		XOR CH, CH
		ADD AX, CX

		INC BX
		JMP strToAXcycle

	exit:

	POP DI DX CX BX

	RET
strToAX ENDP

checkstr PROC; AX = 0 if num in s > num in numcheck
	PUSH BX CX DX DI

	LEA BX, InputString
	ADD BX, 4
	MOV [BX], byte ptr "$"
	LEA BX, InputString

	XOR CX, CX

	strlencycle:
		MOV AX, [BX]

		MOV AH, "$"
		CMP AH, AL
		JZ afterlen

		INC BX
		INC CX

		JMP strlencycle

	afterlen:

	LEA BX, InputString
	LEA DI, numcheck

	CMP CX, 0
	MOV AX, 1
	JZ endcheck

	CMP CX, 4
	MOV AX, 1
	JNZ endcheck

	checkingdigits:
		MOV AX, [DI]
		MOV DX, AX
		MOV AX, [BX]

		INC DI
		INC BX

		CMP DL, AL

		MOV AX, 1

		JC invalidinputprepare
		JNZ endcheck

		LOOP checkingdigits

	JMP endcheck

	invalidinputprepare:
		XOR AX, AX

	endcheck:

	POP DI DX CX BX

	RET
checkstr ENDP

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

enterAX PROC
	CALL input
	CALL strToAX

	RET
enterAX ENDP

start:
	;entering vars
	MOV CX, 4
	LEA BX, a
	ent_vars:
		CALL enterAX
		MOV [BX], AX
		ADD BX, 2
		LOOP ent_vars

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

	MOV AH, 4Ch
	INT 21h

end start
.8086
.model small
.stack 100h
.data
	e db "Enter 1st num:", 13, 10, "$"
	i db 13, "Invalid num", 13 , 10, "$"
	s db "$$$$$$", "$"
	r db "No division by zero!!!", 10, "$"
	numcheck db 54, 53, 53, 51, 53; "6", "5", "5", "3", "5"
.code

cls PROC; clear the console
	PUSH AX

	MOV AX, 3h; clear the console
	INT 10h

	POP AX

	RET
cls ENDP

print PROC; print DX
	PUSH AX

	MOV AH, 9h; DX output
	INT 21h

	POP AX

	RET
print ENDP

strToAX PROC; num from s to AX
	PUSH BX CX DX DI

	XOR AX, AX
	XOR BX, BX
	XOR DX, DX

	MOV DI, 10	
	LEA BX, s; CS:s

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

input PROC; s is a number
	PUSH AX CX DX DI

	XOR AX, AX

	CALL re
	CALL cls
	LEA DX, e
	CALL print

	LEA DI, s; CS:s; MOV DX, offset CS:s

	MOV CX, 0
	cycle:

		MOV AH, 01h; read symbol
		INT 21h

		CMP AL, 0Dh; if Enter
		JZ EnterPressed

		CMP AL, 1Bh; if Esc
		JZ EscPressed

		CMP AL, 08h; if Back
		JZ BackPressed

		CMP AL, 48
		JC next

		CMP AL, 58;
		JC digit

		JMP next

		EnterPressed:
			JMP done

		EscPressed:
			CALL re

			LEA DI, s; CS:s
			MOV CX, 0

			JMP next

		BackPressed:
			CMP CX, 0
			JZ next

			DEC CX
			DEC DI
			MOV [DI], byte ptr "$"
			JMP next

		digit:			

			CMP CX, 5
			JZ next

			MOV [DI], AL
			INC DI
			INC CX

			PUSH AX
			CALL checkstr
			CMP AX, 0
			
			POP AX
			JZ BackPressed

			JMP next

		next:		

		CALL cls
		LEA DX, e
		CALL print
		LEA DX, s
		CALL print

		JMP cycle

	done:

	POP DI DX CX AX

	RET
input ENDP

re PROC; s become "$$$$$$"
	PUSH BX CX

	LEA BX, s
	MOV CX, 5
	recycle:
		MOV [BX], byte ptr "$"
		INC BX
		LOOP recycle

	POP CX BX

	RET
re ENDP

checkstr PROC; AX = 0 if num in s > 65535
	PUSH BX CX DX DI

	LEA BX, s
	ADD BX, 5
	MOV [BX], byte ptr "$"
	LEA BX, s

	XOR CX, CX

	strlencycle:
		MOV AX, [BX]

		MOV AH, "$"
		CMP AH, AL
		JZ afterlen

		XOR AH, AH
		CMP AH, AL
		JZ afterlen

		INC BX
		INC CX

		JMP strlencycle

	afterlen:

	LEA BX, s
	LEA DI, numcheck

	MOV AX, 1

	CMP CX, 0
	JZ endcheck

	CMP CX, 5
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

enterAX PROC
	CALL input
	CALL strToAX

	RET
enterAX ENDP

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

nl PROC
	PUSH AX DX

	MOV DX, 10
	MOV AH, 2h
	INT 21h

	POP DX AX

	RET
nl ENDP

start:
	MOV AX, @data
	MOV DS, AX

	CALL EnterAX; 1st num

	PUSH AX; 1st num to stack

	LEA BX, e
	ADD BX, 6
	MOV [BX], byte ptr "2"
	INC BX
	MOV [BX], byte ptr "n"
	INC BX
	MOV [BX], byte ptr "d"

	CALL EnterAX; 2nd num

	CMP AX, 0
	JZ zeroAX
	JMP pass_zeroAX

	zeroAX:
		LEA DX, r
		CALL print

		MOV AH, 4Ch
		INT 21h

	pass_zeroAX:

	MOV BX, AX
	POP AX; 1st num from stack

	CALL cls
	CALL AXoutput

	XOR DX, DX
	DIV BX	

	MOV DX, "/"
	PUSH AX
	MOV AH, 2h
	INT 21h
	
	MOV AX, BX
	CALL AXoutput

	MOV DX, "="
	MOV AH, 2h
	INT 21h
	POP AX

	CALL AXoutput

	CALL nl

	MOV AH, 4Ch; exit
	INT 21h
end start
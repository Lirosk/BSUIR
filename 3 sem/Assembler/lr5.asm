locals @@

.model small
.stack 100h

.data

n db ?
A db 10 dup (10 dup (?));1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0

min db 1
max db 10

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


read PROC; input to AX
	PUSH BX CX DX

	XOR AX, AX
	XOR BX, BX
	XOR CX, CX
	XOR DX, DX

	read_cycle:
		MOV AH, 08h
		INT 21h

		CMP AL, 0Dh; if Enter pressed
		JZ read_cycle_Enter

		CMP AL, 0Ah; if Enter pressed
		JZ read_cycle_Enter

		CMP AL, " "; yep
		JZ read_cycle_Enter

		CMP AL, 08h; if Back pressed
		JZ read_cycle_Back

		CMP AL, 1Bh; if Esc pressed
		JZ read_cycle_Esc

		CMP AL, 48; if AL < '0'
		JC read_cycle_BadInput

		CMP AL, 58; if AL > '9'
		JNC read_cycle_BadInput

		read_cycle_digit:
			SUB AL, 30h
			PUSH AX

			MOV AX, BX
			MOV BX, 10
			MUL BX

			POP BX
			MOV BH, 0
			ADD AX, BX

			MOV BX, AX
			INC CX

			JMP read_cycle_next

		read_cycle_BadInput:
			;LEA DX, BadInputMessage
			;MOV AH, 09h
			;INT 21h

			MOV AX, 4C01h
			INT 21h

			JMP read_cycle_next

		read_cycle_Esc:
			MOV BX, 0
			MOV CX, 0

			JMP read_cycle_next

		read_cycle_Back:
			MOV AX, BX
			MOV BX, 10
			MOV DX, 0

			DIV BX

			MOV BX, AX
			DEC CX

			JMP read_cycle_next

		read_cycle_Enter:
			JMP read_aftercycle

		read_cycle_next:

		MOV AX, word ptr max

		CMP AX, BX
		JC read_cycle_BadInput

		JMP read_cycle

	read_aftercycle:

	CMP BX, word ptr min
	JZ read_cycle_BadInput

	MOV AX, BX

	read_end:

	POP DX CX BX

	RET
read ENDP


readArr proc
	PUSH AX BX CX DI SI

	MOV CH, 0
	MOV CL, n; step
	MOV AX, CX
	MUL AX
	MOV SI, AX; n^2 - amount of elements

	MOV BX, 0; i
	@@for_i:

		MOV DI, 0; j
		@@for_j:
			CALL read; input to AX
			MOV A[BX][DI], AL

			INC DI
			CMP DI, CX
		JNZ @@for_j

		ADD BX, CX; CX - step
		CMP BX, SI; SI - amount of  elements
	JNZ @@for_i

	POP SI DI CX BX AX

	RET
readArr endp


writeArr proc
	PUSH AX BX CX DX DI SI

	MOV CH, 0
	MOV CL, n; CX - step

	MOV AX, CX
	MUL AX
	MOV SI, AX; SI = n^2 - amount of elements

	MOV BX, 0; i
	@@for_i:

		MOV DI, 0; j
		@@for_j:
			MOV AH, 0
			MOV AL, A[BX][DI]
			CALL AXoutput

			INC DI
			CMP DI, CX
			JZ @@aftercond
				MOV DX, " "; space
				MOV AH, 02h
				INT 21h
			@@aftercond:
			
			CMP DI, CX
		JNZ @@for_j

		MOV DX, 0Ah; new line
		MOV AH, 02h
		INT 21h

		ADD BX, CX; CX - step
		CMP BX, SI; SI - amount of  elements
	JNZ @@for_i

	POP SI DI DX CX BX AX

	RET
writeArr endp

findDist proc
	PUSH AX BX CX DX SI DI

	MOV CH, 0
	MOV CL, n; step
	MOV AX, CX
	MUL AX
	MOV DX, AX; n^2 - amount of elements
	
	MOV SI, 0; k
	@@for_k:

		MOV BX, 0; i
		@@for_i:

			PUSH DX
			MOV DI, 0; j
			@@for_j:
				;if dist[i][k] + dist[k][j] < dist[i][j]

				MOV DL, A[BX][SI]; DL = dist[i][k]

				PUSH DX

				MOV AX, SI; AX = k
				MUL CX; AX = k*n

				POP DX

				PUSH BX
				MOV BX, AX; BX = k*n

				ADD DL, A[BX][DI]; DX = dist[i][k] + dist[k][j]

				POP BX; BX = i

				CMP DL, A[BX][DI]
				JNC @@aftercond
                	;dist[i][j] = dist[i][k] + dist[k][j]
                	MOV A[BX][DI], DL

                @@aftercond:
	            INC DI
				CMP DI, CX
			JC @@for_j

			POP DX
			ADD BX, CX; CX - step
			CMP BX, DX; SI - amount of  elements
		JC @@for_i

		INC SI
		CMP SI, CX
	JC @@for_k
	
	POP DI SI DX CX BX AX

	RET
findDist endp

main:
	MOV AX, @data
	MOV DS, AX

	;CALL read; read n
	MOV n, AL

	MOV max, 100
	MOV min, 0
	;CALL readArr

	CALL findDist
	CALL writeArr

	MOV AX, 4C00h
	INT 21h
end main
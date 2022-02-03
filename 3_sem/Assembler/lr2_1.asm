.8086
.model small
.stack 100h
.data 
n dw 65535
.code

log10 PROC; CX = log10(AX)
	PUSH DX
	PUSH BX
	PUSH AX

	XOR CX, CX
	CMP AX, 0
	JZ done

	MOV BX, 10

	cycle1:

		XOR DX, DX
		DIV BX
		
		INC CX

		CMP AX, 10
		JC done
		JZ done

		JMP cycle1

	done:

	POP AX
	POP BX
	POP DX

	RET
log10 ENDP

tenToPowerCX PROC; AX = 1eCX //(10^CX)
	MOV AX, 1

	PUSH BX
	PUSH CX
	PUSH DX

	MOV BX, 10
	XOR DX, DX

	cycle2:
		MUL BX
		LOOP cycle2

	POP DX
	POP CX
	POP BX

	RET
tenToPowerCX ENDP

AXoutput PROC
	PUSH DX
	PUSH BX
	PUSH AX

	CALL log10
	CALL tenToPowerCX
	MOV BX, AX
	POP AX

	INC CX

	cycle:

		XOR DX, DX

		DIV BX

		PUSH DX; remainder to stack
		MOV DX, AX; int part to DX
		ADD DX, 48; make it symbol

		MOV AH, 2h
		INT 21h; DX output

		XOR DX, DX
		MOV AX, BX; devider to AX
		MOV BX, 10
		DIV BX; make devider 10 times less
		MOV BX, AX; devider to BX

		POP AX; num to AX

		LOOP cycle

	POP BX
	POP DX

	RET
AXoutput ENDP

start:
	PUSH @data
	POP DS

	MOV AX, n
	CALL AXoutput

	MOV DX, 10
	MOV AH, 02h
	INT 21h

	MOV AH, 4Ch
	INT 21h
end start
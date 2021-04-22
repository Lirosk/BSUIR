.model small
.stack 100h
.data 

prime db 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53 ,59, 61, 67, 71, 73, 79, 83, 89, 97

;maxlen db 101
len db 0
s db 101 dup ("$")

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

findperprime PROC; AX = per of str
	CMP len, 1
	JNZ findperprime_lennotzero
		MOV AX, 1
		RET

	findperprime_lennotzero:

	PUSH BX CX DX

	MOV AH, 0

	MOV CH, 0
	MOV CL, len
	DEC CL

	LEA BX, s
	MOV DL, [BX]
	INC BL

	; comparison of str[i] ands str[i-1], i belongs to [1, len]
	findperprime_loop:
		CMP DL, [BX]
		JNZ findperprime_perislen

		MOV DL, [BX]
		INC BL
	LOOP findperprime_loop

		MOV AL, 1
		JMP findperprime_end 

	findperprime_perislen:
		MOV AL, len
	
	findperprime_end:

	POP DX CX BX

	RET
findperprime ENDP

findper PROC
	PUSH BX CX DX

	MOV BH, 0
	MOV BL, len

	MOV CX, 0
	findper_loop:
		INC CX

		MOV AH, 0
		MOV AL, len

		MOV DX, 0
		DIV CX

		CMP DX, 0
		JNZ findper_loop_next; if len % CX != 0

		CALL checksubstrings

		CMP AX, 1
		JZ findper_end

		findper_loop_next:

		CMP CX, BX 
	JNZ findper_loop

	findper_end:
	MOV AX, CX

	POP DX CX BX

	RET
findper ENDP

checksubstrings PROC; params - (AX, CX); CX - checked per, AX = len/CX
	PUSH BX CX DI SI

	DEC AX

	MOV BX, CX
	LEA DI, s

	ADD DI, CX

	; checking 1st substring (len = CX) with others (2nd, 3rd, ...)
	checksubstrings_loop:
		MOV CX, BX
		LEA SI, s

		REPZ CMPSB
		JNZ checksubstrings_missionfailed; if substrings not equal

		DEC AX
	JNZ checksubstrings_loop

	MOV AX, 1; return 1 if all substrigns equal (CX = per)
	JMP checksubstrings_end

	checksubstrings_missionfailed:
	MOV AX, 0; if per != CX

	checksubstrings_end:

	POP SI DI CX BX

	RET
checksubstrings ENDP

checklen PROC; AX = 1, if len is prime num, else 0
	PUSH CX BX SI

	MOV AL, len
	MOV CX, 26
	MOV SI, 0

	checklen_loop:
		CMP AL, prime[SI]
		JZ checklen_isprime
		INC SI
	LOOP checklen_loop

		MOV AX, 0
		JMP checklen_end

	checklen_isprime:
		MOV AX, 1

	checklen_end:

	POP SI BX CX

	RET
checklen ENDP

sread proc 
	PUSH AX CX DI SI

	MOV SI, 0

	sread_loop:
		MOV AH, 08h; read symbol without echo
		INT 21h

		CMP AL, 0Ah; if enter
		JZ sread_loop_enter

		CMP AL, 0Dh; if enter
		JZ sread_loop_enter

		CMP AL, 08h; if back
		JZ sread_loop_back

		MOV s[SI], AL
		INC SI

		JMP sread_loop_next

		sread_loop_enter:
			JMP sread_end

		sread_loop_back:
			DEC SI
			MOV s[SI], byte ptr "$"

			JMP sread_loop_next

		sread_loop_next:

		CMP SI, 101
		JZ sread_end

		LOOP sread_loop

	sread_end:

	MOV AX, SI
	MOV len, AL

	POP SI DI CX AX

	RET
sread endp

givemeperPLEASE PROC
	CALL checklen

	CMP AX, 1
	JNZ givemeperPLEASE_lennotprime
		CALL findperprime
		RET

	givemeperPLEASE_lennotprime:
		CALL findper

	RET
givemeperPLEASE ENDP

main:
	MOV AX, @data
	MOV DS, AX
	MOV ES, AX

	;ввод str
	MOV SI, 0
	MOV DI, 0

	CMPSB


	CALL sread
	CALL givemeperPLEASE
	CALL AXoutput

	MOV AH, 02h
	MOV DX, 0Ah
	INT 21h

	MOV AX, 4C00h
	INT 21h
end main
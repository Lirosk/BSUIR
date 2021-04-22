CSEG segment
assume cs:CSEG; es:CSEG, ds:CSEG, ss:CSEG

org 100h

main:
	JMP Init

	handler_09h proc
		PUSH ax cx dx es

		MOV dx, " ";0Ah

		STI
		
		MOV cx, 32
		MOV bx, 1Eh

		l:
			MOV es:[bx], 3061h
			INC bx
		LOOP l 

		CLI

		POP es dx cx ax

		PUSHF
		CALL dword ptr cs:[old_09h]

		IRET

		key db 13
		old_09h dd ?

		db 26; length of sequence
		alphabet db 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38, 50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44
				;   a,  b,  c,  d,  e,  f,  g,  h,  i,  j,  k,  l,  m,  n,  o,  p,  q,  r,  s,  t,  u,  v,  w,  x,  y,  z 
		
		db 10; length of sequence
		nums db 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
			;   1, 2, 3, 4, 5, 6, 7, 8, 9,  10
		
		db 10; length of sequence
		numpad db 82, 79, 80, 81, 75, 76, 77, 71, 72, 73
				; 0,  1,  2,  3,  4,  5,  6,  7,  8,  9

		; returns encrypted al, if al is in scope
		; input: ah = scan code, al - ascii code, bx = offset of sequence
		; output: ah = encrypted scan code, al - encrypted ascii code
		do_caesar_in_scope proc
			MOV ah, 0

			CMP key, 0
			JNZ not_zero
				RET

			not_zero:

			PUSH cx si

			MOV si, 0
			MOV cl, [bx - 1]; now cx - len of seq
			MOV ch, 0

			check_loop:
				CMP al, bx[si] 
				JZ found

				INC si
			LOOP check_loop

			JMP exit

			found:
			MOV cl, key

			encrypt:
				CMP byte ptr si, [bx - 1]; si == length?
				JNZ after_boundary_check
					MOV si, 0

				after_boundary_check:

				INC si

			LOOP encrypt

			MOV al, bx[si]
			MOV ah, 1

			exit:

			POP si cx

			RET
		do_caesar_in_scope endp

		encrypt_ascii proc
			

			RET
		encrypt_ascii endp

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
	handler_09h endp

	Init:
	MOV ax, 3509h
	INT 21h

	MOV word ptr old_09h,bx
	MOV word ptr old_09h+2,es

	MOV ax, 2509h
	MOV dx, offset handler_09h
	INT 21h

	MOV dx,offset Init
	INT 27h
CSEG ends
end main
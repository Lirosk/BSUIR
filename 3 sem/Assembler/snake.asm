stack1 segment stack
	dw 100h dup(?)
	peak label word
stack1 ends

data segment public
	dir db 0; snake movement direction
	len dw 1; snake length
	maxlen = 78*23

	time dw 0
	speed db 2

	;scan codes
	left db 75
    right db 77
    up db 72
    down db 80

    ;ascii code
    escape db 27

    fruitshave dw 0
    
    SnakeHead = 2; ☻
    SnakeBody = "o";7; •
    FruitsMax = 2
    FruitSymbol = 3; ♥
    SnakeColor = 15; white
    FruitColor = 10
    BoardColor = 4
    FieldColor = 0; black
    FieldSymbol = 219

    snake dw maxlen dup (?); array of snake segment coordinates, 78*23 - size of field => 78*23 - max len of snake

    ScoreMessage db "Your score: $"
data ends

screen segment at 0B800h; display segment in text mode
    symbol db ?
    color db ?
screen ends


code segment
assume cs:code, ds:data, es:screen, ss:stack1
locals @@



main:
	MOV ax, seg data
	MOV ds, ax
	MOV ax, seg stack1
	MOV ss, ax
	MOV ax, seg screen
	MOV es, ax 
	LEA sp, peak




	MOV ax, 3; set the 3rd video mode
	INT 10h

	CALL HideCursor
	;CALL cls
	CALL DrawField	
	CALL DrawBoard
	CALL PrintFruit





	@@calculating:
	CALL GetRandomXY
	CMP color[si], FieldColor
	JNZ @@calculating

	MOV symbol[si], SnakeHead
	MOV color[si], SnakeColor
	MOV snake[0], si; snake[0] - coords of snake head

    @@start:
	MOV ah, 08h; waiting for tapping
	INT 21h

	CMP al, escape
	JNZ @@no_escape
		JMP @@end_of_game

	@@no_escape:

	CMP al, up
	JZ @@run_snake

	CMP al, down
	JZ @@run_snake

	CMP al, right
	JZ @@run_snake

	CMP al, left
	JZ @@run_snake

	JMP @@start

	@@run_snake:
	MOV dir, al

	@@snake_movement:
	MOV di, snake[0]; di = snake head coords
	MOV al, dir

	@@check_left:
	CMP al, left
	JNE @@check_right
		SUB di, 2

	@@check_right:
	CMP al, right
	JNE @@check_up
		ADD di, 2

	@@check_up:
	CMP al, up
	JNE @@check_down
		SUB di, 160

	@@check_down:
	CMP al, down
	JNE @@check_snake_movement
		ADD di, 160

	@@check_snake_movement:
	CALL CheckSnakeMovement

	CALL PrintFruit





	@@check_input:
	MOV ah, 01h; if some key pushed
	INT 16h

	JZ @@process

	MOV ah, 00h; what key is pushed
	INT 16h

	CMP al, escape
	JZ @@end_of_game

	MOV al, dir

	CMP al, left
	JZ @@check_left_dir

	CMP al, right
	JZ @@check_right_dir

	CMP al, up
	JZ @@check_up_dir

	CMP al, down
	JZ @@check_down_dir

	JMP @@process





	@@check_left_dir:
		CMP ah, right
		JZ @@process
		JMP @@dir_selected

	@@check_right_dir:
		CMP ah, left
		JZ @@process
		JMP @@dir_selected

	@@check_up_dir:
		CMP ah, down
		JZ @@process
		JMP @@dir_selected

	@@check_down_dir:
		CMP ah, up
		JZ @@process
		JMP @@dir_selected

	@@dir_selected:

	MOV dir, ah





	@@process:
	MOV ah, 00h
	INT 1Ah

	@@delay:
	CMP dx, time
	JC @@check_input

	MOV cl, speed
	XOR ch, ch

	ADD dx, cx
	MOV time, dx

	JMP @@snake_movement

	@@end_of_game:

	CALL PrintScoreAndExit

	MOV ax, 4C00h
	INT 21h




	;for this snake
	PrintScore proc
		PUSH AX BX CX DX si		

		MOV ax, len
		DEC ax

		MOV BX, 10
		XOR CX, CX
		XOR DX, DX

		@@cycleAXoutput:
			DIV BX

			ADD DX, 48
			PUSH DX
			INC CX

			XOR DX, DX

			CMP AX, word ptr 0
			JNZ @@cycleAXoutput

		MOV si, 3840
		@@outputAXoutput:
			POP DX

			MOV symbol[si], dl

			@@no_equals:

			INC si
			INC si

			LOOP @@outputAXoutput

		POP si DX CX BX AX

		RET
	PrintScore endp





	PrintScoreAndExit proc
		MOV cx, 10
		MOV dx, 0
		MOV ah, 86h
		INT 15h

		CALL cls

		LEA dx, ScoreMessage
		MOV ah, 09h
		INT 21h

		MOV ax, len
		DEC ax

		CALL AXoutput

		MOV dl, 0Ah
		MOV ah, 02h
		INT 21h

		MOV dl, 0Dh
		INT 21h

		MOV ax, 4C00H
		INT 21h

		RET
	PrintScoreAndExit endp





	; input: di - adress of snake head next pos
	CheckSnakeMovement proc
		PUSH ax bx di si

		CMP color[di], FruitColor
		JE @@ok

		CMP color[di], FieldColor
		JE @@ok
			CALL SnakeBlinking
			CALL PrintScoreAndExit

		@@ok:

		XOR bx, bx
		;bl = 1 — fruit has been eaten

		CMP color[di], FruitColor
		JNZ @@after_fruits
			INC len
			MOV bl, 1
			CMP len, maxlen
			JNZ @@no_endgame
				CALL PrintScoreAndExit
				
			@@no_endgame:

			CALL PrintScore

		@@after_fruits:

		CMP len, 1
		JZ @@len_is_1

		@@len_is_not_1:
			CMP bl, 0
			JNZ @@eated

			@@not_eated:      
				MOV cx, len
				DEC cx                                     

				MOV si, len
				DEC si
				ADD si, si               

				PUSH di

				;hide the tail
				MOV di, snake[si]
				MOV symbol[di], FieldSymbol
				MOV color[di], FieldColor  

				POP di
                    
				;move array elements to the right by 1 (except the tail)
				@@ln:                                                          
					MOV ax, snake[si-2]
 					MOV snake[si],ax                                 
					DEC si
					DEC si
				LOOP @@ln
                    
				MOV si, snake[0]
				MOV symbol[si], SnakeBody
				MOV color[di], SnakeColor

				JMP @@new_head

			@@eated:
				DEC fruitshave 

				MOV cx, len
				DEC cx                  

				MOV si, len
				DEC si
				ADD si, si
                    
                ;move array elements to the right by 1
				@@l: 
					MOV ax, snake[si-2]
					MOV snake[si], ax
					DEC si
					DEC si
				LOOP @@l

				MOV si, snake[0]
				MOV symbol[si], SnakeBody
				MOV color[di], SnakeColor

				JMP @@new_head

		@@len_is_1:; len cannot be equal to 1 if snake ate
			;hide the tail
			MOV si, snake[0]
			MOV symbol[si], FieldSymbol
			MOV color[si], FieldColor 

		@@new_head:
		MOV snake[0], di

		MOV symbol[di], SnakeHead
		MOV color[di], SnakeColor

		POP si di bx ax

		RET
	CheckSnakeMovement endp



	SnakeBlinking proc
		PUSH ax bx cx di si 

		MOV bx, 5
		MOV di, snake[0]

		@@l11:			
			MOV color[di], FieldColor

			MOV cx, 10
			MOV dx, 0
			MOV ah, 86h
			INT 15h

			MOV color[di], SnakeColor

			MOV cx, 10
			MOV dx, 0
			MOV ah, 86h
			INT 15h

			DEC bx
		JNZ @@l11

		POP si di cx bx ax

		RET
	SnakeBlinking endp



	DrawField proc
		PUSH cx si

		MOV cx, 80*25
		MOV si, 0

		@@l:
			MOV symbol[si], FieldSymbol
			MOV color[si], FieldColor
			ADD si,2
        LOOP @@l

        POP si cx

		RET
	DrawField endp



	; returns random (depending on time) si - field cell number, ([x][y] = [si])
	GetRandomXY proc
		PUSH ax dx

		@@calculating_y:
		MOV ah, 2ch; random by time
		INT 21h

		XOR ah, ah
		MOV al, dl

		CMP al, 50
		JL @@ok_down
			SUB al, 50

		@@ok_down:

		;make it even
		SHR ax, 1
		SHL ax, 1

		CMP al, 0
		JNZ @@ok_up
			INC al
			INC al

		@@ok_up:

		MOV dl, 80
		MUL dl

		MOV si, ax


		@@calculating_x:
		MOV ah, 2ch; random by time
		INT 21h

		XOR ah, ah
		MOV al, dl

		CMP al, 80
		JL @@ok_right
			SUB al, 20

		@@ok_right:

		CMP al, 0
		JNZ @@ok_left
			INC al

		@@ok_left:

		ADD al, al
		XOR ah, ah
		ADD si, ax

		POP dx ax

		RET
	GetRandomXY endp



	PrintFruit proc
		PUSH ax dx si

		MOV si, fruitshave
		CMP si, fruitsmax
		JZ @@to_ret

		@@calculating:

		CALL GetRandomXY

		CMP color[si], FieldColor
		JNZ @@calculating

		MOV symbol[si], FruitSymbol
		MOV color[si], FruitColor
		INC fruitshave

		MOV si, fruitshave
		CMP si, fruitsmax
		JNZ @@calculating

		@@to_ret:

		POP si dx ax		

		RET
	PrintFruit endp



	; clear the console
	cls PROC
		PUSH ax

		MOV ax, 3h; clear the console
		INT 10h

		POP ax

		RET
	cls ENDP


	HideCursor proc
		PUSH ax cx

		MOV ah, 01h
		MOV cx, 2607h 
		INT 10h

		POP cx ax

		RET
	HideCursor endp



	ShowCursor proc
		PUSH ax cx

		MOV ah, 01h
		MOV cx, 0607h
		INT 10h

		POP cx ax

		RET
	ShowCursor endp



	DrawBoard proc; compiled
		PUSH cx si

		MOV cx, 80*25  
        MOV si, 0

        @@cycle2:; upper line
            CMP si,160; yes
            JGE @@p1_1 ; (>=)
                MOV symbol[si], 219        
                MOV color[si], BoardColor

            @@p1_1:; bottom line                   

            CMP si, 3840 ; 2*80*25=4000 (line: 80 * 2, 4000-160 = 3840)

            JNGE @@p1_2 ;(<)
                MOV symbol[si], 219 
                MOV color[si], BoardColor

            @@p1_2:
            ADD si,2
        loop @@cycle2

        MOV cx,23
        MOV si,160; left line

        @@cycle3:
            MOV symbol[si], 219 
            MOV color[si], BoardColor    
            ADD si,160; next line
        loop @@cycle3
        
        MOV cx,23
        MOV si,318; right line

        @@cycle4:
            MOV symbol[si], 219 
            MOV color[si], BoardColor       
            ADD si,160; next line
        loop @@cycle4

        POP si cx

        RET
	DrawBoard endp



	;from lr2...
	AXoutput PROC
		PUSH AX BX CX DX

		MOV BX, 10
		XOR CX, CX
		XOR DX, DX

		@@cycleAXoutput:
			DIV BX

			ADD DX, 48
			PUSH DX
			INC CX

			XOR DX, DX

			CMP AX, word ptr 0
			JNZ @@cycleAXoutput

		@@outputAXoutput:
			POP DX

			MOV AH, 2h
			INT 21h

			LOOP @@outputAXoutput

		POP DX CX BX AX

		RET
	AXoutput ENDP

code ends
end main
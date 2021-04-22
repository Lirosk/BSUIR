stack1 segment STACK

    dw 1024 dup(?)
    ;peak label word 

stack1 ends

data segment PUBLIC

    txtMenu db "Use arrows for movement", 0Dh, 0Ah
           db "Press ESC to exit", 0Dh, 0Ah, 0Dh, 0Ah         

           db "--------------------------------", 0Dh, 0Ah            
           db "1 - Low speed", 0Dh, 0Ah
           db "2 - Average speed", 0Dh, 0Ah
           db "3 - High speed", 0Dh, 0Ah
           db "4 - Increase fruit limit by 1", 0Dh, 0Ah
           db "5 - Increase fruit limit by 5", 0Dh, 0Ah
           db "6 - Set fruit limit to 2", 0Dh, 0Ah
           db "--------------------------------", 0Dh, 0Ah, 0Dh, 0Ah

           db "Press smth ... $"      

    txtGameResult db 0Dh, 0Ah, " GAME OVER", 0Dh, 0Ah, " Points: $"

    snakeLength dw 1  
    expectation dw 0 
    direction db 0

    left_Key db 75
    right_Key db 77
    up_Key db 72
    down_Key db 80
    esc_Key db 27

    speed db 4
    fruitsOnField dw 0 
    random1 dw 0 
    random2 dw 0
    fruitLimit dw 2

    c_BoardColor equ 11
    c_FieldColor equ 14
    c_SnakeColor equ 15
    c_FruitColor equ 10 
    c_ASCIIField equ 176 
    c_ASCIISnake equ 219
    c_FieldSize equ 1794 ; размер массива, 1794 = (80-2)*(25-2)

    field_snake dw c_FieldSize dup(0)    
data ends

screen segment AT 0B800h 
    scr db ?
    atribute db ?
screen ends
















code segment
    assume cs:code,ds:data,es:screen,ss:stack1

    start:
        mov ax,seg data
        mov ds,ax
        mov ax,seg screen
        mov es,ax
        mov ax,stack1
        mov ss,ax
        ;mov sp,offset peak   

        mov ah,0 
        mov al,3 
        int 10h         

        mov ah, 1
        mov ch, 2bh ;убрать миг. курсор
        mov cl, 0bh
        int 10h      

        mov dx,offset txtMenu
        mov ah,9h ;вывод менюшки
        int 21h 

        call p_DrawingMenu

        mov ah, 00h ; ждем-с нажатия любой клавиши
        int 16h  

        call p_DrawingFieldAndBoard ; рисуем околицу  

        mov scr[2000],219d 
        mov atribute[2000],c_SnakeColor     

        call p_FruitPrint        



















        l_GameStart:

            mov ah,08h 
            int 21h 
            
            cmp al,esc_Key                

            je l_ToEndOfProgram
                jmp l_NoEnd

            l_ToEndOfProgram:
              jmp endOfProgram

            l_NoEnd:            

            cmp al,left_Key 
              je l_StartSnake

            cmp al,right_Key   
              je l_StartSnake

            cmp al,up_Key 
              je l_StartSnake

            cmp al,down_Key  
              je l_StartSnake          

            jmp l_GameStart                           

        l_StartSnake:               

            mov direction,al             

            mov field_snake[0],2000d ;голова всегда в 0                            

        l_SnakeMovement: ; метка для перехода, когда змейка уже на движе
            
            mov di,field_snake[0]                                      
            mov al,direction 

            cmp al,left_Key
            jne l_ArrowsCmp1          
                sub di,2 ; 

          l_ArrowsCmp1:            

            cmp al,right_Key
            jne l_ArrowsCmp2
                add di,2

          l_ArrowsCmp2:
        
            cmp al,up_Key
            jne l_ArrowsCmp3
                sub di,160 ; отнимаем 160 дабы на строку выше 

          l_ArrowsCmp3:
            
            cmp al,down_Key
            jne l_ArrowsCmp4
                add di,160 ; прибавляем для попущения на ряд

          l_ArrowsCmp4:                
            push di ax cx                         
              call p_CheckEveryStep ;тут проверочка: скушали или врезались      
              call p_FruitPrint ;коли нужно, рисует фрукты        
            pop cx ax di                              























        l_CheckKey:

            mov ah,01h 
            int 16h

            jz l_NoKeySelected

            mov ah,00h
            int 16h
            cmp al,esc_Key
              je endOfProgram                    

            cmp al,31h
              je l_Key1       

            cmp al,32h
              je l_Key2     

            cmp al,33h
              je l_Key3                    

            cmp al,34h ;коли 4 - увел кол-во фруктов на 1
              je l_IncreaseLimitBy1        

            cmp al,35h ;коли 5 - на 5
              je l_IncreaseLimitBy5  

            cmp al,36h ;коли 6 - сброс до 2
              je l_ResetLimitTo2                      

            mov direction,ah 

            jmp l_NoKeySelected                          

            l_Key1:
                mov speed,4
                jmp l_NoKeySelected

            l_Key2:
                mov speed,2 
                jmp l_NoKeySelected

            l_Key3:
                mov speed,1
                jmp l_NoKeySelected                                      

            l_IncreaseLimitBy1:
                add fruitLimit,1
                jmp l_NoKeySelected

            l_IncreaseLimitBy5:
                add fruitLimit,5
                jmp l_NoKeySelected

            l_ResetLimitTo2:
                mov fruitLimit,2
                jmp l_NoKeySelected            
            

















        l_NoKeySelected:        

        mov ah,00h
        int 1ah

        cmp dx,expectation
          jb l_CheckKey ; (<) CF = 1
        xor cx,cx
        mov cl,speed
        add dx,cx
        mov expectation,dx

        jmp l_SnakeMovement

        endOfProgram: 
            mov ax,4c00h
            int 21h















































    p_DrawingFieldAndBoard proc
        mov cx,80*25
        mov si,0

        cycle1: ;сначала всеь экран в зел, потом границы
            mov scr[si],c_ASCIIField
            mov atribute[si],c_FieldColor
            add si,2
        loop cycle1              

        mov si,0

        cycle2:; верхняя горизонталь
            cmp si,160
            jge l_p1_1 ; (>=)
                mov scr[si],219d         
                mov atribute[si], c_BoardColor

            l_p1_1: ;нижняя горизонталь                    

            cmp si,3840 ; 2*80*25=4000 (-строка текста 80 * 2, 4000-160 = 3840)

            jnge l_p1_2 ;(<)
                mov scr[si],219d  
                mov atribute[si],c_BoardColor

            l_p1_2:
            add si,2
        loop cycle2

        mov cx,23 ; (((левая вертикаль)))
        mov si,160

        cycle3:
            mov scr[si],219d 
            mov atribute[si],c_BoardColor    
            add si,160 ; +ряд
        loop cycle3
        
        mov cx,23 ; (((правая вертикаль))) 

        mov si,318 ; ласт во второй строке

        cycle4:
            mov scr[si],219d ; 
            mov atribute[si],c_BoardColor       
            add si,160 ; +ряд
        loop cycle4

        ret 
    p_DrawingFieldAndBoard endp

    p_DrawingMenu proc

        mov cx,80*13 ;13 строк для раскраски
        mov si,0*160 ;пачнем с 0 строки

        coloring_Cycle:            
            cmp si,0*160
              je color1
            cmp si,1*160
              je color2
            cmp si,3*160
              je color3            
            cmp si,6*160
              je color4
            cmp si,8*160
              je color3       
            cmp si,12*160
              je color5 

          jmp l_endColoring       

            color1:
                mov al,14d 
                jmp l_endColoring 
            color2:
                mov al,12d 
                jmp l_endColoring
            color3:
                mov al,15d 
                jmp l_endColoring            
            color4:
                mov al,4d
                jmp l_endColoring
            color5:
                mov al,9d
                jmp l_endColoring           

          l_endColoring:   
              mov atribute[si],al     
              add si,2
        loop coloring_Cycle

        ret
    p_DrawingMenu endp

    p_CheckEveryStep proc        

        cmp atribute[di],c_BoardColor ; в di голова змеечки

        jne noBoardChash ; если не в стену
          jmp gameOver ; ну а если привет стена

        noBoardChash:
          cmp atribute[di],c_SnakeColor 

        jne noSelfEating ; если не едим самого себя
          jmp gameOver

        gameOver:  
            mov dx,offset txtGameResult
            mov ah,9h 
            int 21h 

            xor ax,ax
            mov ax,snakeLength
            push ax 

            call p_PrintPoints
            
            mov ah, 00h
            int 16h    
            jmp endOfProgram

        noSelfEating:        

        xor bx,bx   
        mov bl,0 ; bl-флаг, bl = 0 - фрукт не съеден, bl = 1 - съеден
      
        cmp atribute[di],c_FruitColor

        jne noFruit ;коли это не фрукт           
            add snakeLength,1
            mov bl,1     

        noFruit:





            cmp snakeLength,1

            jle ifLength1 ; <= 1
                jmp ifLengthNot1

            ifLength1: 
                jmp ifLength1JMP

                ifLengthNot1:      
                cmp bl,0

                jne eatenFruit                     
                    xor cx,cx                
                    mov cx,snakeLength
                    sub cx,1                                      

                    mov si,snakeLength
                    add si,snakeLength
                    sub si,4                

                    push di
                      xor di,di
                      mov di,field_snake[si+2]
                      mov scr[di],c_ASCIIField
                      mov atribute[di],c_FieldColor                             
                    pop di
                    
                    cycle5:                                                          
                        xor ax,ax
                        mov ax,field_snake[si]
                        mov field_snake[si+2],ax                                 
                        sub si,2
                    loop cycle5
                    
                    jmp l_lb1

                eatenFruit:

                cmp bl,1

                jne l_lb1 
                    
                    sub fruitsOnField,1 

                    xor cx,cx
                    mov cx,snakeLength
                    sub cx,1                   

                    mov si,snakeLength
                    add si,snakeLength
                    sub si,4 
                    
                    cycle6: 
                        xor ax,ax
                        mov ax,field_snake[si] ; предпоследний элемент
                        mov field_snake[si+2],ax ; последний элемент принимает значение предыдущего
                        sub si,2
                    loop cycle6

                    jmp l_lb1

            ifLength1JMP:            
              cmp snakeLength,1

            jne l_lb1 
        
                push di 
                  mov di,field_snake[0] 
                  mov scr[di],c_ASCIIField 
                  mov atribute[di],c_FieldColor
                pop di

                mov field_snake[0],di

                jmp l_lb2               

            l_lb1:            
                mov field_snake[0],di

            l_lb2:            

            mov scr[di],c_ASCIISnake
            mov atribute[di],c_SnakeColor
        ret
    p_CheckEveryStep endp  

    p_FruitPrint proc
        mov si,fruitLimit
        cmp fruitsOnField,si
          jge l_dontPrint

        l_start:
            mov ah,2ch 
            int 21h 

            xor ax,ax
            mov al,dl      

            cmp dl,80
            jle l_lb3 ; (<=)                
                sub al,20

            l_lb3:
              mov random1,ax 
              add ax,random1
              mov random1,ax
              mov ah,2ch 

              int 21h
              xor ax,ax
              mov al,dl              

              cmp dl,50

            jle l_lb4 ; (<=)            
                sub al,50

            l_lb4:
              mov random2,ax 
              mov ax,random1
              mov bx,random2
              mul bx
              mov si,ax
            
            cmp atribute[si],c_FieldColor
              jne l_start ; чтобы кинуло фруктик именно на травку, а не на бортик            

            mov scr[si],219d
            mov atribute[si],c_FruitColor            
            add fruitsOnField,1

        l_dontPrint:
      
        ret
    p_FruitPrint endp

    p_PrintPoints PROC
        ARG number:BYTE = SIZE

        push bp 
          mov bp,sp

          xor ax,ax 
          xor cx,cx

          mov cl,10 ; для дес чисел
          mov di,0 ; 
          mov al,number

          l_lb5:
            div cl
            xor dh,dh
            mov dl,ah
            add dl,30h ; для ascii чисел
            push dx 
              inc di 
              xor ah,ah
              cmp al,0
          jne l_lb5

          mov cx,di

          cycle7:
              pop dx 
              mov ah,2
              int 21h
          loop cycle7      
        pop bp

        ret SIZE
    p_PrintPoints ENDP

code ends

end start
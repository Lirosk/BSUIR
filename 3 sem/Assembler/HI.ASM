.8086
.model small
.stack 100h
.data

s db "hello"

.code
main:
	MOV AX, @data
	MOV DS, AX
	MOV ES, AX

	LEA DI, s; 'h'
	ADD DI, 2; 'l'

	LEA SI, s; 'h'
	ADD SI, 3; 'l'

	CMPSB
	;ZF = 1
	;CF = 0

	MOV AX, 4C00h
	INT 21h

end main
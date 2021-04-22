.model small
.stack 100h

.data

  buffer db 01111111b

.code

main:
  MOV ax, @data
  MOV ds, ax

  TEST buffer, 10000000b

  MOV AX, 4C00h
  INT 21h
end main
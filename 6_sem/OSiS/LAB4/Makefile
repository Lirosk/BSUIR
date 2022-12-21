CC=gcc
CFLAGS=-I.
DEPS = morse.h
OBJ = main.o morse.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

morse: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test:
	./morse input.txt > output.txt
	diff correct.txt output.txt
CC=gcc
CLAGS=-g -I.
DEPS=hack_assem.h

%.o %.c $(DEPS)
	$(CC) -c -o $@ $< $(CLAGS)

assembler: hack_assem.o hack_func.o
	$(CC) -o assembler hack_assem.o hack_func.o

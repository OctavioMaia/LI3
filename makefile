CC = gcc
FILES = main.c source/clientes.c source/produtos.c source/queries.c source/AVL.c
OUT_EXE = gerevendas
CFLAGS=-Wall -pedantic -o2 -ansi

build: $(FILES)
	$(CC) $(CFLAGS) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core

rebuild:
	clean build

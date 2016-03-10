CC = gcc
FILES = main.c source/AVL.c source/clientes.c source/produtos.c source/vendas.c source/faturacao.c source/queries.c
OUT_EXE = gerevendas
CFLAGS=-Wall -pedantic -o2 -ansi

build: $(FILES)
	$(CC) $(CFLAGS) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core

rebuild:
	clean build

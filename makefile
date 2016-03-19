CC = gcc
CFLAGS=-Wall -pedantic -o2 -ansi
FILES = main.o avl.o clientes.o produtos.o vendas.o faturacao.o vendasfilial.o queries.o
OUT_EXE = gerevendas

clear:
	clear

clean: 
	rm -f *.o
	rm gerevendas

avl.o: source/AVL.c headers/AVL.h
	$(CC) $(CFLAGS) -c source/AVL.c -o avl.o

clientes.o: source/clientes.c headers/clientes.h 
	$(CC) $(CFLAGS) -c source/clientes.c  -o clientes.o

produtos.o: headers/produtos.h source/produtos.c
	$(CC) $(CFLAGS) -c source/produtos.c -o produtos.o

vendas.o: source/vendas.c headers/vendas.h
	$(CC) $(CFLAGS) -c source/vendas.c -o vendas.o

faturacao.o: source/faturacao.c headers/faturacao.h
	$(CC) $(CFLAGS) -c source/faturacao.c -o faturacao.o

vendasfilial.o: source/vendasfilial.c headers/vendasfilial.h
	$(CC) $(CFLAGS) -c source/vendasfilial.c -o vendasfilial.o

queries.o: source/queries.c headers/queries.h
	$(CC) $(CFLAGS) -c source/queries.c -o queries.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

gerevendas: $(FILES)
	$(CC) $(CFLAGS) -o $(OUT_EXE) $(FILES)

exec1:
	clear
	./gerevendas data/Vendas_1M.txt
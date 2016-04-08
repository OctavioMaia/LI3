CC = gcc
CFLAGS=-Wall -pedantic -o2 -ansi
FILES = main.o avl.o clientes.o produtos.o vendas.o faturacao.o filial.o queries.o
OUT_EXE = gerevendas

clean: 
	rm *.o
	if [ -f "gerevendas" ]; then rm gerevendas; fi;	

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

filial.o: source/filial.c headers/filial.h
	$(CC) $(CFLAGS) -c source/filial.c -o filial.o

queries.o: source/queries.c headers/queries.h
	$(CC) $(CFLAGS) -c source/queries.c -o queries.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

gerevendas: $(FILES)
	$(CC) $(CFLAGS) -o $(OUT_EXE) $(FILES)

rebuild: 
	clean
	make gerevendas

exec1:
	clear
	./gerevendas data/Vendas_1M.txt
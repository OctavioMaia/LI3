#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "headers/AVL.h"
#include "headers/produtos.h"
#include "headers/clientes.h"

Produtos readProdutos (FILE *fp) {
	char buf[10], *s;
	Produtos p=NULL;
	/*int validos =0;*/
	while (fgets(buf,10,fp)) {
		s=strtok(buf,"\r\n");
		p=insertProduto(p,s);
		addProdutos(p,1);	/*Incremente o nº de produtos*/
		/*validos++;*/
	}
	/*printf("%d\n",validos);*/
	return p;
}

Clientes readClientes (FILE *fp) {
	char buf[10], *s;
	Clientes c=NULL;
	/*int validos =0;*/
	while (fgets(buf,10,fp)) {
		s=strtok(buf,"\r\n");
		c=insertCliente(c,s);
		addClientes(c,1);	/*Incremente o nº de produtos*/
		/*validos++;*/
	}
	/*printf("%d\n",validos);*/
	return c;
}

/* Main */
int main () {
	/*Contadores de tempo de execucao*/
	clock_t begin, end;
	double time_spent;

	/*Estruturas*/
	Produtos prod;
	Clientes cli;

	/*Abertura dos ficheiros*/
	FILE *fp = fopen("data/Produtos.txt","r");
	FILE *fc = fopen("data/Clientes.txt","r");

	/*Verificação da integridade dos ficheiros*/
	if (!fp || !fc) {
		perror("Erro na abertura dos ficheiros");
		return -1;
	}

	/*Inicializacao do contador*/
	begin = clock(); 

	/*Ler os ficheiros para as estruturas*/
	prod=readProdutos(fp);
	cli=readClientes(fc);

	/*Imprimir informacao dos ficheiros*/
	printf("%d produtos válidos\n",getTotalProdutos(prod));
	printf("%d clientes válidos\n",getTotalClientes(cli));

	/*Finalizacao do contador*/
	end = clock(); 
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	/*Tempo que demorou a guardar tudo*/
	printf("Tudo guardado e validado em %fs!\n",time_spent);

	imprimirLista(getListaClientesLetra(cli,'A'),9,8);
	return 0;
}
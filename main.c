#include <stdio.h>
#include <string.h>
#include <time.h>
#include "headers/AVL.h"
#include "headers/produtos.h"
#include "headers/clientes.h"
#include "headers/vendas.h"

Produtos readProdutos (FILE *fp) {
	char buf[10], *s;
	Produtos p=NULL;
	while (fgets(buf,10,fp)) {
		s=strtok(buf,"\r\n");
		p=insertProduto(p,s);
		addProdutos(p,1);
	}
	return p;
}

Clientes readClientes (FILE *fp) {
	char buf[10], *s;
	Clientes c=NULL;
	while (fgets(buf,10,fp)) {
		s=strtok(buf,"\r\n");
		c=insertCliente(c,s);
		addClientes(c,1);
	}
	return c;
}

int readVendas (FILE *fp, Produtos p, Clientes c, Venda v) {
	int i=0;
	char buf[50], *s;
	Venda venda;
	while (fgets(buf,50,fp)) {
		s=strtok(buf,"\r\n");
		venda=initVenda(s);
		if (validaVenda(venda,p,c)==1) {
			
			i++;
		}
		
	}
	return i;
}

/* Main */
int main () {
	/*Contadores de tempo de execucao*/
	clock_t begin, end;
	double time_spent;

	/*Estruturas*/
	Produtos prod;
	Clientes cli;
	Venda vend=NULL;

	/*Variaveis auxiliares*/
	int totalVendas;

	/*Abertura dos ficheiros*/
	FILE *fp = fopen("data/Produtos.txt","r");
	FILE *fc = fopen("data/Clientes.txt","r");
	FILE *fv = fopen("data/Vendas_1M.txt","r");

	/*Verificação da integridade dos ficheiros*/
	if (!fp || !fc || !fv) {
		perror("Erro na abertura dos ficheiros");
		return -1;
	}

	/*Inicializacao do contador*/
	begin = clock(); 

	/*Ler os ficheiros para as estruturas*/
	prod=readProdutos(fp);
	cli=readClientes(fc);
	totalVendas=readVendas(fv,prod,cli,vend);

	/*Imprimir informacao dos ficheiros*/
	printf("%d produtos válidos\n",getTotalProdutos(prod));
	printf("%d clientes válidos\n",getTotalClientes(cli));
	printf("%d vendas válidas\n",totalVendas);
	/*Finalizacao do contador*/
	end = clock(); 
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	/*Tempo que demorou a guardar tudo*/
	printf("Tudo guardado e validado em %fs!\n",time_spent);

	/*imprimirLista(getListaClientesLetra(cli,'A'),9,8);*/
	return 0;
}
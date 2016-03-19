#include <stdio.h>
#include <string.h>
#include <time.h>
#include "headers/tipos.h"
#include "headers/AVL.h"
#include "headers/produtos.h"
#include "headers/clientes.h"
#include "headers/vendas.h"
#include "headers/faturacao.h"
#include "headers/vendasfilial.h"
#include "headers/queries.h"

Produtos readProdutos (FILE *fp, Faturacao f, VendasFilial vf) {
	char buf[10], *s;
	Produtos p=NULL;
	while (fgets(buf,10,fp)) {
		s=strtok(buf,"\r\n");
		p=insertProduto(p,s);
		f=insertInformacao(f,s);
		vf=insertListaProduto(vf,s);
		addProdutos(p,1);
		addFaturacao(f,1);
		addVendasFilial(vf,1);
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

int readVendas (FILE *fp, Faturacao f, VendasFilial vf, Produtos p, Clientes c) {
	int i=0;
	char buf[50], *s;
	Venda venda;
	while (fgets(buf,50,fp)) {
		s=strtok(buf,"\r\n");
		venda=initVenda(s);
		if (validaVenda(venda,p,c)==1) {
			atualizaFaturacao(f,p,c,venda);
			atualizaHistorico(vf,venda);
			i++;
		}
	}
	return i;
}

/* Main */
int main (int argc, char** argv) {
	/*Contadores de tempo de execucao*/
	clock_t begin, end;
	double time_spent;

	/*Estruturas*/
	Produtos prod;
	Clientes cli;
	Faturacao f;
	VendasFilial vf;

	/*Variaveis auxiliares*/
	int totalVendas;		

	/*Abertura dos ficheiros*/
	FILE *fp = fopen("data/Produtos.txt","r");
	FILE *fc = fopen("data/Clientes.txt","r");
	FILE *fv = fopen(argv[1],"r");

	/*Verificação da integridade dos ficheiros*/
	if (!fp) {
		printf("\t\t\033[31m\033[1mErro ao ler o ficheiro \"data/Produtos.txt\"!\033[0m\n");
		return -1;
	}else if(!fc){
		printf("\t\t\033[31m\033[1mErro ao ler o ficheiro \"data/Clientes.txt\"!\033[0m\n");
		return -1;
	}else if(!fv){
		printf("\t\t\033[31m\033[1mErro ao ler o ficheiro %s!\033[0m\n",argv[1]);
		return -1;
	}else{
		puts("\t\t\033[1mLeitura efetuada com sucesso!\033[0m");
		puts("\t\t\033[1mComeçando leitura dos ficheiros para memória...\033[0m");
	}

	/*Inicializacao do contador*/
	begin = clock(); 

	/*Ler os ficheiros para as estruturas*/
	f=initFaturacao();
	vf=initVendasFilial();
	prod=readProdutos(fp,f,vf);
	cli=readClientes(fc);
	totalVendas=readVendas(fv,f,vf,prod,cli);

	/*Imprimir informacao dos ficheiros*/
	printf("\t\t\t\t\033[1m%d\033[0m produtos válidos\n",getTotalProdutos(prod));
	printf("\t\t\t\t\033[1m%d\033[0m clientes válidos\n",getTotalClientes(cli));
	printf("\t\t\t\t\033[1m%d\033[0m vendas válidas\n",totalVendas);

	/*Finalizacao do contador*/
	end = clock(); 
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	/*Tempo que demorou a guardar tudo*/
	printf("\033[1m\x1b[31mTudo guardado e validado em %fs!\n\n\x1b[0m\033[0m",time_spent);

	imprimirQueries();
	exec(prod,cli,f,vf);
	return 0;
}
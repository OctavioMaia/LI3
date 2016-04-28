#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/tipos.h"
#include "headers/AVL.h"
#include "headers/produtos.h"
#include "headers/clientes.h"
#include "headers/vendas.h"
#include "headers/faturacao.h"
#include "headers/filial.h"
#include "headers/queries.h"
#include "main.h"

/*
 * readProdutos
 * funcao de leitura do Produtos.txt
 */
Produtos readProdutos (FILE *fp, Faturacao f, Filial vf[]) {
	int i;
	char buf[10], *s;
	Produtos p=NULL;
	while (fgets(buf,10,fp)) {
		s=strtok(buf,"\r\n");
		p=insertProduto(p,s);
		f=insertInformacao(f,s);
		addProdutos(p,1);
		addFaturacao(f,1);
		for(i=0;i<3;i++){
			vf[i]=insertListaProduto(vf[i],s);
			addVendasFilial(vf[i],1);
		}
	}
	return p;
}

/*
 * readClientes
 * funcao de leitura do Clientes.txt
 */
Clientes readClientes (FILE *fp, Historial h[]) {
	int i;
	char buf[10], *s;
	Clientes c=NULL;
	while (fgets(buf,10,fp)) {
		s=strtok(buf,"\r\n");
		c=insertCliente(c,s);
		addClientes(c,1);
		for(i=0;i<3;i++){
			h[i]=insertHistorialCliente(h[i],s); 
			addHistorial(h[i],1);
		}
	}
	return c;
}


/*
 * readVendas
 * funcao de leitura do Vendas.txt
 */
int readVendas (FILE *fp, Faturacao f, Filial vf[], Produtos p, Clientes c,Historial h[]) {
	int i=0;
	char buf[50], *s;
	Venda venda=NULL;
	while (fgets(buf,50,fp)) {
		s=strtok(buf,"\r\n");
		venda=initVenda(s);
		if (validaVenda(venda,p,c)==1) {
			int filial = getFilial(venda);
			atualizaFaturacao(f,p,venda);
			atualizaHistorico(vf[filial-1],venda);
			updateCliente(h[filial-1],vf[filial-1],venda);
			i++;
		}
	}
	return i;
}


/*
 * verificarFicheiros
 * funcao de verificacao dos ficheiros
 * caso um ficheiro nao exista dá erro
 */
int verificaFicheiros(FILE *fp, FILE *fc, FILE *fv){
	/*Verificação da integridade dos ficheiros*/
	if (!fp) {
		printf("\t\t\033[31m\033[1mErro ao ler o ficheiro \"data/Produtos.txt\"!\033[0m\n");
		return -1;
	}else if(!fc){
		printf("\t\t\033[31m\033[1mErro ao ler o ficheiro \"data/Clientes.txt\"!\033[0m\n");
		return -1;
	}else if(!fv){
		printf("\t\t\033[31m\033[1mErro ao ler o ficheiro \"data/Vendas.txt\"!\033[0m\n");
		return -1;
	}else{
		puts("\t\t\033[1mLeitura efetuada com sucesso!\033[0m");
		puts("\t\t\033[1mComeçando leitura dos ficheiros para memória...\033[0m");
	}
	return 1;
}


/*
 * main
 * funcao principal do programa, que chama as 
 * funcoes previamente declaradas
 */
int main () {
	/*Contadores de tempo de execucao*/
	clock_t begin, end;
	double time_spent;

	/*Estruturas*/
	Produtos prod=NULL;
	Clientes cli=NULL;
	Faturacao f=NULL;
	Filial vf[3];
	Historial h[3];

	/*Variaveis auxiliares*/
	int totalVendas,v,decisao;		

	/*Abertura dos ficheiros*/
	FILE *fp;
	FILE *fc;
	FILE *fv;

	/*Ler os ficheiros para as estruturas*/
	f=initFaturacao();
	for(v=0;v<3;v++){
		vf[v]=initVendasFilial();
		h[v]=initHistorial();
	}

	imprimirInit();
	scanf(" %d", &decisao);

	if(decisao==1){
		fp = fopen("data/Produtos.txt","r");
		fc = fopen("data/Clientes.txt","r");
		fv = fopen("data/Vendas_1M.txt","r");
		verificaFicheiros(fp,fc,fv);
	}else if(decisao==2){
		fp = fopen("data/Produtos.txt","r");
		fc = fopen("data/Clientes.txt","r");
		fv = fopen("data/Vendas_3M.txt","r");
		verificaFicheiros(fp,fc,fv);
	}else if(decisao==3){
		fp = fopen("data/Produtos.txt","r");
		fc = fopen("data/Clientes.txt","r");
		fv = fopen("data/Vendas_5M.txt","r");
		verificaFicheiros(fp,fc,fv);
	}else if(decisao==4){
		char produtos[50], clientes[50], vendas[50];
		puts("");
		printf("\033[1mLocalização do ficheiro Produtos: \033[0m ");
		scanf("%s",produtos);
		fp = fopen(produtos,"r");

		printf("\033[1mLocalização do ficheiro Clientes: \033[0m ");
		scanf("%s",clientes);
		fc = fopen(clientes,"r");
		
		printf("\033[1mLocalização do ficheiro Vendas: \033[0m ");
		scanf("%s",vendas);
		fv = fopen(vendas,"r");
		
		verificaFicheiros(fp,fc,fv);
	}else{
		printf("\t\t\033[31m\033[1m Introduza uma opção válida!\033[0m\n");
		exit(0);
	}

	/*Inicializacao do contador*/
	begin = clock(); 

	puts("");
	prod=readProdutos(fp,f,vf);
	cli=readClientes(fc,h);
	totalVendas=readVendas(fv,f,vf,prod,cli,h);

	/*Fechar ficheiros*/
	fclose(fp);
	fclose(fc);
	fclose(fv);

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
	exec(prod,cli,f,vf,h);

	freeAll(prod,cli,f,vf,h);
	return 0;
}
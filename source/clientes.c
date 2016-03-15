#include <stdlib.h>
#include <string.h>
#include "../headers/AVL.h"
#include "../headers/clientes.h"

typedef struct cliente{
	char codigo[5];
	int comprou_filial[3];
	char** produtos;
	int* quantidade;
	float* faturacao;
	int tabela[12][3];
}cliente;

typedef struct clientes{
	AVL avl[26];
	int total;
}clientes;

/* -------------------
   Funções de consulta
   -------------------
*/
AVL getClientesLetra (Clientes c, char ch) {
	return c->avl[ch-'A'];
}

char* getCodigoCliente (Cliente c) {
	return c->codigo;
}

int getTotalClientes (Clientes c) {
	return c->total;
}

int getComprouFilial (Cliente c, int filial) {
	return c->comprou_filial[filial];
}

char** getProdutosCliente(Cliente c){
	return c->produtos;
}

int* getQuantidadeProdutos(Cliente c){
	return c->quantidade;
}

float* getFaturacaoProdutos(Cliente c){
	return c->faturacao;
}

int getValorTabela(Cliente c, int mes, int filial){
	return c->tabela[mes][filial];
}

char** getListaClientesLetra (Clientes c, char ch) {
	char** s=NULL;
	if (c!=NULL)
		s=toString(getClientesLetra(c,ch),c->total);
	return s;
}

/* ----------------------
   Funções de modificação
   ----------------------
*/
void setClientes (Clientes c, int n) {
	c->total=n;
}

void addClientes (Clientes c, int n) {
	c->total+=n;
}

void setCodigoCliente (Cliente c, char *s) {
	strcpy(c->codigo,s);
}

void setComprouFilial (Cliente c, int filial) {
	c->comprou_filial[filial]=1;
}

/* -----------------------------------
   Funções de manipulação dos Clientes
   -----------------------------------
*/
int clicmp (Cliente a, Cliente b) {
	return strcmp(a->codigo,b->codigo);
}

int clicmpstr (char *a, Cliente b) {
	return strcmp(a,b->codigo);
}

void updateCliente(Clientes c, char* cod_cliente,char* cod_produto, int mes, int filial, int quantidade, float preco){
	int pos, encontrado=0;
	Cliente cliente = searchCliente(c,cod_cliente);
	char** lista_produtos = getProdutosCliente(cliente);

	for(pos=0;lista_produtos[pos]!=NULL;pos++){
		if(lista_produtos[pos]==cod_produto){ /*ja foi comprado pelo cliente, logo apenas atualizamos a quantidade comprada e o dinheiro gasto*/
			cliente->quantidade[pos]+=quantidade;	
			cliente->faturacao[pos]+=preco;
			cliente->tabela[mes-1][filial-1]+=quantidade;
			encontrado=1;
		}
	}
	if(encontrado==0){ /*nao encontramos, logo vamos criar no final da lista*/
		cliente->produtos[pos]=cod_produto;
		cliente->quantidade[pos]=quantidade;
		cliente->faturacao[pos]=preco;
		cliente->tabela[mes-1][filial-1]+=quantidade;
	}
}

Cliente initCliente () {
	int i,j;
	Cliente c = (Cliente)malloc(sizeof(struct cliente));
	c->produtos=(char**)malloc(sizeof(char**)*100); 
	c->quantidade=(int*)malloc(sizeof(int*)*100);
	c->faturacao=(float*)malloc(sizeof(float*)*100); 
	
	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			c->tabela[i][j]=(long)malloc(sizeof(int));
			c->tabela[i][j]=0;
		}
	}
	return c;
}

Clientes insertCliente (Clientes c, char *s) {
	int i, pos=s[0]-'A';

	Cliente aux = initCliente();
	setCodigoCliente(aux,s);
	
	if (c==NULL) {	/*Se não existir a estrutura Clientes, criá-la*/
		c=(Clientes)malloc(sizeof(struct clientes));
		for (i=0; i<26; i++) 
			c->avl[i]=NULL;
		c->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	c->avl[pos]=insertAVL(c->avl[pos],aux,&i,(int (*)(void*,void*))clicmp);
	return c;
}

Cliente searchCliente (Clientes c, char *s) {
	Cliente c1;
	AVL aux=search(c->avl[s[0]-'A'],s,(int (*)(void*,void*))clicmpstr);
	if (aux!=NULL) {
		c1=getData(aux);
		return c1;
	}
	else 
		return NULL;
}
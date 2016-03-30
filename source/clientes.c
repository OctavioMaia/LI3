#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"


typedef struct cliente{
	char codigo[5];
	int comprou_filial[3];
	LISTA_STRING produtos;
	LISTA_INT quantidade;
	LISTA_INT mes;
	LISTA_FLOAT faturacao;
	int tabela[12][3];
}cliente;

typedef struct clientes{
	ListaClientes avl[26];
	int total;
}clientes;

/* -------------------
   Funções de consulta
   -------------------
*/
ListaClientes getClientesLetra (Clientes c, char ch) {
	return c->avl[ch-'A'];
}

CLIENTE getCodigoCliente (Cliente c) {
	return c->codigo;
}

int getTotalClientes (Clientes c) {
	return c->total;
}

int getComprouFilial (Cliente c, int filial) {
	return c->comprou_filial[filial];
}

LISTA_STRING getProdutosCliente(Cliente c){
	return c->produtos;
}

LISTA_INT getQuantidadeProdutos(Cliente c){
	return c->quantidade;
}

LISTA_INT getMesVenda(Cliente c){
	return c->mes;
}

LISTA_FLOAT getFaturacaoProdutos(Cliente c){
	return c->faturacao;
}

int getValorTabela(Cliente c, int mes, int filial){
	return c->tabela[mes][filial];
}

LISTA_STRING getListaClientesLetra (Clientes c, char ch) {
	LISTA_STRING s=NULL;
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

void setCodigoCliente (Cliente c, CLIENTE s) {
	strcpy(c->codigo,s);
}

void setComprouFilial (Cliente c, int filial) {
	c->comprou_filial[filial]=1;
}

void setFaturacaoProdutos(Cliente c, LISTA_FLOAT faturacao){
	c->faturacao=faturacao;
}

/* -----------------------------------
   Funções de manipulação dos Clientes
   -----------------------------------
*/
int clicmp (Cliente a, Cliente b) {
	return strcmp(a->codigo,b->codigo);
}

int clicmpstr (CLIENTE a, Cliente b) {
	return strcmp(a,b->codigo);
}

void updateCliente(Clientes c, CLIENTE cod_cliente, STRING cod_produto, int mes, int filial, int quantidade, float preco){
	int pos, encontrado=0;
	Cliente cliente = searchCliente(c,cod_cliente);
	LISTA_STRING lista_produtos = getProdutosCliente(cliente);
	LISTA_INT lista_mes = getMesVenda(cliente);

	for(pos=0;lista_produtos[pos]!=NULL;pos++){
		if(lista_produtos[pos]==cod_produto && lista_mes[pos]==mes){ /*ja foi comprado pelo cliente nesse mes, 
																			logo apenas atualizamos a quantidade comprada e o dinheiro gasto*/
			cliente->quantidade[pos]+=quantidade;	
			cliente->faturacao[pos]+=preco;
			cliente->tabela[mes-1][filial-1]+=quantidade;
			encontrado=1;
		}
	}
	if(encontrado==0){ /*nao encontramos, logo vamos criar no final da lista*/
		cliente->produtos[pos]=cod_produto;
		cliente->quantidade[pos]=quantidade;
		cliente->mes[pos]=mes;
		cliente->faturacao[pos]=preco;
		cliente->tabela[mes-1][filial-1]+=quantidade;
	}
}

Clientes initClientes(){
	Clientes temp;
	int i;

	temp = (Clientes)malloc(sizeof(struct clientes));
	for(i=0;i<26;i++){
		temp->avl[i]=NULL;
	}

	return temp;
}

Cliente initCliente () {
	int i,j;
	Cliente c = (Cliente)malloc(sizeof(struct cliente));
	c->produtos=(LISTA_STRING)malloc(sizeof(STRING)*100); 
	c->quantidade=(LISTA_INT)malloc(sizeof(int)*100);
	c->faturacao=(LISTA_FLOAT)malloc(sizeof(float)*100); 
	c->mes=(LISTA_INT)malloc(sizeof(int)*100); 
	
	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			c->tabela[i][j]=(long)malloc(sizeof(int));
			c->tabela[i][j]=0;
		}
	}
	return c;
}

Clientes insertCliente (Clientes c, CLIENTE s) {
	int i, pos=s[0]-'A';

	Cliente aux = initCliente();
	setCodigoCliente(aux,s);
	
	if (c==NULL) {	/*Se não existir a estrutura Clientes, criá-la*/
		c=initClientes();
		for (i=0; i<26; i++) 
			c->avl[i]=NULL;
		c->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	c->avl[pos]=insertAVL(c->avl[pos],aux,&i,(int (*)(void*,void*))clicmp);
	return c;
}

Cliente searchCliente (Clientes c, CLIENTE s) {
	Cliente c1=NULL;
	ListaClientes aux=search(c->avl[s[0]-'A'],s,(int (*)(void*,void*))clicmpstr);
	if (aux!=NULL) {
		c1=getData(aux);
		return c1;
	}
	else 
		return NULL;
}

int removeCliente(Clientes c, CLIENTE s){
	int flag=0;
	Cliente temp = searchCliente(c,s);

	if(temp){/*Cliente existe, podemos remover*/
		ListaClientes l = (AVL) getListaClientesLetra(c,s[0]);
		l = deleteAVL(l, s);
		flag=1;
	}else{
		flag=0;
	}
	return flag;
}
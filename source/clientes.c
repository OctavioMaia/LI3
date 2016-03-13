#include <stdlib.h>
#include <string.h>
#include "../headers/AVL.h"
#include "../headers/clientes.h"

typedef struct cliente{
	char codigo[5];
	int comprou_filial1;
	int comprou_filial2;
	int comprou_filial3;
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

int getComprouFilial1 (Cliente c) {
	return c->comprou_filial1;
}

int getComprouFilial2 (Cliente c) {
	return c->comprou_filial2;
}

int getComprouFilial3 (Cliente c) {
	return c->comprou_filial3;
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

void setComprouFilial1 (Cliente c) {
	c->comprou_filial1=1;
}

void setComprouFilial2 (Cliente c) {
	c->comprou_filial2=1;
}

void setComprouFilial3 (Cliente c) {
	c->comprou_filial3=1;
}


/* -----------------------------------
   Funções de manipulação dos Clientes
   -----------------------------------
*/
int clicmp (Cliente a, Cliente b) {
	return strcmp(a->codigo,b->codigo);
}

int clicmpstr (char a[], Cliente b) {
	return strcmp(a,b->codigo);
}

Cliente initCliente () {
	return (Cliente)malloc(sizeof(struct cliente));
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
	else return NULL;
}
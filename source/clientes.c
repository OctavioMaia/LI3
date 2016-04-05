#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"

typedef struct cliente{
	char codigo[6];
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
void addClientes (Clientes c, int n) {
	c->total+=n;
}

void setCodigoCliente (Cliente c, CLIENTE s) {
	strcpy(c->codigo,s);
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

Clientes initClientes(){
	int i;
	Clientes c = (Clientes)malloc(sizeof(struct clientes));

	for(i=0;i<26;i++)
		c->avl[i]=NULL;

	return c;
}

Cliente initCliente () {
	Cliente c = (Cliente)malloc(sizeof(struct cliente));
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

Clientes removeCliente(Clientes c, CLIENTE s){
	Cliente temp = searchCliente(c,s);

	if(temp){/*Cliente existe, podemos remover*/
		ListaClientes l = (ListaClientes) getListaClientesLetra(c,s[0]);
		l = deleteAVL(l, s);
	}
	return c;
}
#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"

/*
 * nodo
 * Esta estrutura contem a informação relativa
 * a um cliente, neste caso, apenas o seu codigo.
 */
typedef struct cliente{
	char codigo[6];
}cliente;

/*
 * clientes
 * Esta estrutura contem 26 ListaClientes. 
 * Ou seja, uma ListaCliente para cada letra
 * do abecedário.
 */
typedef struct clientes{
	ListaClientes avl[26];
	int total;
}clientes;

/* -------------------
   Funções de consulta
   -------------------
*/

/*
 * getClientesLetra
 * retorna a ListaClientes de uma dada letra.
 */
ListaClientes getClientesLetra (Clientes c, char ch) {
	return c->avl[ch-'A'];
}

/*
 * getCodigoCliente
 * retorna o codigo de um Cliente c.
 */
CLIENTE getCodigoCliente (Cliente c) {
	return c->codigo;
}

/*
 * getTotalClientes
 * retorna o total de clientes
 */
int getTotalClientes (Clientes c) {
	return c->total;
}

/*
 * getListaClientesLetra
 * retorna uma lista de clientes, começadas por uma dada letra.
 */
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

/*
 * addClientes
 * adiciona n clientes ao total do sistema
 */
void addClientes (Clientes c, int n) {
	c->total+=n;
}


/*
 * setCodigoCliente
 * copia o codigo de cliente s para um cliente c
 */
void setCodigoCliente (Cliente c, CLIENTE s) {
	strcpy(c->codigo,s);
}

/* -----------------------------------
   Funções de manipulação dos Clientes
   -----------------------------------
*/

/*
 * clicmp
 * funcao de comparacao de dois Cliente
 */
int clicmp (Cliente a, Cliente b) {
	return strcmp(a->codigo,b->codigo);
}


/*
 * clicmpstr
 * funcao de comparacao de um cliente e de um código
 * de cliente
 */
int clicmpstr (CLIENTE a, Cliente b) {
	return strcmp(a,b->codigo);
}

/*
 * initClientes
 * funcao de inicialização da estrutura Clientes
 */
Clientes initClientes(){
	int i;
	Clientes c = (Clientes)malloc(sizeof(struct clientes));

	for(i=0;i<26;i++)
		c->avl[i]=NULL;

	return c;
}

/*
 * initCliente
 * funcao de inicilizacao de um Cliente
 */
Cliente initCliente () {
	Cliente c = (Cliente)malloc(sizeof(struct cliente));
	return c;
}

/*
 * insertCliente
 * funcao de inserção de um cliente na estrutura Clientes
 */
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
	c->avl[pos]=inserirAVL(c->avl[pos],aux,&i,(int (*)(void*,void*))clicmp);
	return c;
}


/*
 * searchCliente
 * função de procura de um dado cliente, através
 * do seu código s
 */
Cliente searchCliente (Clientes c, CLIENTE s) {
	Cliente c1=NULL;
	ListaClientes aux=procurarAVL(c->avl[s[0]-'A'],s,(int (*)(void*,void*))clicmpstr);
	if (aux!=NULL) {
		c1=getData(aux);
		return c1;
	}
	else 
		return NULL;
}

/*
 * removeCliente
 * funcao de remoção de um cliente 
 */
Clientes removeCliente(Clientes c, CLIENTE s){
	Cliente temp = searchCliente(c,s);

	if(temp){/*Cliente existe, podemos remover*/
		ListaClientes l = (ListaClientes) getListaClientesLetra(c,s[0]);
		l = removerAVL(l, s);
	}
	return c;
}

/*
 * freeClientes
 * função de libertar memória da estrutura Clientes.
 */
void freeClientes(Clientes c){
	int i;

	for(i=0;i<26;i++){
		freeAVL(c->avl[i]);
	}
}
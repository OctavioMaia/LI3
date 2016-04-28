#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/produtos.h"

/*
 * produto
 * Esta estrutura contem a informação relativa
 * a um produto, neste caso, apenas o seu codigo.
 */
typedef struct produto{
	char codigo[7];
}produto;

/*
 * produtos
 * Esta estrutura contem 26 ListaProdutos 
 * Ou seja, uma ListaProduto para cada letra
 * do abecedário.
 */
typedef struct produtos {
	ListaProdutos avl[26];		
	int total;					
}produtos;

/* -------------------
   Funções de consulta
   -------------------
*/


/*
 * getProdutosLetra
 * retorna a ListaClientes de uma dada letra.
 */
ListaProdutos getProdutosLetra (Produtos p, char ch) {
	return p->avl[ch-'A'];
}

/*
 * getCodProduto
 * retorna o codigo de um Produto p.
 */
PRODUTO getCodProduto(Produto p){
	return p->codigo;
}

/* 
 * getTotalProdutos
 * retorna o total de produtos
 */ 
int getTotalProdutos (Produtos p) {
	return p->total;
}


/*
 * getListaProdutosLetra
 * retirna uma lista de produtos, começadas por uma dada letra.
 */
LISTA_STRING getListaProdutosLetra (Produtos p, char ch) {
	LISTA_STRING s=NULL;
	if (p!=NULL)
		s=toString(getProdutosLetra(p,ch),p->total);
	return s;
}

/* ----------------------
   Funções de modificação
   ----------------------
*/

/* 
 * addProdutos
 * adiciona total produtos ao total do sistema
 */
void addProdutos (Produtos p, int total) {
	p->total+=total;
}

/*
 * setCodigoProduto
 * copia o codigo de produto s para um produto p
 */
void setCodigoProduto (Produto p, PRODUTO s) {
	strcpy(p->codigo,s);
}

/* 
 * setProdutos
 * altera o número total de produtos do sistema para total
 */
void setProdutos (Produtos p, int total) {
	p->total=total;
}



/* -----------------------------------
   Funções de manipulação dos Produtos
   -----------------------------------
*/

/*
 * prodcmp
 * funcao de comparacao de dois Produto
 */
int prodcmp (Produto a, Produto b) {
	return strcmp(a->codigo,b->codigo);
}

/*
 * prodcmpstr
 * funcao de comparacao de um produto e de um código
 * de produto
 */
int prodcmpstr (PRODUTO a, Produto b) {
	return strcmp(a,b->codigo);
}

/* 
 * initProdutos
 * função de inicialização da estrutura Produtos
 */ 
Produtos initProdutos(){
	int i;
	Produtos p = (Produtos)malloc(sizeof(struct produtos));

	for(i=0;i<26;i++)
		p->avl[i]=NULL;

	return p;
}

/* 
 * initProduto
 * função inicialização de um Produto.
 */
Produto initProduto(){
	Produto p = (Produto)malloc(sizeof(struct produto));
	return p;
}

/* 
 * insertProduto
 * função de inserção de um produto na estrutura Produtos
 */
Produtos insertProduto(Produtos p, PRODUTO s) {
	int i, pos=s[0]-'A';

	Produto aux = initProduto();
	setCodigoProduto(aux,s);

	if (p==NULL) {	/*Se não existir a estrutura Produtos, criá-la*/
		p = initProdutos();
		for (i=0; i<26; i++) 
			p->avl[i]=NULL;
		p->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	p->avl[pos]=inserirAVL(p->avl[pos],aux,&i,(int (*)(void*,void*))prodcmp);
	return p;
}

/* 
 * searchProduto
 * função de procura de um dado produto, através
 * do seu código s
 */
Produto searchProduto(Produtos p, PRODUTO s) {
	Produto p1=NULL;
	ListaProdutos aux=procurarAVL(p->avl[s[0]-'A'],s,(int (*)(void*,void*))prodcmpstr);
	if (aux!=NULL) {
		p1=getData(aux);
		return p1;
	}else{
		return NULL;
	}
}

/* 
 * removeProduto
 * função de remoção de um produto
 */
Produtos removeProduto(Produtos p, PRODUTO s){
	Produto temp = searchProduto(p,s);

	if(temp){/*Cliente existe, podemos remover*/
		ListaProdutos l = (ListaProdutos) getListaProdutosLetra(p,s[0]);
		l = removerAVL(l, s);
	}
	return p;
}

/* 
 * freeClientes
 * função de libertar memória da estrutura Produtos
 */
void freeProdutos(Produtos p){
	int i;

	for(i=0;i<26;i++){
		freeAVL(p->avl[i]);
	}
}















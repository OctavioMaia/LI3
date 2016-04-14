#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/produtos.h"

typedef struct produto{
	char codigo[7];
}produto;

typedef struct produtos {
	ListaProdutos avl[26];		/*Divisao dos produtos em 26 avl's*/
	int total;					/*Nº produtos total (nas 3 filiais)*/
}produtos;

/*  ========================================
     Funções relativas à estrutura Produtos
    ========================================
 */

int prodcmp (Produto a, Produto b) {
	return strcmp(a->codigo,b->codigo);
}

int prodcmpstr (PRODUTO a, Produto b) {
	return strcmp(a,b->codigo);
}

void setCodigoProduto (Produto p, PRODUTO s) {
	strcpy(p->codigo,s);
}

/* -------------------
   Funções de consulta
   -------------------
*/
ListaProdutos getProdutosLetra (Produtos p, char ch) {
	return p->avl[ch-'A'];
}

PRODUTO getCodProduto(Produto p){
	return p->codigo;
}

int getTotalProdutos (Produtos p) {
	return p->total;
}

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
void setProdutos (Produtos p, int total) {
	p->total=total;
}

void addProdutos (Produtos p, int total) {
	p->total+=total;
}

Produtos initProdutos(){
	int i;
	Produtos p = (Produtos)malloc(sizeof(struct produtos));

	for(i=0;i<26;i++)
		p->avl[i]=NULL;

	return p;
}

Produto initProduto(){
	Produto p = (Produto)malloc(sizeof(struct produto));
	return p;
}

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

Produtos removeProduto(Produtos p, PRODUTO s){
	Produto temp = searchProduto(p,s);

	if(temp){/*Cliente existe, podemos remover*/
		ListaProdutos l = (ListaProdutos) getListaProdutosLetra(p,s[0]);
		l = removerAVL(l, s);
	}
	return p;
}
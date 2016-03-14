#include <stdlib.h>
#include <string.h>
#include "../headers/AVL.h"
#include "../headers/produtos.h"

typedef struct produto{
	char codigo[6];
	int quantidade_vendida;
}produto;

typedef struct produtos {
	AVL avl[26];			/*Divisao dos produtos em 26 AVL's*/
	int total;					/*Nº produtos total (nas 3 filiais)*/
}produtos;

/*  ========================================
     Funções relativas à estrutura Produtos
    ========================================
 */

int prodcmp (Produto a, Produto b) {
	return strcmp(a->codigo,b->codigo);
}

int prodcmpstr (char *a, Produto b) {
	return strcmp(a,b->codigo);
}

void setCodigoProduto (Produto p, char *s) {
	strcpy(p->codigo,s);
}

/* -------------------
   Funções de consulta
   -------------------
*/
AVL getProdutosLetra (Produtos p, char ch) {
	return p->avl[ch-'A'];
}

char* getCodProduto(Produto p){
	return p->codigo;
}

int getTotalProdutos (Produtos p) {
	return p->total;
}

int getQuantidadeVendida(Produto p){
	return p->quantidade_vendida;
}

char** getListaProdutosLetra (Produtos p, char ch) {
	char** s=NULL;
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

void setQuantidadeVendida(Produto p, int qt){
	p->quantidade_vendida+=qt;
}

Produto initProduto(){
	Produto p = (Produto)malloc(sizeof(struct produto));
	setQuantidadeVendida(p,0);
	return p;
}

Produtos insertProduto(Produtos p, char *s) {
	int i, pos=s[0]-'A';

	Produto aux = initProduto();
	setCodigoProduto(aux,s);

	if (p==NULL) {	/*Se não existir a estrutura Produtos, criá-la*/
		p=(Produtos)malloc(sizeof(struct produtos));
		for (i=0; i<26; i++) 
			p->avl[i]=NULL;
		p->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	p->avl[pos]=insertAVL(p->avl[pos],aux,&i,(int (*)(void*,void*))prodcmp);
	return p;
}

Produto searchProduto(Produtos p, char *s) {
	Produto p1;
	AVL aux=search(p->avl[s[0]-'A'],s,(int (*)(void*,void*))prodcmpstr);
	if (aux!=NULL) {
		p1=getData(aux);
		return p1;
	}else{
		return NULL;
	}
}

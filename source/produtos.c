#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/produtos.h"

typedef struct produto{
	char codigo[6];
	int quantidade_clientes;
	int quantidade_vendida[3];
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

int getQuantidadeVendidaFilial(Produto p, int filial){
	return p->quantidade_vendida[filial];
}

int getQuantidadeVendida(Produto p){
	return p->quantidade_vendida[0]+p->quantidade_vendida[1]+p->quantidade_vendida[2];
}

int getQuantidadeClientes(Produto p){
	return p->quantidade_clientes;
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

void setQuantidadeVendidaFilial(Produto p, int filial, int qt){
	p->quantidade_vendida[filial]+=qt;
}

void setQuantidadeClientes(Produto p, int qt){
	p->quantidade_clientes+=qt;
}

Produtos initProdutos(){
	Produtos temp;
	int i;

	temp = (Produtos)malloc(sizeof(struct produtos));
	for(i=0;i<26;i++){
		temp->avl[i]=NULL;
	}

	return temp;
}

Produto initProduto(){
	Produto p = (Produto)malloc(sizeof(struct produto));
	p->quantidade_vendida[0]=0;
	p->quantidade_vendida[1]=0;
	p->quantidade_vendida[2]=0;
	p->quantidade_clientes=0;
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
	p->avl[pos]=insertAVL(p->avl[pos],aux,&i,(int (*)(void*,void*))prodcmp);
	return p;
}

Produto searchProduto(Produtos p, PRODUTO s) {
	Produto p1=NULL;
	ListaProdutos aux=search(p->avl[s[0]-'A'],s,(int (*)(void*,void*))prodcmpstr);
	if (aux!=NULL) {
		p1=getData(aux);
		return p1;
	}else{
		return NULL;
	}
}

int removeProduto(Produtos p, PRODUTO s){
	int flag=0;
	Produto temp = searchProduto(p,s);

	if(temp){/*Cliente existe, podemos remover*/
		ListaProdutos l = (AVL) getListaProdutosLetra(p,s[0]);
		l = deleteAVL(l, s);
		flag=1;
	}else{
		flag=0;
	}
	return flag;
}
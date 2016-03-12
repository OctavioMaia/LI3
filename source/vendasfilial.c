#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/AVL.h"
#include "../headers/clientes.h"
#include "../headers/produtos.h"
#include "../headers/vendas.h"
#include "../headers/vendasfilial.h"

typedef struct historico{
	char** clientes;
	int* quantidade;
}historico;

typedef struct listaproduto{
	char produto[6];
	Historico h[12][3];
}listaproduto;

typedef struct vendasfilial {
	AVL avl[26];	/*Divisao dos produtos em 26 AVL's*/
	int total;
}vendasfilial;

/*GETS*/
AVL getVendasFilialLetra (VendasFilial vf, char ch) {
	return vf->avl[ch-'A'];
}

Historico getHistorico(ListaProduto lp, int mes, int filial){
	return lp->h[mes][filial];
}

char* getCodigoListaProduto (ListaProduto p){
	return p->produto;
}

int getTotalVendasFilial (VendasFilial vf) {
	return vf->total;
}

char** getListaVendasFilialLetra (VendasFilial vf, char ch) {
	char** s=NULL;
	if (vf!=NULL)
		s=toString(getVendasFilialLetra(vf,ch),vf->total);
	return s;
}

/*SETS*/
void setCodigoListaProduto (ListaProduto p, char *s) {
	strcpy(p->produto,s);
}

void addVendasFilial (VendasFilial vf, int total) {
	vf->total+=total;
}

/*funcoes comparacao*/
int vfcmp (ListaProduto a, ListaProduto b) {
	return strcmp(a->produto,b->produto);
}

int vfcmpstr (char *a, ListaProduto b) {
	return strcmp(a,b->produto);
}

/*funcoes*/
VendasFilial initVendasFilial(){
	return (VendasFilial)malloc(sizeof(vendasfilial));
}

ListaProduto initListaProduto(){
	int i,j;
	ListaProduto lp = (ListaProduto)malloc(sizeof(struct listaproduto));

	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			lp->h[i][j]=(Historico)malloc(sizeof(historico));
			lp->h[i][j]->clientes=(char**)malloc(sizeof(char**));
			lp->h[i][j]->quantidade=(int*)malloc(sizeof(int*));
		}
	}
	return lp;
}

VendasFilial insertListaProduto(VendasFilial f, char *s) {
	int i, pos=s[0]-'A';
	ListaProduto aux = initListaProduto();
	/*printf("antes %s ", getCodigoListaProduto(aux));*/
	setCodigoListaProduto(aux,s);
	/*printf("depois %s\n", getCodigoListaProduto(aux));*/

	if (f==NULL) {	/*Se não existir a estrutura , criá-la*/
		f=(VendasFilial)malloc(sizeof(struct vendasfilial));
		for (i=0; i<26; i++) 
			f->avl[i]=NULL;
		f->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	f->avl[pos]=insertAVL(f->avl[pos],aux,&i,(int (*)(void*,void*))vfcmp);
	return f;
}

ListaProduto searchListaProduto(VendasFilial f, char *s) {
	ListaProduto p1;
	AVL aux=search(f->avl[s[0]-'A'],s,(int (*)(void*,void*))vfcmpstr);
	if (aux!=NULL) {
		p1=getData(aux);
		return p1;
	}else{
		return NULL;
	}
}

/*funcoes auxiliares*/
void atualizaHistorico(VendasFilial vf, Venda v){
	int i;
	int mes = getMes(v);
	int filial = getFilial(v);
	int quantidade = getQuantidade(v);
	char* cliente = getCliente(v);

	ListaProduto lp = searchListaProduto(vf,getProduto(v));
	Historico h = getHistorico(lp,mes-1,filial-1);

	if(h){
		for(i=0;h->clientes[i]!=NULL;i++);

		h->clientes[i]=(char*)malloc(sizeof(char)*5); /*aloca espaço para um cod de cliente (5 char)*/
		h->clientes[i]=cliente;
		h->quantidade[i]=(long)malloc(sizeof(int)); /*aloquei long, pois se meter int da um aviso qq*/
		h->quantidade[i]=quantidade;	
		
		printf("Pos:%d Cl:%s Prod:%s Qt:%d Mes:%d Filial:%d\n",i,h->clientes[i],getCodigoListaProduto(lp),h->quantidade[i],mes,filial);
	}else{
		printf("Nao devia acontecer\n");
	}
}
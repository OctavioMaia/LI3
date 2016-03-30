#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"
#include "../headers/produtos.h"
#include "../headers/vendas.h"
#include "../headers/vendasfilial.h"

typedef struct historico{
	LISTA_STRING clientesN;
	LISTA_INT quantidadeN;
	LISTA_STRING clientesP;
	LISTA_INT quantidadeP;
}historico;

typedef struct listaproduto{
	char produto[6];
	Historico h[12][3];
}listaproduto;

typedef struct vendasfilial {
	ListaVFilial avl[26];	/*Divisao dos produtos em 26 avl's*/
	int total;
}vendasfilial;

/*GETS*/
ListaVFilial getVendasFilialLetra (VendasFilial vf, char ch) {
	return vf->avl[ch-'A'];
}

int getTotalVendasFilial (VendasFilial vf) {
	return vf->total;
}

Historico getHistorico(ListaProduto lp, int mes, int filial){
	return lp->h[mes][filial];
}

STRING getCodigoListaProduto (ListaProduto p){
	return p->produto;
}

LISTA_STRING getClientesN(Historico h){
	return h->clientesN;
}

LISTA_INT getQuantidadeN(Historico h){
	return h->quantidadeN;
}

LISTA_STRING getClientesP(Historico h){
	return h->clientesP;
}

LISTA_INT getQuantidadeP(Historico h){
	return h->quantidadeP;
}

LISTA_STRING getListaVendasFilialLetra (VendasFilial vf, char ch) {
	LISTA_STRING s=NULL;
	if (vf!=NULL)
		s=toString(getVendasFilialLetra(vf,ch),vf->total);
	return s;
}

/*SETS*/
void setCodigoListaProduto (ListaProduto p, STRING s) {
	strcpy(p->produto,s);
}

void addVendasFilial (VendasFilial vf, int total) {
	vf->total+=total;
}

/*funcoes comparacao*/
int vfcmp (ListaProduto a, ListaProduto b) {
	return strcmp(a->produto,b->produto);
}

int vfcmpstr (STRING a, ListaProduto b) {
	return strcmp(a,b->produto);
}

/*funcoes*/
VendasFilial initVendasFilial(){
	VendasFilial temp;
	int i;

	temp = (VendasFilial)malloc(sizeof(struct vendasfilial));
	for(i=0;i<26;i++){
		temp->avl[i]=NULL;
	}

	return temp;
}

ListaProduto initListaProduto(){
	int i,j;
	ListaProduto lp = (ListaProduto)malloc(sizeof(struct listaproduto));

	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			lp->h[i][j]=(Historico)malloc(sizeof(historico));
			lp->h[i][j]->clientesN=(LISTA_STRING)malloc(sizeof(STRING)*100); /*Esta merda crasha!, tirar o *100*/
			lp->h[i][j]->quantidadeN=(LISTA_INT)malloc(sizeof(int)*100);
			lp->h[i][j]->clientesP=(LISTA_STRING)malloc(sizeof(STRING)*100);
			lp->h[i][j]->quantidadeP=(LISTA_INT)malloc(sizeof(int)*100);
		}
	}
	return lp;
}

VendasFilial insertListaProduto(VendasFilial f, STRING s) {
	int i, pos=s[0]-'A';
	ListaProduto aux = initListaProduto();
	/*printf("antes %s ", getCodigoListaProduto(aux));*/
	setCodigoListaProduto(aux,s);
	/*printf("depois %s\n", getCodigoListaProduto(aux));*/

	if (f==NULL) {	/*Se não existir a estrutura , criá-la*/
		f=initVendasFilial();
		for (i=0; i<26; i++) 
			f->avl[i]=NULL;
		f->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	f->avl[pos]=insertAVL(f->avl[pos],aux,&i,(int (*)(void*,void*))vfcmp);
	return f;
}

ListaProduto searchListaProduto(VendasFilial f, STRING s) {
	ListaProduto p1=NULL;
	ListaVFilial aux=search(f->avl[s[0]-'A'],s,(int (*)(void*,void*))vfcmpstr);
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
	STRING cliente = getCliente(v);
	char tipo = getPromo(v);

	ListaProduto lp = searchListaProduto(vf,getProduto(v));
	Historico h = getHistorico(lp,mes-1,filial-1);

	if(h){
		if(tipo=='N'){
			for(i=0;h->clientesN[i]!=NULL;i++);

			h->clientesN[i]=(STRING)malloc(sizeof(char)*5); /*aloca espaço para um cod de cliente (5 char)*/
			h->clientesN[i]=cliente;
			h->quantidadeN[i]=(long)malloc(sizeof(int)); /*aloquei long, pois se meter int da um aviso qq*/
			h->quantidadeN[i]=quantidade;	
			
			/*printf("Pos:%d Cl:%s Prod:%s Qt:%d Mes:%d Filial:%d\n",i,h->clientes[i],getCodigoListaProduto(lp),h->quantidade[i],mes,filial);*/
		}else{
			for(i=0;h->clientesP[i]!=NULL;i++);

			h->clientesP[i]=(STRING)malloc(sizeof(char)*5); /*aloca espaço para um cod de cliente (5 char)*/
			h->clientesP[i]=cliente;
			h->quantidadeP[i]=(long)malloc(sizeof(int)); /*aloquei long, pois se meter int da um aviso qq*/
			h->quantidadeP[i]=quantidade;	
			
			/*printf("Pos:%d Cl:%s Prod:%s Qt:%d Mes:%d Filial:%d\n",i,h->clientes[i],getCodigoListaProduto(lp),h->quantidade[i],mes,filial);*/
		}
	}else{
		printf("Nao devia acontecer\n");
	}
}
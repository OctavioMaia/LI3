#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"
#include "../headers/produtos.h"
#include "../headers/vendas.h"
#include "../headers/vendasfilial.h"


typedef struct mes_filial{
	char codigo[6]; /*cod cliente*/
	int quantidade;	
}mes_filial;


typedef struct historico{
	AVL clientesN;
	AVL clientesP;
}historico;

typedef struct listaproduto{
	char produto[7];
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

AVL getClientesN(Historico h){
	return h->clientesN;
}

AVL getClientesP(Historico h){
	return h->clientesP;
}

STRING getCodigoMesFilial(Mes_Filial mf){
	return mf->codigo;
}

int getQuantidadeMesFilial(Mes_Filial h){
	return h->quantidade;
}

LISTA_STRING getListaVendasFilialN (Historico h, VendasFilial vf) {
	LISTA_STRING s=NULL;
	if (vf!=NULL)
		s=toString(h->clientesN,vf->total);
	return s;
}

LISTA_STRING getListaVendasFilialP (Historico h, VendasFilial vf) {
	LISTA_STRING s=NULL;
	if (vf!=NULL)
		s=toString(h->clientesP,vf->total);
	return s;
}

/*SETS*/
void setCodigoListaProduto (ListaProduto p, STRING s) {
	strcpy(p->produto,s);
}

void addVendasFilial (VendasFilial vf, int total) {
	vf->total+=total;
}

void setQuantidade(Mes_Filial mf, int quantidade){
	mf->quantidade=quantidade;
}

void addQuantidade(Mes_Filial mf, int quantidade){
	mf->quantidade+=quantidade;
}

void setCodigoClienteMesFilial(Mes_Filial mf, char *codigo){
	strcpy(mf->codigo,codigo);
}

void setAvlN(Historico h, AVL a){
	h->clientesN=a;
}

void setAvlP(Historico h, AVL a){
	h->clientesP=a;
}

/*funcoes comparacao*/
int vfcmp (ListaProduto a, ListaProduto b) {
	return strcmp(a->produto,b->produto);
}

int vfcmpstr (STRING a, ListaProduto b) {
	return strcmp(a,b->produto);
}

int mfcmp (Mes_Filial a, Mes_Filial b) {
	return strcmp(a->codigo,b->codigo);
}

int mfcmpstr (STRING a, Mes_Filial b) {
	return strcmp(a,b->codigo);
}

/*funcoes*/
VendasFilial initVendasFilial(){
	int i;
	VendasFilial vf = (VendasFilial)malloc(sizeof(struct vendasfilial));
	
	for(i=0;i<26;i++)
		vf->avl[i]=NULL;

	return vf;
}

ListaProduto initListaProduto(){
	int i,j;
	ListaProduto lp = (ListaProduto)malloc(sizeof(struct listaproduto));

	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			lp->h[i][j]=(Historico)malloc(sizeof(struct historico));
			lp->h[i][j]->clientesN=NULL;
			lp->h[i][j]->clientesP=NULL;
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

Mes_Filial initMesFilial(){
	Mes_Filial mf = (Mes_Filial)malloc(sizeof(mes_filial));

	setCodigoClienteMesFilial(mf,"");
	setQuantidade(mf,0);

	return mf;
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
	AVL t=NULL;
	Mes_Filial mf=NULL;

	if(h){
		if(tipo=='N'){
			t=getClientesN(h);
			if(t==NULL){
				mf = initMesFilial();
				setCodigoClienteMesFilial(mf,cliente);
				setQuantidade(mf,quantidade);
				i=0;
				setAvlN(h,insertAVL(t,mf,&i,(int (*)(void*,void*))mfcmp));
				/*x=getData(search(t,cliente,(int (*)(void*,void*))mfcmpstr));
				printf("NORMAL %s QUANTIDADE %d\n",getCodigoMesFilial(x),getQuantidadeMesFilial(x) );*/
			}
		}else{
			t=getClientesP(h);
			if(t==NULL){
				mf = initMesFilial();
				setCodigoClienteMesFilial(mf,cliente);
				setQuantidade(mf,quantidade);
				i=0;
				setAvlP(h,insertAVL(t,mf,&i,(int (*)(void*,void*))mfcmp));
				/*x=getData(search(t,cliente,(int (*)(void*,void*))mfcmpstr));
				printf("PROMOCAO %s QUANTIDADE %d\n",getCodigoMesFilial(x),getQuantidadeMesFilial(x));*/
			}
		}
	}else{
		printf("Nao devia acontecer\n");
	}
}
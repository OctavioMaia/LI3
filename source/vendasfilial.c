#include <stdlib.h>
#include <string.h>
#include "../headers/AVL.h"
#include "../headers/produtos.h"
#include "../headers/vendas.h"
#include "../headers/vendasfilial.h"

typedef struct historico{
	char** clientes;
	int* quantidade;
}historico;

typedef struct listaproduto{
	char produto[6];
	Historico historico[12][3];
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
	return lp->historico[mes][filial];
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
ListaProduto initListaProduto(){
	int i,j;
	ListaProduto lp = (ListaProduto)malloc(sizeof(struct listaproduto));

	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			lp->historico[i][j]=(Historico)malloc(sizeof(historico));
			lp->historico[i][j]->clientes=(char**)malloc(sizeof(char**));
			lp->historico[i][j]->quantidade=0;
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
	int i,j;
	int mes = getMes(v);
	int filial = getFilial(v);
	char* cliente = getCliente(v);

	printf("antes1 %s\n",getProduto(v));
	ListaProduto lp = searchListaProduto(vf,getProduto(v));
	printf("antes2\n");
	Historico h = getHistorico(lp,mes-1,filial-1);
	printf("depois\n");

	if(h){
		for(i=0; h->clientes[i]!=NULL;i++);
		for(j=0; h->quantidade[j]!=NULL;j++);
		printf("c:%d q:%d\n",i,j );

	}else{
		printf("Nao devia acontecer\n");
	}
}
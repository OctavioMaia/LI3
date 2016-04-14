#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"
#include "../headers/produtos.h"
#include "../headers/vendas.h"
#include "../headers/filial.h"

/*========================================*/

typedef struct historialcliente{
	char cliente[6];
	int tabela[12];
	BOOLEAN comprou_filial;
	LISTA_STRING produtos;
	LISTA_INT quantidade;
	LISTA_INT mes;
	LISTA_FLOAT faturacao;
}historialcliente;

typedef struct historial{
	ListaClientes avl[26];
	int total;
}historial;

/*========================================*/

typedef struct mes_filial{
	char codigo[6]; /*cod cliente*/
	int quantidade;	
}mes_filial;

typedef struct historico{
	ListaClientes clientesN;
	ListaClientes clientesP;
}historico;

typedef struct listaproduto{
	char produto[7];
	int quantidade_clientes;
	int quantidade_vendida;
	Historico h[12];
}listaproduto;

typedef struct vendasfilial {
	ListaVFilial avl[26];	/*Divisao dos produtos em 26 avl's*/
	int total;
}vendasfilial;

/*========================================*/

/*GETS*/
ListaVFilial getVendasFilialLetra (Filial vf, char ch) {
	return vf->avl[ch-'A'];
}

int getTotalVendasFilial (Filial vf) {
	return vf->total;
}

Historico getHistorico(ListaProduto lp, int mes){
	return lp->h[mes];
}

PRODUTO getCodigoListaProduto (ListaProduto p){
	return p->produto;
}

ListaClientes getClientesN(Historico h){
	return h->clientesN;
}

ListaClientes getClientesP(Historico h){
	return h->clientesP;
}

CLIENTE getCodigoMesFilial(Mes_Filial mf){
	return mf->codigo;
}

int getQuantidadeMesFilial(Mes_Filial h){
	return h->quantidade;
}

LISTA_STRING getListaVendasFilialN (Historico h, Filial vf) {
	LISTA_STRING s=NULL;
	if (vf!=NULL)
		s=toString(h->clientesN,vf->total);
	return s;
}

LISTA_STRING getListaVendasFilialP (Historico h, Filial vf) {
	LISTA_STRING s=NULL;
	if (vf!=NULL)
		s=toString(h->clientesP,vf->total);
	return s;
}

/*cenas produtos.c*/
int getQuantidadeVendida(ListaProduto p){
	return p->quantidade_vendida;
}

int getQuantidadeClientes(ListaProduto p){
	return p->quantidade_clientes;
}

/*cenas clientes.c*/
ListaClientes getHistorialLetra (Historial h, char ch) {
	return h->avl[ch-'A'];
}

int getTotalHistorial(Historial h){
	return h->total;
}

CLIENTE getCodigoHistorialCliente (HistorialCliente hc){
	return hc->cliente;
}

BOOLEAN getComprouFilial (HistorialCliente c) {
	return c->comprou_filial;
}

LISTA_STRING getProdutosCliente(HistorialCliente c){
	return c->produtos;
}

LISTA_INT getQuantidadeProdutos(HistorialCliente c){
	return c->quantidade;
}

LISTA_INT getMesVenda(HistorialCliente c){
	return c->mes;
}

LISTA_FLOAT getFaturacaoProdutos(HistorialCliente c){
	return c->faturacao;
}

int getValorTabela(HistorialCliente c, int mes){
	return c->tabela[mes];
}


/*SETS*/
void setCodigoListaProduto (ListaProduto p, STRING s) {
	strcpy(p->produto,s);
}

void addVendasFilial (Filial vf, int total) {
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

void setAvlN(Historico h, ListaClientes a){
	h->clientesN=a;
}

void setAvlP(Historico h, ListaClientes a){
	h->clientesP=a;
}

/*produtos.c*/
void setQuantidadeVendida(ListaProduto p, int qt){
	p->quantidade_vendida+=qt;
}

void setQuantidadeClientes(ListaProduto p, int qt){
	p->quantidade_clientes+=qt;
}

/*clientes.c*/
void addHistorial (Historial h, int total) {
	h->total+=total;
}

void setCodigoHistorialCliente(HistorialCliente h, CLIENTE s){
	strcpy(h->cliente,s);
}

void setComprouFilial (HistorialCliente c, int filial) {
	c->comprou_filial=1;
}

void setFaturacaoProdutos(HistorialCliente c, LISTA_FLOAT faturacao){
	c->faturacao=faturacao;
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

int hccmp (HistorialCliente a, HistorialCliente b) {
	return strcmp(a->cliente,b->cliente);
}

int hccmpstr (STRING a, HistorialCliente b) {
	return strcmp(a,b->cliente);
}

/*funcoes*/
Filial initVendasFilial(){
	int i;
	Filial vf = (Filial)malloc(sizeof(struct vendasfilial));
	
	for(i=0;i<26;i++)
		vf->avl[i]=NULL;

	return vf;
}

ListaProduto initListaProduto(){
	int i;
	ListaProduto lp = (ListaProduto)malloc(sizeof(struct listaproduto));

	for(i=0;i<12;i++){
		lp->h[i]=(Historico)malloc(sizeof(struct historico));
		lp->h[i]->clientesN=NULL;
		lp->h[i]->clientesP=NULL;
	}

	lp->quantidade_vendida=0;
	lp->quantidade_clientes=0;
	return lp;
}

Filial insertListaProduto(Filial f, STRING s) {
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
	f->avl[pos]=inserirAVL(f->avl[pos],aux,&i,(int (*)(void*,void*))vfcmp);
	return f;
}

ListaProduto searchListaProduto(Filial f, STRING s) {
	ListaProduto p1=NULL;
	ListaVFilial aux=procurarAVL(f->avl[s[0]-'A'],s,(int (*)(void*,void*))vfcmpstr);
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

/*clientes.c*/

Historial initHistorial(){
	int i;
	Historial h = (Historial)malloc(sizeof(struct historial));
	
	for(i=0;i<26;i++)
		h->avl[i]=NULL;

	return h;
}

HistorialCliente initHistorialCliente(){
	int i;
	HistorialCliente hc = (HistorialCliente)malloc(sizeof(historialcliente));
	
	hc->produtos=(LISTA_STRING)malloc(sizeof(STRING)*1000); 
	hc->quantidade=(LISTA_INT)malloc(sizeof(int)*1000);
	hc->faturacao=(LISTA_FLOAT)malloc(sizeof(float)*1000); 
	hc->mes=(LISTA_INT)malloc(sizeof(int)*1000); 
	
	for(i=0;i<12;i++){
		hc->tabela[i]=0;
	}

	return hc;
}

Historial insertHistorialCliente(Historial f, STRING s) {
	int i, pos=s[0]-'A';
	HistorialCliente aux = initHistorialCliente();
	/*printf("antes %s ", getCodigoListaProduto(aux));*/
	setCodigoHistorialCliente(aux,s);
	/*printf("depois %s\n", getCodigoListaProduto(aux));*/

	if (f==NULL) {	/*Se não existir a estrutura , criá-la*/
		f=initHistorial();
		for (i=0; i<26; i++) 
			f->avl[i]=NULL;
		f->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	f->avl[pos]=inserirAVL(f->avl[pos],aux,&i,(int (*)(void*,void*))hccmp);
	return f;
}

HistorialCliente searchHistorialCliente(Historial f, STRING s) {
	HistorialCliente p1=NULL;
	ListaClientes aux=procurarAVL(f->avl[s[0]-'A'],s,(int (*)(void*,void*))hccmpstr);
	if (aux!=NULL) {
		p1=getData(aux);
		return p1;
	}else{
		return NULL;
	}
}

/*funcoes auxiliares*/
void atualizaHistorico(Filial vf, Venda v){
	int i;
	int mes = getMes(v);
	int quantidade = getQuantidade(v);
	STRING cliente = getCliente(v);
	char tipo = getPromo(v);

	ListaProduto lp = searchListaProduto(vf,getProduto(v));
	Historico h = getHistorico(lp,mes-1);
	ListaClientes t=NULL;
	Mes_Filial mf=NULL;

	if(h){
		if(tipo=='N'){
			t=getClientesN(h);
			if(t==NULL){
				mf = initMesFilial();
				setCodigoClienteMesFilial(mf,cliente);
				setQuantidade(mf,quantidade);
				i=0;
				setAvlN(h,inserirAVL(t,mf,&i,(int (*)(void*,void*))mfcmp));
				/*x=getData(procurarAVL(t,cliente,(int (*)(void*,void*))mfcmpstr));
				printf("NORMAL %s QUANTIDADE %d\n",getCodigoMesFilial(x),getQuantidadeMesFilial(x) );*/
			}
		}else{
			t=getClientesP(h);
			if(t==NULL){
				mf = initMesFilial();
				setCodigoClienteMesFilial(mf,cliente);
				setQuantidade(mf,quantidade);
				i=0;
				setAvlP(h,inserirAVL(t,mf,&i,(int (*)(void*,void*))mfcmp));
				/*x=getData(procurarAVL(t,cliente,(int (*)(void*,void*))mfcmpstr));
				printf("PROMOCAO %s QUANTIDADE %d\n",getCodigoMesFilial(x),getQuantidadeMesFilial(x));*/
			}
		}
	}else{
		printf("Nao devia acontecer\n");
	}
}

/*clientes.c*/
void updateCliente(Historial h,Filial vf, Venda v){
	LISTA_STRING lista_produtos;
	LISTA_INT lista_mes;
	HistorialCliente cliente;

	int pos, encontrado=0;
	CLIENTE cod_cliente = getCliente(v);
	PRODUTO cod_produto = getProduto(v);
	int quantidade = getQuantidade(v);
	int mes = getMes(v);
	int filial = getFilial(v);
	float preco = getPreco(v);
	
	ListaProduto prod = searchListaProduto(vf,cod_produto);

	setQuantidadeVendida(prod,quantidade);
	setQuantidadeClientes(prod,1);

	cliente = searchHistorialCliente(h,cod_cliente);

	if(cliente){
		setComprouFilial(cliente,filial-1);
		lista_produtos = getProdutosCliente(cliente);
		lista_mes = getMesVenda(cliente);

		for(pos=0;lista_produtos[pos]!=NULL;pos++){
			if(lista_produtos[pos]==cod_produto && lista_mes[pos]==mes){ /*ja foi comprado pelo cliente nesse mes, 
																				logo apenas atualizamos a quantidade comprada e o dinheiro gasto*/
				cliente->quantidade[pos]+=quantidade;	
				cliente->faturacao[pos]+=(preco*quantidade);
				cliente->tabela[mes-1]+=quantidade;
				encontrado=1;
			}
		}
		if(encontrado==0){ /*nao encontramos, logo vamos criar no final da lista*/
			cliente->produtos[pos]=cod_produto;
			cliente->quantidade[pos]=quantidade;
			cliente->mes[pos]=mes;
			cliente->faturacao[pos]=(preco*quantidade);
			cliente->tabela[mes-1]+=quantidade;
		}

	}
}
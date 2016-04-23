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

/*
 * historialcliente
 * Esta estrutura contem a informação relativa
 * a um historialcliente
 */
typedef struct historialcliente{
	char cliente[6];
	int tabela[12];
	BOOLEAN comprou_filial;
	LISTA_STRING produtos;
	LISTA_INT quantidade;
	LISTA_INT mes;
	LISTA_FLOAT faturacao;
}historialcliente;

/*
 * historial
 * Esta estrutura contem 26 ListaClientes. 
 * Ou seja, uma ListaCliente para cada letra
 * do abecedário.
 */
typedef struct historial{
	ListaClientes avl[26];
	int total;
}historial;

/*========================================*/

/*
 * mes_filial
 * Esta estrutura contem a informação relativa
 * a um mes_filial
 */
typedef struct mes_filial{
	char codigo[6]; /*cod cliente*/
	int quantidade;	
}mes_filial;

/*
 * historico
 * Esta estrutura contem a informação relativa
 * a um historico
 */
typedef struct historico{
	ListaClientes clientesN;
	ListaClientes clientesP;
}historico;

/*
 * listaproduto
 * Esta estrutura contem a informação relativa
 * a um listaproduto
 */
typedef struct listaproduto{
	char produto[7];
	int quantidade_clientes;
	int quantidade_vendida;
	Historico h[12];
}listaproduto;

/*
 * vendasfilial
 * Esta estrutura contem 26 ListaVFilial. 
 * Ou seja, uma ListaVFilial para cada letra
 * do abecedário.
 */
typedef struct vendasfilial {
	ListaVFilial avl[26];	/*Divisao dos produtos em 26 avl's*/
	int total;
}vendasfilial;

/*========================================*/

/*GETS*/

/*
 * getVendasFilialLetra
 * retorna a ListaVFilial de uma dada letra.
 */
ListaVFilial getVendasFilialLetra (Filial vf, char ch) {
	return vf->avl[ch-'A'];
}

/*
 * getTotalVendasFilial
 * retorna o total de uma dada filial
 */
int getTotalVendasFilial (Filial vf) {
	return vf->total;
}

/*
 * getHistorico
 * retorna o historico de uma dada ListaProduto,
 * num dado mes
 */
Historico getHistorico(ListaProduto lp, int mes){
	return lp->h[mes];
}

/*
 * getCodigoListaProduto
 * devolve o codigo de produto de uma dada ListaProduto
 */
PRODUTO getCodigoListaProduto (ListaProduto p){
	return p->produto;
}

/*
 * getClientesN
 * retorna o total de clientes de um Historico,
 * em modo N
 */
ListaClientes getClientesN(Historico h){
	return h->clientesN;
}

/*
 * getClientesP
 * retorna o total de clientes de um Historico,
 * em modo P
 */
ListaClientes getClientesP(Historico h){
	return h->clientesP;
}

/*
 * getCodigoMesFilial
 * retorna o codigo de cliente, de um dado
 * Mes_Filial
 */
CLIENTE getCodigoMesFilial(Mes_Filial mf){
	return mf->codigo;
}

/*
 * getQuantidadeMesFilial
 * retorna a quantidade de um dado Mes_Filial
 */
int getQuantidadeMesFilial(Mes_Filial h){
	return h->quantidade;
}

/*
 * getListaVendasFilialN
 * retorna uma lista de strings de vendas numa
 * dada filial em modo N
 */
LISTA_STRING getListaVendasFilialN (Historico h, Filial vf) {
	LISTA_STRING s=NULL;
	if (vf!=NULL)
		s=toString(h->clientesN,vf->total);
	return s;
}

/*
 * getListaVendasFilialP
 * retorna uma lista de strings de vendas numa
 * dada filial em modo P
 */
LISTA_STRING getListaVendasFilialP (Historico h, Filial vf) {
	LISTA_STRING s=NULL;
	if (vf!=NULL)
		s=toString(h->clientesP,vf->total);
	return s;
}

/*
 * getQuantidadeVendida
 * retorna a quantidade vendida de uma dada
 * ListaProduto
 */
int getQuantidadeVendida(ListaProduto p){
	return p->quantidade_vendida;
}

/*
 * getQuantidadeClientes
 * retorna a quantidade de clientes de uma dada
 * ListaProduto
 */
int getQuantidadeClientes(ListaProduto p){
	return p->quantidade_clientes;
}

/*
 * getHistorialLetra
 * retorna a ListaClientes comecada por uma dada letrs
 */
ListaClientes getHistorialLetra (Historial h, char ch) {
	return h->avl[ch-'A'];
}

/*
 * getTotalHistorial
 * retorna o total de um dado Historial
 */
int getTotalHistorial(Historial h){
	return h->total;
}

/*
 * getCodigoHistorialCliente
 * retorna o codigo de cliente de um dado
 * HistorialCliente
 */
CLIENTE getCodigoHistorialCliente (HistorialCliente hc){
	return hc->cliente;
}
/*
 * getComprouFilial
 * retorna se um dado HistorialCliente foi comprado
 */
BOOLEAN getComprouFilial (HistorialCliente c) {
	return c->comprou_filial;
}

/*
 * getProdutosClientes
 * retorna a lista de string dos produtos comprados
 * por um dado cliente
 */
LISTA_STRING getProdutosCliente(HistorialCliente c){
	return c->produtos;
}

/*
 * getQuantidadeProdutos
 * retorna a quantidade de produtos comprados
 * por um dado cliente
 */
LISTA_INT getQuantidadeProdutos(HistorialCliente c){
	return c->quantidade;
}

/*
 * getMesVenda
 * retorna a lista de int num dado mes
 */
LISTA_INT getMesVenda(HistorialCliente c){
	return c->mes;
}

/*
 * getFaturacaoProdutos
 * retorna a faturacao de um dado HistorialCliente
 */
LISTA_FLOAT getFaturacaoProdutos(HistorialCliente c){
	return c->faturacao;
}

/*
 * getValorTabela
 * retorna o valor de um HistorialCliente, num dado mes
 */
int getValorTabela(HistorialCliente c, int mes){
	return c->tabela[mes];
}

/*SETS*/

/*
 * setCodigoListaProduto
 * copia um codigo s, para uma ListaProduto
 */
void setCodigoListaProduto (ListaProduto p, STRING s) {
	strcpy(p->produto,s);
}

/*
 * addVendasFilial
 * adiciona um valor ao total de vendas
 */
void addVendasFilial (Filial vf, int total) {
	vf->total+=total;
}

/*
 * setQuantidade
 * mete uma dada quantidade num Mes_Filail
 */
void setQuantidade(Mes_Filial mf, int quantidade){
	mf->quantidade=quantidade;
}

/*
 * addQuantidade
 * adiciona uma dada quantidade num Mes_Filail
 */
void addQuantidade(Mes_Filial mf, int quantidade){
	mf->quantidade+=quantidade;
}

/*
 * setCodigoClienteMesFilial
 * copia um dado codigo para um Mes_Filial
 */
void setCodigoClienteMesFilial(Mes_Filial mf, char *codigo){
	strcpy(mf->codigo,codigo);
}

/*
 * setAvlN
 * copia uma dada ListaClientes para um Historico
 */
void setAvlN(Historico h, ListaClientes a){
	h->clientesN=a;
}

/*
 * setAvlP
 * copia uma dada ListaClientes para um Historico
 */
void setAvlP(Historico h, ListaClientes a){
	h->clientesP=a;
}

/*
 * setQuantidadeVendida
 * adiciona uma dada quantidade qt ao total de quantidae
 * de uma dada ListaProduto
 */
void setQuantidadeVendida(ListaProduto p, int qt){
	p->quantidade_vendida+=qt;
}


/*
 * setQuantidadeClientes
 * adiciona uma dada quantidade de clientes qt ao total de 
 * clientes de uma dada ListaProduto
 */
void setQuantidadeClientes(ListaProduto p, int qt){
	p->quantidade_clientes+=qt;
}

/*
 * addHistorial
 * adiciona uma dada quantidade total ao total
 * de uma dada Historial
 */
void addHistorial (Historial h, int total) {
	h->total+=total;
}

/*
 * setCodigoHistorialCliente
 * copia um dado cliente s para um HistorialCliente
 */
void setCodigoHistorialCliente(HistorialCliente h, CLIENTE s){
	strcpy(h->cliente,s);
}

/*
 * setComprouFilial
 * esta funcao diz que um dado cliente comprou numa filial
 */
void setComprouFilial (HistorialCliente c, int filial) {
	c->comprou_filial=1;
}

/*
 * setFaturacaoProdutos
 * copia uma lista de floats para o Historial de um cliente
 */
void setFaturacaoProdutos(HistorialCliente c, LISTA_FLOAT faturacao){
	c->faturacao=faturacao;
}

/*funcoes comparacao*/

/*
 * vfcmp
 * Funcao de comparacao de duas ListaProduto
 */
int vfcmp (ListaProduto a, ListaProduto b) {
	return strcmp(a->produto,b->produto);
}

/*
 * vfcmpstr
 * Funcao de comparacao de uma ListaProduto
 * e uma String a
 */
int vfcmpstr (STRING a, ListaProduto b) {
	return strcmp(a,b->produto);
}

/*
 * mpcmp
 * Funcao de comparacao de dois Mes_Filial
 */
int mfcmp (Mes_Filial a, Mes_Filial b) {
	return strcmp(a->codigo,b->codigo);
}

/*
 * mfcmpstr
 * Funcao de comparacao de um Mes_Filial
 * e uma String a
 */
int mfcmpstr (STRING a, Mes_Filial b) {
	return strcmp(a,b->codigo);
}

/*
 * hccmp
 * Funcao de comparacao de dois HistorialCliente
 */
int hccmp (HistorialCliente a, HistorialCliente b) {
	return strcmp(a->cliente,b->cliente);
}

/*
 * hccmpstr
 * Funcao de comparacao de uma HistorialCliente
 * e uma String a
 */
int hccmpstr (STRING a, HistorialCliente b) {
	return strcmp(a,b->cliente);
}

/*funcoes*/

/*
 * initVendasFilial
 * Funcao de inicializacao de uma Filial
 */
Filial initVendasFilial(){
	int i;
	Filial vf = (Filial)malloc(sizeof(struct vendasfilial));
	
	for(i=0;i<26;i++)
		vf->avl[i]=NULL;

	return vf;
}

/*
 * initListaProduto
 * Funcao de inicializacao de uma ListaProduto
 */
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

/*
 * insertListaProduto
 * Funcao de insercao de uma ListaProduto numa filial
 */
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

/*
 * searchListaProduto
 * Funcao de procura numa dada Filial
 */
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

/*
 * initMesFilial
 * Funcao de inicializacao de um Mes_Filial
 */
Mes_Filial initMesFilial(){
	Mes_Filial mf = (Mes_Filial)malloc(sizeof(mes_filial));

	setCodigoClienteMesFilial(mf,"");
	setQuantidade(mf,0);

	return mf;
}

/*
 * initHistorial
 * Funcao de inicializacao de um Historial
 */
Historial initHistorial(){
	int i;
	Historial h = (Historial)malloc(sizeof(struct historial));
	
	for(i=0;i<26;i++)
		h->avl[i]=NULL;

	return h;
}

/*
 * initHistorialCliente
 * Funcao de inicializacao de um HistorialCliente
 */
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

/*
 * insertHistorialCliente
 * Funcao de insercao de um HistorialCliente
 */
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

/*
 * searchHistorialCliente
 * Funcao de procura de um HistorialCliente
 */
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

/*
 * atualizaHistorico
 * Funcao de atualizacao de uma dada Filial
 * através de uma Venda
 */
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

/*
 * updateCliente
 * Funcao que atualizacao de um dado HistorialCliente
 */
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

/*
 * freeFilial
 * Funcao que liberta a memoria ocupada
 * por uma dada filial e um dado historial
 */
void freeFilial(Filial f, Historial h){
	int i;

	for(i=0;i<26;i++){
		freeAVL(f->avl[i]);
		freeAVL(h->avl[i]);
	}
}
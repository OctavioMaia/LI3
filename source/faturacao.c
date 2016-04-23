#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/produtos.h"
#include "../headers/clientes.h"
#include "../headers/vendas.h"
#include "../headers/faturacao.h"

/*
 * informacao
 * Esta estrutura contem a informação relativa
 * a uma informacao
 */
typedef struct informacao{
	char produto[7];
	int vendas[12];
	int quantidadeN[12][3];
	int quantidadeP[12][3];
	float faturadoN[12][3];
	float faturadoP[12][3];
}informacao;

/*
 * faturacao
 * Esta estrutura contem 26 ListaFaturacao. 
 * Ou seja, uma ListaFaturacao para cada letra
 * do abecedário.
 */
typedef struct faturacao {
	ListaFaturacao avl[26];			/*Divisao das faturacoes em 26 AVL's*/
	int total;
}faturacao;

/*GETS*/

/*
 * getFaturacaoLetra
 * retorna a ListaFaturacao de uma dada letra.
 */
ListaFaturacao getFaturacaoLetra (Faturacao f, char ch) {
	return f->avl[ch-'A'];
}

/*
 * getCodigoProduto
 * retorna o codigo de produto de uma dada Informacao
 */
PRODUTO getCodigoProduto(Informacao i){
	return i->produto;
}

/*
 * getNumeroVendas
 * retorna o numero de vendas de uma dada Informacao num dado mes
 */
int getNumeroVendas(Informacao i, int mes){
	return i->vendas[mes];
}

/*
 * getQuantidadeNormal
 * retorna a quantidade de um produto vendida num dado mes
 * e numa dada filial em modo N
 */
int getQuantidadeNormal(Informacao i, int mes, int filial){
	return i->quantidadeN[mes][filial];
}

/*
 * getQuantidadePromocao
 * retorna a quantidade de um produto vendida num dado mes
 * e numa dada filial em modo P
 */
int getQuantidadePromocao(Informacao i, int mes, int filial){
	return i->quantidadeP[mes][filial];
}

/*
 * getFaturadoNormal
 * retorna a faturacao de um produto vendida num dado mes
 * e numa dada filial em modo N
 */
float getFaturadoNormal(Informacao i, int mes, int filial){
	return i->faturadoN[mes][filial];
}

/*
 * getFaturadoPromocao
 * retorna a faturacao de um produto vendida num dado mes
 * e numa dada filial em modo P
 */
float getFaturadoPromocao(Informacao i, int mes, int filial){
	return i->faturadoP[mes][filial];
}


/*
 * getTotalFaturacoes
 * retorna o total de todas as faturacoes
 */
int getTotalFaturacoes (Faturacao f) {
	return f->total;
}


/*
 * getListaFaturacaoLetra
 * retorna a lista de todas as faturacoes, começadas
 * por uma dada letra
 */
LISTA_STRING getListaFaturacaoLetra (Faturacao f, char ch) {
	LISTA_STRING s=NULL;
	if (f!=NULL)
		s=toString(getFaturacaoLetra(f,ch),f->total);
	return s;
}

/*SETS*/

/*
 * setCodigoProdutoFaturacao
 * copia o codigo de produto s para uma informação i
 */
void setCodigoProdutoFaturacao (Informacao i, PRODUTO s) {
	strcpy(i->produto,s);
}

/*
 * addQuantidadeVendasMes
 * adiciona a quantidade de vendas, num dado mes
 */
void addQuantidadeVendasMes(Informacao i, int mes, int quantidade){
	i->vendas[mes]+=quantidade;
}

/* addQuantidadeNormal
 * adiciona a quantidade normal a uma informacao i, 
 * num mes e numa dada filial
 */
void addQuantidadeNormal(Informacao i, int mes, int filial, int quantidade){
	i->quantidadeN[mes][filial]+=quantidade;
}

/* addQuantidadePromocao
 * adiciona a quantidade em promoção a uma informacao i, 
 * num mes e numa dada filial
 */
void addQuantidadePromocao(Informacao i, int mes, int filial, int quantidade){
	i->quantidadeP[mes][filial]+=quantidade;
}

/* addFaturadoNormal
 * adiciona a faturacao em modo normal a uma informacao i, 
 * num mes e numa dada filial
 */
void addFaturadoNormal(Informacao i, int mes, int filial, float faturado){
	i->faturadoN[mes][filial]+=faturado;
}

/* addFaturadoPromocao
 * adiciona a faturacao em modo promocao a uma informacao i, 
 * num mes e numa dada filial
 */
void addFaturadoPromocao(Informacao i, int mes, int filial, float faturado){
	i->faturadoP[mes][filial]+=faturado;
}

/* addFaturacao
 * adiciona um dado numero, ao total das faturacoes
 */
void addFaturacao (Faturacao f, int total) {
	f->total+=total;
}

/*funcoes comparacao*/

/* infcmp
 * funcao de comparacao entre duas Informacao
 */
int infcmp (Informacao a, Informacao b) {
	return strcmp(a->produto,b->produto);
}

/* infcmpstr
 * funcao de comparacao entre uma informacao
 * e um produto
 */
int infcmpstr (PRODUTO a, Informacao b) {
	return strcmp(a,b->produto);
}

/*funcoes*/

/* initFaturacao
 * funcao de inicialiação de uma Faturacao
 */
Faturacao initFaturacao(){
	int i;
	Faturacao f = (Faturacao)malloc(sizeof(struct faturacao));

	for(i=0;i<26;i++)
		f->avl[i]=NULL;

	return f;
}

/* initInformacao
 * funcao de inicialiação de uma Informacao
 */
Informacao initInformacao(){
	int i,j;
	Informacao info = (Informacao)malloc(sizeof(struct informacao));

	for(i=0;i<12;i++){
		info->vendas[i]=0;
		for(j=0;j<3;j++){
			info->quantidadeN[i][j]=0;
			info->quantidadeP[i][j]=0;
			info->faturadoN[i][j]=0;
			info->faturadoP[i][j]=0;
		}
	}

	return info;
}

/* insertInformacao
 * funcao de inserção de uma um codigo s
 * na Faturacao
 */
Faturacao insertInformacao(Faturacao f, PRODUTO s) {
	int i, pos=s[0]-'A';
	Informacao aux = initInformacao();
	setCodigoProdutoFaturacao(aux,s);

	if (f==NULL) {	/*Se não existir a estrutura, criá-la*/
		f=initFaturacao();
		for (i=0; i<26; i++) 
			f->avl[i]=NULL;
		f->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	f->avl[pos]=inserirAVL(f->avl[pos],aux,&i,(int (*)(void*,void*))infcmp);
	return f;
}

/* searchInformacao
 * funcao de procura de uma informacao através
 * de um código de produto s
 */
Informacao searchInformacao(Faturacao f, PRODUTO s) {
	Informacao p1=NULL;
	ListaFaturacao aux=procurarAVL(f->avl[s[0]-'A'],s,(int (*)(void*,void*))infcmpstr);
	if (aux!=NULL) {
		/*printf("encontrei %s\n",s);*/
		p1=getData(aux);
		return p1;
	}else{
		return NULL;
	}
}

/*funcoes de atualizacao*/

/* atualizaFaturacao
 * funcao que atualiza as faturacoes de um dado
 * produto, através de uma Venda
 */
void atualizaFaturacao(Faturacao f, Produtos p, Venda v){
	Informacao i = searchInformacao(f,getProduto(v));
	int quantidade = getQuantidade(v);
	float preco = getPreco(v);
	int mes = getMes(v);
	int filial = getFilial(v);

	addQuantidadeVendasMes(i,mes-1,1);

	if(getPromo(v)=='N'){
		addQuantidadeNormal(i,mes-1,filial-1,quantidade);
		addFaturadoNormal(i,mes-1,filial-1,preco*quantidade);
		/*printf("NORMAL %s Q:%d F:%f\n", getProduto(i), getQuantidadeNormal(i,mes-1,filial-1), getFaturadoNormal(i,mes-1,filial-1));*/
	}else{
		addQuantidadePromocao(i,mes-1,filial-1,quantidade);
		addFaturadoPromocao(i,mes-1,filial-1,preco*quantidade);
		/*printf("PROMO %s Q:%d F:%f\n",getProduto(i), getQuantidadePromocao(i,mes-1,filial-1), getFaturadoPromocao(i,mes-1,filial-1));*/
	}
}


/* nuncaCompradoGlobal
 * funcao que retorna um booleano caso essa informacao
 * tenha sido comprada
 */
BOOLEAN nuncaCompradoGlobal(Informacao i){
	int quantidadeN=0,quantidadeP=0,m,f;
	for(m=0;m<12;m++){
		for(f=0;f<3;f++){
			quantidadeN+=getQuantidadeNormal(i,m,f);
			quantidadeP+=getQuantidadePromocao(i,m,f);
		}
	}
	return quantidadeN+quantidadeP;
}

/* nuncaCompradoFilial
 * funcao que retorna um boleano caso essa informacao
 * tenha sido comprada, numa dada filial
 */
BOOLEAN nuncaCompradoFilial(Informacao i, int filial){
	int quantidadeN=0,quantidadeP=0,m;
	for(m=0;m<12;m++){
		quantidadeN+=getQuantidadeNormal(i,m,filial-1);
		quantidadeP+=getQuantidadePromocao(i,m,filial-1);	
	}
	return quantidadeN+quantidadeP;
}

/* freeFaturacao
 * funcao que liberta a memoria ocupada por uma dada Faturacao
 */
void freeFaturacao(Faturacao f){
	int i;

	for(i=0;i<26;i++){
		freeAVL(f->avl[i]);
	}
}
#include <stdio.h>
#include <stdlib.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"
#include "../headers/produtos.h"
#include "../headers/vendas.h"

/*
 * venda
 * Esta estrutura contem a informação relativa
 * a uma venda, ou seja, o código do produto, 
 * o preço do produto, a quantidade vendida, 
 * o tipo de compra N ou P, o código do
 * cliemte, o mes e a filial.
 */
typedef struct venda {
	char produto[7];
	float preco;
	int quant;
	char promo;
	char cliente[6];
	int mes;
	int filial;
}venda;

/* -------------------
   Funções de consulta
   -------------------
*/

/*
 * getProduto
 * retorna o código do produto.
 */
PRODUTO getProduto(Venda v){
	return v->produto;
}

/* 
 * getPreco
 * devolve o preço de um produto.
 */
float getPreco (Venda v) {
	return v->preco;
}

/*
 * getQuantidade
 * retorna a quantidade vendida do produto 
 */
int getQuantidade (Venda v) {
	return v->quant;
}

/* 
 * getPromo
 * retorna o tipo do produto, N ou P
 */
char getPromo(Venda v){
	return v->promo;
}

/* 
 * getCliente
 * devolve código do cliente que fez compra
 */
CLIENTE getCliente(Venda v){
	return v->cliente;
}

/* 
 * getMes
 * devolve mes em que a compra foi efetuada
 */
int getMes (Venda v) {
	return v->mes;
}

/* 
 * getFilial
 * devolve a filial em que a compra ocorreu.
 */
int getFilial (Venda v) {
	return v->filial;
}

/* ----------------------
   Funções de modificação
   ----------------------
*/

/* 
 * initVenda
 * inicializa da estrutura Venda
*/
Venda initVenda (STRING s) {
	Venda v=(Venda)malloc(sizeof(struct venda));
	sscanf(s,"%s %f %d %c %s %d %d",v->produto,&v->preco,&v->quant,&v->promo,v->cliente,&v->mes,&v->filial);	
	return v;
}

/* validaVenda
 * verifica se uma determinada venda é válida.
 */
BOOLEAN validaVenda (Venda v, Produtos prod, Clientes cli) {
	if (v->preco<0 || v->quant<0) return 0;
	if (v->mes<1 || v->mes>12) return 0;
	if (v->filial != 1 && v->filial != 2 && v->filial != 3) return 0;
	if (v->promo!='N' && v->promo!='P') return 0;
	if (!searchProduto(prod,v->produto)) return 0;
	if (!searchCliente(cli,v->cliente)) return 0;
	return 1;	
}
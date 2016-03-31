#include <stdio.h>
#include <stdlib.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/clientes.h"
#include "../headers/produtos.h"
#include "../headers/vendas.h"

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
PRODUTO getProduto(Venda v){
	return v->produto;
}

float getPreco (Venda v) {
	return v->preco;
}

int getQuantidade (Venda v) {
	return v->quant;
}

char getPromo(Venda v){
	return v->promo;
}

CLIENTE getCliente(Venda v){
	return v->cliente;
}

int getMes (Venda v) {
	return v->mes;
}

int getFilial (Venda v) {
	return v->filial;
}

/* ----------------------
   Funções de modificação
   ----------------------
*/
Venda initVenda (STRING s) {
	Venda v=(Venda)malloc(sizeof(struct venda));
	sscanf(s,"%s %f %d %c %s %d %d",v->produto,&v->preco,&v->quant,&v->promo,v->cliente,&v->mes,&v->filial);	
	return v;
}

int validaVenda (Venda v, Produtos prod, Clientes cli) {
	if (v->preco<0 || v->quant<0) return 0;
	if (v->mes<1 || v->mes>12) return 0;
	if (v->filial != 1 && v->filial != 2 && v->filial != 3) return 0;
	if (v->promo!='N' && v->promo!='P') return 0;
	if (!searchProduto(prod,v->produto)) return 0;
	if (!searchCliente(cli,v->cliente)) return 0;
	return 1;	
}
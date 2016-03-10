#include <stdio.h>
#include <stdlib.h>
#include "../headers/AVL.h"
#include "../headers/produtos.h"
#include "../headers/clientes.h"
#include "../headers/vendas.h"
#include "../headers/faturacao.h"

typedef struct venda {
	char produto[6];
	float preco;
	int quant;
	char promo;
	char cliente[5];
	int mes;
	int filial;
}venda;

/*            ====================================
              Funções relativas à estrutura Venda
              ====================================
 */

/* -------------------
   Funções de consulta
   -------------------
*/
float getPreco (Venda c) {
	return c->preco;
}

int getQuantidade (Venda c) {
	return c->quant;
}

char getPromo(Venda c){
	return c->promo;
}

int getMes (Venda c) {
	return c->mes;
}

int getFilial (Venda c) {
	return c->filial;
}

/* ----------------------
   Funções de modificação
   ----------------------
*/
Venda initVenda (char *s) {
	Venda c=(Venda)malloc(sizeof(struct venda));
	sscanf(s,"%s %f %d %c %s %d %d",c->produto,&c->preco,&c->quant,&c->promo,c->cliente,&c->mes,&c->filial);	
	return c;
}

int validaVenda (Venda c, Produtos prod, Clientes cli) {
	if (c->preco<0 || c->quant<0) return 0;
	if (c->mes<1 || c->mes>12) return 0;
	if (c->filial != 1 && c->filial != 2 && c->filial != 3) return 0;
	if (c->promo!='N' && c->promo!='P') return 0;
	if (!searchProduto(prod,c->produto)) return 0;
	if (!searchCliente(cli,c->cliente)) return 0;
	return 1;	
}

/*
Faturacao updateProduto (Faturacao p, Venda c) {
	if (c->promo=='N') {
		incNormalProduto(p,c->mes-1,1,c->filial-1);
		incQuantNormalProduto(p,c->mes-1,c->quant,c->filial-1);
		addClienteNormalProduto(p,c->mes-1,c->cliente,c->filial-1);
	}
	else {
		
		incPromoProduto(p,c->mes-1,1,c->filial-1);
		incQuantPromoProduto(p,c->mes-1,c->quant,c->filial-1);
		addClientePromoProduto(p,c->mes-1,c->cliente,c->filial-1);
	}
	incReceitaProduto(p,c->mes-1,c->preco*c->quant,c->filial-1);
	return p;	
}

int updateProdutos (Produtos p, Venda c) {
	Faturacao p1 = searchProduto(p,c->produto);
	if (p1!=NULL) {
		p1=updateProduto(p1,c);
		return 1;
	}else{
		return 0;
	} 
}

Cliente updateCliente (Cliente c, Venda venda) {
	int filial = venda->filial;
	incNProdutosCliente(c,venda->mes-1,venda->quant,filial-1);
	addProdutoCliente(c,venda->mes-1,venda->produto,filial-1);
	return c;
}

int updateClientes (Clientes c, Venda venda) {
	Cliente c1 = searchCliente(c,venda->cliente);
	if (c1!=NULL) {
		c1=updateCliente(c1,venda);
		return 1;
	}
	else return 0;
}
*/
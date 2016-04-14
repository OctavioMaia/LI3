#ifndef PRODUTO_H /* corresponde ao ficheiro produtos.h */
#define PRODUTO_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct nodo *ListaProdutos;

typedef struct produtos *Produtos;
typedef struct produto *Produto;

typedef char* PRODUTO;

/*            ======================================
              Funções relativas à estrutura Produtos
              ======================================
 */

/* -------------------
   Funções de consulta
   -------------------
*/
ListaProdutos getProdutosLetra (Produtos p, char ch);
int getTotalProdutos (Produtos p);
PRODUTO getCodProduto(Produto p);
LISTA_STRING  getListaProdutosLetra (Produtos p, char ch);
LISTA_STRING  getListaTodosProdutos (Produtos p);
/* ----------------------
   Funções de modificação
   ----------------------
*/
void setProdutos (Produtos p, int n);
void addProdutos (Produtos p, int n);

/* -----------------------------------
   Funções de manipulação dos Produtos
   -----------------------------------
*/
Produto initProduto();
Produtos initProdutos();
Produtos insertProduto (Produtos p, PRODUTO s);
Produto searchProduto(Produtos p, PRODUTO s);
Produtos removeProduto(Produtos p, PRODUTO s);

#endif
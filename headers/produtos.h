/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaProdutos;

typedef struct produtos *Produtos;
typedef struct produto *Produto;

/*            ======================================
              Funções relativas à estrutura Produtos
              ======================================
 */

/* -------------------
   Funções de consulta
   -------------------
*/
AVL getProdutosLetra (Produtos p, char ch);
char* getCodProduto(Produto p);
int getTotalProdutos (Produtos p);
int getQuantidadeVendidaFilial(Produto p, int filial);
int getQuantidadeVendida(Produto p);
int getQuantidadeClientes(Produto p);
LISTA  getListaProdutosLetra (Produtos p, char ch);
LISTA  getListaTodosProdutos (Produtos p);

/* ----------------------
   Funções de modificação
   ----------------------
*/
void setProdutos (Produtos p, int n);
void addProdutos (Produtos p, int n);
void setQuantidadeVendidaFilial(Produto p, int filial, int qt);
void setQuantidadeClientes(Produto p, int qt);

/* -----------------------------------
   Funções de manipulação dos Produtos
   -----------------------------------
*/
Produto initProduto();
Produtos initProdutos();
Produtos insertProduto (Produtos p, char *s);
Produto searchProduto(Produtos p, char *s);
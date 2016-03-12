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
int getTotalProdutos (Produtos p);
char** getListaProdutosLetra (Produtos p, char ch);
char** getListaTodosProdutos (Produtos p);

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
Produtos insertProduto (Produtos p, char *s);
Produto searchProduto(Produtos p, char *s);
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

/* getProdutosLetra
 * Devolve uma AVL cujos nós contém código dos produtos que 
 * começam por uma determinada letra.
 * @parametros - Apontador para catálogo produtos - Produtos p
 *               Letra que se pretende efetuar procura - char ch
 * @return - Apontador para nó de AVL
 */
ListaProdutos getProdutosLetra (Produtos p, char ch);

/* getTotalProdutos
 * Devolve o número de produtos existentes no catálogo.
 * @parametros - Apontador para catálogo de produtos - Produtos p
 * @return - Número de produtos existentes no catálogo.
 */
int getTotalProdutos (Produtos p);

/* getCodProduto
 * Esta função devolve o código de um produto.
 * @parametros - Apontador para produto - Produto p
 * @return - Código do produto.
 */
PRODUTO getCodProduto(Produto p);

/*getListaProdutosLetra
 * Esta função devolve uma lista com os códigos dos produtos
 * existentes no catálogo cujo código começa por uma determinada letra.
 * @parametros - Apontador para catálogo de produtos - Produtos p
 *               Letra que se pretende que a procura seja efetuada - char ch
 * @return - Lista com código dos produtos.
 */
LISTA_STRING  getListaProdutosLetra (Produtos p, char ch);

/*getListaTodosProdutos
 * Esta função devolve uma lista com os códigos dos produtos
 * existentes no catálogo 
 * @parametros - Apontador para catálogo de produtos - Produtos p
 * @return - Lista com código dos produtos.
 */
LISTA_STRING  getListaTodosProdutos (Produtos p);
/* ----------------------
   Funções de modificação
   ----------------------
*/

/* setProdutos
 * Altera o número de produtos existentes no catálogo.
 * @parametros - Apontador para catálogo de produtos - Produtos p
 *               Nova quantidade de produtos - int total
 */
void setProdutos (Produtos p, int n);

/* addProdutos
 * Adiciona uma quantidade ao total de produtos do catálogo.
 * @parametros - Apontador para catálogo produtos - Produtos p
 *               Total de produtos a acrescentar - int total
 */
void addProdutos (Produtos p, int n);

/* -----------------------------------
   Funções de manipulação dos Produtos
   -----------------------------------
*/

/* initProdutos()
 * Inicia a estrutura Produtos inicializando as 26 posicoes do array
 * a NULL.
 * @return - Apontador para catálogo de produtos
 */
Produto initProduto();

/* initProduto
 * Esta funcao inicializa um produto.
 * @return - Apontador para produto.
 */
Produtos initProdutos();

/* insertProduto
 * Esta funcao insere um produtono catálogo.
 * @parametros - Apontador para catálogo de produto.
 *             - Código do produto que se pretende inserir.
 * @return - Apontador para catálogo de produtos.
 */
Produtos insertProduto (Produtos p, PRODUTO s);

/* searchProduto
 * Esta funcao procura se o codigo de um produto existe no catalogo.
 * @parametros - Apontador para catalogo Produto - Produtos c
                 Código do produto que se pretende procurar - PRODUTO s.
   @return - Apontador para Produto
             Se o produto não existir - NULL              
 */
Produto searchProduto(Produtos p, PRODUTO s);

/* removeProduto
 * Esta funcao remove um produto do catálogo Produtos
 *  @parametros - Apontador para catálogo - Produtos p
                  Código do produto que se pretende remover - PRODUTO s.
   @return - Apontador para catálogo Produtos             
 */
Produtos removeProduto(Produtos p, PRODUTO s);

/* freeClientes
 * Liberta memória ocupada pelo catálogo Produtos
 */
void freeProdutos(Produtos p);
#endif
#ifndef VENDAS_H /* corresponde ao ficheiro vendas.h */
#define VENDAS_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

typedef struct venda *Venda;

/* getCliente
 * Devolve o CLIENTE relativo à informação de uma venda
 * @parametros - Apontador para venda - Venda v
 * @return - Código de CLIENTE
 */
CLIENTE getCliente(Venda v);

/* getProduto
 * Devolve o produto relativo à informação de uma venda
 * @parametros - Apontador para venda - Venda v
 * @return - Código do produto
 */
PRODUTO getProduto(Venda v);

/* getPreco
 * Devolve o preço de um produto.
 * @parametros  - Apontador para venda - Venda v
 * @return - Preço do produto 
 */
float getPreco (Venda c);

/* getPromo
 * Verifica se o produto é do tipo normal ou promoção
 * @parametros - Apontador para venda - Venda v
 * @return - Indicador se produto é do tipo P ou N
 */
char getPromo(Venda c);

/* getMes
 * Devolve mes em que a compra foi efetuada
 * @parametros - Apontador para venda - Venda v
 * @return - Mes em que a venda foi realizada
 */
int getMes (Venda c);

/* getFilial
 * Devolve a filial em que o produto foi vendido
 * @parametros - Apontador para venda - Venda v
 * @return - Filial em que produto foi vendido
 */
int getFilial (Venda c);

/* getQuantidade
 * Retorna a quantidade vendida de um produto numa determinada venda
 * @parametros - Apontador para venda - Venda v
 * @return -  Quantidade vendida de um produto numa determinada venda
 */
int getQuantidade (Venda c);

/* initVenda
 * Inicializa uma venda
 * @parametros - Linha do ficheiro vendas
 * @return - Apontador para Venda
 */
Venda initVenda (STRING s);

/* validaVenda
 * Verifica se uma determinada linha do ficheiro vendas é valido, ou seja, 
 * se o preço é maior que 0 e a quantidade maior 0, verifica se o mes é valido,
 * verifica se a filial e válida, verifica se o tipo do produto é valido, 
 * verifica se o código de cliente e produto existe.
 * @return - Boolean corresponde se a venda é valida 1, ou 0 caso contrário
 */
BOOLEAN validaVenda (Venda c, Produtos prod, Clientes cli);

#endif
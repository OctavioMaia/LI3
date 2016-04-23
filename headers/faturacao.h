#ifndef FATURACAO_H /* corresponde ao ficheiro faturacao.h */
#define FATURACAO_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct nodo *ListaFaturacao;

typedef struct informacao *Informacao;
typedef struct faturacao *Faturacao;

/* getFaturacaoLetra
 * Devolve o catalogo de faturacao dos produtos que cujo codigo
 * comeca por uma determinada letra.
 */
ListaFaturacao getFaturacaoLetra (Faturacao f, char ch);

/* getCodigoProduto
 * Devolve o codigo de um produto referente a Informacao i.
 */
PRODUTO getCodigoProduto(Informacao i);

/* getNumeroVendas
 * Esta função retorna a quantidade vendida de um produto num
 * determinado mes.
 */
int getNumeroVendas(Informacao i, int mes);

/* getQuantidadeNormal
 * Esta funcao devolve a quantidade vendida de um produto do 
 * tipo Normal, num determinado mes e filial.
 */
int getQuantidadeNormal(Informacao i, int mes, int filial);

/* getQuantidadePromocao
 * Esta funcao devolve a quantidade vendida de um produto do
 * tipo Promocao, num determinado mes e filial.
 */
int getQuantidadePromocao(Informacao i, int mes, int filial);

/* getFaturadoNormal
 * Esta funcao devolve o valor faturado de um produto do tipo
 * Normal, num determinado mes e filial.
 */
float getFaturadoNormal(Informacao i, int mes, int filial);

/* getFaturadoPromocao
 * Esta funcao devolve o valor faturado de um produto do tipo
 * Promocao, num determinado mes e filial.
 */
float getFaturadoPromocao(Informacao i, int mes, int filial);

/* getTotalFaturacoes
 * Esta funcao devolve o numero de faturacoes existentes.
 */
int getTotalFaturacoes (Faturacao f);

/* getListaFaturacaoLista
 * Esta funcao devolve uma lista com as faturacoes cujos codigos dos 
 * produtos se iniciem por uma determinada letra. 
 */
LISTA_STRING  getListaFaturacaoLetra (Faturacao f, char ch);

/* setCodigoProdutoFaturacao
 * Esta funcao altera o codigo de um produto de uma faturacao.
 */
void setCodigoProdutoFaturacao (Informacao i, PRODUTO s);

/* addQuantidadeNormal
 * Acrescenta à quantidade vendida de um produto do tipo normal num mes e filial 
 * uma determinada qt.
 * @parametros - Apontador para informação do produto - Informação i
 *               Mes relativo a venda - int mes
 *               Filial correspondente - int filial
 *               Quantidade que se pretende adicionar - int quantidade
 */
void addQuantidadeNormal(Informacao i, int mes, int filial, int quantidade);

/* addQuantidadePromocao
 * Acrescenta à quantidade vendida de um produto do tipo promoção num mes uma 
 * determinada qt.
 * @parametros - Apontador para informação do produto - Informação i
 *               Mes relativo a venda - int mes
 *               Filial correspondente - int filial
 *               Quantidade que se pretende adicionar - int quantidade
 */
void addQuantidadePromocao(Informacao i, int mes, int filial, int quantidade);

/* addFaturacaoNormal
 * Acrescenta à faturação de um produto do tipo normal num mes e filial uma 
 * determinada quantia.
 * @parametros - Apontador para informação do produto - Informação i
 *               Mes relativo a venda - int mes
 *               Filial correspondente - int filial
 *               Quantia que se pretende adicionar - float faturado
 */
void addFaturadoNormal(Informacao i, int mes, int filial, float faturado);

/* addFaturadoPromocao
 * Acrescenta à faturação vendida de um produto do tipo promoção num mes e filial
 * uma determinada quantia.
 * @parametros - Apontador para informação do produto - Informação i
 *               Mes relativo a venda - int mes
 *               Filial correspondente - int filial
 *               Quantia que se pretende adicionar - float faturado
 */
void addFaturadoPromocao(Informacao i, int mes, int filial, float faturado);

/* addFaturacao
 * Acrescenta um determinado valor ao número de faturações
 * @parametros - Apontador para Faturacao - Faturacao f
  				 Valor que se pretende acrescentar - int total
 */ 
void addFaturacao (Faturacao f, int total);

/*funcoes*/

/* initClientes()
 * Inicia a Faturacao inicializando as 26 posicoes do array
 * a NULL.
 * @return - Apontador para Faturacao
 */
Faturacao initFaturacao();

/* initInformacao
 * Inicializa a informação de um produto
 * @return - Apontador para Informação
 */
Informacao initInformacao();

/* insertInformacao
 * Insere informação relativa a faturação de um produto no catálogo Faturação
 * @parametros - Apontador para catálogo Faturação - Faturacao f
 * 				 Código do produto que se pretende inserir - PRODUTO s
 * @return - Apontador para Faturacao
 */
Faturacao insertInformacao(Faturacao f, PRODUTO s);

/* searchInformacao
 * Procura informação sobre a faturação de um determinado produto, cujo código
 * é passado como parametro.
 * @parametros - Apontador para faturacao - Faturacao f
 *				 Código do produto que se pretende fazer procura - PRODUTO s
 * @return - Apontador para Informacao caso exista, NULL caso contrário
 */
Informacao searchInformacao(Faturacao f, PRODUTO s);

/*funcoes de atualizacao*/

/* atualizaFaturacao
 * Esta função atualiza as informações de  faturação de um produto 
 * relativamente a uma venda. Verifica o tipo de produto (N ou P)
 * e incrementa a quantidade e a faturação. 
 * @parametros - Apontador para faturação - Faturacao f
 *               Apontador para catálogo de produtos - Produtos p
 *               Apontador para venda - Venda v
 */
void atualizaFaturacao(Faturacao f, Produtos p, Venda v);

/* nuncaCompradoGlobal
 * Verifica se um produto já foi comprado
 * @parametros- Apontador para informação do produto
 * @return - Returna um booleano corresponde a informação calculada
 */
BOOLEAN nuncaCompradoGlobal(Informacao i);

/* nuncaCompradoGlobal
 * Verifica se um produto já foi comprado numa determinada filial
 * @parametros- Apontador para informação do produto
 * @return - Returna um booleano corresponde a informação calculada
 */
BOOLEAN nuncaCompradoFilial(Informacao i, int filial);

/* freeFaturacao
 * Liberta memória alocada para módulo Faturação.
 */
void freeFaturacao(Faturacao f);
#endif
#ifndef FILIAL_H /* corresponde ao ficheiro filial.h */
#define FILIAL_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct nodo *ListaVFilial;

typedef struct mes_filial *Mes_Filial;
typedef struct historico *Historico;
typedef struct vendasfilial *Filial;
typedef struct listaproduto *ListaProduto;
typedef struct historialcliente *HistorialCliente;
typedef struct historial *Historial;

/*---*/

/* getVendasFilialLetra
 * Devolve um apontador para o nó cujo códido dos produtos
 * começa por uma determinada letra.
 * @parametros - Apontador para filial - Filial vf
 *             - Letra que se pretende que a pesquisa seja feita - char ch
 * @return - Apontador para AVL.
 */
ListaVFilial getVendasFilialLetra (Filial vf, char ch);

/* getHistorico
 * Devolve um apontador para histórico que contém as listas de clientes
 * que compraram num determinado mes.
 * @parametro - Apontador para Lista de produto - ListaProduto lp
 *            - Mes que se pretende que a pesquisa seja feita - int mes
 * @return - Apontador para Historico que contém listas de clientes que 
 *           que compraram o produto do tipo P e N.
 */
Historico getHistorico(ListaProduto lp, int mes);

/*ints*/

/* getTotalVendasFilial 
 * Devolve o total de nós presentes no módulo vendas por filial.
 * @parametros - Apontador para módulo vendas por filial - Filial vf
 * @return - Total de nós presentes no módulo vendas por filial.
 */
int getTotalVendasFilial (Filial vf);

/* getQuantidadeVendida
 * Devolve a quantidade vendida um determinado produto
 * @parametros - Apontador para ListaProduto que contem informação relativa
 *               a relação entre um produto e os clientes que o comparam - ListaProduto p
 * @return - Quantidade de produtos vendida
 */
int getQuantidadeVendida(ListaProduto p);

/* getQuantidadeClientes
 * Devolve a quantidade de clientes que compraram um determinado produto
 * @parametros - Apontador para ListaProduto que contem informação relativa
 *               a relação entre um produto e os clientes que o comparam - ListaProduto p
 * @return - Quantidade de clientes que compraram o produto
 */
int getQuantidadeClientes(ListaProduto p);

/* getTotalHistorial
 * Devolve o número de nós da estrutura Historial.
 * @parametros - Apontador para estrutura Historial - Historial h
 * @return - Devolve o número de nós da estrutura Historial.
 */
int getTotalHistorial(Historial h);

/* getComprouFilial
 * Devolve se o cliente fez compras numa determinada filial à estrutura HistorialCliente
 * que relaciona um cliente com os produtos que comprou - HistorialCliente hc
 * @parametros - Apontador para estrurura HistotialCliente que relaciona um cliente com 
 *               os produtos que comprou - HistorialCliente hc
 * @return - 0 ou 1, que representam se um cliente comprou ou não
 *           comprou numa determinada filial
 */
int getComprouFilial (HistorialCliente c);

/* getValorTabela
 * Verifica se um cliente comprou num determinado mes.
 * @parametros - Apontador para HistorialCliente c
 *               Mes que pretende fazer pesquisa - int mes
 * @return - BOOLEAN correspondente a se comprou ou não.
 */
BOOLEAN getValorTabela(HistorialCliente c, int mes);

/*listas*/

/* getClientesN
 * Devolve a lista de clientes que compraram um determinado produto
 * do tipo Normal
 * @parametros - Apontador para histórico que contém as listas de clientes
 *               que compraram um produto do tipo N e P.
 * @return - Lista de Clientes que compraram um produto do tipo normal
 */
ListaClientes getClientesN(Historico h);

/* getClientesP
 * Devolve a lista de clientes que compraram um determinado produto
 * do tipo Promoção
 * @parametros - Apontador para histórico que contém as listas de clientes
 *               que compraram um produto do tipo N e P.
 * @return - Lista de Clientes que compraram um produto do tipo promoção
 */
ListaClientes getClientesP(Historico h);

/* getHistorialLetra
 * Devolve um apontador para nó de AVL cujos códigos de cliente começem
 * por uma determinada letra - char ch
 */
ListaClientes getHistorialLetra (Historial h, char ch);

/* getCodigoHistorialCliente
 * Devolve o código de cliente relativo à estrutura HistorialCliente
 * que relaciona um cliente com os produtos que comprou - HistorialCliente hc
 * @parametros - Apontador para estrurura HistotialCliente hc
 * @return - Código de cliente
 */
CLIENTE getCodigoHistorialCliente (HistorialCliente hc);

/* getCodigoMesFilial
 * Devolve o código de um cliente.
 * @parametros - Apontador para estrutura que relaciona um cliente com a quantidade
 *               de produtos comprados - Mes_Filial mf
 * @return - Código de um cliente.
 */
CLIENTE getCodigoMesFilial(Mes_Filial mf);

/* getProdutosCliente
 * Devolve uma lista com os códigos dos produtos que um cliente comprou
 * @parametros - Apontador para estrurura HistotialCliente que relaciona um cliente com 
 *               os produtos que comprou - HistorialCliente hc
 * @return - Lista com os códigos dos produtos comprados por um cliente 
 */
LISTA_STRING  getProdutosCliente(HistorialCliente c);

/* getListaVendasFilialN
 * Devolve uma lista com todos os clientes que compraram um produto numa
 * filial do tipo Normal.
 * @parametros - Apontador para Historico - Historico h
 *             - Apontador para Filial - Filial vf
 * @return - Lista com clientes que compraram produtos do tipo N
 */
LISTA_STRING getListaVendasFilialN (Historico h, Filial vf);

/* getListaVendasFilialP
 * Devolve uma lista com todos os clientes que compraram um produto numa
 * filial do tipo Promoção.
 * @parametros - Apontador para Historico - Historico h
 *             - Apontador para Filial - Filial vf
 * @return - Lista com clientes que compraram produtos do tipo P
 */
LISTA_STRING getListaVendasFilialP (Historico h, Filial vf);

/* getQuantidadeProdutos
 * Devolve uma lista com as quantidades dos produtos que um cliente comprou
 * @parametros - Apontador para estrurura HistotialCliente que relaciona um cliente com 
 *               os produtos que comprou - HistorialCliente hc
 * @return - Lista com as quantidades dos produtos comprados por um cliente 
 */
LISTA_INT getQuantidadeProdutos(HistorialCliente c);

/* getMesVenda
 * Devolve uma lista com os meses em que cliente comprou
 * @parametros - Apontador para estrurura HistotialCliente que relaciona um cliente com 
 *               os produtos que comprou - HistorialCliente hc
 * @return - Lista com os meses em que cliente comprou
 */
LISTA_INT getMesVenda(HistorialCliente c);

/* getFaturacaoProdutos
 * Devolve uma lista com as faturações relativas a um produto
 * @parametros - Apontador para estrurura HistotialCliente que relaciona um cliente com 
 *               os produtos que comprou - HistorialCliente hc
 * @return - Lista com as faturações relativas a um produto
 */
LISTA_FLOAT getFaturacaoProdutos(HistorialCliente c);

/*funcoes*/

/* initVendasFilial()
 * Inicializa a estrutura VendasFilial alocando memória.
 */
Filial initVendasFilial();

/* insertListaProduto
 * Insere um produto na estrutura Filial
 */
Filial insertListaProduto(Filial f, PRODUTO s);

/* initListaProduto()
 * Inicializa a estrutura ListaProduto alocando memória
 */

ListaProduto initListaProduto();

/* searchListaProduto
 * Procura se o código de um produto passado como parametro se encontra
 * na estrutura Filial
 */
ListaProduto searchListaProduto(Filial f, PRODUTO s);

/* initHistorial
 * Inicializa a estrutura Historial alocando memória
 */
Historial initHistorial();

/* insertHistorialCliente
 * Insere um cliente na estrutura Historial 
 */
Historial insertHistorialCliente(Historial f, STRING s);

/* initHistorialCliente()
 * Aloca memórria para a estrutura HistorialCliente() alocando memória
 */
HistorialCliente initHistorialCliente();

/* searchHistorialCliente
 * Verifica se um cliente passado o seu código como parametro se encontra na estrutura
 * Historial
 */
HistorialCliente searchHistorialCliente(Historial f, STRING s);

/*funcoes void*/
/* addHistorial
 * Adiciona um número de nós passado como parametro a estrutura Historial
 */
void addHistorial (Historial h, int total);

/* atualizaHistorico
 * Atualiza uma Filial de acordo com uma venda
 * @parametros - Apontador para Filial vf
 *               Venda que vai fazer com que haja update na filial - Venda v
 */
void atualizaHistorico(Filial vf, Venda v);

/* addVendasFilial
 * Adiciona uma quantidade ao número de nós existentes na estrutura Filial
 * @parametros - Apontador para estrutura Filial vf
 *               Quantidade a adicionar - int total
 */
void addVendasFilial (Filial vf, int total);

/* setFaturacaoProdutos
 * Altera a lista de faturação da estrutura HistorialCliente para a lista passada como
 * parametro.
 */
void setFaturacaoProdutos(HistorialCliente c, LISTA_FLOAT faturacao);

/* updateCliente
 * Atualiza o Historial de um cliente de acordo com uma venda.
 * @parametros- Apontador para Historial h
 *              Apontador para Filial vf
 *              Venda que vai fazer update nas estruturas - Venda v
 */
void updateCliente(Historial h,Filial vf, Venda v);

/* freeFilial
 * Liberta memória ocupada por uma Filial
 */
void freeFilial(Filial f, Historial h);
#endif
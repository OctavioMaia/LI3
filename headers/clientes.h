#ifndef CLIENTES_H /* corresponde ao ficheiro clientes.h */
#define CLIENTES_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct nodo *ListaClientes;

typedef struct cliente *Cliente;
typedef struct clientes *Clientes;

typedef char* CLIENTE;

/* getClientesLetra
 * Esta função procura a AVL cujos códigos dos clientes
 * comecem por uma determinada letra.
 * @parametros - Apontador paracatálogo Clientes - Clientes c
 *				 Letra que se pretende que seja efetuada a 
 *               procura - char ch
 * @return - AVL com os codigos dos clientes existentes que 
 *           começam pela letra ch 
 */
ListaClientes getClientesLetra (Clientes c, char ch);

/* getCodigoCliente
 * Esta função devolve o código de um cliente.
 * @parametros - Apontador para o cliente que se pretende 
 *               descobrir o codigo - Cliente c
 * @return - Código do cliente
 */ 
CLIENTE getCodigoCliente (Cliente c);

/* getListaClientesLetra
 * Coloca numa lista os códigos dos clientes que começam 
 * por uma determinada letra.
 * @parametros - Apontador para catálogo de clientes - Clientes c
 *             - Letra que se pretende que seja efetuada a 
 *               procura - char ch
 *  @return - Apontador para lista com os c+odigos clientes.
 */
LISTA_STRING  getListaClientesLetra (Clientes c, char ch);

/* getTotalClientes
 * Esta função devolve o número de clientes do catálogo.
 * @parametros - Apontador para catalogo Clientes.
 * @return - Numero de clientes existentes no catalogo.
 */
int getTotalClientes (Clientes c);

/* ----------------------
   Funções de modificação
   ----------------------
*/

/* addClientes
 * Adiciona um número de clientes ao total dos clientes
 * do catálogo.
 * @parametros - Apontador para catálogo de clientes - Clientes c
 *               Número de clientes que se pretende adicionar - int n
 */   
void addClientes (Clientes c, int n);

/* setCodigoCliente
 * Modifica o código de um cliente.
 * @parametro - Apontador para catálogo de clientes - Cliente c
 *            - Novo código cliente - CLIENTE s 
 */
void setCodigoCliente (Cliente c, CLIENTE s);


/* initCliente
 * Esta funcao inicializa um cliente alocando memória.
 * @return - Apontador para cliente.
 */
Cliente initCliente();

/* initClientes()
 * Inicia a estrutura Clientes inicializando as 26 posicoes do array
 * a NULL.
 * @return - Apontador para catálogo de clientes
 */
Clientes initClientes();

/* insertCliente
 * Esta funcao insere um cliente no catálogo.
 * @parametros - Apontador para catálogo de clientes.
 *             - Código do cliente que se pretende inserir.
 * @return - Apontador para catálogo de clientes.
 */
Clientes insertCliente (Clientes c, CLIENTE s);

/* searchCliente
 * Esta funcao procura se o codigo de um cliente existe no catalogo.
 * @parametros - Apontador para catalogo Clientes - Clientes c
                 Código do cliente que se pretende procurar - CLIENTE s.
   @return - Apontador para Cliente
             Se o cliente não existir - NULL              
 */
Cliente searchCliente (Clientes c, CLIENTE s);

/* removeCliente
 * Esta funcao remove um cliente do catálogo Clientes
 *  @parametros - Apontador para catálogo - Clientes c
                  Código do cliente que se pretende remover - CLIENTE s.
   @return - Apontador para catálogo Clientes              
 */
Clientes removeCliente(Clientes c, CLIENTE s);

void freeClientes(Clientes c);
#endif
/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaClientes;

typedef struct cliente *Cliente;
typedef struct clientes *Clientes;

typedef STRING CLIENTE;

/*            ======================================
              Funções relativas à estrutura Clientes
              ======================================
 */

/* -------------------
   Funções de consulta
   -------------------
*/
AVL getClientesLetra (Clientes c, char ch);
CLIENTE getCodigoCliente (Cliente c);
int getTotalClientes (Clientes c);
LISTA_STRING  getListaClientesLetra (Clientes c, char ch);
int getComprouFilial (Cliente c, int filial);
LISTA_STRING  getProdutosCliente(Cliente c);
LISTA_INT getQuantidadeProdutos(Cliente c);
LISTA_INT getMesVenda(Cliente c);
LISTA_FLOAT getFaturacaoProdutos(Cliente c);
int getValorTabela(Cliente c, int mes, int filial);

/* ----------------------
   Funções de modificação
   ----------------------
*/
void setClientes (Clientes c, int n);
void addClientes (Clientes c, int n);
void setCodigoCliente (Cliente c, STRING s);
void setComprouFilial (Cliente c, int filial);
void setFaturacaoProdutos(Cliente c, LISTA_FLOAT faturacao);

void updateCliente(Clientes c, STRING cod_cliente,STRING cod_produto, int mes, int filial, int quantidade, float preco);

Cliente initCliente();
Clientes initClientes();
Clientes insertCliente (Clientes c, STRING s);
Cliente searchCliente (Clientes c, STRING s);
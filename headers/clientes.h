#ifndef CLIENTES_H /* corresponde ao ficheiro clientes.h */
#define CLIENTES_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct nodo *ListaClientes;

typedef struct cliente *Cliente;
typedef struct clientes *Clientes;

typedef char* CLIENTE;

/*            ======================================
              Funções relativas à estrutura Clientes
              ======================================
 */

/* -------------------
   Funções de consulta
   -------------------
*/
ListaClientes getClientesLetra (Clientes c, char ch);
CLIENTE getCodigoCliente (Cliente c);
LISTA_STRING  getListaClientesLetra (Clientes c, char ch);
int getTotalClientes (Clientes c);

/* ----------------------
   Funções de modificação
   ----------------------
*/
void addClientes (Clientes c, int n);
void setCodigoCliente (Cliente c, CLIENTE s);

Cliente initCliente();
Clientes initClientes();
Clientes insertCliente (Clientes c, CLIENTE s);
Cliente searchCliente (Clientes c, CLIENTE s);
Clientes removeCliente(Clientes c, CLIENTE s);

#endif
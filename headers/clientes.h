typedef struct cliente *Cliente;
typedef struct clientes *Clientes;

/*            ======================================
              Funções relativas à estrutura Clientes
              ======================================
 */

/* -------------------
   Funções de consulta
   -------------------
*/
AVL getClientesLetra (Clientes c, char ch);
char* getCodigoCliente (Cliente c);
int getTotalClientes (Clientes c);
char** getListaClientesLetra (Clientes c, char ch);

/* ----------------------
   Funções de modificação
   ----------------------
*/
void setClientes (Clientes c, int n);
void addClientes (Clientes c, int n);
void setCodigoCliente (Cliente c, char *s);

Cliente initCliente();
Clientes insertCliente (Clientes c, char *s);
Cliente searchCliente (Clientes c, char *s);
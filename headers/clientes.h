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
int getComprouFilial1 (Cliente c);
int getComprouFilial2 (Cliente c);
int getComprouFilial3 (Cliente c);

/* ----------------------
   Funções de modificação
   ----------------------
*/
void setClientes (Clientes c, int n);
void addClientes (Clientes c, int n);
void setCodigoCliente (Cliente c, char *s);
void setComprouFilial1 (Cliente c);
void setComprouFilial2 (Cliente c);
void setComprouFilial3 (Cliente c) ;

Cliente initCliente();
Clientes insertCliente (Clientes c, char *s);
Cliente searchCliente (Clientes c, char *s);
/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

typedef struct venda *Venda;

/* -------------------
   Funções de consulta
   -------------------
*/
char* getProduto(Venda v);
float getPreco (Venda c);
int getQuantidade (Venda c);
char getPromo(Venda c);
char* getCliente(Venda v);
int getMes (Venda c);
int getFilial (Venda c);

Venda initVenda (char *s);
int validaVenda (Venda c, Produtos prod, Clientes cli);
/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

typedef struct venda *Venda;

/* -------------------
   Funções de consulta
   -------------------
*/
PRODUTO getProduto(Venda v);
float getPreco (Venda c);
int getQuantidade (Venda c);
char getPromo(Venda c);
CLIENTE getCliente(Venda v);
int getMes (Venda c);
int getFilial (Venda c);

Venda initVenda (STRING s);
int validaVenda (Venda c, Produtos prod, Clientes cli);
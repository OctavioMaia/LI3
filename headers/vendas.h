/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

typedef struct venda *Venda;

/* -------------------
   Funções de consulta
   -------------------
*/
CLIENTE getCliente(Venda v);
PRODUTO getProduto(Venda v);
float getPreco (Venda c);
char getPromo(Venda c);
int getMes (Venda c);
int getFilial (Venda c);
int getQuantidade (Venda c);

Venda initVenda (STRING s);
int validaVenda (Venda c, Produtos prod, Clientes cli);
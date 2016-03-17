/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

typedef char** LISTA;

#define L 0	/*Esquerda*/
#define R 1	/*Direita*/
#define EH -1	/*Balanço equivalente*/

typedef struct node *AVL;


/* getData
   Devolve a informação contida num nó de uma AVL
 */
void * getData (AVL a);

/* getChild
   Devolve um apontador para um filho da AVL, na direção dir
 */
AVL getChild (AVL a, int dir);

/* insertAVL
 * Esta função recebe uma AVL, um apontador para a informação que se
 * deseja adicionar, um apontador que servirá como flag para balanciamento
 * e uma função que compara dois apontadores.
 * Se a AVL estiver a NULL, reserva espaço na memória, copia a informação,
 * coloca a child left e right a NULL e coloca a flag a 1.
 * Se a AVL contém elementos, usa a função de comparação para decidir se
 * insere a informação à esquerda ou à direita.
 */
AVL insertAVL (AVL t, void* data, int *cresceu, int(*comp)(void*,void*));


/* toString
 * Esta função reserva espaço na memoria para a informação
 * devolvida pela função toStringAux.
 */
LISTA toString (AVL a, int n);


/* search
 * Esta função recebe uma AVL, um código de produtos ou clientes e
 * uma função de comparação. Percorre a AVL à procura do código dado,
 * se um elemento for igual ao código, devolve um apontador para a 
 * sua posição, se for menor é invocada novamente para a esquerda,
 * se for maior é invocada para a direita.
 */
AVL search (AVL a, void* s, int(*comp)(void*,void*));

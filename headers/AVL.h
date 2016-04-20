#ifndef AVL_H /* corresponde ao ficheiro AVL.h */
#define AVL_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

#define ESQ 0	/*Esquerda*/
#define DIR 1	/*Direita*/
#define EQUAL -1	/*Balanço equivalente*/

typedef struct nodo *AVL;


/* getData
   Devolve a informação contida num nó de uma AVL
 */
void * getData (AVL a);

/* getFilho
   Devolve um apontador para um filho da AVL, na direção dir
 */
AVL getFilho (AVL a, int dir);

/* inserirAVL
 * Esta função recebe uma AVL, um apontador para a informação que se
 * deseja adicionar, um apontador que servirá como flag para balanciamento
 * e uma função que compara dois apontadores.
 * Se a AVL estiver a NULL, reserva espaço na memória, copia a informação,
 * coloca a filho left e right a NULL e coloca a flag a 1.
 * Se a AVL contém elementos, usa a função de comparação para decidir se
 * insere a informação à esquerda ou à direita.
 */
AVL inserirAVL (AVL t, void* data, int* cresceu, int(*comp)(void*,void*));


/* removerAVL
 * Esta função recebe uma AVL, bem como o objeto a remover,
 * seja ele um código de produto, cliente, venda, etc.
 * Esta função itera a AVL e irá remover esse objeto, balanceando
 * de seguida a AVL.
 */
AVL removerAVL(AVL t, void *data);

/* toString
 * Esta função reserva espaço na memoria para a informação
 * devolvida pela função toStringAux.
 */
LISTA_STRING toString (AVL a, int n);


/* procurarAVL
 * Esta função recebe uma AVL, um código de produtos ou clientes e
 * uma função de comparação. Percorre a AVL à procura do código dado,
 * se um elemento for igual ao código, devolve um apontador para a 
 * sua posição, se for menor é invocada novamente para a esquerda,
 * se for maior é invocada para a direita.
 */
AVL procurarAVL (AVL a, void* s, int(*comp)(void*,void*));

/*free avl*/
void freeAVL(AVL a);

/* removerAVL
----documentar
*/
AVL removerAVL(AVL t, void *data);

#endif
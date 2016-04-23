#ifndef AVL_H /* corresponde ao ficheiro AVL.h */
#define AVL_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

#define ESQ 0	/*Esquerda*/
#define DIR 1	/*Direita*/
#define EQUAL -1	/*Balanço equivalente*/

typedef struct nodo *AVL;


/* getData
 * Esta função retorna a informação contida num nó de uma AVL.
 * @parametros  Apontador para nó de AVL - AVL a.
 */
void * getData (AVL a);

/* getFilho
 * Esta função devolve um apontador para o filho da direita.
 * @parametros - Apontador para nó de AVL - AVL a
 				 Inteiro para indicar que o apontador 
				 dos filhos do nó deve ser o direito - int dir 
 * @return - Apontador para filho da direita do nó.
 */
AVL getFilho (AVL a, int dir);

/* inserirAVL
 * Esta função insere um nó numa AVL grantido que ela fique balanceada
 * @parametros - Apontador para nó de AVL - AVL t
 *               Informação que se deseja inserir no nó - void *data
 *               Apontador que serve com flag para balanciamento - int *cresceu
 *               Função de comparação - int(*comp)(void*,void*))
 * @return - Apontador para AVL 
 */
AVL inserirAVL (AVL t, void* data, int* cresceu, int(*comp)(void*,void*));


/* removerAVL
 * Esta função remove da AVL um nó caso a informação contida no
 * nó seja igual à informação passada como parâmetro.
 * @parametros - Apontador para AVL - AVL t
                  Informação que se vai comparar à informação 
 * presente nos nós da AVL - void *data.
 * @return - Apontador para AVL                
 */ 
AVL removerAVL(AVL t, void *data);

/* toString
 * Esta função reserva espaço na memoria para a informação
 * devolvida pela função toStringAux. A função toStringAux 
 * é uma função recursiva coloca numa lista a informação presente nos 
 * nós de uma AVL.
 * @parametros - Apontador para nó AVL a
 *             - Número de nós da AVL - int n
 * @return - Lista com informação presente nos nós da AVL.
 */
LISTA_STRING toString (AVL a, int n);


/* procurarAVL
 * Esta função procura se na AVL contém um nó cuja informação 
 * seja igual à informação passada como parâmetro.
 * @parametros - Apontador para AVL - AVL t
                  Informação que se vai comparar à informação 
 * presente nos nós da AVL - void *data.
 * @return - Apontador para AVL                
 */ 
AVL procurarAVL (AVL a, void* s, int(*comp)(void*,void*));

/* freeAVL
 * Esta função liberta a memória ocupada por uma AVL.
 * @parametros - Apontador para nó da AVL - AVL a
 */
void freeAVL(AVL a);

/* removerAVL
 * Esta função remove da AVL um nó caso a informação contida no
 * nó seja igual à informação passada como parâmetro.
 * @parametros - Apontador para AVL - AVL t
                  Informação que se vai comparar à informação 
 * presente nos nós da AVL - void *data.
 * @return - Apontador para AVL                
 */ 
AVL removerAVL(AVL t, void *data);

#endif
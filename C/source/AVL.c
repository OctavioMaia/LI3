#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tipos.h"
#include "../headers/AVL.h"

/* nodo
 * Esta estrutura contem:
 * - O apontador para informação do nó, representado pelo void* data.
 * - O factor de balanceamento do nó, representado pelo factor_balanceamento.
 * - Os apontadores para os filhos do nó, representado pelo *filho[2].
 */
typedef struct nodo {
	void *data;					/*Apontador para informação do nó*/
	int factor_balanceamento;	/*Factor de balanceamento do nó*/
	struct nodo *filho[2];		/*Apontadores para os filhos do nó*/
}nodo;

/*
 * getData
 * Esta funcao retorna os dados que um nodo
 * de uma AVL possui.
 */
void * getData (AVL a) {
	return a->data;
}

/*
 * getFilho
 * Esta funcao retorna o apontador para o nodo
 * filho especificado pelo int dir.
 */
AVL getFilho (AVL a, int dir) {
	return a->filho[dir];
}

/*
 * setData
 * Esta funcao atribui um valao ao data
 * de um nodo de AVL.
 */
void setData (AVL a, void *v) {
	a->data=v;
}

/*
 * rodar
 * Esta função recebe uma AVL e a direção para onde
 * a vai rodar.
 */
AVL rodar(AVL t, int dir) {
	AVL aux;
	if((!t) || (!t->filho[!dir])) return NULL;
	else{
		aux = t->filho[!dir];
		t->filho[!dir]=aux->filho[dir];
		aux->filho[dir]=t;
		t=aux;
	}
	return t;
}


/* balancear
 * Esta função recebe uma AVL e a direção para onde
 * a vai rodar e balanceia os nós da àrvore.
 */
AVL balancear(AVL t, int dir) {
	if (t->filho[dir]->factor_balanceamento==dir) {
		/* Rotacao simples a filho[!dir]uerda*/
		t = rodar(t,!dir);
		t->factor_balanceamento = EQUAL;
		t->filho[!dir]->factor_balanceamento = EQUAL;
	}else{
		/*Dupla rotacao*/
		t->filho[dir] = rodar(t->filho[dir],dir);
		t = rodar(t,!dir);
		if (t->factor_balanceamento==EQUAL)
			t->filho[dir]->factor_balanceamento=t->filho[!dir]->factor_balanceamento=EQUAL;
		else if (t->factor_balanceamento==!dir) {
			t->filho[!dir]->factor_balanceamento = EQUAL;
			t->filho[dir]->factor_balanceamento = dir;			
		}
		else if (t->factor_balanceamento==dir) {
			t->filho[!dir]->factor_balanceamento = !dir;
			t->filho[dir]->factor_balanceamento = EQUAL;			
		}
		t->factor_balanceamento = EQUAL; 
	}
	return t;
}


/* inserir
 * Esta função recebe uma AVL, a direção para onde a AVL vai rodar,
 * a informação que se deseja inserir, um apontador que serve com flag
 * para balanciamento, e uma função de comparação. Insere a informação
 * num dos nodos e balanceia a árvore de modo a manter a diferença de
 * altura entre estes menor ou igual a 1.
 */
AVL inserir(AVL t, int dir, void *data, int* cresceu,int(*comp)(void*,void*)) {
	t->filho[dir] = inserirAVL(t->filho[dir],data,cresceu,comp);
	if (*cresceu) {
		if (t->factor_balanceamento==!dir) {
			t->factor_balanceamento=EQUAL;
			*cresceu=0;
		}
		else if (t->factor_balanceamento==EQUAL) {
			t->factor_balanceamento=dir;
			*cresceu=1;
		}
		else if (t->factor_balanceamento==dir) {
			t=balancear(t,dir);
			*cresceu=0;
		}
	}
	return t;
}

/*
 * inserirAVL
 * Esta funcao verifica se estamos no nodo correto
 * da AVL a inserir. Se estivermos no nodo correto
 * chama a funcao auxiliar inserir.
*/

AVL inserirAVL(AVL t, void* data, int* cresceu, int(*comp)(void*,void*)){
	if (t==NULL) {
		t = (AVL)malloc(sizeof(struct nodo));
		t->data = data;
		t->filho[ESQ] = t->filho[DIR] = NULL;
		t->factor_balanceamento = EQUAL;
		*cresceu = 1;
	}
    else if (comp(data,t->data)>0)
        t = inserir(t,DIR,data,cresceu,comp);
    else
        t = inserir(t,ESQ,data,cresceu,comp);
  return t;
}

/*
 * min
 * Esta funcao calcula o nodo minimo de uma AVL
 * e retorna esse nodo.
 */
AVL min(AVL nodo){
    AVL atual = nodo;
    while (atual->filho[ESQ] != NULL){
        atual = atual->filho[ESQ];
    } 
    return atual;
}

/*
 * removerAVL
 * Esta funcao tem como objetivo remover dados da AVL.
 * Para isso recebe a AVL em questão e itera até
 * encontrar o nodo a remover.
 */
AVL removerAVL(AVL t, void *data){
    if (data == NULL) return t;
    if (strcmp(data,t->data)<0){
        t->filho[ESQ] = removerAVL(t->filho[ESQ], data);
    }else if (strcmp(data,t->data)>0){
            t->filho[DIR] = removerAVL(t->filho[DIR], data);
    }
    else{
        AVL temp;
        if (t->filho[ESQ] == NULL){
            AVL temp2 = t->filho[DIR];
            free(t);
            return temp2;
        }else{
            if (t->filho[DIR] == NULL){
                AVL temp2 = t->filho[ESQ];
                free(t);
                return temp2;
            }
        }
        temp = min(t->filho[DIR]);
        strcpy(t->data,temp->data);
        t->filho[DIR] = removerAVL(t->filho[DIR], temp->data);
    }
    return t;
}


/*
 * procurarAVL
 * Esta funcao tem como objetivo encontrar o nodo de uma AVL
 * que contem a informacao "s" que lhe damos como parametro.
 * Como a AVL é do tipo genérico temos que lhe passar uma 
 * função de comparacão.
 */
AVL procurarAVL (AVL a, void* s, int(*comp)(void*,void*)) {
	int c;
	if (!a) return NULL;
	c=comp(s,a->data);
	
	if (c==0)
		return a;
	else if (c<0) 
		return procurarAVL(a->filho[ESQ],s,comp); 
	else 
		return procurarAVL(a->filho[DIR],s,comp);
	
	return NULL; 
}

/*
 * freeAVL
 * Esta função tem como objetivo libertar a memória ocupada
 * por uma AVL, recorrendo à funcao free.
 */
void freeAVL(AVL a){
	if(!a)
		return;

	freeAVL(getFilho(a,ESQ));
	freeAVL(getFilho(a,DIR));
	free(a->data);
	free(a);
}

/* toStringAux
 * Esta função recebe uma AVL, uma lista de apontadores,
 * um apontador que serve como flag para saber onde inserir
 * a informação da AVL na lista na posição dada pela flag.
 * É depois chamada recursivamente para a esquerda e
 * direita da AVL.
 */
LISTA_STRING stringAux (AVL a, LISTA_STRING s, int* i) {
	if (a!=NULL) {		
		s=stringAux(a->filho[ESQ],s,i);
		s[(*i)]=a->data;
		(*i)++;
		s=stringAux(a->filho[DIR],s,i);
	}
	return s;
}

/*
 * toString
 * Esta funcao transforma uma AVL numa lista de strings,
 * de modo a ser possivel ler de forma facil.
 */
LISTA_STRING toString (AVL a, int n) {
	int i=0;
	LISTA_STRING s = malloc(sizeof(STRING)*n);

	if (a!=NULL) {
		s=stringAux(a,s,&i);
		return s;
	}else{
		return NULL;
	}
}
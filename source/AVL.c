#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/AVL.h"


/* node
 * Esta estrutura contem:
 * o apontador para informação do nó,
 * o factor de balanceamento do nó,
 * e os apontadores para os filhos do nó.
 */
typedef struct node {
	void *data;		/*Apontador para informação do nó*/
	int bf;			/*Factor de balanceamento do nó*/
	struct node *child[2];	/*Apontadores para os filhos do nó*/
}node;


void * getData (AVL a) {
	return a->data;
}

AVL getChild (AVL a, int dir) {
	return a->child[dir];
}

void setData (AVL a, void *v) {
	a->data=v;
}


/*
 * rotate
 * Esta função recebe uma AVL e a direção para onde
 * a vai rodar.
 */
AVL rotate(AVL t, int dir) {
	AVL aux;
	if((!t) || (!t->child[!dir])) return NULL;
	else{
		aux = t->child[!dir];
		t->child[!dir]=aux->child[dir];
		aux->child[dir]=t;
		t=aux;
	}
	return t;
}


/* balance
 * Esta função recebe uma AVL e a direção para onde
 * a vai rodar e balanceia os nós da àrvore.
 */
AVL balance(AVL t, int dir) {
	if (t->child[dir]->bf==dir) {
		/* Rotacao simples a child[!dir]uerda*/
		t = rotate(t,!dir);
		t->bf = EH;
		t->child[!dir]->bf = EH;
	}else{
		/*Dupla rotacao*/
		t->child[dir] = rotate(t->child[dir],dir);
		t = rotate(t,!dir);
		if (t->bf==EH)
			t->child[dir]->bf=t->child[!dir]->bf=EH;
		else if (t->bf==!dir) {
			t->child[!dir]->bf = EH;
			t->child[dir]->bf = dir;			
		}
		else if (t->bf==dir) {
			t->child[!dir]->bf = !dir;
			t->child[dir]->bf = EH;			
		}
		t->bf = EH; 
	}
	return t;
}


/* insert
 * Esta função recebe uma AVL, a direção para onde a AVL vai rodar,
 * a informação que se deseja inserir, um apontador que serve com flag
 * para balanciamento, e uma função de comparação. Insere a informação
 * num dos nodos e balanceia a árvore de modo a manter a diferença de
 * altura entre estes menor ou igual a 1.
 */
AVL insert(AVL t, int dir, void *data, int *cresceu,int(*comp)(void*,void*)) {
	t->child[dir] = insertAVL(t->child[dir],data,cresceu,comp);
	if (*cresceu) {
		if (t->bf==!dir) {
			t->bf=EH;
			*cresceu=0;
		}
		else if (t->bf==EH) {
			t->bf=dir;
			*cresceu=1;
		}
		else if (t->bf==dir) {
			t=balance(t,dir);
			*cresceu=0;
		}
	}
	return t;
}

AVL insertAVL(AVL t, void* data, int *cresceu, int(*comp)(void*,void*)){
	if (t==NULL) {
		t = (AVL)malloc(sizeof(struct node));
		t->data = data;
		t->child[L] = t->child[R] = NULL;
		t->bf = EH;
		*cresceu = 1;
	}
    else if (comp(data,t->data)>0)
        t = insert(t,R,data,cresceu,comp);
    else
        t = insert(t,L,data,cresceu,comp);
  return t;
}


/* toStringAux
 * Esta função recebe uma AVL, uma lista de apontadores,
 * um apontador que serve como flag para saber onde inserir
 * a informação da AVL na lista na posição dada pela flag.
 * É depois chamada recursivamente para a esquerda e
 * direita da AVL.
 */
char** toStringAux (AVL a, char** s, int *i) {
	if (a!=NULL) {		
		s=toStringAux(a->child[L],s,i);
		s[(*i)]=a->data;
		(*i)++;
		s=toStringAux(a->child[R],s,i);
	}
	return s;
}


char** toString (AVL a, int n) {
	int i=0;
	char** s = malloc(sizeof(char*)*n);

	if (a!=NULL) {
		s=toStringAux(a,s,&i);
		return s;
	}else{
		return NULL;
	}
}


AVL search (AVL a, void* s, int(*comp)(void*,void*)) {
	int c;
	if (!a) return NULL;
	c=comp(s,a->data);
	
	if (c==0)
		return a;
	else if (c<0) 
		return search(a->child[L],s,comp); 
	else 
		return search(a->child[R],s,comp);
	
	return NULL; 
}

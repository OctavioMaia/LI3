#include "../headers/AVL.h"
#include "../headers/faturacao.h"

typedef struct informacao{
	char produto[5];
	int quantidadeN[12][3];
	int quantidadeP[12][3];
	float faturadoN[12][3];
	float faturadoP[12][3];
}informacao;

typedef struct faturacao {
	AVL avl[26];			/*Divisao dos produtos em 26 AVL's*/
}faturacao;
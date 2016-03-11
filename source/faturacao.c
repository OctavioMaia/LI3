#include <stdlib.h>
#include <string.h>
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
	int total;
}faturacao;

/*cenas*/
void setCodProduto (Informacao p, char *s) {
	strcpy(p->produto,s);
}


int infcmp (Informacao a, Informacao b) {
	return strcmp(a->produto,b->produto);
}

int infcmpstr (char *a, Informacao b) {
	return strcmp(a,b->produto);
}

/*funcoes*/
Informacao initInformacao(){
	int i,j;
	Informacao info = (Informacao)malloc(sizeof(struct informacao));

	for(i=0;i<12;i++){
		for(j=0;j<3;j++){
			info->quantidadeN[i][j]=info->quantidadeP[i][j]=info->faturadoN[i][j]=info->faturadoP[i][j]=0;
		}
	}

	return info;
}

Faturacao insertInformacao(Faturacao p, char *s) {
	int i, pos=s[0]-'A';

	Informacao aux = initInformacao();
	setCodProduto(aux,s);

	if (p==NULL) {	/*Se não existir a estrutura Produtos, criá-la*/
		printf("criado faturacao global\n");
		p=(Faturacao)malloc(sizeof(struct faturacao));
		for (i=0; i<26; i++) 
			p->avl[i]=NULL;
		p->total=0;
	}
	i=0;	/*A variável i, passa a servir como flag para a próxima função*/
	p->avl[pos]=insertAVL(p->avl[pos],aux,&i,(int (*)(void*,void*))infcmp);
	return p;
}

Informacao searchInformacao(Faturacao p, char *s) {
	Informacao p1;
	AVL aux=search(p->avl[s[0]-'A'],s,(int (*)(void*,void*))infcmpstr);
	if (aux!=NULL) {
		p1=getData(aux);
		return p1;
	}else{
		return NULL;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/AVL.h"
#include "../headers/produtos.h"
#include "../headers/clientes.h"
#include "../headers/queries.h"

/* Lista google*/
void imprimirLista(char **s,int c,int l) {
  int i = 0;
  int numpags;

  while (s[i]!='\0'){ /*calcula o numero de elems em s*/
    i++;
  } 

  numpags= i/(c*l);  /*calcula o numero de paginas*/

  imprimirAux(s,c,l,numpags,0);
}

void imprimirAux(char **s, int c , int l,int t, int pa) {
    int j /*j vai ate ao numero de colunas*/, p; /*scanf da pagina a ler*/
  int i=0;
  int y=0;
  char **aux = s;
  char **atual;
  
  printf("-------------------------Página %d--------------------------\n",pa+1);
  for (i=0;i<l && aux[y+1];i++){   
      for (j=0;j<c && aux[y];j++,y++){
        printf("%s\t", aux[y]);
      }
    putchar('\n');
  }
    
    printf("------------------------------------------------------------\n");
  printf("Existem %d páginas. Página a verificar? (-1 para sair) ",t);  
    scanf(" %d",&p);
  if (p==-1 || p > t || p==0)
    printf("Exit!\n");
  else{
    atual=s+(p-1)*l*c-(pa*c*l);
      imprimirAux (atual,c,l,t,p-1);   
  }
}
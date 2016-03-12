#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../headers/AVL.h"
#include "../headers/produtos.h"
#include "../headers/clientes.h"
#include "../headers/vendas.h"
#include "../headers/faturacao.h"
#include "../headers/vendasfilial.h"
#include "../headers/queries.h"

/* Lista google*/
void imprimirLista(char **s,int c,int l) {
  int i = 0;
  int numpags;

  while (s[i]!='\0'){ /*calcula o numero de elems em s*/
    i++;
  } 

  numpags= i/(c*l)+1;  /*calcula o numero de paginas*/

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

void exec(Produtos prod, Clientes cli, Faturacao f, VendasFilial vf){
  int decisao; /*para o switch*/
  printf("Introduza o número da query a executar: ");
  scanf("%d", &decisao);
  switch (decisao){
  char ch;
  char codigo[6];
  int global;
  int mes;
    case -1:
      puts("Execução cancelada pelo utilizador!");
      exit(0);
      break;
    case 1:
      puts("Ficheiros já validados e guardados!");
      break;
    case 2:
     printf("---------------------------Query 2-------------------------------\n");
      printf("Introduza a letra para pesquisar: ");
      scanf(" %c", &ch);
      query2(prod,ch);
      break;
    case 3:
      printf("---------------------------Query 3-------------------------------\n");
      printf("Introduza o mês de pesquisa: ");
      scanf(" %d", &mes);
      printf("Introduza o código de produto: ");
      scanf(" %s", codigo);
      printf("Deseja ver os resultados por filial (1) ou global (0)? ");
      scanf(" %d", &global);
      query3(f,mes,codigo,global);
      break;
    default: /* execute default action */
      puts("Query inválida!");
      break;
  }
  exec(prod,cli,f,vf);
}

/*Queries*/
void query2(Produtos p, char ch){
  clock_t begin, end; /*Contadores de tempo de execucao para query 2*/
  double time_spent;
  char **lista;

  begin = clock(); /*init contador*/
  lista = getListaProdutosLetra (p,ch);
  end = clock(); /*end contador*/
  
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
  printf("Sucesso, demoramos %fs!\n",time_spent);
  imprimirLista(lista,9,8);
}

void query3(Faturacao F, int mes, char *s, int global){
  Informacao info;
  clock_t begin, end; /*Contadores de tempo de execucao para query 2*/
  double time_spent;
  int f,qN=0,qP=0;
  float fN=0,fP=0;

  begin = clock(); /*init contador*/
  info = searchInformacao(F,s);
  end = clock(); /*end contador*/

  if(global==0){ /*se = 0 mostrar resultados globais*/
    for(f=0;f<3;f++){
      qN+=getQuantidadeNormal(info,mes-1,f);
      qP+=getQuantidadePromocao(info,mes-1,f);
      fN+=getFaturadoNormal(info,mes-1,f);
      fP+=getFaturadoPromocao(info,mes-1,f);
    }
    printf("Quantidade vendida em modo N: %d\n",qN);
    printf("Quantidade vendida em modo P: %d\n",qP);
    printf("Faturacao em modo N: %f\n",fN);
    printf("Faturacao em modo P: %f\n",fP);
  }else{
    printf("\t\t\t\tFilial 1 \t Filial 2 \t Filial 3\n");
    printf("Quantidade vendida em modo N: \t%d\t\t%d\t\t%d\n",getQuantidadeNormal(info,mes-1,0),getQuantidadeNormal(info,mes-1,1),getQuantidadeNormal(info,mes-1,2));
    printf("Quantidade vendida em modo P: \t%d\t\t%d\t\t%d\n",getQuantidadePromocao(info,mes-1,0),getQuantidadePromocao(info,mes-1,1),getQuantidadePromocao(info,mes-1,2));
    printf("Faturacao em modo N: \t\t%f\t%f\t%f\n",getFaturadoNormal(info,mes-1,0),getFaturadoNormal(info,mes-1,1),getFaturadoNormal(info,mes-1,2));
    printf("Faturacao em modo P: \t\t%f\t%f\t%f\n",getFaturadoPromocao(info,mes-1,0),getFaturadoPromocao(info,mes-1,1),getFaturadoPromocao(info,mes-1,2));
  }
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
  printf("Sucesso, demoramos %fs!\n",time_spent);
  printf("---------------------------------------------------------------------\n");
}
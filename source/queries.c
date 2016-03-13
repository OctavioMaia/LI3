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

  numpags= i/(c*l) + 1;  /*calcula o numero de paginas*/

  imprimirAux(s,c,l,numpags,0);
}

void imprimirAux(char **s, int c , int l,int t, int pa) {
  int j /*j vai ate ao numero de colunas*/, p; /*scanf da pagina a ler*/
  int i=0;
  int y=0;
  char **aux = s;
  char **atual;
  
  printf("\033[1m-------------------------Página %d--------------------------\033[0m \n",pa+1);
  for (i=0;i<l && aux[y+1];i++){   
      for (j=0;j<c && aux[y];j++,y++){
        printf("%s\t", aux[y]);
      }
    putchar('\n');
  }
    
  printf("\033[1m-----------------------------------------------------------\033[0m\n");
  printf("\033[1mExistem %d páginas. Página a verificar? (-1 para sair) \033[0m",t);  
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
  printf("\033[1mIntroduza o número da query a executar: \033[0m");
  scanf("%d", &decisao);
  switch (decisao){
  char ch;
  char codigo[6];
  int global;
  int mes;
    case -1:
      puts("Execução cancelada pelo utilizador!");
      printf("---------------------------------------------------------------------\n");
      exit(0);
      break;
    case 1:
      puts("\033[1mFicheiros já validados e guardados!");
      printf("---------------------------------------------------------------------\033[0m \n");
      break;
    case 2:
      printf("\033[1m-------------------------Query 2--------------------------\033[0m \n");
      printf("\033[1mIntroduza a letra para pesquisar: \033[0m");
      scanf(" %c", &ch);
      query2(prod,ch);
      break;
    case 3:
      printf("\033[1m-------------------------Query 3--------------------------\033[0m \n");
      printf("\033[1mIntroduza o mês de pesquisa: \033[0m ");
      scanf(" %d", &mes);
      printf("\033[1mIntroduza o código de produto: \033[0m ");
      scanf(" %s", codigo);
      printf("\033[1mDeseja ver os resultados por filial (1) ou global (0)? \033[0m ");
      scanf(" %d", &global);
      query3(f,mes,codigo,global);
      break;
    case 4:
      printf("\033[1m-------------------------Query 4--------------------------\033[0m \n");
      printf("\033[1mDeseja ver os resultados por filial (1) ou global (0)? \033[0m ");
      scanf(" %d", &global);
      query4(f,prod,global);
      break;
    case 7:
      printf("\033[1m-------------------------Query 7--------------------------\033[0m \n");
      query7(cli);
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

  if(ch >= 'A' && ch <= 'Z'){
    begin = clock(); /*init contador*/
    lista = getListaProdutosLetra (p,ch);
    end = clock(); /*end contador*/
    
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
    printf("Sucesso, demoramos %fs!\n",time_spent);
    imprimirLista(lista,10,9);
  }else{
    printf("Introduza uma letra maiúscula!\n");
  }
  printf("---------------------------------------------------------------------\n");
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

  if(info){
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
  }else{
    printf("Código de produto inválido!\n");
    printf("---------------------------------------------------------------------\n");
  }
}

void query4(Faturacao F, Produtos prod, int decisao){
  Informacao info;
  char **lista=(char**)malloc(sizeof(char**)),**s,ch;
  int i,n=0,filial1=0,filial2=0,filial3=0;

  if(decisao==0){ /*resultados globais , ou seja, soma das 3 filiais*/
    if (prod){
      for(ch='A';ch<='Z';ch++){
        s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
        for(i=0; s[i]!=NULL;i++){
          info=searchInformacao(F,s[i]);
          if(nuncaCompradoGlobal(info)==0){ /*passamos 0 pois 0 significa todas as filiais*/
            lista[n]=malloc(sizeof(char*));
            lista[n]=getCodigoProduto(info);
            n++;
          }
        }
      }
    }
    printf("Existem %d códigos de produtos que ninguém comprou!\n",n);
  }else{ /*filial a filial*/
    if (prod){
      for(ch='A';ch<='Z';ch++){
        s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
        for(i=0; s[i]!=NULL;i++){
          info=searchInformacao(F,s[i]);
          if(nuncaCompradoFilial(info,1)==0 && nuncaCompradoFilial(info,2)!=0 && nuncaCompradoFilial(info,3)!=0){ /*passamos 1 para procurar na filial 1*/
            lista[n]=malloc(sizeof(char*));
            lista[n]=getCodigoProduto(info);
            n++;
            filial1++;
          }if(nuncaCompradoFilial(info,2)==0 && nuncaCompradoFilial(info,1)!=0 && nuncaCompradoFilial(info,3)!=0){ /*passamos 2 para procurar na filial 2*/
            lista[n]=malloc(sizeof(char*));
            lista[n]=getCodigoProduto(info);
            n++;
            filial2++;
          }if(nuncaCompradoFilial(info,3)==0 && nuncaCompradoFilial(info,1)!=0 && nuncaCompradoFilial(info,2)!=0){ /*passamos 3 para procurar na filial 3*/
            lista[n]=malloc(sizeof(char*));
            lista[n]=getCodigoProduto(info);
            n++;
            filial3++;
          }
        }
      }
    }
    printf("Existem %d códigos de produtos que ninguém comprou na filial 1!\n",filial1);
    printf("Existem %d códigos de produtos que ninguém comprou na filial 2!\n",filial2);
    printf("Existem %d códigos de produtos que ninguém comprou na filial 3!\n",filial3);
  }
  imprimirLista(lista,10,9);
}

void query7(Clientes cli){
  int i,n=0;
  char **lista=(char**)malloc(sizeof(char**)),**s,ch;
  Cliente temporario=NULL;

  if (cli){
    for(ch='A';ch<='Z';ch++){
      s=toString(getClientesLetra(cli,ch),getTotalClientes(cli));
      for(i=0; s[i]!=NULL;i++){
        temporario=searchCliente(cli,s[i]);
        if(getComprouFilial1(temporario)==1 && getComprouFilial2(temporario)==1 && getComprouFilial3(temporario)==1){ /*passamos 0 pois 0 significa todas as filiais*/
          lista[n]=malloc(sizeof(char*));
          lista[n]=getCodigoCliente(temporario);
          n++;
        }
      }
    }
  }
  printf("Existem %d clientes que compraram em todas as filiais!\n",n);
  imprimirLista(lista,10,9);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../main.h"
#include "../headers/tipos.h"
#include "../headers/AVL.h"
#include "../headers/produtos.h"
#include "../headers/clientes.h"
#include "../headers/vendas.h"
#include "../headers/faturacao.h"
#include "../headers/filial.h"
#include "../headers/queries.h"

/*
 * função que permite ao utilizador navegar pelas diferentes páginas 
 */

void imprimirLista(LISTA_STRING s,int c,int l, int opcao) {
  int i = 0;
  int numpags;

  if(opcao==0){
    while (s[i]!='\0'){ /*calcula o numero de elems em s*/
      i++;
    } 

    if(i%(c*l)==0)
      numpags=i/(c*l);
    else
      numpags=i/(c*l) + 1;
  }else{
    if(opcao < 10){
      numpags = 1;
    }else if(opcao%10 == 0){
      numpags = opcao/10 ;
    }else{
      numpags = opcao/10 + 1;
    }
  }

  imprimirAux(s,c,l,numpags,0,opcao);
}

void imprimirAux(LISTA_STRING s, int c , int l,int t, int pa, int opcao) {
  int j,p;/*j vai ate ao numero de colunas*/ /*scanf da pagina a ler*/
  int i=0;
  int y=0;
  int total=0;
  LISTA_STRING aux = s;
  char buf[30];

  if(pa>=0){
    printf("\033[1m----------------------------------Página %d----------------------------------\033[0m \n",pa+1);
    for (i=0;i<l && aux[y+1];i++){   
        for (j=0;j<c && aux[y];j++,y++,total++){
          if(opcao==0) 
            printf("%s\t", aux[y]);
          if(total<opcao)
            printf("%s\n", aux[y]);
        }
      putchar('\n');
    }
      
    printf("\033[1m----------------------------------------------------------------------------\033[0m\n");
    printf("\033[1mExistem %d páginas. \nPágina a verificar? (+ pag. seguinte | - pag. anterior | 0 sair) \033[0m",t);  
    scanf(" %s",buf);

    p=atoi(buf); 
    if (buf[0]=='+' && pa+1<t) imprimirAux(s+(pa+1)*l*c-(pa*c*l),c,l,t,pa+1,opcao); 
    else if (buf[0]=='-') imprimirAux(s+(pa-1)*l*c-(pa*c*l),c,l,t,pa-1,opcao);
    else if (p==-1 || p > t || p<=0) printf("Exit!\n");
    else imprimirAux (s+(p-1)*l*c-(pa*c*l),c,l,t,p-1,opcao);   
  }else{
    printf("Exit!\n");
  }
}

int valor_max(int n, int valores[]) {
  int i;
  int max = valores[0];
  for(i = 1; i < n; ++i)
    max = valores[i] > max ? valores[i] : max;
  
  return max;
}

float valor_max_float(int n, float valores[]) {
  int i;
  float max = valores[0];
  for(i = 1; i < n; ++i)
    max = valores[i] > max ? valores[i] : max;
  
  return max;
}

/* 
 * menu inicial
 */
void imprimirInit() {
  puts("\t\t\t\t\033[1mEscolha de execução\033[0m");
  puts("\033[1mOpção 1\033[0m - Ler ficheiros Produtos.txt, Clientes.txt e Vendas_1M.txt");
  puts("\033[1mOpção 2\033[0m - Ler ficheiros Produtos.txt, Clientes.txt e Vendas_3M.txt");
  puts("\033[1mOpção 3\033[0m - Ler ficheiros Produtos.txt, Clientes.txt e Vendas_5M.txt");
  puts("\033[1mOpção 4\033[0m - Ler ficheiros não standarts");
  printf("\033[1mOpção escolhida: \033[0m ");
}

/*
 * menu imprimir menu
 */
void imprimirQueries() {
  puts("\t\t\t\t\033[1mLista de Queries\033[0m");
  puts("\033[1mQuery 2\033[0m - Imprimir lista de produtos cujo código se inicia por uma dada letra.");
  puts("\033[1mQuery 3\033[0m - Dado um código de produto, apresentar o número total de vendas e total faturado num dado mês.");
  puts("\033[1mQuery 4\033[0m - Imprimir lista dos códigos de produto que ninguém comprou (global ou filial).");
  puts("\033[1mQuery 5\033[0m - Dado um código de cliente, criar uma tabela, organizada por filiais, com o número total de produtos comprados.");
  puts("\033[1mQuery 6\033[0m - Dado um intervalo fechado de meses, determinar o total de vendas e o total faturado.");
  puts("\033[1mQuery 7\033[0m - Imprimir lista de clientes que realizaram compras em todas as filiais.");
  puts("\033[1mQuery 8\033[0m - Dado um código de produto e filial, determinar os códigos de clientes que o compraram.");
  puts("\033[1mQuery 9\033[0m - Dado um código de cliente e um mês, determinar a lista de produtos que mais comprou.");
  puts("\033[1mQuery 10\033[0m - Imprimir uma lista dos N produtos mais vendidos em todo o ano.");
  puts("\033[1mQuery 11\033[0m - Dado um código de cliente, determinar quais os 3 produtos que mais gastou dinheiro durante o ano.");
  puts("\033[1mQuery 12\033[0m - Determinar o número de clientes que não realizaram compras, bem como os produtos que ninguém comprou.");
  puts("\033[1mQuery 13\033[0m - Libertar todos os dados em memória.");
  puts("\033[1mQuery 14\033[0m - Carregar dados em memória.");
  puts("");
}

/* 
 * função que lê do teclado um inteiro
 */
int lerInt(){
  int num;
  char term;
  if(scanf("%d%c", &num, &term) != 2 || term != '\n')
      return -1;
  else
      return num;
}

/* 
 * função que liberta memória das estruturas utilizadas pelo programa
 */
void freeAll(Produtos prod, Clientes cli, Faturacao f, Filial vf[] ,Historial h[]){
  freeClientes(cli);
  freeProdutos(prod);
  freeFaturacao(f);
  freeFilial(vf[0],h[0]);
  freeFilial(vf[1],h[1]);
  freeFilial(vf[2],h[2]);
}

/*QUERIES*/


void exec(Produtos prod, Clientes cli, Faturacao f, Filial vf[] ,Historial h[]){
  int decisao,i; /*para o switch*/
  char ch;
  char codigo[6];
  int global;
  int mes;
  int filial;
  
  printf("\033[1mQuery a executar (0 para apresentar a lista de queries | -1 para sair ): \033[0m");
  decisao=lerInt();
  puts("");
  switch (decisao){
    case -1:
      puts("Execução cancelada pelo utilizador!");
      puts("---------------------------------------------------------------------");
      exit(0);
      break;
    case 0:
      for(i=0;i<100;i++) puts("");
      imprimirQueries();
      break;
    case 1:
      puts("\033[1mFicheiros já validados e guardados!");
      puts("---------------------------------------------------------------------\033[0m");
      break;
    case 2:
      puts("\033[1m-----------------------------------Query 2-----------------------------------\033[0m");
      printf("\033[1mIntroduza a letra para pesquisar: \033[0m");
      scanf(" %c", &ch);
      query2(prod,ch);
      break;
    case 3:
      puts("\033[1m-----------------------------------Query 3-----------------------------------\033[0m");
      printf("\033[1mIntroduza o mês de pesquisa: \033[0m ");
      scanf(" %d", &mes);
      printf("\033[1mIntroduza o código de produto: \033[0m ");
      scanf(" %s", codigo);
      printf("\033[1mDeseja ver os resultados por filial (1) ou global (0)? \033[0m ");
      scanf(" %d", &global);
      query3(f,mes,codigo,global);
      break;
    case 4:
      puts("\033[1m-----------------------------------Query 4-----------------------------------\033[0m");
      printf("\033[1mDeseja ver os resultados por filial (1) ou global (0)? \033[0m ");
      scanf(" %d", &global);
      query4(f,prod,global);
      break;
    case 5:
      puts("\033[1m-----------------------------------Query 5-----------------------------------\033[0m");
      printf("\033[1mIntroduza o código de cliente: \033[0m ");
      scanf(" %s", codigo);
      query5(h,codigo);
      break;
    case 6:
      puts("\033[1m-----------------------------------Query 6-----------------------------------\033[0m");
      printf("\033[1mIntroduza o mês inicial de pesquisa: \033[0m ");
      scanf(" %d", &mes);
      printf("\033[1mIntroduza o mês final de pesquisa: \033[0m ");
      scanf(" %d", &filial);
      query6(f,prod,mes,filial);
      break;
    case 7:
      puts("\033[1m-----------------------------------Query 7-----------------------------------\033[0m");
      query7(h);
      break;
    case 8:
      puts("\033[1m-----------------------------------Query 8-----------------------------------\033[0m");
      printf("\033[1mIntroduza o código de produto: \033[0m ");
      scanf(" %s", codigo);
      printf("\033[1mIntroduza a filial para pesquisar: \033[0m ");
      scanf(" %d", &filial);
      query8(vf[filial-1],codigo);
      break;
    case 9:
      puts("\033[1m-----------------------------------Query 9-----------------------------------\033[0m");
      printf("\033[1mIntroduza o código de cliente: \033[0m ");
      scanf(" %s", codigo);
      printf("\033[1mIntroduza o mês de pesquisa: \033[0m ");
      scanf(" %d", &mes);
      query9(h,codigo,mes);
      break;
    case 10:
      puts("\033[1m-----------------------------------Query 10----------------------------------\033[0m");
      printf("\033[1mIntroduza o número de produtos a listar: \033[0m ");
      scanf(" %d", &mes);
      query10(vf,prod,mes);
      break;
    case 11:
      puts("\033[1m-----------------------------------Query 11----------------------------------\033[0m");
      printf("\033[1mIntroduza o código de cliente: \033[0m ");
      scanf(" %s", codigo);
      query11(h,codigo);
      break;
    case 12:
      puts("\033[1m-----------------------------------Query 12----------------------------------\033[0m");
      query12(h,prod,vf);
      break;
    case 13:
      freeAll(prod,cli,f,vf,h);
    case 14:
      main();
    default: /* execute default action */
      puts("Query inválida!");
      break;
  }
  exec(prod,cli,f,vf,h);
}

/*Queries*/

/* 
 * método de execução da query2
 */

void query2(Produtos p, char ch){
  clock_t begin, end; /*Contadores de tempo de execucao */
  double time_spent;
  LISTA_STRING lista;
  int i;

  if(ch >= 'A' && ch <= 'Z'){
    begin = clock(); /*init contador*/
    lista = getListaProdutosLetra (p,ch);
    end = clock(); /*end contador*/
    
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);

    for(i=0;lista[i]!=NULL;i++);
    printf("\nExistem \033[1m%d\033[0m produtos começados pela letra %c!\n",i,ch );
    imprimirLista(lista,10,9,0);
  }else{
    printf("Introduza uma letra maiúscula!\n");
  }
  printf("---------------------------------------------------------------------\n");
}

/* 
 * método de execução da query3
 */
void query3(Faturacao F, int mes, PRODUTO s, int global){
  Informacao info=NULL;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  double time_spent;
  int f,qN=0,qP=0;
  float fN=0,fP=0;

  begin = clock(); /*init contador*/
  info = searchInformacao(F,s);
  end = clock(); /*end contador*/

  if(info && (global==0 || global==1) && (mes>=1 && mes<=12)){
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
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
    printf("---------------------------------------------------------------------\n");
  }else{
    printf("Código de produto inválido!\n");
    printf("---------------------------------------------------------------------\n");
  }
}


/* 
 * método de execução da query4
 */
void query4(Faturacao F, Produtos prod, int decisao){
  Informacao info=NULL;
  LISTA_STRING lista=(LISTA_STRING)malloc(sizeof(PRODUTO)*2000), s;
  char ch;
  int i,n=0,filial1=0,filial2=0,filial3=0;
  
  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  if(decisao==0){ /*resultados globais , ou seja, soma das 3 filiais*/
    if (prod){
      for(ch='A';ch<='Z';ch++){
        s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
        for(i=0; s[i]!=NULL;i++){
          info=searchInformacao(F,s[i]);
          if(info){
            if(nuncaCompradoGlobal(info)==0){ /*passamos 0 pois 0 significa todas as filiais*/
              lista[n]=getCodigoProduto(info);
              n++;
            }
          }
        }
      }
    }
    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
    printf("Existem %d códigos de produtos que ninguém comprou!\n",n);
  }else{ /*filial a filial*/
    if (prod){
      for(ch='A';ch<='Z';ch++){
        s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
        for(i=0; s[i]!=NULL;i++){
          info=searchInformacao(F,s[i]);
          if(nuncaCompradoFilial(info,1)==0){ /*passamos 1 para procurar na filial 1*/
            lista[n]=malloc(sizeof(PRODUTO));
            lista[n]=getCodigoProduto(info);
            n++;
            filial1++;
          }if(nuncaCompradoFilial(info,2)==0){ /*passamos 2 para procurar na filial 2*/
            lista[n]=malloc(sizeof(PRODUTO));
            lista[n]=getCodigoProduto(info);
            n++;
            filial2++;
          }if(nuncaCompradoFilial(info,3)==0){ /*passamos 3 para procurar na filial 3*/
            lista[n]=malloc(sizeof(PRODUTO));
            lista[n]=getCodigoProduto(info);
            n++;
            filial3++;
          }
        }
      }
    }
    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);

    printf("Existem %d códigos de produtos que ninguém comprou na filial 1!\n",filial1);
    printf("Existem %d códigos de produtos que ninguém comprou na filial 2!\n",filial2);
    printf("Existem %d códigos de produtos que ninguém comprou na filial 3!\n",filial3);
  }
  imprimirLista(lista,10,9,0);
}


/* 
 * método de execução da query5
 */
void query5(Historial h[], CLIENTE cod_cliente){
  int mes;
  HistorialCliente c1 = searchHistorialCliente(h[0],cod_cliente);
  HistorialCliente c2 = searchHistorialCliente(h[1],cod_cliente);
  HistorialCliente c3 = searchHistorialCliente(h[2],cod_cliente);

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  if(c1 || c2 || c3){
    printf("\033[1m Mês\t\tFilial 1\tFilial 2\tFilial3\n\033[0m");
    for(mes=0;mes<12;mes++){
      printf("  %d\t\t %d\t\t %d\t\t %d\n",mes+1,getValorTabela(c1,mes),getValorTabela(c2,mes),getValorTabela(c3,mes));
    }
  }else{
    printf("Código de cliente inválido!\n");
  }
  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
  printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
  printf("---------------------------------------------------------------------\n");
}


/* 
 * método de execução da query6
 */
void query6(Faturacao f, Produtos prod, int m1, int m2){
  int i,mes,filial,vTotal=0,qTotal=0;
  double fTotal=0;
  LISTA_STRING s;
  char ch;
  Informacao temp=NULL;

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  if((m1<=m2) && m1>0 && m1 <=12 && m2>0 && m2 <=12 ){
    for(ch='A';ch<='Z';ch++){
      s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
      for(i=0; s[i]!=NULL;i++){
        temp = searchInformacao(f,s[i]);
        for(mes=m1-1;mes<=m2-1;mes++){
          vTotal+=getNumeroVendas(temp,mes);
          for(filial=0;filial<3;filial++){
            qTotal+=getQuantidadeNormal(temp,mes,filial)+getQuantidadePromocao(temp,mes,filial);
            fTotal+=getFaturadoNormal(temp,mes,filial)+getFaturadoPromocao(temp,mes,filial);
          }
        }
      }
    }
    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec */
    printf("Total de produtos vendidos: %d\n",vTotal); 
    printf("Total de unidades vendidas: %d\n",qTotal); 
    printf("Total faturado: %f\n",fTotal);
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
    printf("---------------------------------------------------------------------\n");
  }else{
    printf("Introduza um intervalo de meses correto!\n");
  }
}

/* 
 * método de execução da query7
 */
void query7(Historial h[]){
  int i,n=0;
  LISTA_STRING lista=(LISTA_STRING)malloc(sizeof(CLIENTE)*2000),s;
  char ch;
  HistorialCliente temporario1,temporario2,temporario3;

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  temporario1=temporario2=temporario3=NULL;

  if (h){
    for(ch='A';ch<='Z';ch++){
      s=toString(getHistorialLetra(h[0],ch),getTotalHistorial(h[0]));
      for(i=0; s[i]!=NULL;i++){
        temporario1=searchHistorialCliente(h[0],s[i]);
        temporario2=searchHistorialCliente(h[1],s[i]);
        temporario3=searchHistorialCliente(h[2],s[i]);
        if(getComprouFilial(temporario1)==1 && getComprouFilial(temporario2)==1 && getComprouFilial(temporario3)==1){ 
          lista[n]=malloc(sizeof(CLIENTE));
          lista[n]=getCodigoHistorialCliente(temporario1);
          n++;
        }
      }
    }
    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
    printf("Existem %d clientes que compraram em todas as filiais!\n",n);
    imprimirLista(lista,10,9,0);
  }
}

/* 
 * método de execução da query8
 */
void query8(Filial vf, PRODUTO produto){
  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  
  LISTA_STRING tempN,tempP,listaN,listaP;
  ListaProduto lp=NULL;
  Historico h=NULL;
  int i,mes,qN,qP,n=0,p=0;
  listaN=(LISTA_STRING)malloc(sizeof(PRODUTO)*1000);
  listaP=(LISTA_STRING)malloc(sizeof(PRODUTO)*1000);

  lp= searchListaProduto(vf,produto);
  begin = clock(); /*init contador*/

  if(lp){
    for(mes=0;mes<12;mes++){
      h=getHistorico(lp,mes);
      if(h){
        if(getClientesN(h)){
          tempN=getListaVendasFilialN(h,vf);
          for(qN=0;tempN[qN]!=NULL;qN++){
            listaN[n]=tempN[qN];
            n++;
          }
        }
        if(getClientesP(h)){
          tempP=getListaVendasFilialP(h,vf);
          for(qP=0;tempP[qP]!=NULL;qP++){
            listaP[p]=tempP[qP];
            p++;
          }
        }
      }
    }

    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/

    printf("Quantidade de clientes que compraram em modo N: %d\n",n);
    printf("Lista de clientes que compraram em modo N: ");
    for(i=0;listaN[i]!=NULL;i++) printf("%s ",listaN[i]);
    printf("\n");

    printf("Quantidade de clientes que compraram em modo P: %d\n",p);
    printf("Lista de clientes que compraram em modo P: ");
    for(i=0;listaP[i]!=NULL;i++) printf("%s ",listaP[i]);
    printf("\n");
    printf("---------------------------------------------------------------------\n");
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
  }else{
    printf("Introduza um código de produto válido!\n");
  }
}

/* 
 * método de execução da query9
 */
void query9(Historial h[], CLIENTE cod_cliente, int m){
  HistorialCliente temp1,temp2,temp3;
  LISTA_STRING lista_produtos[3],lista_mes;
  LISTA_INT quantidade[3],quantidade_mes, mes[3], copia;
  int i,x, j=0, k,max;

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  temp1=temp2=temp3=NULL;

  temp1 = searchHistorialCliente(h[0],cod_cliente);
  temp2 = searchHistorialCliente(h[1],cod_cliente);
  temp3 = searchHistorialCliente(h[2],cod_cliente);
  if( (temp1 || temp2 || temp3) && m>=1 && m<=12){
    lista_mes=(LISTA_STRING)malloc(sizeof(CLIENTE)*1000);
    quantidade_mes=(LISTA_INT)malloc(sizeof(int)*1000);
    
    lista_produtos[0]=getProdutosCliente(temp1);
    quantidade[0]=getQuantidadeProdutos(temp1);
    mes[0]=getMesVenda(temp1);

    lista_produtos[1]=getProdutosCliente(temp2);
    quantidade[1]=getQuantidadeProdutos(temp2);
    mes[1]=getMesVenda(temp2);

    lista_produtos[2]=getProdutosCliente(temp3);
    quantidade[2]=getQuantidadeProdutos(temp3);
    mes[2]=getMesVenda(temp3);

    for(x=0;x<3;x++){
      for(i=0;lista_produtos[x][i]!=NULL;i++){
        if(mes[x][i]==m){
          lista_mes[j]=lista_produtos[x][i];
          quantidade_mes[j]=quantidade[x][i];
          j++;
        }
      }
    }

    copia=quantidade_mes;
  
    printf("\033[1m Produto    Mês\t   Total comprado\033[0m\n");
    for(i=0;i<j;i++){
      max=valor_max(j,copia);
      for(k=0;quantidade_mes[k]!=max;k++); /*percorre o array ate encontrar o valor, ou seja, descobre a posicao do mesmo*/  
        printf(" %s     %d           %d\n", lista_mes[k],m,quantidade_mes[k]);
      quantidade_mes[k]=0;
    }

    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query*/
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
    printf("---------------------------------------------------------------------\n");
  }else{
    printf("Introduza um código de cliente válido!\n");
  }
}

/* 
 * método de execução da query10
 */
void query10(Filial vf[], Produtos prod, int n){
  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  int i,j, conta=0,posicao=0, max,pos=0;
  LISTA_INT qClientes,filial1,filial2,filial3,total,copia;
  LISTA_STRING s=NULL,lista = (LISTA_STRING)malloc(sizeof(PRODUTO)*180000),imprimir=(LISTA_STRING)malloc(sizeof(PRODUTO)*180000);
  char ch;
  ListaProduto p[3];

  qClientes=(LISTA_INT)malloc(sizeof(int)*180000);
  filial1=(LISTA_INT)malloc(sizeof(int)*180000);
  filial2=(LISTA_INT)malloc(sizeof(int)*180000);
  filial3=(LISTA_INT)malloc(sizeof(int)*180000);
  total=(LISTA_INT)malloc(sizeof(int)*180000);
  
  begin = clock(); /*init contador*/

  if (vf){
    for(ch='A';ch<='Z';ch++){
      s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
      for(i=0; s[i]!=NULL;i++){
        conta++;
        p[0]=searchListaProduto(vf[0],s[i]);
        p[1]=searchListaProduto(vf[1],s[i]);
        p[2]=searchListaProduto(vf[2],s[i]);
        if(p[0] || p[1] || p[3]){
          lista[posicao]=malloc(sizeof(PRODUTO));
          lista[posicao]=s[i];
          qClientes[posicao]=getQuantidadeClientes(p[0])+getQuantidadeClientes(p[1])+getQuantidadeClientes(p[2]);
          filial1[posicao]=getQuantidadeVendida(p[0]);
          filial2[posicao]=getQuantidadeVendida(p[1]);
          filial3[posicao]=getQuantidadeVendida(p[2]);
          total[posicao]=filial1[posicao]+filial2[posicao]+filial3[posicao];
          posicao++;
        }
      }
    }
  }

  copia=total;

  for(j=0;j<n;j++){
    max=valor_max(conta,copia);
    for(i=0;total[i]!=max;i++); /*percorre o array ate encontrar o valor, ou seja, descobre a posicao do mesmo*/  
      imprimir[pos]=(STRING)malloc(sizeof(char)*1000);
      sprintf(imprimir[pos],"\033[1mCódigo:\033[0m%s \033[1mClientes:\033[0m%d \033[1mTotal:\033[0m%d \033[1mF1:\033[0m%d \033[1mF2:\033[0m%d \033[1mF3:\033[0m%d", lista[i],qClientes[i],total[i],filial1[i],filial2[i],filial3[i]);
      pos++;
    total[i]=0;
  }
  imprimir[pos]='\0';
  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
  printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
  imprimirLista(imprimir,10,1,n);
  printf("---------------------------------------------------------------------\n");
}


/* 
 * método de execução da query11
 */
void query11(Historial h[], CLIENTE cod_cliente){
  int i,j,x,flag=0,total=0,conta, pos[3];
  double faturado=0,max, valores[3];
  clock_t begin, end; /*Contadores de tempo de execucao*/
  double time_spent;
  LISTA_INT quantidades=(LISTA_INT)malloc(sizeof(int)*180000),quantidades_backup;
  LISTA_FLOAT faturacoes=(LISTA_FLOAT)malloc(sizeof(double)*180000),copia=(LISTA_FLOAT)malloc(sizeof(double)*180000),faturacoes_backup;
  LISTA_STRING lista=(LISTA_STRING)malloc(sizeof(STRING)*180000),lista_backup;
  HistorialCliente temp[3];

  begin = clock(); /*init contador*/

  temp[0]= searchHistorialCliente(h[0],cod_cliente);
  temp[1]= searchHistorialCliente(h[1],cod_cliente);
  temp[2]= searchHistorialCliente(h[2],cod_cliente);

  if(temp[0] || temp[1] || temp[2] ){
    for(x=0;x<3;x++){
      lista_backup = getProdutosCliente(temp[x]);
      quantidades_backup = getQuantidadeProdutos(temp[x]);
      faturacoes_backup = getFaturacaoProdutos(temp[x]);

      for(i=0;lista_backup[i]!=NULL;i++){
        lista[flag]=malloc(sizeof(char)*7);
        strcpy(lista[flag],lista_backup[i]);
        quantidades[flag]=quantidades_backup[i];
        faturacoes[flag]=faturacoes_backup[i];
        flag++;      
      }
      copia=faturacoes;
    }

    for(i=0;lista[i]!=NULL;i++){ /*soma as quantidades compradas, bem como o € gasto*/
      total+=quantidades[i];
      faturado+=faturacoes[i];
    }

    for(conta=0;lista[conta]!=NULL;conta++);

    printf("Produtos nos quais o cliente \033[1m%s\033[0m gastou mais dinheiro durante o ano: \033[1m(top 3)\033[0m\n\n", cod_cliente);
    for(i=0;i<3;i++){
      max=valor_max_float(conta,copia);
      valores[i]=max;
      for(j=0;copia[j]!=max;j++); /*percorre o array ate encontrar o valor, ou seja, descobre a posicao do mesmo*/  
      printf("\t\t\t\t%s %f\n",lista[j],max);
      copia[j]=0;
      pos[i]=j;
    }

    faturacoes[pos[0]]=valores[0];
    faturacoes[pos[1]]=valores[1];
    faturacoes[pos[2]]=valores[2];

    printf("\nNo total, o cliente \033[1m%s\033[0m comprou \033[1m%d\033[0m produtos, num valor total de \033[1m%f\033[0m !\n",cod_cliente,total,faturado);

    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/

    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
    printf("---------------------------------------------------------------------\n");
    /*setFaturacaoProdutos(temp, faturacoes);*/
  }else{
    printf("Introduza um código de cliente válido!\n");
  }
}


/* 
 * método de execução da query12
 */
void query12(Historial h[], Produtos prod, Filial vf[]){
  int i,clientes=0,produtos=0;
  LISTA_STRING s;
  char ch;
  HistorialCliente temporarioC[3];
  ListaProduto temporarioP[3];

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  temporarioP[0]=temporarioP[1]=temporarioP[2]=NULL;
  if (h && prod){
    for(ch='A';ch<='Z';ch++){
      s=toString(getHistorialLetra(h[0],ch),getTotalHistorial(h[0]));
      for(i=0; s[i]!=NULL;i++){
        temporarioC[0]=searchHistorialCliente(h[0],s[i]);
        temporarioC[1]=searchHistorialCliente(h[1],s[i]);
        temporarioC[2]=searchHistorialCliente(h[2],s[i]);
        if(getComprouFilial(temporarioC[0])==0 && getComprouFilial(temporarioC[1])==0 && getComprouFilial(temporarioC[2])==0){ /*nunca comprou */
          clientes++;
        }
      }
    }
    for(ch='A';ch<='Z';ch++){
      s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
      for(i=0; s[i]!=NULL;i++){
        temporarioP[0]=searchListaProduto(vf[0],s[i]);
        temporarioP[1]=searchListaProduto(vf[1],s[i]);
        temporarioP[2]=searchListaProduto(vf[2],s[i]);
        if(getQuantidadeVendida(temporarioP[0])==0 && getQuantidadeVendida(temporarioP[1])==0 && getQuantidadeVendida(temporarioP[2])==0){ /*nunca comprou */
          produtos++;
        }
      }
    }
    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
    printf("\033[1m\x1b[31mSucesso, demoramos %fs!\x1b[0m\033[0m \n",time_spent);
    printf("Existem %d clientes que nunca compraram!\n",clientes);
    printf("Existem %d produtos que nunca foram comprados!\n",produtos);
    printf("---------------------------------------------------------------------\n");
  }
}
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

int valor_max(int n, int valores[]) {
  int i;
  int max = valores[0];
  for(i = 1; i < n; ++i) {
        max = valores[i] > max ? valores[i] : max;
  }
  return max;
}

/*QUERIES*/

void exec(Produtos prod, Clientes cli, Faturacao f, VendasFilial vf){
  int decisao; /*para o switch*/
  printf("\033[1mIntroduza o número da query a executar: \033[0m");
  scanf("%d", &decisao);
  switch (decisao){
  char ch;
  char codigo[6];
  int global;
  int mes;
  int filial;
    case -1:
      puts("Execução cancelada pelo utilizador!");
      puts("---------------------------------------------------------------------");
      exit(0);
      break;
    case 1:
      puts("\033[1mFicheiros já validados e guardados!");
      puts("---------------------------------------------------------------------\033[0m");
      break;
    case 2:
      puts("\033[1m-------------------------Query 2--------------------------\033[0m");
      printf("\033[1mIntroduza a letra para pesquisar: \033[0m");
      scanf(" %c", &ch);
      query2(prod,ch);
      break;
    case 3:
      puts("\033[1m-------------------------Query 3--------------------------\033[0m");
      printf("\033[1mIntroduza o mês de pesquisa: \033[0m ");
      scanf(" %d", &mes);
      printf("\033[1mIntroduza o código de produto: \033[0m ");
      scanf(" %s", codigo);
      printf("\033[1mDeseja ver os resultados por filial (1) ou global (0)? \033[0m ");
      scanf(" %d", &global);
      if((global==0 || global==1) && (mes>=1 && mes<=12)) query3(f,mes,codigo,global);
      else puts("Introduza valores corretos (mês e decisão)!");
      break;
    case 4:
      puts("\033[1m-------------------------Query 4--------------------------\033[0m");
      printf("\033[1mDeseja ver os resultados por filial (1) ou global (0)? \033[0m ");
      scanf(" %d", &global);
      if(global==0 || global==1) query4(f,prod,global);
      else puts("Introduza uma decisão válida (0 ou 1)!");
      break;
    case 5:
      puts("\033[1m-------------------------Query 5--------------------------\033[0m");
      printf("\033[1mIntroduza o código de cliente: \033[0m ");
      scanf(" %s", codigo);
      query5(cli,codigo);
      break;
    case 6:
      puts("\033[1m-------------------------Query 6--------------------------\033[0m");
      printf("\033[1mIntroduza o mês inicial de pesquisa: \033[0m ");
      scanf(" %d", &mes);
      printf("\033[1mIntroduza o mês final de pesquisa: \033[0m ");
      scanf(" %d", &filial);
      query6(f,prod,mes,filial);
      break;
    case 7:
      puts("\033[1m-------------------------Query 7--------------------------\033[0m");
      query7(cli);
      break;
    case 8:
      puts("\033[1m-------------------------Query 8--------------------------\033[0m");
      printf("\033[1mIntroduza o código de produto: \033[0m ");
      scanf(" %s", codigo);
      printf("\033[1mIntroduza a filial para pesquisar: \033[0m ");
      scanf(" %d", &filial);
      if(filial==1 || filial==2 || filial==3) query8(vf,codigo,filial);
      else puts("Introduza um número de filial válido!");
      break;

    case 10:
      puts("\033[1m-------------------------Query 10-------------------------\033[0m");
      printf("\033[1mIntroduza o número de produtos a listar: \033[0m ");
      scanf(" %d", &mes);
      query10(prod,mes);
      break;
    case 11:
      puts("\033[1m-------------------------Query 11-------------------------\033[0m");
      printf("\033[1mIntroduza o código de cliente: \033[0m ");
      scanf(" %s", codigo);
      query11(cli,codigo);
      break;
    case 12:
      puts("\033[1m-------------------------Query 12-------------------------\033[0m");
      query12(cli,prod);
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
    printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
    imprimirLista(lista,10,9);
  }else{
    printf("Introduza uma letra maiúscula!\n");
  }
  printf("---------------------------------------------------------------------\n");
}

void query3(Faturacao F, int mes, char *s, int global){
  Informacao info;
  clock_t begin, end; /*Contadores de tempo de execucao*/
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
    printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
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
  
  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

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
    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
    printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
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
    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
    printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);

    printf("Existem %d códigos de produtos que ninguém comprou na filial 1!\n",filial1);
    printf("Existem %d códigos de produtos que ninguém comprou na filial 2!\n",filial2);
    printf("Existem %d códigos de produtos que ninguém comprou na filial 3!\n",filial3);
  }
  imprimirLista(lista,10,9);
}

void query5(Clientes cli, char *cod_cliente){
  int mes;
  Cliente c = searchCliente(cli,cod_cliente);

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  if(c){
    printf("\033[1m Mês\t\tFilial 1\tFilial 2\tFilial3\n\033[0m");
    for(mes=0;mes<12;mes++){
      printf("  %d\t\t %d\t\t %d\t\t %d\n",mes+1,getValorTabela(c,mes,0),getValorTabela(c,mes,1),getValorTabela(c,mes,2));
    }
  }else{
    printf("Código de cliente inválido!\n");
  }
  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
  printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
}

void query6(Faturacao f, Produtos prod, int m1, int m2){
  int i,mes,filial,qTotal=0;
  float fTotal=0;
  char **s,ch;
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
          for(filial=0;filial<3;filial++){
            qTotal+=getQuantidadeNormal(temp,mes,filial)+getQuantidadePromocao(temp,mes,filial);
            fTotal+=getFaturadoNormal(temp,mes,filial)+getFaturadoPromocao(temp,mes,filial);
          }
        }
      }
    }
  }else{
    printf("Introduza um intervalo de meses correto!\n");
  }
  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
  printf("Total de vendas registadas: %d\n",qTotal); 
  printf("Total faturado: %f\n",fTotal);
  printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
}

void query7(Clientes cli){
  int i,n=0;
  char **lista=(char**)malloc(sizeof(char**)),**s,ch;
  Cliente temporario=NULL;

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  if (cli){
    for(ch='A';ch<='Z';ch++){
      s=toString(getClientesLetra(cli,ch),getTotalClientes(cli));
      for(i=0; s[i]!=NULL;i++){
        temporario=searchCliente(cli,s[i]);
        if(getComprouFilial(temporario,0)==1 && getComprouFilial(temporario,1)==1 && getComprouFilial(temporario,2)==1){ 
          lista[n]=malloc(sizeof(char*));
          lista[n]=getCodigoCliente(temporario);
          n++;
        }
      }
    }
  }
  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
  printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
  
  printf("Existem %d clientes que compraram em todas as filiais!\n",n);
  imprimirLista(lista,10,9);
}

void query8(VendasFilial vf,char *produto, int filial){
  int i,mes,qN,qP,n=0,p=0;
  char **tempN,**tempP, **listaN=(char**)malloc(sizeof(char*)*100), **listaP=(char**)malloc(sizeof(char*)*100);
  Historico h=NULL;
  ListaProduto lp = searchListaProduto(vf,produto);

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  if(lp){
    for(mes=0;mes<12;mes++){
      h=getHistorico(lp,mes,filial-1);
      if(h){
        tempN=getClientesN(h);
        tempP=getClientesP(h);

        if(tempN)
          for(qN=0;tempN[qN]!=NULL;qN++){
            listaN[n]=malloc(sizeof(char*));
            listaN[n]=tempN[qN];
            n++;
          }
      
        if(tempP)
          for(qP=0;tempP[qP]!=NULL;qP++){
            listaP[p]=malloc(sizeof(char*));
            listaP[p]=tempP[qP];
            p++;
          }
      }
    }

    end = clock(); /*end contador*/
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/
    printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);

    printf("Quantidade de clientes que compraram em modo N: %d\n",n);
    printf("Lista de clientes que compraram em modo N: ");
    for(i=0;listaN[i]!=NULL;i++) printf("%s ",listaN[i]);
    printf("\n");

    printf("Quantidade de clientes que compraram em modo P: %d\n",p);
    printf("Lista de clientes que compraram em modo P: ");
    for(i=0;listaP[i]!=NULL;i++) printf("%s ",listaP[i]);
    printf("\n");
  }else{
    printf("Introduza um código de produto válido!\n");
  }
}

void query10(Produtos prod, int n){
  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  int i,j, conta=0,posicao=0, *qClientes,*filial1,*filial2,*filial3,*total,*copia,max;
  char **s,ch,**lista = (char**)malloc(sizeof(char*)*190000);
  Produto p=NULL;

  qClientes=(int*)malloc(sizeof(int)*190000);
  filial1=(int*)malloc(sizeof(int)*190000);
  filial2=(int*)malloc(sizeof(int)*190000);
  filial3=(int*)malloc(sizeof(int)*190000);
  total=(int*)malloc(sizeof(int)*190000);
  
  begin = clock(); /*init contador*/

  if (prod){
    for(ch='A';ch<='Z';ch++){
      s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
      for(i=0; s[i]!=NULL;i++){
        conta++;
        p=searchProduto(prod,s[i]);
        if(p){
          lista[posicao]=malloc(sizeof(char*));
          lista[posicao]=s[i];
          qClientes[posicao]=getQuantidadeClientes(p);
          filial1[posicao]=getQuantidadeVendidaFilial(p,0);
          filial2[posicao]=getQuantidadeVendidaFilial(p,1);
          filial3[posicao]=getQuantidadeVendidaFilial(p,2);
          total[posicao]=filial1[posicao]+filial2[posicao]+filial3[posicao];
          posicao++;
        }
      }
    }
  }

  copia=total;
  
  printf("\033[1m Código\tClientes\tTotal\tFilial 1\tFilial 2\tFilial 3\033[0m\n");
  for(j=0;j<n;j++){
    max=valor_max(conta,copia);
    for(i=0;total[i]!=max;i++); /*percorre o array ate encontrar o valor, ou seja, descobre a posicao do mesmo*/  
    printf(" %s     %d           %d     %d             %d             %d\n", 
      lista[i],
      qClientes[i],
      total[i],
      filial1[i],
      filial2[i],
      filial3[i]);
    total[i]=0;
  }

  /*for(i=0;lista[i];i++) printf("cod %s qC %d f1 %d f2 %d f3 %d\n",lista[i],qClientes[i],filial1[i],filial2[i],filial3[i]);*/
  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
  printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
}

void query11(Clientes c, char* cod_cliente){
  int *quantidades,i,total=0;
  float *faturacoes,*copia,faturado=0,largest[3];
  clock_t begin, end; /*Contadores de tempo de execucao*/
  double time_spent;
  char **lista, **tres_maiores = (char**)malloc(sizeof(char*));
  Cliente temp;

  begin = clock(); /*init contador*/

  temp = searchCliente(c,cod_cliente);
  lista= getProdutosCliente(temp);
  quantidades = getQuantidadeProdutos(temp);
  faturacoes = getFaturacaoProdutos(temp);

  for(i=0;lista[i]!=NULL;i++){ /*soma as quantidades compradas, bem como o € gasto*/
    total+=quantidades[i];
    faturado+=faturacoes[i];
  }

  copia=faturacoes;
  largest[0] = 0;
  largest[1] = 0;
  largest[2] = 0;
 
  for(i=0; copia[i]; i++) {
    if(copia[i] > largest[0] && copia[i] < largest[1] && copia[i] < largest[2]) {
      largest[0] = copia[i];
      tres_maiores[0] = lista[i];
      copia[i]=0;
    }
    if(copia[i] > largest[1] && copia[i] > largest[0] && copia[i] < largest[2]) {;
      largest[1] = copia[i];
      tres_maiores[1] = lista[i];
      copia[i]=0;
    }
    if(copia[i] > largest[2] && copia[i] > largest[0] && copia[i] > largest[1]) {;
      largest[2] = copia[i];
      tres_maiores[2] = lista[i];
      copia[i]=0;
    }
  }

  printf("Produtos nos quais o cliente \033[1m%s\033[0m gastou mais dinheiro durante o ano: \033[1m(top 3)\033[0m\n\n", cod_cliente);
  for(i=0;i<3;i++) printf("\t\t\t\t\t%s %f\n",tres_maiores[i],largest[i]);

  printf("\nNo total, o cliente \033[1m%s\033[0m comprou \033[1m%d\033[0m produtos, num valor total de \033[1m%f\033[0m !\n",cod_cliente,total,faturado);

  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec*/

  printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
  printf("---------------------------------------------------------------------\n");
}

void query12(Clientes cli, Produtos prod){
  int i,clientes=0,produtos=0;
  char **s,ch;
  Cliente temporarioC=NULL;
  Produto temporarioP=NULL;

  double time_spent;
  clock_t begin, end; /*Contadores de tempo de execucao*/
  begin = clock(); /*init contador*/

  if (cli && prod){
    for(ch='A';ch<='Z';ch++){
      s=toString(getClientesLetra(cli,ch),getTotalClientes(cli));
      for(i=0; s[i]!=NULL;i++){
        temporarioC=searchCliente(cli,s[i]);
        if(getComprouFilial(temporarioC,0)==0 && getComprouFilial(temporarioC,1)==0 && getComprouFilial(temporarioC,2)==0){ /*nunca comprou */
          clientes++;
        }
      }
    }
    for(ch='A';ch<='Z';ch++){
      s=toString(getProdutosLetra(prod,ch),getTotalProdutos(prod));
      for(i=0; s[i]!=NULL;i++){
        temporarioP=searchProduto(prod,s[i]);
        if(getQuantidadeVendida(temporarioP)==0){ /*nunca comprou */
          produtos++;
        }
      }
    }
  }
  end = clock(); /*end contador*/
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/
  printf("\x1b[31mSucesso, demoramos %fs!\n\x1b[0m",time_spent);
  
  printf("Existem %d clientes que nunca compraram!\n",clientes);
  printf("Existem %d produtos que nunca foram comprados!\n",produtos);
}
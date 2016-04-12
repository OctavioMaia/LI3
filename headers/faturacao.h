#ifndef FATURACAO_H /* corresponde ao ficheiro faturacao.h */
#define FATURACAO_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaFaturacao;

typedef struct informacao *Informacao;
typedef struct faturacao *Faturacao;

/*gets*/
ListaFaturacao getFaturacaoLetra (Faturacao f, char ch);
PRODUTO getCodigoProduto(Informacao i);
int getNumeroVendas(Informacao i, int mes);
int getQuantidadeNormal(Informacao i, int mes, int filial);
int getQuantidadePromocao(Informacao i, int mes, int filial);
float getFaturadoNormal(Informacao i, int mes, int filial);
float getFaturadoPromocao(Informacao i, int mes, int filial);
int getTotalFaturacoes (Faturacao f);
LISTA_STRING  getListaFaturacaoLetra (Faturacao f, char ch);

/*Sets*/
void setCodigoProdutoFaturacao (Informacao i, PRODUTO s);
void addQuantidadeNormal(Informacao i, int mes, int filial, int quantidade);
void addQuantidadePromocao(Informacao i, int mes, int filial, int quantidade);
void addFaturadoNormal(Informacao i, int mes, int filial, float faturado);
void addFaturadoPromocao(Informacao i, int mes, int filial, float faturado);
void addFaturacao (Faturacao f, int total);

/*funcoes*/
Faturacao initFaturacao();
Informacao initInformacao();
Faturacao insertInformacao(Faturacao f, PRODUTO s);
Informacao searchInformacao(Faturacao f, PRODUTO s);

/*funcoes de atualizacao*/
void atualizaFaturacao(Faturacao f, Produtos p, Venda v);
int nuncaCompradoGlobal(Informacao i);
int nuncaCompradoFilial(Informacao i, int filial);

#endif
#ifndef FILIAL_H /* corresponde ao ficheiro filial.h */
#define FILIAL_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct nodo *ListaVFilial;

typedef struct mes_filial *Mes_Filial;
typedef struct historico *Historico;
typedef struct vendasfilial *Filial;
typedef struct listaproduto *ListaProduto;
typedef struct historialcliente *HistorialCliente;
typedef struct historial *Historial;

/*---*/
ListaVFilial getVendasFilialLetra (Filial vf, char ch);
Historico getHistorico(ListaProduto lp, int mes);

/*ints*/
int getTotalVendasFilial (Filial vf);
int getQuantidadeVendida(ListaProduto p);
int getQuantidadeClientes(ListaProduto p);
int getTotalHistorial(Historial h);
int getComprouFilial (HistorialCliente c, int filial);
int getValorTabela(HistorialCliente c, int mes, int filial);

/*listas*/
ListaClientes getClientesN(Historico h);
ListaClientes getClientesP(Historico h);
ListaClientes getHistorialLetra (Historial h, char ch);

CLIENTE getCodigoHistorialCliente (HistorialCliente hc);
CLIENTE getCodigoMesFilial(Mes_Filial mf);

LISTA_STRING  getProdutosCliente(HistorialCliente c);
LISTA_STRING getListaVendasFilialN (Historico h, Filial vf);
LISTA_STRING getListaVendasFilialP (Historico h, Filial vf);


LISTA_INT getQuantidadeProdutos(HistorialCliente c);
LISTA_INT getMesVenda(HistorialCliente c);
LISTA_FLOAT getFaturacaoProdutos(HistorialCliente c);

/*funcoes*/
Filial initVendasFilial();
Filial insertListaProduto(Filial f, PRODUTO s);

ListaProduto initListaProduto();
ListaProduto searchListaProduto(Filial f, PRODUTO s);

Historial initHistorial();
Historial insertHistorialCliente(Historial f, STRING s);

HistorialCliente initHistorialCliente();
HistorialCliente searchHistorialCliente(Historial f, STRING s);

/*funcoes void*/
void addHistorial (Historial h, int total);
void atualizaHistorico(Filial vf, Venda v);
void addVendasFilial (Filial vf, int total);
void setFaturacaoProdutos(HistorialCliente c, LISTA_FLOAT faturacao);
void updateCliente(Historial h,Filial vf, Venda v);

#endif
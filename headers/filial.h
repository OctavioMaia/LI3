#ifndef FILIAL_H /* corresponde ao ficheiro filial.h */
#define FILIAL_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaVFilial;

typedef struct mes_filial *Mes_Filial;
typedef struct historico *Historico;
typedef struct vendasfilial *Filial;
typedef struct listaproduto *ListaProduto;
typedef struct historialcliente *HistorialCliente;
typedef struct historial *Historial;

/*GETS*/
ListaVFilial getVendasFilialLetra (Filial vf, char ch);
int getTotalVendasFilial (Filial vf);
Historico getHistorico(ListaProduto lp, int mes);
STRING getCodigoListaProduto (ListaProduto p);
ListaClientes getClientesN(Historico h);
ListaClientes getClientesP(Historico h);
STRING getCodigoMesFilial(Mes_Filial mf);
int getQuantidadeMesFilial(Mes_Filial h);
LISTA_STRING getListaVendasFilialN (Historico h, Filial vf);
LISTA_STRING getListaVendasFilialP (Historico h, Filial vf);

/*produtos.c*/
int getQuantidadeVendidaFilial(ListaProduto p);
int getQuantidadeVendida(ListaProduto p);
int getQuantidadeClientes(ListaProduto p);

/*clientes.c*/
ListaClientes getHistorialLetra (Historial h, char ch);
int getTotalHistorial(Historial h);
int getComprouFilial (HistorialCliente c, int filial);
CLIENTE getCodigoHistorialCliente (HistorialCliente hc);
LISTA_STRING  getProdutosCliente(HistorialCliente c);
LISTA_INT getQuantidadeProdutos(HistorialCliente c);
LISTA_INT getMesVenda(HistorialCliente c);
LISTA_FLOAT getFaturacaoProdutos(HistorialCliente c);
int getValorTabela(HistorialCliente c, int mes, int filial);
void addHistorial (Historial h, int total);


/*SETS*/
void setCodigoListaProduto (ListaProduto p, PRODUTO s);
void addVendasFilial (Filial vf, int total);

/*produtos.c*/
void setQuantidadeVendidaFilial(ListaProduto p, int qt);
void setQuantidadeClientes(ListaProduto p, int qt);

/*clientes.c*/
void setComprouFilial (HistorialCliente c, int filial);
void setFaturacaoProdutos(HistorialCliente c, LISTA_FLOAT faturacao);

void updateCliente(Historial h,Filial vf, Venda v);

/*funcoes*/
Filial initVendasFilial();
Filial insertListaProduto(Filial f, PRODUTO s);

ListaProduto initListaProduto();
ListaProduto searchListaProduto(Filial f, PRODUTO s);

Historial initHistorial();
Historial insertHistorialCliente(Historial f, STRING s);

HistorialCliente initHistorialCliente();
HistorialCliente searchHistorialCliente(Historial f, STRING s);

/*funcoes auxiliares*/
void atualizaHistorico(Filial vf, Venda v);

#endif
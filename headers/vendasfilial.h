/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaVFilial;

typedef struct mes_filial *Mes_Filial;
typedef struct historico *Historico;
typedef struct vendasfilial *VendasFilial;
typedef struct listaproduto *ListaProduto;
typedef struct historialcliente *HistorialCliente;
typedef struct historial *Historial;

/*GETS*/
ListaVFilial getVendasFilialLetra (VendasFilial vf, char ch);
int getTotalVendasFilial (VendasFilial vf);
Historico getHistorico(ListaProduto lp, int mes);
STRING getCodigoListaProduto (ListaProduto p);
ListaClientes getClientesN(Historico h);
ListaClientes getClientesP(Historico h);
STRING getCodigoMesFilial(Mes_Filial mf);
int getQuantidadeMesFilial(Mes_Filial h);
LISTA_STRING getListaVendasFilialN (Historico h, VendasFilial vf);
LISTA_STRING getListaVendasFilialP (Historico h, VendasFilial vf);

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
void addVendasFilial (VendasFilial vf, int total);

/*produtos.c*/
void setQuantidadeVendidaFilial(ListaProduto p, int qt);
void setQuantidadeClientes(ListaProduto p, int qt);

/*clientes.c*/
void setComprouFilial (HistorialCliente c, int filial);
void setFaturacaoProdutos(HistorialCliente c, LISTA_FLOAT faturacao);

void updateCliente(Historial h,VendasFilial vf, Venda v);

/*funcoes*/
VendasFilial initVendasFilial();
VendasFilial insertListaProduto(VendasFilial f, PRODUTO s);

ListaProduto initListaProduto();
ListaProduto searchListaProduto(VendasFilial f, PRODUTO s);

Historial initHistorial();
Historial insertHistorialCliente(Historial f, STRING s);

HistorialCliente initHistorialCliente();
HistorialCliente searchHistorialCliente(Historial f, STRING s);

/*funcoes auxiliares*/
void atualizaHistorico(VendasFilial vf, Venda v);
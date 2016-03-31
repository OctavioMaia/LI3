/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaVFilial;

typedef struct mes_filial *Mes_Filial;
typedef struct historico *Historico;
typedef struct vendasfilial *VendasFilial;
typedef struct listaproduto *ListaProduto;

/*GETS*/
ListaVFilial getVendasFilialLetra (VendasFilial vf, char ch);
int getTotalVendasFilial (VendasFilial vf);
Historico getHistorico(ListaProduto lp, int mes, int filial);
STRING getCodigoListaProduto (ListaProduto p);
ListaClientes getClientesN(Historico h);
ListaClientes getClientesP(Historico h);
STRING getCodigoMesFilial(Mes_Filial mf);
int getQuantidadeMesFilial(Mes_Filial h);
LISTA_STRING getListaVendasFilialN (Historico h, VendasFilial vf);
LISTA_STRING getListaVendasFilialP (Historico h, VendasFilial vf);

/*SETS*/
void setCodigoListaProduto (ListaProduto p, PRODUTO s);
void addVendasFilial (VendasFilial vf, int total);
/*funcoes*/
VendasFilial initVendasFilial();
ListaProduto initListaProduto();
VendasFilial insertListaProduto(VendasFilial f, PRODUTO s);
ListaProduto searchListaProduto(VendasFilial f, PRODUTO s);

/*funcoes auxiliares*/
void atualizaHistorico(VendasFilial vf, Venda v);
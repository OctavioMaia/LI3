/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaVFilial;

typedef struct historico *Historico;
typedef struct vendasfilial *VendasFilial;
typedef struct listaproduto *ListaProduto;

/*GETS*/
AVL getVendasFilialLetra (VendasFilial vf, char ch);
int getTotalVendasFilial (VendasFilial vf);
Historico getHistorico(ListaProduto lp, int mes, int filial);
STRING getCodigoListaProduto (ListaProduto p);
LISTA_STRING  getClientesN(Historico h);
LISTA_INT getQuantidadeN(Historico h);
LISTA_STRING  getClientesP(Historico h);
LISTA_INT getQuantidadeP(Historico h);
LISTA_STRING  getListaVendasFilialLetra (VendasFilial vf, char ch);

/*SETS*/
void setCodigoListaProduto (ListaProduto p, STRING s);
void addVendasFilial (VendasFilial vf, int total);
/*funcoes*/
VendasFilial initVendasFilial();
ListaProduto initListaProduto();
VendasFilial insertListaProduto(VendasFilial f, STRING s);
ListaProduto searchListaProduto(VendasFilial f, STRING s);

/*funcoes auxiliares*/
void atualizaHistorico(VendasFilial vf, Venda v);
typedef struct historico *Historico;
typedef struct vendasfilial *VendasFilial;
typedef struct listaproduto *ListaProduto;

/*GETS*/
AVL getVendasFilialLetra (VendasFilial vf, char ch);
Historico getHistorico(ListaProduto lp, int mes, int filial);
char* getCodigoListaProduto (ListaProduto p);
int getTotalVendasFilial (VendasFilial vf);
char** getListaVendasFilialLetra (VendasFilial vf, char ch);

/*SETS*/
void setCodigoListaProduto (ListaProduto p, char *s);
void addVendasFilial (VendasFilial vf, int total);
/*funcoes*/
VendasFilial initVendasFilial();
ListaProduto initListaProduto();
VendasFilial insertListaProduto(VendasFilial f, char *s);
ListaProduto searchListaProduto(VendasFilial f, char *s);

/*funcoes auxiliares*/
void atualizaHistorico(VendasFilial vf, Venda v);
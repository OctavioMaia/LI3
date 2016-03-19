/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/
typedef struct node *ListaFaturacao;

typedef struct informacao *Informacao;
typedef struct faturacao *Faturacao;

AVL getFaturacaoLetra (Faturacao f, char ch);
PRODUTO getCodigoProduto(Informacao i);
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
void addFaturadoNormal(Informacao i, int mes, int filial, int faturado);
void addFaturadoPromocao(Informacao i, int mes, int filial, int faturado);
void addFaturacao (Faturacao f, int total);

/*funcoes*/
Faturacao initFaturacao();
Informacao initInformacao();
Faturacao insertInformacao(Faturacao f, PRODUTO s);
Informacao searchInformacao(Faturacao f, PRODUTO s);

/*funcoes de atualizacao*/
void atualizaFaturacao(Faturacao f, Produtos p, Clientes c, Venda v);
int nuncaCompradoGlobal(Informacao i);
int nuncaCompradoFilial(Informacao i, int filial);
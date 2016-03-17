/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

void imprimirLista(STRING *s,int c,int l);
void imprimirAux(STRING *s, int c , int l,int t, int pa);
void imprimirQueries();
int valor_max(int n, int valores[]);

void exec(Produtos prod, Clientes cli, Faturacao f, VendasFilial vf);
void query2(Produtos p, char ch);
void query3(Faturacao f, int mes, STRING s, int global);
void query4(Faturacao F, Produtos prod, int global);
void query5(Clientes cli, STRING cod_cliente);
void query6(Faturacao f, Produtos prod, int m1, int m2);
void query7(Clientes cli);
void query8(VendasFilial vf,STRING produto, int filial);
void query9(Clientes cli, STRING cod_cliente, int mes);
void query10(Produtos prod, int n);
void query11(Clientes c, STRING cod_cliente);
void query12(Clientes cli, Produtos prod);
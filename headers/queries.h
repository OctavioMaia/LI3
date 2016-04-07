#ifndef QUERIES_H /* corresponde ao ficheiro queries.h */
#define QUERIES_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

void imprimirLista(STRING *s,int c,int l);
void imprimirAux(STRING *s, int c , int l,int t, int pa);
void imprimirQueries();
int valor_max(int n, int valores[]);

void exec(Produtos prod, Clientes cli, Faturacao f, Filial vf[] ,Historial h);
void query2(Produtos p, char ch);
void query3(Faturacao f, int mes, PRODUTO s, int global);
void query4(Faturacao F, Produtos prod, int global);
void query5(Historial h, CLIENTE cod_cliente);
void query6(Faturacao f, Produtos prod, int m1, int m2);
void query7(Historial h);
void query8(Filial vf,PRODUTO produto);
void query9(Historial h, CLIENTE cod_cliente, int m);
void query10(Filial vf[], Produtos prod, int n);
void query11(Historial h, CLIENTE cod_cliente);
void query12(Historial h, Produtos prod, Filial vf[]);

#endif
void imprimirLista(char **s,int c,int l);
void imprimirAux(char **s, int c , int l,int t, int pa);

void exec(Produtos prod, Clientes cli, Faturacao f, VendasFilial vf);
void query2(Produtos p, char ch);
void query3(Faturacao f, int mes, char *s, int global);
void query4(Faturacao F, Produtos prod, int global);
void query5(Clientes cli, char *cod_cliente);
void query6(Faturacao f, Produtos prod, int m1, int m2);
void query7(Clientes cli);
void query8(VendasFilial vf,char *produto, int filial);

void query11(Clientes c, char* cod_cliente);
void query12(Clientes cli, Produtos prod);
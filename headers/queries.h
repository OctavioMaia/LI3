#ifndef QUERIES_H /* corresponde ao ficheiro queries.h */
#define QUERIES_H

/*@authors Alfredo Gomes, Cecília Marciel, Octávio Maia*/

/* Apresentar tal lista ao utilizador e permitir que o mesmo navegue 
na mesma, sendo tal lista apresentada por ordem alfabética; */
void imprimirLista(STRING *s,int c,int l, int opcao);
void imprimirAux(STRING *s, int c , int l,int t, int pa, int opcao);
void imprimirInit();
void imprimirQueries();
void freeAll(Produtos prod, Clientes cli, Faturacao f, Filial vf[] ,Historial h[]);

/*
 * Funcao de execucao do programa GereVendas.
 */
void exec(Produtos prod, Clientes cli, Faturacao f, Filial vf[] ,Historial h[]);

/* query2
 * Esta query tem como objectivo determinar a lista e 
 * o total de produtos cujo código se inicia por uma dada letra 
 * (maiúscula).  
 * @parametros - Apontador para catálogo Produtos - Produtos p
 *				 Letra que se pretende que seja efetuada a 
 *               procura - char ch
 */
void query2(Produtos p, char ch);

/* query3
 * Esta query tem como objectivo determinar e apresentar 
 * o número total de vendas e o total facturado com um dado
 * produto num dado mês, distinguindo os totais em modo N 
 * e os totais em modo P. O utilizador deverá    
 * decidir se pretende o resultado global ou os valores totais filial a filial.   
 * @parametros - Apontador para a faturação - Faturacao F
 * 				 Mês em que se pretende efectuar a procura -int mes
 * 				 Produto que se pretende procurar - PRODUTO s
 *				 Inteiro para decidir se pretende procurar por
 * 				 filial (1), ou global (0) - int global 
 */
void query3(Faturacao f, int mes, PRODUTO s, int global);

/* query4
 * Esta query tem como objectivo determinar a lista 
 * ordenada dos códigos dos produtos (e o seu número total), 
 * que ninguém comprou, podendo o utilizador decidir se pretende 
 * valores totais ou divididos pelas filiais.    
 * @parametros - Apontador para a faturação - Faturacao F
 * 				 Apontador para o catalogo de produtos - Produtos prod
 *				 Inteiro para decidir se pretende procurar por
 * 				 filial (1), ou global (0) - int decisao 
 */
void query4(Faturacao F, Produtos prod, int global);

/* query5
 * Esta query tem como objectivo criar uma tabela 
 * com o numero total de produtos comprados, dado um 
 * código de cliente, mês a mês.
 * @parametros - Array do historial relativo as filiais - Historial h[].
 *				 Código do cliente que se pretende procurar - CLIENTE cod_cliente. 
 */
void query5(Historial h[], CLIENTE cod_cliente);

/* query6
 * Esta query tem como objectivo determinar o total de 
 * vendas registadas num dado intervalo fechado de meses
 * e o total facturado. 
 * @parametros - Apontador para a faturação - Faturacao f
 *				 Apontador para o catálogo de produtos - Produtos prod
 *   			 Inteiros para limitar o intervalo de meses que se efectua 
 *				 a procura - int m1, int m2 
 */
void query6(Faturacao f, Produtos prod, int m1, int m2);

/* query7
 * Esta query tem como objectivo determinar a lista ordenada 
 * de códigos de clientes que realizaram compras em todas as filiais. 
 * @parametros - Array do historial relativo as filiais - Historial h[].
 */
void query7(Historial h[]);

/* query8
 * Esta query tem como objectivo determinar os códigos (e número total) 
 * dos clientes que compraram um dado um código de produto e duma filial, 
 * distinguindo entre compra N e compra P; 
 * @parametros - Filial onde se pretende procurar - Filial vf
 				 Produto que se pretende procurar - PRODUTO produto
 */
void query8(Filial vf,PRODUTO produto);

/* query9
 * Esta query tem como objectivo determinar a  lista  de  códigos  de 
 * produtos que mais comprou por quantidade, por ordem descendente, 
 * dado  um  código  de  cliente  e  um  mês.  
 * @parametros - Array do historial relativo as filiais - Historial h[].
 *				 Código do cliente que se pretende procurar - CLIENTE cod_cliente.
 *				 Mês em que se pretende efectuar a procura - int m.
 */
void query9(Historial h[], CLIENTE cod_cliente, int m);

/* query10
 * Esta query tem como objectivo criar  uma  lista dos N 
 * produtos mais  vendidos  em  todo  o  ano,  indicando  o 
 * número total de clientes e o número de unidades ven
 * didas, filial a filial; 
 * @parametros - Array relativo as filiais - Filial vl[].
 *				 Apontador para o catálogo de produtos - Produtos prod
 *   			 Inteiro com o numero de produtos a listar - int n 
 */
void query10(Filial vf[], Produtos prod, int n);

/* query11
 * Esta query tem como objectivo determinar quais os códigos 
 * dos 3 produtos em que mais gastou dinheiro durante o ano,
 * dado um código de cliente. 
 * @parametros - Array do historial relativo as filiais - Historial h[].
 *				 Código do cliente que se pretende procurar - CLIENTE cod_cliente.
 */
void query11(Historial h[], CLIENTE cod_cliente);

/* query12
 * Esta query tem como objectivo determinar o número de clientes 
 * registados que não realizaram compras bem como o número de 
 * produtos que ninguém comprou. 
 * @parametros - Array do historial relativo as filiais - Historial h[]
 * 				 Array relativo as filiais - Filial vl[].
 *				 Apontador para o catálogo de produtos - Produtos prod

 */
void query12(Historial h[], Produtos prod, Filial vf[]);

#endif
package source;

import java.util.*;

import static java.lang.System.out;

public class Queries {

	   public static void query2(Catalogo produtos){
	       Scanner sc = new Scanner(System.in);
	       Crono.start();
	       ArrayList<String> cat = produtos.getCodigosLetra('A');
	       
	       imprimirAux(cat,10,9,cat.size()/90,0);
	   }

	   /*private static void apresentarPaginas(ArrayList<String> lista, int linhas, int colunas){
	       Scanner sc = new Scanner(System.in);
	       int size = lista.size();
	       int paginaAtual = 1;
	       int paginas = size/(linhas*colunas);
	       if(size%(linhas*colunas) != 0) paginas++;
	       System.out.println("");
	       for(int i=0; i<colunas && i<size; i++){
	    	   for(int j=0; j<linhas && j<size; j++)
	    		   System.out.print(lista.get(i) + "\t");
	       	   System.out.println("");
	       }
	       System.out.printf("Página %d de %d (%d resultados  - %.2f segundos)\n", paginaAtual, paginas, size, Crono.stop());
	       while(true){
	           System.out.println("Introduza número de página (0 para sair)");
	           while(!sc.hasNextInt()) sc.nextLine();
	           paginaAtual = sc.nextInt();
	           while(paginaAtual < 0 || paginaAtual >paginas){
	               System.out.println("Página inválida");
	               System.out.printf("Introduza número de página (%d páginas, 0 para sair)\n",paginas);
	               while(!sc.hasNextInt()) 
	            	   sc.nextLine();
	               paginaAtual = sc.nextInt();
	           }
	           if(paginaAtual == 0) 
	        	   return;
	           System.out.println("");
	           for(int i=0; i<colunas && i<size; i++){
		    	   for(int j=0; j<linhas && j<size; j++)
		    		   System.out.print(lista.get(i) + "\t");
		       	   System.out.println("");
		       }
	           System.out.printf("Página %d de %d (%d resultados)\n", paginaAtual,paginas,size);
	       }
	   }*/
	   
	   private static void imprimirAux(List<String> s, int c , int l,int t, int pa) {
		   Scanner sc = new Scanner(System.in);
		   int j,p;
		   int i=0;
		   int y=0;
		   int total=0;

		   if(pa>=0){
			 out.println("----------------------------------Página "+pa+1+"----------------------------------");
		     for (i=0;i<l && s.get(y+1)!=null;i++){   
		         for (j=0;j<c && s.get(y)!=null;j++,y++,total++){
		             out.print(s.get(y)+"\t");
		         }
		       out.println("");
		     }
		       
		     out.println("----------------------------------------------------------------------------\n");
		     out.print("Existem "+(t+1)+" páginas. \nPágina a verificar? (+ pag. seguinte | - pag. anterior | 0 sair)");  

		     p=sc.nextInt();

		     List<String> prox =  s.subList(y,s.size()-y);
		     if (p=='+' && pa+1<t) imprimirAux(prox,c,l,t,pa+1); 
		     else if (p=='-') imprimirAux(prox,c,l,t,pa-1);
		     else if (p==-1 || p > t || p<=0) out.println("Exit!\n");
		     else imprimirAux (prox,c,l,t,p-1);   
		   }else{
			   out.println("Exit!\n");
		   }
		   sc.close();
		 }
	
}

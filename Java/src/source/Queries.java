package source;

import java.util.*;

import static java.lang.System.out;

public class Queries {

	public static void query1(Faturacao f) {
		Crono.start();
		ArrayList<String> l = f.getProdutosSemVendas();
		int total = f.getTotProdutosSemVendas();

		out.println("Existem " + total + " produtos que nunca foram comprados.");
		out.println("Demoramos " +Crono.print()+" segundos.");

		apresentarPaginas(l, 10);
	}
	
	public static void query2(Filial[] f) { //ta mal, temos que juntar tipo num array os clientes de todas as filiais e remover os repetidos
		int mes,filial, total_vendas=0, total_clientes=0;
		
		out.print("Introduza um mês: ");
		mes = Input.lerInt();
		
		Crono.start();
		for(filial=0;filial<3;filial++){
			TreeMap<String, DetalhesProduto> m = f[filial].getInformacaoProdutos();
			Set<String> keys = m.keySet();
			Iterator<String> it = keys.iterator();
			
			while(it.hasNext()){
				String s = it.next();
				//out.println("debug " + s);
				try{
					ProdutosMes dp = m.get(s).getProdutos().get(mes);
					total_vendas += dp.getQuantidadeVendida();
					total_clientes += dp.getQuantidadeClientes();
				}catch(Exception e){
					
				}
			}	
		}
		
		out.printf("No mês %d, foram realizadas %d vendas e houve %d clientes distintos.\n",mes,total_vendas,total_clientes);
		out.println("Demoramos " +Crono.print()+" segundos.");
	}

	public static void query3(Filial[] f){
		DetalhesCliente dc = null;
		String codigo;
		int filial,mes;
		int compras[] = new int[12];
		int qt_prod[] = new int[12];
		double faturado[] = new double[12];
		codigo = Input.lerString();
		Crono.start();		
		
		for(int i=0;i<12;i++){
			compras[i]=0;
			qt_prod[i]=0;
			faturado[i]=0;
		}
		
		for(filial=0;filial<3;filial++){
			try{
				dc = f[filial].getInformacaoClientes().get(codigo);
			}catch(Exception e){
			}
			for(mes=1;mes<=12;mes++){
				try{
					TreeMap<String, InfoProduto> tm  = dc.getComprasMes(mes).getInformacao();
					
					for(Map.Entry<String,InfoProduto> entry : tm.entrySet()) {
						InfoProduto value = entry.getValue();	  
						compras[mes-1]+=value.getNCompras();
						qt_prod[mes-1]++;
						faturado[mes-1]+=value.getGasto();	  
					}
				}catch(Exception e){
				}
			}
		}
		
		
		for(int i=0;i<12;i++)
			out.printf("Mês: " + (i+1) +" Compras: " + compras[i] /*+" Produtos: " + qt_prod[i]*/ + " Faturado:" +faturado[i] + "\n");		
	
		out.println("Demoramos " +Crono.print()+" segundos.");
	}
	
	private static void apresentarPaginas(ArrayList<String> lista, int sizePagina) {
		if (lista.isEmpty() || sizePagina == 0) return;
		Scanner sc = new Scanner(System.in);
		int size = lista.size();
		int paginaAtual = 1;
		int paginas = size / sizePagina;
		if (size % sizePagina != 0) paginas++;
		out.printf("--------------------Página %d--------------------\n",paginaAtual);
		for (int i = 0; i < sizePagina && i < size; i++)
			out.println((i + 1) + ".\t" + lista.get(i));
		out.printf("Página %d de %d (%d resultados  - %.2f segundos)\n", paginaAtual, paginas, size, Crono.stop());
		while (true) {
			out.println("Introduza número da página (0 para sair)");
			out.print("Página: ");
			while (!sc.hasNextInt())
				sc.nextLine();
			paginaAtual = sc.nextInt();
			while (paginaAtual < 0 || paginaAtual > paginas) {
				out.println("Página inválida");
				out.printf("Introduza número da página (%d páginas, 0 para sair)\n", paginas);
				while (!sc.hasNextInt())
					sc.nextLine();
				paginaAtual = sc.nextInt();
			}
			if (paginaAtual == 0)
				return;
			out.printf("--------------------Página %d--------------------\n",paginaAtual);
			for (int i = (paginaAtual - 1) * sizePagina; i < (paginaAtual * sizePagina) && i < size; i++)
				out.println((i + 1) + ".\t" + lista.get(i));
			out.printf("Página %d de %d (%d resultados)\n", paginaAtual, paginas, size);
		}
	}

}

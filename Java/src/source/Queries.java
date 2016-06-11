package source;

import java.util.*;
import java.util.Map.Entry;

import exceptions.ClienteInvalidoException;
import exceptions.DecisaoInvalidaException;
import exceptions.ProdutoInvalidoException;

import static java.lang.System.out;

import java.io.Serializable;
import java.text.DecimalFormat;

public class Queries implements Serializable{

	
	/**
	 * Lista ordenada alfabeticamente com os códigos dos produtos nunca comprados e o
	 * seu respectivo total.
	 * @param f informacao relativa as vendas.
	 */
	private static void query1(Faturacao f) {
		Crono.start();
		ArrayList<String> l = f.getProdutosSemVendas();
		int total = f.getTotProdutosSemVendas();

		out.println("Existem " + total + " produtos que nunca foram comprados.");
		out.println("Demoramos " +Crono.print()+" segundos.");

		apresentarPaginas(l, 10);
	}
	
	
	/**
	 * Dado um mês válido, determinar o número total global de vendas realizadas e o
     * número total de clientes distintos que as fizeram. 
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 */
	private static void query2(Filial[] f) {
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
		
		out.printf("No mês %d, foram realizadas %d vendas.\n",mes,total_clientes);

		out.println("Demoramos " +Crono.print()+" segundos.");
	}

	/**
	 * Dado um código de cliente, determinar, para cada mês, quantas compras fez,
	 * quantos produtos distintos comprou e quanto gastou no total.  	
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 * @throws ClienteInvalidoException Codigo do cliente não existe.
	 */
	private static void query3(Filial[] f) throws ClienteInvalidoException{
		DetalhesCliente dc = null;
		int filial,mes;
		int compras[] = new int[12];
		int qt_prod[] = new int[12];
		double faturado[] = new double[12];
		out.print("Introduza um código de cliente: ");
		String codigo = Input.lerString();
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
	
	/**
	 * Dado o código de um produto existente, determinar, mês a mês, quantas vezes foi
     * comprado, por quantos clientes diferentes e o total facturado
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 * @throws ProdutoInvalidoException Codigo do produto inválido.
	 */
	private static void query4(Filial[] f) throws ProdutoInvalidoException{
		DetalhesProduto dp = null;
		int mes,filial, total_comprado[] = new int[12], total_clientes[]= new int[12];
		double total_faturado[] = new double[12];
		String produto;
		
		out.print("Introduza um código produto: ");
		produto = Input.lerString();
		
		for(int i=0;i<12;i++){
			total_clientes[i]=0;
			total_comprado[i]=0;
			total_faturado[i]=0;
		}		
		
		Crono.start();
		for (filial = 0; filial < 3; filial++) {
			try {
				dp = f[filial].getInformacaoProdutos().get(produto);
			}catch(Exception e) {
				
			}
			for (mes = 1; mes <= 12; mes++) {
				try {
					total_clientes[mes - 1] += dp.getQuantidadeClientesMes(mes);
					total_comprado[mes - 1] += dp.getQuantidadeVendidaMes(mes);
					total_faturado[mes - 1] += dp.getFaturadoMes(mes);
				} catch (Exception e) {
					
				}
			}
		}
		
		out.println("Demoramos " +Crono.print()+" segundos.");
		for(mes=0;mes<12;mes++){
			out.printf("Mês: %d Total compras: %d Total clientes: %d Total faturado: %f\n",mes+1,total_comprado[mes],total_clientes[mes],total_faturado[mes]);
		}
	}
	
	/**
	 * Dado o código de um cliente determinar a lista de códigos de produtos que mais
     * comprou. 
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 * @throws ClienteInvalidoException Código do cliente inválido.
	 */
	private static void query5(Filial[] f) throws ClienteInvalidoException{
		DetalhesCliente dc = null;
		int filial,mes, qt;
		String cliente, produto;
		TreeMap<String,Integer> temp = new TreeMap<>();
		ArrayList<String> print = new ArrayList<>();
		
		out.print("Introduza um código de cliente: ");
		cliente = Input.lerString();
		
		Crono.start();
		for(filial=0;filial<3;filial++){
			try{
				dc = f[filial].getInformacaoClientes().get(cliente);
				for(mes=1;mes<=12;mes++){
					try{
						ComprasMes cm = dc.getComprasMes(mes);
						TreeMap<String, InfoProduto> tm = cm.getInformacao();
						
						for(Entry<String, InfoProduto> entry : tm.entrySet()){
							InfoProduto ip = entry.getValue();
							produto = entry.getKey();
							qt = ip.getQuantidade();
							
							if(!temp.containsKey(produto)){
								temp.put(produto, qt);
							}else{
								qt += temp.get(produto); //se ja existe, soma a qt que la estava à que temos
								temp.put(produto,qt);
							}
						}
					}catch(Exception e){
						
					}
				}
			}catch(Exception e){
				throw new ClienteInvalidoException();
			}
		}
		
		out.printf("Este cliente comprou %d produtos.\n", temp.size());

		Iterator<Entry<String, Integer>> it = sortDecrescente(temp).iterator();
		while (it.hasNext()) {
			Object element = it.next();
			String str = element.toString();
			String[] split = str.split("=");
			print.add("Produto: " + split[0] + " Quantidade: " + split[1]);
		}
		out.println("Demoramos " + Crono.print() + " segundos.");
		apresentarPaginas(print, 10);
	}
	
	/**
	 * Determinar o conjunto dos X produtos mais vendidos em todo o ano (em número de
	 * unidades vendidas) indicando o número total de distintos clientes que o
	 * compraram.	
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 */
	private static void query6(Filial[] f){
		int N,contador=0,filial,mes,qt=0;
		String codigo;
		TreeMap<String,Integer> map = new TreeMap<>();
		ArrayList<String> print = new ArrayList<>();
		
		out.print("Introduza o total de produtos a listar: ");
		N = Input.lerInt();
		Crono.start();
		
		for(filial=0;filial<3;filial++){
			TreeMap<String, DetalhesProduto> tm = f[filial].getInformacaoProdutos();
			
			for(Entry<String,DetalhesProduto> entry : tm.entrySet()){ //key = cod produto
				codigo = entry.getKey();
				for(mes=1;mes<=12;mes++){
					try{
						qt += entry.getValue().getQuantidadeVendidaMes(mes);
					}catch(Exception e){
						
					}
				}
				if(!map.containsKey(codigo)){
					map.put(codigo,qt);
				}else{
					map.put(codigo, map.get(codigo)+qt);
				}
				qt=0;
			}
		}
		
		Iterator<Entry<String, Integer>> it = sortDecrescente(map).iterator();
		while (it.hasNext() && contador<N) {
			Object element = it.next();
			String str = element.toString();
			String[] split = str.split("=");
			print.add("Produto: " + split[0] + " Quantidade: " + split[1]);
			contador++;
		}
		out.println("Demoramos " +Crono.print()+" segundos.");
		apresentarPaginas(print, 10);
	}

	/**
	 * Determinar, para cada filial, a lista dos três maiores compradores em termos de
	 * dinheiro facturado.
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 */
	private static void query7(Filial[] f){
		int filial,mes,contador=0;
		double qt[]= new double[3];
		qt[0]=qt[1]=qt[2]=0.0;
		String codigo;
		TreeMap<String,Double> map1 =  new TreeMap<>();
		TreeMap<String,Double> map2 =  new TreeMap<>();
		TreeMap<String,Double> map3 =  new TreeMap<>();
		
		Crono.start();
		for(filial=0;filial<3;filial++){
			TreeMap<String, DetalhesCliente> tm = f[filial].getInformacaoClientes();
			
			for(Entry<String, DetalhesCliente> entry : tm.entrySet()){ //key = cod produto
				codigo = entry.getKey();
				for(mes=1;mes<=12;mes++){
					try{
						qt[filial] += entry.getValue().getTotalFaturado();
					}catch(Exception e){
						
					}
				}
				if(filial==0) map1.put(codigo, qt[filial]);
				if(filial==1) map2.put(codigo, qt[filial]);
				if(filial==2) map3.put(codigo, qt[filial]);
				qt[filial]=0;
			}
		}
		
		out.println("Demoramos " +Crono.print()+" segundos.");
		for(filial=0; filial<3;filial++){
			Iterator<Entry<String, Double>> it = null;
			if(filial==0) it = sortDecrescente(map1).iterator();
			if(filial==1) it = sortDecrescente(map2).iterator();
			if(filial==2) it = sortDecrescente(map3).iterator();
			
			while (it.hasNext() && contador<3) {
				Object element = it.next();
				String str = element.toString();
				String[] split = str.split("=");
				out.printf("Filial: %d Cliente: %s  Quantidade: %s\n",filial+1,split[0],new DecimalFormat("#0.0000").format(Double.parseDouble(split[1])) );
				contador++;
			}
			contador=0;
		}
	}
	
	/**
	 * Determinar os códigos dos X clientes (sendo X dado pelo utilizador) que compraram
     * mais produtos diferentes.
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 */
	private static void query8(Filial[] f){
		int N,filial,contador=0;
		TreeMap<String,Integer> map = new TreeMap<>();
		ArrayList<String> print = new ArrayList<>();
		
		out.print("Introduza o total de clientes a listar: ");
		N = Input.lerInt();
		Crono.start();
		
		for(filial=0;filial<3;filial++){
			TreeMap<String, DetalhesCliente> tm = f[filial].getInformacaoClientes();
			
			for(Entry<String,DetalhesCliente> entry : tm.entrySet()){ //key = cliente
				if(!map.containsKey(entry.getKey())){
					map.put(entry.getKey(),entry.getValue().getListaProdutos().size());
				}else{
					map.put(entry.getKey(), map.get(entry.getKey())+entry.getValue().getListaProdutos().size());
				}
					
			}
		}
		
		Iterator<Entry<String, Integer>> it = sortDecrescente(map).iterator();
		while (it.hasNext() && contador<N) {
			Object element = it.next();
			String str = element.toString();
			String[] split = str.split("=");
			print.add("Cliente: " + split[0] + " Quantidade: " + split[1]);
			contador++;
		}
		out.println("Demoramos " +Crono.print()+" segundos.");
		apresentarPaginas(print, 10);
	}
	
	/**
	 * Dado o código de um produto que deve existir, determinar o conjunto dos X clientes
     * que mais o compraram e, para cada um, qual o valor gasto 
	 * @param f Informação das vendas relativas ás 3 Filiais.
	 */
	private static void query9(Filial[] f) {
		int N,filial,mes;
		String codigo,cliente;
		TreeMap<String,Integer> map1 = new TreeMap<>();
		TreeMap<String,Double> map2 = new TreeMap<>();
		ArrayList<String> array1 = new ArrayList<>();
		ArrayList<Integer> array2 = new ArrayList<>();
		ArrayList<Double> array3 = new ArrayList<>();
		ArrayList<String> print = new ArrayList<>();
		
		out.print("Introduza o código de produto: ");
		codigo = Input.lerString();
		out.print("Introduza o total de clientes a listar: ");
		N = Input.lerInt();
		Crono.start();
		
		for(filial=0;filial<3;filial++){
			TreeMap<String, DetalhesCliente> tm = f[filial].getInformacaoClientes();
			
			for(Entry<String,DetalhesCliente> entry : tm.entrySet()){
				cliente = entry.getKey();
				try{
					DetalhesCliente dc = entry.getValue();
					for(mes=1;mes<=12;mes++){
						try{
							TreeMap<String,InfoProduto> info = dc.getComprasMes(mes).getInformacao();
							if(info.containsKey(codigo)){
								if(map1.containsKey(cliente)){
									map1.put(cliente, map1.get(cliente)+info.get(codigo).getQuantidade());
									map2.put(cliente, map2.get(cliente)+info.get(codigo).getGasto());
								}else{
									map1.put(cliente, info.get(codigo).getQuantidade());
									map2.put(cliente, info.get(codigo).getGasto());
								}
							}
						}catch(Exception e){
							throw new ProdutoInvalidoException();
						}
					}
				}catch(Exception e){
					
				}
			}
		}
		
		for(Entry<String,Integer> entry: map1.entrySet()){
			String key = entry.getKey();
			Integer value = entry.getValue();
			Double gasto = map2.get(key);
			
			if(array1.contains(key)){
				int index = array1.indexOf(key);
				array1.add(index, key);
				array2.add(index, value);
				array3.add(index, gasto);
			}else{
				array1.add(key);
				array2.add(value);
				array3.add(gasto);
			}
		}
		
		for(int conta=0;conta<N && conta<array1.size();conta++){
			int max = Collections.max(array2);
			int index = array2.indexOf(max);
			String cli = array1.get(index);
			Double gasto = array3.get(index);
			
			print.add("Cliente: "+cli+" Quantidade: "+max+" Faturado: "+gasto);
			array2.set(index, 0);
			array3.set(index, 0.0);
		}
		
		out.println("Demoramos " +Crono.print()+" segundos.");
		apresentarPaginas(print, 10);
	}

	/**
	 * Função de ordenação crescente de um Map genérico.
	 * @param map
	 * @return SortedSet ordenado.
	 */
	static <K, V extends Comparable<? super V>> SortedSet<Map.Entry<K, V>> sortDecrescente(Map<K, V> map) {
		SortedSet<Map.Entry<K, V>> sortedEntries = new TreeSet<Map.Entry<K, V>>(new Comparator<Map.Entry<K, V>>() {
			@Override
			public int compare(Map.Entry<K, V> e1, Map.Entry<K, V> e2) {
				int res = e2.getValue().compareTo(e1.getValue());
				return res != 0 ? res : 1;
			}
		});
		sortedEntries.addAll(map.entrySet());
		return sortedEntries;
	}
	
	/**
	 * Função de ordenação crescente de um Map genérico.
	 * @param map
	 * @return SortedSet ordenado.
	 */
	static <K, V extends Comparable<? super V>> SortedSet<Map.Entry<K, V>> sortCrescente(Map<K, V> map) {
		SortedSet<Map.Entry<K, V>> sortedEntries = new TreeSet<Map.Entry<K, V>>(new Comparator<Map.Entry<K, V>>() {
			@Override
			public int compare(Map.Entry<K, V> e1, Map.Entry<K, V> e2) {
				int res = e1.getValue().compareTo(e2.getValue());
				return res != 0 ? res : 1;
			}
		});
		sortedEntries.addAll(map.entrySet());
		return sortedEntries;
	}
	
	/**
	 * Função de impressão de informação para o terminal.
	 * @param lista Arraylist a imprimir.
	 * @param sizePagina numero de linhas.
	 */
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
			out.print("Introduza número da página (0 para sair): ");
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

	
	/**
	 * Função de execucao das queries.
	 * @param f Instancia da classe Faturacao.
	 * @param filiais Instancias da classe Filial.
	 */
	public static void execute(Faturacao f, Filial[] filiais){
		boolean flag = true;
        
        while(flag){
			Integer decisao;
			out.println("\n---------------QUERIES---------------");
			out.println("\t1. Lista ordenada de produtos nunca comprados e o seu total.");
			out.println("\t2. Dado um mês, determinar número total vendas e clientes que as realizaram.");
			out.println("\t3. Dado um cliente, determinar as suas estatisticas mensais.");
			out.println("\t4. Dado um produto, determinar as suas estatisticas mensais.");
			out.println("\t5. Dado um cliente, determinar os produtos que mais comprou.");
			out.println("\t6. Determinar os N produtos mais vendidos em todo o ano.");
			out.println("\t7. Para cada filial, listar os três maiores compradores.");
			out.println("\t8. Determinar os N clientes que mais produtos diferentes compraram.");
			out.println("\t9. Dado um produto, determinar os clientes que mais o compraram.");
			out.println("\t0. Sair.");
			out.print("Query a executar: ");
			decisao = Input.lerInt();
			try{
				switch(decisao){
					case 0:
						flag=false;
						out.println("Exit!");
						break;
					case 1:
						out.println("---------------Query 1---------------");
						query1(f);
						out.println("-------------------------------------");
						break;
					case 2:
						out.println("---------------Query 2---------------");
						query2(filiais);
						out.println("-------------------------------------");
						break;
					case 3:
						out.println("---------------Query 3---------------");
						query3(filiais);
						out.println("-------------------------------------");
						break;
					case 4:
						out.println("---------------Query 4---------------");
						query4(filiais);
						out.println("-------------------------------------");
						break;
					case 5:
						out.println("---------------Query 5---------------");
						query5(filiais);
						out.println("-------------------------------------");
						break;
					case 6:
						out.println("---------------Query 6---------------");
						query6(filiais);
						out.println("-------------------------------------");
						break;
					case 7:
						out.println("---------------Query 7---------------");
						query7(filiais);
						out.println("-------------------------------------");
						break;
					case 8:
						out.println("---------------Query 8---------------");
						query8(filiais);
						out.println("-------------------------------------");
						break;
					case 9:
						out.println("---------------Query 9---------------");
						query9(filiais);
						out.println("-------------------------------------");
						break;
					default:
						throw new DecisaoInvalidaException();
				}
			}catch(DecisaoInvalidaException e){
				out.println("Introduza uma decisão válida!");
			} catch(ProdutoInvalidoException e) {
				out.println("Código de produto inválido!");
			} catch(ClienteInvalidoException e) {
				out.println("Código de cliente inválido!");
			}
		}
	}
	
}

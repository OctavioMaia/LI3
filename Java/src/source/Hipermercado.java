package source;

import static java.lang.System.out;
import java.io.*;
import java.text.DecimalFormat;
import java.util.*;

public class Hipermercado implements Serializable{
	private Filial[] filial;
	private Faturacao faturacao;
	private Integer validos=0,invalidos=0,clientes=0,produtos=0,vendas_zero=0;	
	
	public Hipermercado(){
		filial = new Filial[3];
		filial[0] = new Filial();
		filial[1] = new Filial();
		filial[2] = new Filial();
		faturacao = new Faturacao();
	}
	
	private ArrayList<String> readLinesWithBuff(String fich) {
		ArrayList<String> linhas = new ArrayList<>();
		BufferedReader inStream = null;
		String linha = null;
		try {
			inStream = new BufferedReader(new FileReader(fich));
			while ((linha = inStream.readLine()) != null)
				linhas.add(linha);
		} catch (IOException e) {
			out.println(e.getMessage());
			return null;
		}
		return linhas;
	}

	private Catalogo readProdutos(Faturacao f, String path){
		Crono.start();
		ArrayList<String> produtos = readLinesWithBuff(path);
        Catalogo CatalogoProdutos = new Catalogo(produtos);
        f.addProdutos(produtos);
        Crono.stop();
        
        out.println("\tTodos os produtos inseridos em "+Crono.print() );
        this.produtos=produtos.size();
        return CatalogoProdutos;
	}
	
	private Catalogo readClientes(String path){
		Crono.start();
		ArrayList<String> clientes = readLinesWithBuff(path);
        Catalogo CatalogoClientes = new Catalogo(clientes);
        Crono.stop();
        
        out.println("\tTodos os clientes inseridos em "+Crono.print() );
        this.clientes=clientes.size();
        return CatalogoClientes;
	}
	
	private void readCompras(Filial[] filial, Faturacao f, Catalogo produtos, Catalogo clientes, String path){
		Crono.start();
		Venda v = new Venda();
		ArrayList<String> teste = readLinesWithBuff(path);
		int contador=0;
		try {
			for (int i = 0; i < teste.size(); i++) {
				String[] campos = teste.get(i).split(" ");
				String produto = campos[0];
				double preco = Double.parseDouble(campos[1]);
				int quantidade = Integer.parseInt(campos[2]);
				char tipo = campos[3].charAt(0);
				String cliente = campos[4];
				int mes = Integer.parseInt(campos[5]);
				int fil = Integer.parseInt(campos[6]);

				contador++;
				
				if(produtos.contains(produto) && clientes.contains(cliente) && preco>=0 && quantidade>0 && (tipo=='P' || tipo=='N') && (mes>=1 && mes<=12) && (fil>=1 && fil<=3)){
					v = new Venda(produto, preco, quantidade, tipo, cliente, mes, fil);
					f.addVenda(v);
					filial[fil-1].update(v);
					validos++;
					if(v.getPreco()==0) vendas_zero++;
				}else{
					invalidos++;
				}
			}
		} catch (NullPointerException e) {
			out.println(e.getMessage());
		} catch (NumberFormatException e) {
			out.println(e.getMessage());
		} catch (OutOfMemoryError e){
			out.print("crashei "+contador + "\n");
		}
		out.println("\tTodas as vendas processadas e inseridas em "  + Crono.print() );
	}

	public void run(String fichVendas) {
		out.println("\n----------------------------------------");
        Catalogo CatalogoProdutos = readProdutos(faturacao,"src/data/Produtos.txt");
        Catalogo CatalogoClientes = readClientes("src/data/Clientes.txt");
        readCompras(filial,faturacao,CatalogoProdutos,CatalogoClientes,fichVendas);
        boolean flag=true;
        
        while(flag){
	        out.println("----------------Menu--------------------");
	        out.println("\t1. Consultas estatísticas.");
	        out.println("\t2. Consultas interativas.");
	        out.println("\t0. Sair.");
	        out.println("----------------------------------------");
	        out.print("Decisão: ");
	        Integer decisao = Input.lerInt();
	        
	        switch(decisao){
	        	case 0:
	        		flag=false;
	        		break;
	        	case 1:
		        	estatisticas(fichVendas);
		        	break;
		        case 2:
		        	execute();
		        	break;
		        default:
		        	out.println("Introduza uma decisão válida.");
		    }
        }
	}
	
	public void estatisticas(String nomeFicheiro){
		out.println("\n--------------Estatisticas--------------");
		out.println("\tFoi lido o ficheiro: " + nomeFicheiro.split("/")[2]);
		out.println("\tExistem "+ produtos +" produtos.");
		out.println("\tExistem "+ clientes +" clientes.");
		out.println("\tExistem "+ invalidos +" vendas inválidas.");
		out.println("\tExistem "+ validos +" vendas válidas.");
		out.println("\tExistem "+ vendas_zero +" vendas de valor 0.");
		out.println("\tExistem "+ this.faturacao.getProdutosComVendas().size() + " produtos comprados.");
		out.println("\tExistem "+ this.faturacao.getProdutosSemVendas().size() + " produtos nunca comprados.");
		out.println("\tFaturação total: "+ new DecimalFormat("#0.0000").format(this.faturacao.getTotalFaturado()));
        out.println("----------------------------------------\n");
		
	}
	
	public void execute(){
		Queries.execute(faturacao, filial);
	}
}
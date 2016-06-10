package source;

import static java.lang.System.out;
import java.io.*;
import java.util.*;

public class Hipermercado {

	public static ArrayList<String> readLinesWithBuff(String fich) {
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

	public static Catalogo readProdutos(Faturacao f, String path){
		Crono.start();
		ArrayList<String> produtos = readLinesWithBuff(path);
        Catalogo CatalogoProdutos = new Catalogo(produtos);
        f.addProdutos(produtos);
        Crono.stop();
        
        out.println("Inseri "+ produtos.size() +" produtos em " + Crono.print() );
        return CatalogoProdutos;
	}
	
	public static Catalogo readClientes(String path){
		Crono.start();
		ArrayList<String> clientes = readLinesWithBuff(path);
        Catalogo CatalogoClientes = new Catalogo(clientes);
        Crono.stop();
        
        out.println("Inseri "+ clientes.size() +" clientes em " + Crono.print() );
        return CatalogoClientes;
	}
	
	public static void readCompras(Filial[] filial, Faturacao f, Catalogo produtos, Catalogo clientes, String path){
		Crono.start();
		Venda v = new Venda();
		ArrayList<String> teste = readLinesWithBuff(path);
		int validos=0, invalidos=0,contador=0;
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
					//out.println("filial "+(fil-1));
					filial[fil-1].update(v);
					//out.print("depois update");
					validos++;
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
		out.println("Todas as vendas processadas e inseridas em "  + Crono.print() );
		out.println("Existem "+ invalidos +" vendas inválidas.");
		out.println("Existem "+ validos +" vendas válidas.");
	}

	public static void main(String[] args) {
		Filial[] filial = new Filial[3];
		filial[0] = new Filial();
		filial[1] = new Filial();
		filial[2] = new Filial();
		Faturacao faturacao = new Faturacao();
		
        Catalogo CatalogoProdutos = readProdutos(faturacao,"src/data/Produtos.txt");
        Catalogo CatalogoClientes = readClientes("src/data/Clientes.txt");

        readCompras(filial,faturacao,CatalogoProdutos,CatalogoClientes,"src/data/Vendas_1M.txt");
        
        /*
        out.print(filial[0].toString());
        out.print(filial[1].toString());
        out.print(filial[2].toString());
        
        Queries.query2(CatalogoProdutos);
        
        out.println(f.getQuantidadeProdutoMesN(6,"AF1184"));
        out.println(f.getQuantidadeProdutoMesP(6,"AF1184"));
        out.println(f.getFaturadoNMes(6,"AF1184"));
        out.println(f.getFaturadoPMes(6,"AF1184"));
        */
        
        //Queries.query1(faturacao);
        //Queries.query2(filial); ---> ta mal
        //Queries.query3(filial);
        //Queries.query4(filial);
        //Queries.query5(filial);
        Queries.query6(filial);
        //Queries.query7(filial);
        //Queries.query8(filial);
        //Queries.query9(filial);
	}
}
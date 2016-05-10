package source;

import static java.lang.System.out;
import java.io.*;
import java.nio.file.*;
import java.util.*;

public class Main {

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
	
	public static void readCompras(Faturacao f, Catalogo produtos, Catalogo clientes, String path){
		Crono.start();
		ArrayList<String> teste = readLinesWithBuff(path);
		int validos=0, invalidos=0;
		try {
			for (int i = 0; i < teste.size(); i++) {
				String linha = teste.get(i);
				String[] campos = linha.split(" ");
				String produto = campos[0];
				double preco = Double.parseDouble(campos[1]);
				int quantidade = Integer.parseInt(campos[2]);
				char tipo = campos[3].charAt(0);
				String cliente = campos[4];
				int mes = Integer.parseInt(campos[5]);
				int filial = Integer.parseInt(campos[6]);

				if(produtos.contains(produto) && clientes.contains(cliente) && preco>=0 && quantidade>0 && (tipo=='P' || tipo=='N') && (mes>=1 && mes<=12) && (filial>=1 && filial<=3)){
					Venda v = new Venda(produto, preco, quantidade, tipo, cliente, mes, filial);
					f.addVenda(v);
					validos++;
				}else{
					invalidos++;
				}
			}
		} catch (NullPointerException e) {
			out.println(e.getMessage());
		} catch (NumberFormatException e) {
			out.println(e.getMessage());
		}
		Crono.stop();
		out.println("Existem "+ invalidos +" vendas inválidas.");
		out.println("Inseri "+ validos +" vendas válidas em " + Crono.print() );
	}

	public static void main(String[] args) {
		Faturacao f = new Faturacao();
    
        Catalogo CatalogoProdutos = readProdutos(f,"src/data/Produtos.txt");
        Catalogo CatalogoClientes = readClientes("src/data/Clientes.txt");

        readCompras(f,CatalogoProdutos,CatalogoClientes,"src/data/Vendas_1M.txt");
        
        /*Queries.query2(CatalogoProdutos);
        
        out.println(f.getQuantidadeProdutoMesN(6,"AF1184"));
        out.println(f.getQuantidadeProdutoMesP(6,"AF1184"));
        out.println(f.getFaturadoNMes(6,"AF1184"));
        out.println(f.getFaturadoPMes(6,"AF1184"));
        */
        }
}
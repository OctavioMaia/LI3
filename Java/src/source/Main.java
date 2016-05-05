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

	public static void main(String[] args) {
		int count, invalidas;
		Crono.start();
		
		ArrayList<String> teste = new ArrayList<>();
		teste = readLinesWithBuff("src/data/Vendas_3M.txt");
		
		count = 0;
        invalidas = 0;
     
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
            
            Venda v = new Venda(produto,preco,quantidade,tipo,cliente,mes,filial);
            
            if(v.isValida(v)){
            	count++;
            }else{
            	invalidas++;
            }
            
        }
		
		Crono.stop();
		out.println("Demorei: "+Crono.print());
		out.print("validas "+count );
	}

}
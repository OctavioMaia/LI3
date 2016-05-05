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
		Crono.start();
		
		ArrayList<String> teste = new ArrayList<>();
		teste = readLinesWithBuff("src/data/Vendas_3M.txt");
		
		Crono.stop();
		out.println(Crono.print());
	}

}
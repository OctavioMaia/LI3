package source;

import static java.lang.System.out;

import java.io.*;

public class GereVendas {

	public static void main(String[] args) throws ClassNotFoundException, IOException {
		Hipermercado hipermercado = new Hipermercado();
		Persistencia state = new Persistencia();
		boolean flag=true,firstRun=false;
		
			while(flag){
				out.println("---------------GereVendas---------------");
				out.println("\t1. Iniciar população a partir do ficheiro Vendas_1M.txt");
				out.println("\t2. Iniciar população a partir do ficheiro Vendas_3M.txt");
				out.println("\t3. Iniciar população a partir do ficheiro Vendas_5M.txt");
				out.println("\t4. Gravar estrutura de dados.");
				out.println("\t5. Carregar estrutura de dados.");
				out.println("\t0. Sair.");
				out.println("----------------------------------------");
				out.print("Opção a executar: ");
				Integer decisao = Input.lerInt();
		
				switch(decisao){
				case 0:
					out.print("Exit!");
					System.exit(0);
					break;
				case 1:
					hipermercado = new Hipermercado();
					firstRun=true;
					hipermercado.run("src/data/Vendas_1M.txt");
					break;
				case 2:
					hipermercado = new Hipermercado();
					firstRun=true;
					hipermercado.run("src/data/Vendas_3M.txt");
					break;
				case 3:
					hipermercado = new Hipermercado();
					firstRun=true;
					hipermercado.run("src/data/Vendas_5M.txt");
					break;
				case 4:
					if(firstRun){
						out.print("Ficheiro a criar: ");
						String fich = Input.lerString();
						state.guardarEstado(hipermercado,fich);
						out.println("Estado guardado com sucesso!\n");
					}else{
						out.println("Impossível guardar estado, visto nunca ter sido executado!");
					}
					break;
				case 5:
					out.print("Ficheiro a carregar: ");
					String path = Input.lerString();
					try{
						hipermercado = state.carregarEstado(path);
						out.println("Estado carregado com sucesso!\n");
						hipermercado.execute();
					}catch(FileNotFoundException e){
						out.println("Ficheiro inválido!");
					}
					break;
				}
			}
		
        out.println("Exit!");
    }
	
}

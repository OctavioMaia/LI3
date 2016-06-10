package source;

import static java.lang.System.out;

import java.io.IOException;
import java.io.Serializable;

public class GereVendas implements Serializable{

	public static void main(String[] args) throws ClassNotFoundException, IOException {
		Hipermercado hipermercado = new Hipermercado();
		Persistencia state = new Persistencia();
		boolean flag=true;
		
			while(flag){
				out.println("---------------GereVendas---------------");
				out.println("1. Iniciar população a partir do ficheiro Vendas_1M.txt");
				out.println("2. Iniciar população a partir do ficheiro Vendas_3M.txt");
				out.println("3. Iniciar população a partir do ficheiro Vendas_5M.txt");
				out.println("4. Gravar estrutura de dados.");
				out.println("5. Carregar estrutura de dados.");
				out.println("0. Sair.");
				out.print("Opção a executar: ");
				Integer decisao = Input.lerInt();
				out.println("----------------------------------------\n");
				switch(decisao){
				case 0:
					out.print("Exit!");
					System.exit(0);
					break;
				case 1:
					hipermercado = new Hipermercado();
					hipermercado.run("src/data/Vendas_1M.txt");
					break;
				case 2:
					hipermercado = new Hipermercado();
					hipermercado.run("src/data/Vendas_3M.txt");
					break;
				case 3:
					hipermercado = new Hipermercado();
					hipermercado.run("src/data/Vendas_5M.txt");
					break;
				case 4:
					state.guardarEstado(hipermercado);
					out.println("Estado guardado com sucesso!\n");
					break;
				case 5:
					hipermercado = state.carregarEstado();
					out.println("Estado carregado com sucesso!\n");
					hipermercado.execute();
					break;
				}
			}
		
        out.println("Exit!");
    }
	
}

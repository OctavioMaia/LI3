package source;

import java.io.Serializable;
import java.util.TreeMap;

public class DetalhesCliente implements Serializable{
	
	private TreeMap<Integer, ComprasMes> compras; /*Para um dado mes, tem os detalhes do cliente*/

	public void update(String produto, int quantidade, char tipo, int mes, double preco){
		this.compras.get(mes).add(produto, quantidade, preco*quantidade);
	}
}


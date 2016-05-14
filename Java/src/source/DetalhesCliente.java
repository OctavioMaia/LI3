package source;

import java.io.Serializable;
import java.util.TreeMap;

public class DetalhesCliente implements Serializable{
	
	private TreeMap<Integer, ComprasMes> compras; /*Para um dado mes, tem os detalhes do cliente*/
	
	public DetalhesCliente(){
		this.compras = new TreeMap<>();
	}

	public void update(String produto, int quantidade, char tipo, int mes, double preco){
		if(this.compras.containsKey(mes)){
			this.compras.get(mes).add(produto, quantidade, preco*quantidade);
		}else{
			this.compras.put(mes, new ComprasMes());
			this.compras.get(mes).add(produto, quantidade, preco*quantidade);
		}
		
	}
}


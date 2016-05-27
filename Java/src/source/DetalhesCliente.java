package source;

import java.io.Serializable;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeMap;

public class DetalhesCliente implements Serializable{
	
	private TreeMap<Integer, ComprasMes> compras; /*Para um dado mes, tem os detalhes do cliente*/
	
	public DetalhesCliente(){
		this.compras = new TreeMap<>();
	}
	
	public ComprasMes getComprasMes(int mes){
		return this.compras.get(mes).clone();
	}
	
	public void update(String produto, int quantidade, char tipo, int mes, double preco){
		if(this.compras.containsKey(mes)){
			this.compras.get(mes).add(produto, quantidade, preco*quantidade);
		}else{
			this.compras.put(mes, new ComprasMes());
			this.compras.get(mes).add(produto, quantidade, preco*quantidade);
		}
		
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		Set<Integer> c = compras.keySet();
		Iterator<Integer> i = c.iterator();
		
		while(i.hasNext()){
			sb.append("Mes: "+ i.next() +"\n");
		}

		return sb.toString();
	}

}
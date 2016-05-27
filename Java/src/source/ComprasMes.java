package source;

import java.io.Serializable;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.TreeMap;

/*
 * Compras mensais de um cliente.
 */
public class ComprasMes implements Serializable{

	private TreeMap<String, InfoProduto> info; //Key = produto
	
	public ComprasMes(){
		this.info = new TreeMap<>();
	}
	
	public ComprasMes(ComprasMes c){
		this.info = c.getInformacao();
	}
	
	public TreeMap<String,InfoProduto> getInformacao(){
		TreeMap<String,InfoProduto> copia = new TreeMap<>();
		copia.putAll(this.info);
		
		return copia;
	}
	
	public void add(String codigo, Integer quantidade, Double faturado) {
		int pos;
		if(this.contains(codigo)){
			this.info.get(codigo).add(quantidade, faturado);
		}else{
			this.info.put(codigo, new InfoProduto());
			this.info.get(codigo).add(quantidade, faturado);
		}
	}

	public void remove(String codigo) throws ClienteNaoExisteException {
		if(this.contains(codigo)){
			this.remove(codigo);
		}else{
			throw new ClienteNaoExisteException();
		}
	}

	public boolean contains(String codigo) {
		return this.info.containsKey(codigo);
	}

	public int size() {
		return this.info.size();
	}

	public boolean equals(Object o) {
		if (this == o)
			return true;
		if ((o == null) || (this.getClass() != o.getClass()))
			return false;

		ComprasMes info = (ComprasMes) o;
		return this.info.equals(info.getInformacao());
	}

	public ComprasMes clone() {
		return new ComprasMes(this);
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		Set<String> chaves = info.keySet();
		Iterator<String> it = chaves.iterator();
		
		while(it.hasNext()){
			sb.append("Cliente: "+ it.next() +"\n");
		}

		return sb.toString();
	}
	
}
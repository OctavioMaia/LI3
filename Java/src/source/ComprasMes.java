package source;

import java.io.Serializable;
import java.util.*;
import java.util.Map.*;

/*
 * Compras mensais de um cliente.
 */
public class ComprasMes implements Serializable{

	private TreeMap<String, InfoProduto> info; //Key = produto
	
	/**
     * Construtor vazio da classe ComprasMes.
     */
	public ComprasMes(){
		this.info = new TreeMap<>();
	}
	
	/**
     * Construtor por copia da classe ComprasMes.
     * @param c ComprasMes a copiar.
     */
	public ComprasMes(ComprasMes c){
		this.info = c.getInformacao();
	}
	
	/**
	 * Função que retorna toda a informação da classe ComprasMes.
	 * @return copia do TreeMap info.
	 */
	public TreeMap<String,InfoProduto> getInformacao(){
		TreeMap<String,InfoProduto> copia = new TreeMap<>();
		copia.putAll(this.info);
		
		return copia;
	}
	
	/**
	 * Função que retorna o total de compras.
	 * @return total de compras.
	 */
	public int getTotalCompras(){
		int total=0;
		
		for(Entry<String,InfoProduto> entry : this.info.entrySet()){
			total += entry.getValue().getNCompras();
		}
		
		return total;
	}
	
	/**
	 * Função que retorna o total faturado.
	 * @return total faturado.
	 */
	public double getTotalFaturado(){
		double total=0;
		
		for(Entry<String,InfoProduto> entry : this.info.entrySet()){
			total += entry.getValue().getGasto();
		}
		
		return total;
	}
	
	/**
	 * Função que retorna todos os produtos.
	 * @return ArrayList com todos os produtos.
	 */
	public ArrayList<String> getProdutos(){
		ArrayList<String> lista = new ArrayList<>();
		
		for(Entry<String,InfoProduto> entry: info.entrySet()){
			lista.add(entry.getKey());
		}
		
		return lista;
	}
	
	/**
	 * Função que adiciona um InfoProduto.
	 * @param codigo codigo a adicionar (key)
	 * @param quantidade quantidade a adicionar.
	 * @param faturado gasto a adicionar.
	 */
	public void add(String codigo, Integer quantidade, Double faturado) {
		int pos;
		if(this.contains(codigo)){
			this.info.get(codigo).add(quantidade, faturado);
		}else{
			this.info.put(codigo, new InfoProduto());
			this.info.get(codigo).add(quantidade, faturado);
		}
	}

	/**
	 * Função que remove a informação relativa a um cliente.
	 * @param codigo codigo de cliente.
	 * @throws ClienteInvalidoException caso um cliente nao existe.
	 */
	public void remove(String codigo) throws ClienteInvalidoException {
		if(this.contains(codigo)){
			this.remove(codigo);
		}else{
			throw new ClienteInvalidoException();
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
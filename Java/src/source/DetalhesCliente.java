package source;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeMap;

public class DetalhesCliente implements Serializable{
	
	private TreeMap<Integer, ComprasMes> compras; /*Para um dado mes, tem os detalhes do cliente*/
	
	/**
	 * Construtor vazio da classe DetalhesCliente
	 */
	public DetalhesCliente(){
		this.compras = new TreeMap<>();
	}
	
	/**
	 * Função que retorna uma instancia ComprasMes
	 * @param mes mês para procura da instancia.
	 * @return clone da instancia ComprasMes encontrada.
	 */
	public ComprasMes getComprasMes(int mes){
		return this.compras.get(mes).clone();
	}
	
	/**
	 * Função que calcula o total faturado no sistema.
	 * @return total faturado.
	 */
	public double getTotalFaturado(){
		double total=0;
		int mes;
		
		for(Entry<Integer,ComprasMes> entry : this.compras.entrySet()){
			try{
				ComprasMes cm = entry.getValue();
				total+=cm.getTotalFaturado();
			}catch(Exception e){
				
			}
		}
		
		return total;
	}
	
	/**
	 * Função que retorna a lista de produtos.
	 * @return lista de produtos comprados pelo cliente.
	 */
	public ArrayList<String> getListaProdutos(){
		ArrayList<String> lista = new ArrayList<>();
		
		for(Entry<Integer,ComprasMes> entry: compras.entrySet()){
			try{
				ComprasMes cm = entry.getValue();
				ArrayList<String> lista2 = cm.getProdutos();
				
				for(String s : lista2){
					if(!lista.contains(s)){
						lista.add(s);
					}
				}
			}catch(Exception e){
				
			}
		}
		
		return lista;
	}
	
	/**
	 * Função que atualiza os detalhes de um dado cliente.
	 * @param produto produto a atualizar.
	 * @param quantidade quantidade a adicionar.
	 * @param mes mes da venda.
	 * @param preco preço da venda.
	 */
	public void update(String produto, int quantidade, int mes, double preco){
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
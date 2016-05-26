package source;

import java.io.Serializable;
import java.util.*;

public class DetalhesProduto implements Serializable{

	private TreeMap<Integer, ProdutosMes> produtos; /*Para um dado mes, tem os detalhes do produto*/
	
	public DetalhesProduto(){
		this.produtos=new TreeMap<>();
	}
	
	public void update(String cliente, int quantidade, char tipo, int mes){
		if(this.produtos.containsKey(mes)){
			this.produtos.get(mes).add(cliente, quantidade,tipo);
		}else{
			this.produtos.put(mes, new ProdutosMes());
			this.produtos.get(mes).add(cliente, quantidade,tipo);
		}
	}
	
	public TreeMap<Integer, ProdutosMes> getProdutos(){
		TreeMap<Integer,ProdutosMes> copia = new TreeMap<>();
		copia.putAll(this.produtos);
		
		return copia;
	}
	
	public Map<String, Integer> getClientesMesN(Integer mes){
		return this.produtos.get(mes).getClientesN();
	}
	
	public Map<String, Integer> getClientesMesP(Integer mes){
		return this.produtos.get(mes).getClientesP();
	}
	
	public int getQuantidadeClientesMes(Integer mes){
		return this.produtos.get(mes).getQuantidadeClientes();
	}
	
	public int getQuantidadeVendidaMes(Integer mes){
		return this.produtos.get(mes).getQuantidadeVendida();
	}	
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		Set<Integer> c = produtos.keySet();
		Iterator<Integer> i = c.iterator();
		
		while(i.hasNext()){
			sb.append("Mes: "+ i.next() +"\n");
		}
		

		return sb.toString();
	}
	
}

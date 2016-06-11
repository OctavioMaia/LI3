package source;

import java.io.Serializable;
import java.util.*;

public class DetalhesProduto implements Serializable{

	private TreeMap<Integer, ProdutosMes> produtos; /*Para um dado mes, tem os detalhes do produto*/
	
	/**
	 * Construtor vazio da classe DetalhesProduto.
	 */
	public DetalhesProduto(){
		this.produtos=new TreeMap<>();
	}
	
	/**
	 * Atualiza o DetalheProduto relativamente a uma venda.
	 * @param cliente Código cliente.
	 * @param quantidade Quantidade vendida.
	 * @param faturado Total faturado.
	 * @param tipo Tipo venda.
	 * @param mes Mês.
	 */
	public void update(String cliente, int quantidade, double faturado, char tipo, int mes){
		if(this.produtos.containsKey(mes)){
			this.produtos.get(mes).add(cliente, quantidade, faturado,tipo);
		}else{
			this.produtos.put(mes, new ProdutosMes());
			this.produtos.get(mes).add(cliente, quantidade,faturado,tipo);
		}
	}
	
	/**
	 * Devolve cópia DetalhesProduto.
	 * @returncópia DetalhesProduto.
	 */
	public TreeMap<Integer, ProdutosMes> getProdutos(){
		TreeMap<Integer,ProdutosMes> copia = new TreeMap<>();
		copia.putAll(this.produtos);
		
		return copia;
	}
	
	/**
	 * Devolve a lista dos clientes que compraram um produto do tipo N num determinado mês e
	 * a quantidade comprada.
	 * @param mes Mês.
	 * @return lista de clientes e quantidade comprada.
	 */
	public Map<String, Integer> getClientesMesN(Integer mes){
		return this.produtos.get(mes).getClientesN();
	}
	
	/**
	 * Devolve a lista dos clientes que compraram um produto do tipo P num determinado mês e
	 * a quantidade comprada.
	 * @param mes Mês.
	 * @return lista de clientes e quantidade comprada.
	 */
	public Map<String, Integer> getClientesMesP(Integer mes){
		return this.produtos.get(mes).getClientesP();
	}
	/**
	 * Devolve a quantidade de clientes que compraram o produto num determiando mês.
	 * @param mes Mês.
	 * @return quantidade de clientes.
	 */
	public int getQuantidadeClientesMes(Integer mes){
		return this.produtos.get(mes).getQuantidadeClientes();
	}
	
	/**
	 * Devolve a quantidade vendida do produto num determinado mes.
	 * @param mes Mês.
	 * @return quantidade de produtos vendida.
	 */
	public int getQuantidadeVendidaMes(Integer mes){
		return this.produtos.get(mes).getQuantidadeVendida();
	}	
	
	/**
	 * Devolve a quantidade faturada durante um mês.
	 * @param mes Mês.
	 * @return quantidade faturada.
	 */
	public double getFaturadoMes(Integer mes){
		return this.produtos.get(mes).getFaturado();
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

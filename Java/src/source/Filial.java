package source;

import java.io.Serializable;
import java.util.*;

public class Filial implements Serializable{
	private Map<String, DetalhesCliente> informacaoClientes;
	private Map<String, DetalhesProduto> informacaoProduto;
	
	/**
	 * Construtor vazio da classe Filial.
	 */
	public Filial(){
		this.informacaoClientes = new TreeMap<>();
		this.informacaoProduto = new TreeMap<>();
	}
	
	/**
	 * Função responsável por retornar um map contendo todos os clientes e a sua informação.
	 * @return map contendo a informação acima mencionada.
	 */
	public TreeMap<String, DetalhesCliente> getInformacaoClientes(){
		TreeMap<String,DetalhesCliente> copia = new TreeMap<>();
		copia.putAll(this.informacaoClientes);
		
		return copia;
	}
	
	/**
	 * Função responsável por retornar um map contendo todos os produtos e a sua informação.
	 * @return map contendo a informação acima mencionada.
	 */
	public TreeMap<String, DetalhesProduto> getInformacaoProdutos(){
		TreeMap<String,DetalhesProduto> copia = new TreeMap<>();
		copia.putAll(this.informacaoProduto);
		
		return copia;
	}
	
	/**
	 * Função responsável pelo processamento de uma venda.
	 * @param v Venda a processar.
	 */
	public void update(Venda v){
		String cliente = v.getCliente();
		String produto = v.getProduto();
		int quantidade = v.getQuantidade();
		char tipo = v.getTipo();
		int mes = v.getMes();
		double preco = v.getPreco();
		double faturado = preco*quantidade;
		
		
		if(this.informacaoClientes.containsKey(cliente)){
			this.informacaoClientes.get(cliente).update(produto, quantidade, mes, preco);
		}else{
			this.informacaoClientes.put(cliente, new DetalhesCliente());
			this.informacaoClientes.get(cliente).update(produto, quantidade, mes, preco);
		}
		
		if(this.informacaoProduto.containsKey(produto)){
			this.informacaoProduto.get(produto).update(cliente, quantidade, faturado,tipo, mes); 
		}else{
			this.informacaoProduto.put(produto, new DetalhesProduto());
			this.informacaoProduto.get(produto).update(cliente, quantidade, faturado,tipo, mes);
		}
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder();
		
		sb.append("cli" + informacaoClientes.size() + "prod" + informacaoProduto.size() +"\n");
		
		return sb.toString();
	}
	
}

package source;

import java.io.Serializable;
import java.util.TreeMap;

public class Filial implements Serializable{

	private TreeMap<String, DetalhesCliente> informacaoClientes;
	private TreeMap<String, DetalhesProduto> informacaoProduto;
	
	public Filial(){
		this.informacaoClientes = new TreeMap<>();
		this.informacaoProduto = new TreeMap<>();
	}
	
	public void update(Venda v){
		String cliente = v.getCliente();
		String produto = v.getProduto();
		int quantidade = v.getQuantidade();
		char tipo = v.getTipo();
		int mes = v.getMes();
		double preco = v.getPreco();
		
		this.informacaoClientes.get(cliente).update(produto, quantidade, tipo, mes, preco); // falta fazer
		this.informacaoProduto.get(produto).update(cliente, quantidade, tipo, mes, preco); // falta fazer
	}
	
}

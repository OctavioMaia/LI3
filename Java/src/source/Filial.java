package source;

import java.io.Serializable;
import java.util.*;

public class Filial implements Serializable{

	private Map<String, DetalhesCliente> informacaoClientes;
	private Map<String, DetalhesProduto> informacaoProduto;
	
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
		
		//System.out.println("depois de invocar");
		//System.out.print("venda:" +v.toString());
		
		if(this.informacaoClientes.containsKey(cliente)){
			this.informacaoClientes.get(cliente).update(produto, quantidade, tipo, mes, preco);
		//	System.out.println("nao existe cliente");
		}else{
			this.informacaoClientes.put(cliente, new DetalhesCliente());
			this.informacaoClientes.get(cliente).update(produto, quantidade, tipo, mes, preco);
			//System.out.println("nao existe cliente");
		}
		
		if(this.informacaoProduto.containsKey(produto)){
			this.informacaoProduto.get(produto).update(cliente, quantidade, tipo, mes); 
			//System.out.println("nao existe produto");
		}else{
			this.informacaoProduto.put(produto, new DetalhesProduto());
			this.informacaoProduto.get(produto).update(cliente, quantidade, tipo, mes);
			//System.out.println("existe produto");
		}
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder();
		
		sb.append("cli" + informacaoClientes.size() + "prod" + informacaoProduto.size() +"\n");
		
		return sb.toString();
	}
	
}
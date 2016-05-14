package source;

import java.io.Serializable;
import java.util.*;

public class InfoProduto implements Serializable {
	private List<String> clientes;
	private List<Integer> quantidade;
	private List<Double> faturado;

	public InfoProduto() {
		this.clientes = new ArrayList<>();
		this.quantidade = new ArrayList<>();
		this.faturado = new ArrayList<>();
	}

	public InfoProduto(InfoProduto i){
		this.clientes = i.getClientes();
		this.quantidade = i.getQuantidade();
		this.faturado = i.getFaturado();
	}
	
	public List<String> getClientes() {
		List<String> cop_clientes = new ArrayList<>();
		
		for(String s : this.clientes)
			cop_clientes.add(s);
		
		return cop_clientes;
	}
	
	public List<Integer> getQuantidade() {
		List<Integer> cop_quantidade = new ArrayList<>();
		
		for(Integer s : this.quantidade)
			cop_quantidade.add(s);
		
		return cop_quantidade;
	}
	
	public List<Double> getFaturado() {
		List<Double> cop_faturado = new ArrayList<>();
		
		for(Double s : this.faturado)
			cop_faturado.add(s);
		
		return cop_faturado;
	}

	public void add(String codigo, Integer quantidade, Double faturado) {
		int pos;
		if(this.contains(codigo)){
			pos=this.clientes.indexOf(codigo);
			this.quantidade.set(pos, this.quantidade.get(pos)+quantidade);
			this.faturado.set(pos, this.faturado.get(pos)+faturado);
		}else{
			this.clientes.add(codigo);
			pos=this.clientes.indexOf(codigo);
			this.quantidade.set(pos, quantidade);
			this.faturado.set(pos, faturado);
		}
	}

	public void remove(String codigo) throws ClienteNaoExisteException {
		if(this.clientes.contains(codigo)){
			int pos = this.clientes.indexOf(codigo);
			this.clientes.remove(codigo);
			this.quantidade.remove(pos);
			this.faturado.remove(pos);
		}else{
			throw new ClienteNaoExisteException();
		}
	}

	public boolean contains(String codigo) {
		return this.clientes.contains(codigo);
	}

	public int size() {
		return this.clientes.size();
	}

	public boolean equals(Object o) {
		if (this == o)
			return true;
		if ((o == null) || (this.getClass() != o.getClass()))
			return false;

		InfoProduto info = (InfoProduto) o;
		return this.clientes.equals(info.getClientes()) && this.quantidade.equals(info.getQuantidade()) && this.faturado.equals(info.getFaturado());
	}

	public InfoProduto clone() {
		return new InfoProduto(this);
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		List<String> c = this.getClientes();
		List<Integer> q = this.getQuantidade();
		List<Double> f = this.getFaturado();
		
		for (int i = 0; i < c.size(); i++) {
			sb.append("Cliente: "+ c.get(i) + "Quantidade: "+q.get(i) + "Faturado: "+f.get(i)+"\n");
		}

		return sb.toString();
	}

}

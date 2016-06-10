package source;

import java.io.Serializable;
import java.util.*;

public class ProdutosMes implements Serializable{
	
	private Map<String, Integer> clientesN; //Key = cliente, value = qt comprada por esse cliente
	private Map<String, Integer> clientesP; //Key = cliente, value = qt comprada por esse cliente
	private int quantidade_clientes; // = nº clientes que compraram
	private int quantidade_vendida; 
	private double faturado;
	
	public ProdutosMes(){
		this.clientesN = new TreeMap<>();
		this.clientesP = new TreeMap<>();
		this.quantidade_clientes = 0;
		this.quantidade_vendida = 0;
		this.faturado=0;
	}

	public ProdutosMes(ProdutosMes pm){
		this.clientesN = pm.getClientesN();
		this.clientesP = pm.getClientesP();
		this.quantidade_clientes = pm.getQuantidadeClientes();
		this.quantidade_vendida = pm.getQuantidadeVendida();
		this.faturado = pm.getFaturado();
	}
	
	public int getQuantidadeVendida() {
		return this.quantidade_vendida;
	}

	public int getQuantidadeClientes() {
		return this.quantidade_clientes;
	}
	
	public double getFaturado(){
		return this.faturado;
	}

	public Map<String, Integer> getClientesN(){
		TreeMap<String,Integer> copia = new TreeMap<>();
		copia.putAll(this.clientesN);
		
		return copia;
	}
	
	public Map<String, Integer> getClientesP(){
		TreeMap<String,Integer> copia = new TreeMap<>();
		copia.putAll(this.clientesP);
		
		return copia;
	}
	
	public void setQuantidadeVendida(int qt){
		this.quantidade_vendida+=qt;
	}
	
	public void setQuantidadeClientes(int qt){
		this.quantidade_clientes+=qt;
	}
	
	public void setFaturado(double ft){
		this.faturado+=ft;
	}
	
	public void add(String codigo, Integer quantidade, Double faturado, char tipo) {
		int qt=0;
		//System.out.println("entrei");
		if(tipo == 'N'){
			if(this.containsN(codigo)){
				qt=this.clientesN.get(codigo);
				this.clientesN.put(codigo,quantidade+qt);
			}else{
				this.clientesN.put(codigo, quantidade);
				qt=quantidade;
				this.quantidade_clientes++;
			}
		}else{
			if(this.containsP(codigo)){
				qt=this.clientesP.get(codigo);
				this.clientesP.put(codigo,quantidade+qt);
			}else{
				this.clientesP.put(codigo, quantidade);
				qt=quantidade;
				this.quantidade_clientes++;
			}
		}
		setQuantidadeVendida(qt);
		setFaturado(faturado);
	}

	public void remove(String codigo) throws ClienteInvalidoException {
		if(this.containsN(codigo)){
			this.clientesN.remove(codigo);
		}else{
			throw new ClienteInvalidoException();
		}
		
		if(this.containsP(codigo)){
			this.clientesP.remove(codigo);
		}else{
			throw new ClienteInvalidoException();
		}
	}

	public boolean containsN(String codigo) {
		return this.clientesN.containsKey(codigo);
	}
	
	public boolean containsP(String codigo) {
		return this.clientesP.containsKey(codigo);
	}

	public boolean equals(Object o) {
		if (this == o)
			return true;
		if ((o == null) || (this.getClass() != o.getClass()))
			return false;

		ProdutosMes info = (ProdutosMes) o;
		return this.clientesN.equals(info.getClientesN()) 
			&& this.clientesP.equals(info.getClientesP()) 
			&& this.quantidade_clientes==info.getQuantidadeClientes() 
			&& this.quantidade_vendida==info.getQuantidadeVendida()
			&& this.faturado == info.getFaturado();
	}

	public ProdutosMes clone() {
		return new ProdutosMes(this);
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		Set<String> chavesN = clientesN.keySet();
		Iterator<String> itN = chavesN.iterator();
		Set<String> chavesP = clientesP.keySet();
		Iterator<String> itP = chavesP.iterator();
		
		while(itN.hasNext()){
			sb.append("ClienteN: "+ itN.next() +"\n");
		}
		
		while(itP.hasNext()){
			sb.append("ClienteP: "+ itP.next() +"\n");
		}

		return sb.toString();
	}
	
}
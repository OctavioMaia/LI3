package source;

import java.io.Serializable;
import java.util.*;

import exceptions.ClienteInvalidoException;

/**
 * Representa os produtos num dado mês. E formada
 * pela quantidade de clientes que compraram, 
 * pela quantidade vendida e o faturado. 
 * Tambem e formada por dois maps cuja chave 
 * sao os clientes e cujo o valor é a quantidade
 * comprada por esse cliente, sendo que estes sao
 * separados em normal ou promocao. 
  */

public class ProdutosMes implements Serializable{
	
	private Map<String, Integer> clientesN; //Key = cliente, value = qt comprada por esse cliente
	private Map<String, Integer> clientesP; //Key = cliente, value = qt comprada por esse cliente
	private int quantidade_clientes; // = nÂº clientes que compraram
	private int quantidade_vendida; 
	private double faturado;
	
	
	 /**
	  * Construtor vazio da classe ProdutosMes.
	  */
	public ProdutosMes(){
		this.clientesN = new TreeMap<>();
		this.clientesP = new TreeMap<>();
		this.quantidade_clientes = 0;
		this.quantidade_vendida = 0;
		this.faturado=0;
	}

	/**
	 * Construtor por copia da classe ProdutosMes.
	 * @param pm ProdutosMes a copiar.
	 */
	public ProdutosMes(ProdutosMes pm){
		this.clientesN = pm.getClientesN();
		this.clientesP = pm.getClientesP();
		this.quantidade_clientes = pm.getQuantidadeClientes();
		this.quantidade_vendida = pm.getQuantidadeVendida();
		this.faturado = pm.getFaturado();
	}
	
	/**
     * Funcao que devolve a quantidade vendida.
     * @return quantidade vendida.
     */
	public int getQuantidadeVendida() {
		return this.quantidade_vendida;
	}

	/**
     * Funcao que devolve a quantidade de clientes.
     * @return quantidade clientes.
     */
	public int getQuantidadeClientes() {
		return this.quantidade_clientes;
	}
	
	/**
     * Funcao que devolve o faturado.
     * @return faturado.
     */
	public double getFaturado(){
		return this.faturado;
	}

	/**
     * Funcao que devolve um map com os codigos dos clientes
     * e a quantidade comprada por esse cliente no tipo Normal.
     * @return map com os codigos de clientes e a quantidade comprada por cada cliente.
     */
	public Map<String, Integer> getClientesN(){
		TreeMap<String,Integer> copia = new TreeMap<>();
		copia.putAll(this.clientesN);
		
		return copia;
	}
	
	/**
     * Funcao que devolve um map com os codigo dos clientes
     * e a quantidade comprada por esse cliente no tipo Promoção.
     * @return map com os codigos dos clientes e a quantidade comprada por cada cliente.
     */
	public Map<String, Integer> getClientesP(){
		TreeMap<String,Integer> copia = new TreeMap<>();
		copia.putAll(this.clientesP);
		
		return copia;
	}
	
	/**
     * Funcao que altera a quantidade vendida.
     * @param qt quantidade vendida.
     */
	public void setQuantidadeVendida(int qt){
		this.quantidade_vendida+=qt;
	}
	
	/**
     * Funcao que altera a quantidade de clientes.
     * @param qt Quantidade de clientes.
     */
	public void setQuantidadeClientes(int qt){
		this.quantidade_clientes+=qt;
	}
	
	/**
     * Funcao que altera o total faturado.
     * @param ft Total faturado.
     */
	public void setFaturado(double ft){
		this.faturado+=ft;
	}
	
	
	/** 
	 * Adiciona ao map correspondente a informação da quantidade comprada por um cliente.
	 * @param codigo String do codigo de cliente.	
	 * @param quantidade comprada por esse cliente.
	 * @param faturado .
	 * @param tipo Tipo do produto (Normal ou Promocao).
	 */
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

	/**
	 * Remove a informação relativa de um dado cliente.
	 * @param codigo a remover
	 * @throws ClienteInvalidoException exceção lançada caso o cliente nao exista.
	 */
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

	/** 
	 * Verifica se clientesN contem o codigo do cliente.	
	 * @param codigo String do codigo de cliente.
	 * @return true se existir esse codigo false caso contrario.
	 */
	public boolean containsN(String codigo) {
		return this.clientesN.containsKey(codigo);
	}
	
	/** 
	 * Verifica se clientesP contem o codigo do cliente.	
	 * @param codigo String do codigo do produto.
	 * @return true se existir esse codigo false caso contrario.
	 */
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
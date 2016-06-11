package source;

import java.io.Serializable;
import java.util.*;

public class InfoProduto implements Serializable {
	private int quantidade;
	private double gasto;
	private int n_compras;
		
	/**
	 * Construtor vazio da classe InfoProduto.
	 */
	public InfoProduto() {
		this.quantidade = 0;
		this.gasto = 0;
		this.n_compras = 0;
	}

	/**
	 * Construtor por copia da classe InfoProduto.
	 * @param i Informação do produto que se pretende copiar.
	 */
	public InfoProduto(InfoProduto i){
		this.quantidade = i.getQuantidade();
		this.gasto = i.getGasto();
		this.n_compras = i.getNCompras();
	}

	/**
	 * Devolve a quantidade vendida do produto.
	 * @return Numero de unidades vendidas.
	 */
	public int getQuantidade() {
		return this.quantidade;
	}
	
	/**
	 * Devolve o total faturado pelo produto.
	 * @return total faturado pelo produto.
	 */
	public double getGasto(){
		return this.gasto;
	}

	/**
	 * Numero de compras relativas ao produto.
	 * @return numero de compras.
	 */
	public int getNCompras(){
		return this.n_compras;
	}
	
	/** 
	 * Adiciona uma venda a informação do produto.	
	 * @param quantidade Numero de unidades da compra.
	 * @param faturado Total faturado com o produto.
	 */
	public void add(Integer quantidade, Double faturado) {
		this.quantidade+=quantidade;
		this.gasto+=faturado;
		this.n_compras++;
	}

	public boolean equals(Object o) {
		if (this == o)
			return true;
		if ((o == null) || (this.getClass() != o.getClass()))
			return false;

		InfoProduto info = (InfoProduto) o;
		return this.quantidade == info.getQuantidade() && this.gasto ==info.getGasto() && this.n_compras == info.getNCompras();
	}

	public InfoProduto clone() {
		return new InfoProduto(this);
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("Quantidade: "+ this.getQuantidade() + "Gasto: "+this.getGasto() + "N_Compras: "+ this.getNCompras()+"\n");
		
		return sb.toString();
	}

}

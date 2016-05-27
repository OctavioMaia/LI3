package source;

import java.io.Serializable;
import java.util.*;

public class InfoProduto implements Serializable {
	private int quantidade;
	private double gasto;
	private int n_compras;
	
	public InfoProduto() {
		this.quantidade = 0;
		this.gasto = 0;
		this.n_compras = 0;
	}

	public InfoProduto(InfoProduto i){
		this.quantidade = i.getQuantidade();
		this.gasto = i.getGasto();
		this.n_compras = i.getNCompras();
	}
	
	public int getQuantidade() {
		return this.quantidade;
	}
	
	public double getGasto(){
		return this.gasto;
	}

	public int getNCompras(){
		return this.n_compras;
	}
	
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

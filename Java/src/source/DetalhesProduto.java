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
	
}

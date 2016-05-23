package source;

import java.util.TreeMap;

public class DetalhesProduto {

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

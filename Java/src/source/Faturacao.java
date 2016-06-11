package source;

import java.io.Serializable;
import java.util.*;

import exceptions.ProdutoInvalidoException;

public class Faturacao implements Serializable{
	
	private TreeMap<String, FaturacaoProduto> faturacao;
    
 /**
  * Construtor vazio da classe Faturacao  
  */
	public Faturacao () {
        this.faturacao = new TreeMap<String,FaturacaoProduto>();
    }
   
	/**
	 * Construtor parametrizado da classe Faturacao
	 * @param cat Lista a adicionar a faturacao.
	 */
    public Faturacao (List<String> cat) {
        this.faturacao = new TreeMap<String, FaturacaoProduto>();
        for(String s: cat) 
        	this.faturacao.put(s,new FaturacaoProduto());
    }
	    
	/**
	 * Construtor por copia da classe Faturacao.
	 * @param c Faturacao a copiar.
	 */
    public Faturacao (Faturacao c) {
        this.faturacao = c.getFaturacao();
    }
	/**
	 * Devolve a faturacao relativa a todos os produtos. 
	 * @return faturacao de todos os produtos.
	 */
    public TreeMap<String,FaturacaoProduto> getFaturacao () {
            TreeMap<String,FaturacaoProduto> faturacao = new TreeMap <String,FaturacaoProduto>();
            
            for (String s: faturacao.keySet())
            	faturacao.put(s,faturacao.get(s).clone());
            
            return faturacao;
    }
    
	 /**
	  * Devolve a contabilidade relativa a um produto.   
	  * @param produto Código de produto.
	  * @return faturacao relativa ao produto passado como parâmetro.
	  * @throws ProdutoInvalidoException Código do produto inválido.
	  */
    public FaturacaoProduto getContabilidadeProduto(String produto) throws ProdutoInvalidoException{
        if(!this.faturacao.containsKey(produto))
            throw new ProdutoInvalidoException(produto);
        
        return this.faturacao.get(produto).clone();
    }
    
	 /**
	  * Cria a faturacao de uma lista de produtos.
	  * @param cat Lista com código de produtos.
	  */
    public void addProdutos(List<String> cat) {
        for(String s: cat){
        	if(!this.faturacao.containsKey(s))
        		this.faturacao.put(s,new FaturacaoProduto());
        }
    }

	  /**
	   * Cria a faturacao de um produto.
	   * @param produto Código de produto.
	   */
    public void addProduto(String produto){
        if(!this.faturacao.containsKey(produto))
            this.faturacao.put(produto,new FaturacaoProduto());
    }
  
	  /**
	   * A partir de uma venda de um produto atualiza a sua Faturacao. 
	   * @param v Informação relativa a uma venda.
	   */
    public void addVenda(Venda v){
        String produto = v.getProduto();
        if(!this.faturacao.containsKey(produto))
            this.faturacao.put(produto, new FaturacaoProduto());
        
        this.faturacao.get(produto).addVenda(v);
    }
  
    /**
     * Remove da faturacao de um produto a informação relativa a uma venda.
     * @param v Informação relativa a venda.
     */
    public void removeVenda(Venda v){
        String produto = v.getProduto();
        if(this.faturacao.containsKey(produto))
            this.faturacao.get(produto).removeVenda(v);
    }
   
    /**
     * Remove da faturação um produto.  
     * @param produto Código de produto.
     */
    public void removeProduto(String produto){
        this.faturacao.remove(produto);
    }
   
   /**
    * Calcula o numero total de produtos que foram vendidos.
    * @return Quantidade de produtos que registaram vendas.
    */
    public int getTotProdutosComVendas(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	if(!f.semVendas())
        		total++;
        
        return total;
    }
    /**
     * Calcula o numero total de produtos que não foram vendidos.
     * @return Quantidade de produtos que não registaram vendas.
     */
    public int getTotProdutosSemVendas(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	if(f.semVendas()) 
        		total++;
        
        return total;
    }
    
    /**
     * Devolve lista com códigos de produtos que não foram vendidos.
     * @return lista com códigos de produtos que não registaram vendas.
     */
    public ArrayList<String> getProdutosSemVendas(){
        ArrayList<String> produtos = new ArrayList<String>();
        for(String s: this.faturacao.keySet()){
            if(this.faturacao.get(s).semVendas()){
                produtos.add(s);
            }
        }
        return produtos;
    }
    /**
     * Devolve lista com códigos de produtos que foram vendidos.
     * @return lista com códigos de produtos que registaram vendas.
     */ 
    public ArrayList<String> getProdutosComVendas(){
        ArrayList<String> produtos = new ArrayList<String>();
        for(String s: this.faturacao.keySet()){
            if(!this.faturacao.get(s).semVendas()){
                produtos.add(s);
            }
        }
        return produtos;
    }
  
    /**
     * Devolve a quantidade vendida de produtos.
     * @return quantidade vendida de produtos.
     */
    public int getQuantidadeTotal(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadeVendidaTotal();
        
        return total;
    }
   
   /**
    * Devolve a quantidade de produtos vendida num mês.
    * @param mes Mes que se pretende determinar.
    * @return quantidade de produtos vendida.
    */
    public int getQuantidadeMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadeVendidaMes(mes);
        
        return total;
    }
    
    /**
     * Devolve a quantidade vendida de produtos do tipo N.
     * @return quantidade vendida de produtos.
     */
    public int getQuantidadeProdutoN(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadeVendidaN();
    }
    
    /**
     * Devolve a quantidade vendida de produtos do tipo P.
     * @return quantidade vendida de produtos.
     */
    public int getQuantidadeProdutoP(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadeVendidaP();
    }
    
    /**
     * Devolve a quantidade vendida de produtos do tipo P num determinado mes.
     * @param mes Mes.
     * @return quantidade vendida de produtos.
     */
    public int getQuantidadeNMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadeNMes(mes);
        
        return total;
    }
 
    /**
     * Devolve a quantidade vendida de produtos do tipo N num determinado mes.
     * @param mes Mes.
     * @return quantidade vendida de produtos.
     */
    public int getQuantidadePMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadePMes(mes);
        
        return total;
    }
   
    /**
     * Determina a quantidade vendida de um produto do tipo N num determinado mes.
     * @param mes Mes.
     * @param produto Código do produto.
     * @return quantidade vendida do produto.
     */
    public int getQuantidadeProdutoMesN(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadeNMes(mes);
    }
    
    /**
     * Determina a quantidade vendida de um produto do tipo P num determinado mes.
     * @param mes Mes.
     * @param produto Código do produto.
     * @return quantidade vendida do produto.
     */ 
    public int getQuantidadeProdutoMesP(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadePMes(mes);
    }
    
   /**
    * Determina o total de vendas.
    * @return total de vendas.
    */
    public int getTotalVendas(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasTotal();
        
        return total;
    }
   
    /**
     * Determina o total de vendas num mes.
     * @param mes Mes.
     * @return total de vendas.
     */
    public int getVendasMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasTotalMes(mes);
        
        return total;
    }
    

    /**
     * Determina o total de vendas de um produto do tipo N.
     * @param produto Código do produto.
     * @return total de vendas.
     */
    public int getVendasProdutoN(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasN();
    }
    
    /**
     * Determina o total de vendas de um produto do tipo P.
     * @param produto Código do produto.
     * @return total de vendas.
     */
    public int getVendasProdutoP(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasP();
    }
    
   /**
    * Determina o número total de vendas dos produtos do tipo N num determinado mês.
    * @param mes Mês.
    * @return número total de vendas.
    */
    public int getVendasNMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasNMes(mes);
        
        return total;
    }
    
    /**
     * Determina o número total de vendas dos produtos do tipo P num determinado mês.
     * @param mes Mês.
     * @return número total de vendas.
     */
    public int getVendasPMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasPMes(mes);
        
        return total;
    }
    
    /**
     * Determina o numero total de vendas de um produto do tipo N num determinado mês.
     * @param mes Mês.
     * @param produto Código de produto.
     * @return número total de vendas.
     */
    public int getVendasNMesProduto(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasNMes(mes);
    }
    /**
     * Determina o numero total de vendas de um produto do tipo P num determinado mês.
     * @param mes Mês.
     * @param produto Código de produto.
     * @return número total de vendas.
     */
    public int getVendasPMesProduto(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasPMes(mes);
    }
    
    /**
     * Determina o total faturado.
     * @return total faturado.
     */
    public double getTotalFaturado(){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturado();
        
        return total;
    }
    /**
     * Determina o total faturado de produtos do tipo N.
     * @return total faturado.
     */
    public double getTotalFaturadoN(){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturadoN();
        
        return total;
    }
    /**
     * Determina o total faturado de produtos do tipo P.
     * @return total faturado.
     */
    public double getTotalFaturadoP(){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturadoP();
        
        return total;
    }
    
    /**
     * Determina o total faturado de um produto do tipo N.
     * @param produto Código do produto.
     * @return total faturado.
     */
    public double getFaturadoNProduto(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null)
        	return 0;
        else 
        	return f.getTotalFaturadoN();
    }
    /**
     * Determina o total faturado de um produto do tipo P.
     * @param produto Código do produto.
     * @return total faturado.
     */ 
    public double getFaturadoPProduto(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null)
        	return 0;
        else 
        	return f.getTotalFaturadoP();
    }
    /**
     * Determina o total faturado num determinado mês.
     * @param mes Mês.
     * @return total faturado.
     */
    public double getTotalFaturadoMes(int mes){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturadoMes(mes);
        
        return total;
    }
    
    /**
     * Determina o total faturado dos produtos do tipo N num determinado mês.
     * @param mes Mês.
     * @return total faturado.
     */
    public double getTotalFaturadoNMes(int mes){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	total += f.getFaturadoNMes(mes);
        
        return total;
    }
    /**
     * Determina o total faturado dos produtos do tipo P num determinado mês.
     * @param mes Mês.
     * @return total faturado.
     */
    public double getTotalFaturadoPMes(int mes){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	total += f.getFaturadoPMes(mes);
        
        return total;
    }
    
    /**
     * Determina o total faturado de um produto do tipo N nem determiando mês. 
     * @param mes Mês.
     * @param produto Código de produto.
     * @return total faturado.
     */
    public double getFaturadoNMes(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getFaturadoNMes(mes);
    }
   
    /**
     * Determina o total faturado de um produto do tipo P nem determiando mês. 
     * @param mes Mês.
     * @param produto Código de produto.
     * @return total faturado.
     */
    public double getFaturadoPMes(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getFaturadoPMes(mes);
    }
    
    public boolean equals(Object o) {
        if (this == o) 
        	return true;
        if ((o == null) || (this.getClass() != o.getClass())) 
        	return false;
        
        Faturacao faturacao = (Faturacao) o;
        
        return this.faturacao.equals(faturacao.getFaturacao());
    }
    
    public Faturacao clone() {
        return new Faturacao(this);    
    }
}
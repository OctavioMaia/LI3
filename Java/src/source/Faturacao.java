package source;

import java.io.Serializable;
import java.util.*;

import exceptions.ProdutoInvalidoException;

public class Faturacao implements Serializable{
	
	private TreeMap<String, FaturacaoProduto> faturacao;
    
    public Faturacao () {
        this.faturacao = new TreeMap<String,FaturacaoProduto>();
    }
    
    public Faturacao (List<String> cat) {
        this.faturacao = new TreeMap<String, FaturacaoProduto>();
        for(String s: cat) 
        	this.faturacao.put(s,new FaturacaoProduto());
    }
    
    public Faturacao (Faturacao c) {
        this.faturacao = c.getFaturacao();
    }
    
    public TreeMap<String,FaturacaoProduto> getFaturacao () {
            TreeMap<String,FaturacaoProduto> faturacao = new TreeMap <String,FaturacaoProduto>();
            
            for (String s: faturacao.keySet())
            	faturacao.put(s,faturacao.get(s).clone());
            
            return faturacao;
    }
    
    public FaturacaoProduto getContabilidadeProduto(String produto) throws ProdutoInvalidoException{
        if(!this.faturacao.containsKey(produto))
            throw new ProdutoInvalidoException(produto);
        
        return this.faturacao.get(produto).clone();
    }
    
    public void addProdutos(List<String> cat) {
        for(String s: cat){
        	if(!this.faturacao.containsKey(s))
        		this.faturacao.put(s,new FaturacaoProduto());
        }
    }
    
    public void addProduto(String produto){
        if(!this.faturacao.containsKey(produto))
            this.faturacao.put(produto,new FaturacaoProduto());
    }
    
    public void addVenda(Venda v){
        String produto = v.getProduto();
        if(!this.faturacao.containsKey(produto))
            this.faturacao.put(produto, new FaturacaoProduto());
        
        this.faturacao.get(produto).addVenda(v);
    }
    
    public void removeVenda(Venda v){
        String produto = v.getProduto();
        if(this.faturacao.containsKey(produto))
            this.faturacao.get(produto).removeVenda(v);
    }
    
    public void removeProduto(String produto){
        this.faturacao.remove(produto);
    }
    
    public int getTotProdutosComVendas(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	if(!f.semVendas())
        		total++;
        
        return total;
    }
    
    public int getTotProdutosSemVendas(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	if(f.semVendas()) 
        		total++;
        
        return total;
    }
    
    public ArrayList<String> getProdutosSemVendas(){
        ArrayList<String> produtos = new ArrayList<String>();
        for(String s: this.faturacao.keySet()){
            if(this.faturacao.get(s).semVendas()){
                produtos.add(s);
            }
        }
        return produtos;
    }
    
    public ArrayList<String> getProdutosComVendas(){
        ArrayList<String> produtos = new ArrayList<String>();
        for(String s: this.faturacao.keySet()){
            if(!this.faturacao.get(s).semVendas()){
                produtos.add(s);
            }
        }
        return produtos;
    }
    
    public int getQuantidadeTotal(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadeVendidaTotal();
        
        return total;
    }
    
    public int getQuantidadeMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadeVendidaMes(mes);
        
        return total;
    }
    
    public int getQuantidadeProdutoN(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadeVendidaN();
    }
    
    public int getQuantidadeProdutoP(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadeVendidaP();
    }
    
    public int getQuantidadeNMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadeNMes(mes);
        
        return total;
    }
    
    public int getQuantidadePMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getQuantidadePMes(mes);
        
        return total;
    }
    
    public int getQuantidadeProdutoMesN(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadeNMes(mes);
    }
    
    public int getQuantidadeProdutoMesP(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getQuantidadePMes(mes);
    }
    
    public int getTotalVendas(){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasTotal();
        
        return total;
    }
    
    public int getVendasMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasTotalMes(mes);
        
        return total;
    }
    
    public int getVendasProdutoN(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasN();
    }
    
    public int getVendasProdutoP(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasP();
    }
    
    public int getVendasNMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasNMes(mes);
        
        return total;
    }
    
    public int getVendasPMes(int mes){
        int total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getNumeroVendasPMes(mes);
        
        return total;
    }
    
    public int getVendasNMesProduto(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasNMes(mes);
    }
    
    public int getVendasPMesProduto(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getNumeroVendasPMes(mes);
    }
    
    public double getTotalFaturado(){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturado();
        
        return total;
    }
    
    public double getTotalFaturadoN(){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturadoN();
        
        return total;
    }
    
    public double getTotalFaturadoP(){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturadoP();
        
        return total;
    }
    
    public double getFaturadoNProduto(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null)
        	return 0;
        else 
        	return f.getTotalFaturadoN();
    }
    
    public double getFaturadoPProduto(String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null)
        	return 0;
        else 
        	return f.getTotalFaturadoP();
    }
    
    public double getTotalFaturadoMes(int mes){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
            total += f.getTotalFaturadoMes(mes);
        
        return total;
    }
    
    public double getTotalFaturadoNMes(int mes){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	total += f.getFaturadoNMes(mes);
        
        return total;
    }
    
    public double getTotalFaturadoPMes(int mes){
        double total = 0;
        for(FaturacaoProduto f: this.faturacao.values())
        	total += f.getFaturadoPMes(mes);
        
        return total;
    }
    
    public double getFaturadoNMes(int mes, String produto){
        FaturacaoProduto f = this.faturacao.get(produto);
        if(f == null) 
        	return 0;
        else 
        	return f.getFaturadoNMes(mes);
    }
   
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
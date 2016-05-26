package source;

import java.io.Serializable;

/**
 * Faturacao de um dado produto
 */
public class FaturacaoProduto implements Serializable{
    private int[][] vendasN;
    private int[][] vendasP;
    private int[][] quantidadeN;
    private int[][] quantidadeP;
    private double[][] faturadoN;
    private double[][] faturadoP;
    
    public FaturacaoProduto() {
        this.vendasN = new int[12][3];
        this.vendasP = new int[12][3];
        this.quantidadeN = new int[12][3];
        this.quantidadeP = new int[12][3];
        this.faturadoN = new double[12][3];
        this.faturadoP = new double[12][3];
    }
    
    public FaturacaoProduto (int[][] vendasN, int[][] vendasP, int[][] quantidadeN, int[][] quantidadeP, double[][] factN, double[][] factP) {
        this.vendasN = vendasN.clone();
        this.vendasP = vendasP.clone();
        this.quantidadeN = quantidadeN.clone();
        this.quantidadeP = quantidadeP.clone();
        this.faturadoN = factN.clone();
        this.faturadoP = factP.clone();
    }
    
    public FaturacaoProduto (FaturacaoProduto cont) {
        this.vendasN = cont.getComprasN();
        this.vendasP = cont.getComprasP();
        this.quantidadeN = cont.getVendasN();
        this.quantidadeP = cont.getVendasP();
        this.faturadoN = cont.getFaturacaoN();
        this.faturadoP = cont.getFaturacaoP();
    }
    
    public int[][] getComprasN() { 
        return this.vendasN.clone();
    }  
    
    public int[][] getComprasP(){
        return this.vendasP.clone();
    }
    
    public int[][] getVendasN() {
        return this.quantidadeN.clone();
    }
    
    public int[][] getVendasP() {
        return this.quantidadeP.clone();
    }
    
    public double[][] getFaturacaoN() {
        return this.faturadoN.clone();
    }
    
    public double[][] getFaturacaoP() { 
        return this.faturadoP.clone();
    }
    
    public void addVenda(Venda v){
        int mes = v.getMes();
        int filial = v.getFilial();
        char tipo = v.getTipo();
        
        if(mes >= 1 && mes <= 12){
        	if(filial >= 1 && filial <= 3){
	            if(tipo == 'N'){
	                this.vendasN[mes-1][filial-1] += 1;
	                this.quantidadeN[mes-1][filial-1] += v.getQuantidade();
	                this.faturadoN[mes-1][filial-1] += (v.getQuantidade()*v.getPreco());
	            }
	            else if(tipo == 'P'){
	                this.vendasP[mes-1][filial-1] += 1;
	                this.quantidadeP[mes-1][filial-1] += v.getQuantidade();
	                this.faturadoP[mes-1][filial-1] += (v.getQuantidade()*v.getPreco());
	            }
        	}
        }
    }
    
    public void removeVenda(Venda v){
        int mes = v.getMes();
        int filial = v.getFilial();
        char tipo = v.getTipo();
       
        if(mes >= 1 && mes <= 12){
        	if(filial >= 1 && filial <= 3){
	            if(tipo == 'N'){
	                this.vendasN[mes-1][filial-1] -= 1;
	                this.quantidadeN[mes-1][filial-1] -= v.getQuantidade();
	                this.faturadoN[mes-1][filial-1] -= (v.getQuantidade()*v.getPreco());
	            }
	            else if(tipo == 'P'){
	                this.vendasN[mes-1][filial-1] -= 1;
	                this.quantidadeP[mes-1][filial-1] -= v.getQuantidade();
	                this.faturadoP[mes-1][filial-1] -= (v.getQuantidade()*v.getPreco());
	            }
        	}
        }
    }
    
    public boolean semVendas(){
        boolean venda = true;
        for(int i = 0; i<12 && venda; i++){
        	for(int j = 0; j<3; j++ ){
        		if(this.vendasN[i][j] > 0 || this.vendasP[i][j] > 0){
        			venda = false;
        		}
        	}
        }
        return venda;
    }
    
    public int getNumeroVendasTotal(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += (this.vendasN[i][j] + this.vendasP[i][j]);
			}
        }
        return count;
    }
    	
    public int getNumeroVendasN(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasN[i][j];
        	}
        }
        return count;
    }
    
    public int getNumeroVendasP(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasP[i][j];
        	}
    	}
        return count;
    }
    
    public int getNumeroVendasTotalMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += (this.vendasN[mes-1][j] + this.vendasP[mes-1][j]);
        	}
        }
        return count;
    }
    
    public int getNumeroVendasNMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasN[mes-1][j];
        	}
        }
        return count;
    }
    
    public int getNumeroVendasPMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasP[mes-1][j];
        	}
        }
        return count;
    }

    public int getQuantidadeVendidaTotal(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += (this.quantidadeN[i][j] + this.quantidadeP[i][j]);
			}
        }
        return count;
    }
    	
    public int getQuantidadeVendidaN(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeN[i][j];
        	}
        }
        return count;
    }
    
    public int getQuantidadeVendidaP(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeP[i][j];
        	}
    	}
        return count;
    }
    
    public int getQuantidadeVendidaMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += (this.quantidadeN[mes-1][j] + this.quantidadeP[mes-1][j]);
        	}
        }
        return count;
    }
    
    public int getQuantidadeNMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeN[mes-1][j];
        	}
        }
        return count;
    }
    
    public int getQuantidadePMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeP[mes-1][j];
        	}
        }
        return count;
    }
    
    public double getTotalFaturado(){
        double fact = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		fact += (faturadoN[i][j]+faturadoP[i][j]);
        	}
        }
        return fact;
    }
    
    public double getTotalFaturadoN(){
        double fact = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoN[i][j];
        	}
        }
        return fact;
    }
    
    public double getTotalFaturadoP(){
        double fact = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoP[i][j];
        	}
        }
        return fact;
    }
    
    public double getTotalFaturadoMes(int mes){
        double fact = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoN[mes-1][j]+faturadoP[mes-1][j];
        	}
        }
        return fact;
    }
    
    public double getFaturadoNMes(int mes){
        double fact = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoN[mes-1][j];
        	}
        }
        return fact;
    }
    
    public double getFaturadoPMes(int mes){
        double fact = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoP[mes-1][j];
        	}
        }
        return fact;
    }
    
    public boolean equals(Object o) {
        if (this == o) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;
        FaturacaoProduto cont = (FaturacaoProduto) o;
        boolean flag = true;
        
        for(int i = 0; i<12 && flag; i++){
        	for(int j = 0; j<3 && flag; j++){
	            if(this.vendasN[i][j] != cont.getComprasN()[i][j] 	   ||
	            	this.vendasP[i][j] != cont.getComprasP()[i][j] 	   ||
	               	this.quantidadeN[i][j] != cont.getVendasN()[i][j]  ||
	               	this.quantidadeP[i][j] != cont.getVendasP()[i][j]  ||
	               	this.faturadoN[i][j] != cont.getFaturacaoN()[i][j] ||
	               	this.faturadoP[i][j] != cont.getFaturacaoP()[i][j]){
	            	flag = false;
	            }
        	}
        }
        return flag;
    }
    
    public FaturacaoProduto clone() {
        return new FaturacaoProduto(this);
    }
}

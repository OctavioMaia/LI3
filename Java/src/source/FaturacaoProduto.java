package source;

import java.io.Serializable;

/**
 * Faturacao de um dado produto. E formada 
 * pelas vendas, quantidade e faturado todos
 * estes separados em Normal ou Promocao.
 * 
 */
public class FaturacaoProduto implements Serializable{
    private int[][] vendasN;
    private int[][] vendasP;
    private int[][] quantidadeN;
    private int[][] quantidadeP;
    private double[][] faturadoN;
    private double[][] faturadoP;
    
    
    /**
	  * Construtor vazio da classe FaturacaoProduto.
	  */
    public FaturacaoProduto() {
        this.vendasN = new int[12][3];
        this.vendasP = new int[12][3];
        this.quantidadeN = new int[12][3];
        this.quantidadeP = new int[12][3];
        this.faturadoN = new double[12][3];
        this.faturadoP = new double[12][3];
    }
    
    /**
     * Construtor parametrizado da classe FaturacaoProduto.
     * @param vendasN Vendas do tipo normal.
     * @param vendasP Vendas do tipo promocao.
     * @param quantidadeN Quantidade do tipo Normal.
     * @param quantidadeP Quantidade do tipo Promocao.
     * @param factN Faturado em modo Normal.
     * @param factP Faturado em modo Promocao.
     */   
    public FaturacaoProduto (int[][] vendasN, int[][] vendasP, int[][] quantidadeN, int[][] quantidadeP, double[][] factN, double[][] factP) {
        this.vendasN = vendasN.clone();
        this.vendasP = vendasP.clone();
        this.quantidadeN = quantidadeN.clone();
        this.quantidadeP = quantidadeP.clone();
        this.faturadoN = factN.clone();
        this.faturadoP = factP.clone();
    }
    
    
    /**
	    * Construtor por copia da classe FaturacaoProduto.
	    * @param cont FaturacaoProduto a copiar.
	    */
    public FaturacaoProduto (FaturacaoProduto cont) {
        this.vendasN = cont.getComprasN();
        this.vendasP = cont.getComprasP();
        this.quantidadeN = cont.getVendasN();
        this.quantidadeP = cont.getVendasP();
        this.faturadoN = cont.getFaturacaoN();
        this.faturadoP = cont.getFaturacaoP();
    }
    
    /**
     * Funcao que devolve as vendas em modo Normal.
     * @return vendas em modo Normal.
     */
    public int[][] getComprasN() { 
        return this.vendasN.clone();
    }  
    
    /**
     * Funcao que devolve as vendas em modo Promocao.
     * @return vendas em modo Promocao.
     */
    public int[][] getComprasP(){
        return this.vendasP.clone();
    }
    
    /**
     * Funcao que devolve a quantidade em modo Normal.
     * @return quantidade em modo Normal.
     */
    public int[][] getVendasN() {
        return this.quantidadeN.clone();
    }
    
    /**
     * Funcao que devolve a quantidade em modo Promocao.
     * @return quantidade em modo Promocao.
     */
    public int[][] getVendasP() {
        return this.quantidadeP.clone();
    }
    
    /**
     * Funcao que devolve o faturado em modo Normal.
     * @return faturado em modo Normal.
     */
    public double[][] getFaturacaoN() {
        return this.faturadoN.clone();
    }
    
    /**
     * Funcao que devolve o faturado em modo Promocao.
     * @return faturado em modo Promocao.
     */
    public double[][] getFaturacaoP() { 
        return this.faturadoP.clone();
    }
    
    /**
     * Funcao resposável por adicionar uma Venda válida.
     * @param v venda a adicionar.
     */
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
    
    /**
     * Função responsável pela remoção de uma venda.
     * @param v venda a remover.
     */
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
    
    /**
     * Funcao que verifica se na matriz vendasP 
     * ou vendasN existem vendas.
     * @return true se nao existirem vendas, false caso contrario.
     */
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
    
    /**
     * Funcao que devolve o numero total de vendas.
     * @return numero de vendas total.
     */
    public int getNumeroVendasTotal(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += (this.vendasN[i][j] + this.vendasP[i][j]);
			}
        }
        return count;
    }
    	
    /**
     * Funcao que devolve o numero de vendas em modo Normal.
     * @return numero de vendas em modo normal.
     */
    public int getNumeroVendasN(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasN[i][j];
        	}
        }
        return count;
    }
    
    /**
     * Funcao que devolve o numero de vendas em modo Promocao.
     * @return numero de vendas em modo Promocao.
     */
    public int getNumeroVendasP(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasP[i][j];
        	}
    	}
        return count;
    }
    
    /**
     * Funcao que devolve o numero total de vendas num dado mes.
     * @param mes Mes para o qual se pretende saber o numero de vendas.
     * @return numero total de vendas num dado mes.
     */
    public int getNumeroVendasTotalMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += (this.vendasN[mes-1][j] + this.vendasP[mes-1][j]);
        	}
        }
        return count;
    }
    

    /**
     * Funcao que devolve o numero total de vendas em modo Normal num dado mes.
     * @param mes Mes para o qual se pretende saber o numero de vendas.
     * @return numero total de vendas em modo Normal num dado mes.
     */
    public int getNumeroVendasNMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasN[mes-1][j];
        	}
        }
        return count;
    }
    
    

    /**
     * Funcao que devolve o numero total de vendas em modo Promocao num dado mes.
     * @param mes Mes para o qual se pretende saber o numero de vendas.
     * @return numero total de vendas em modo Promocao num dado mes.
     */
    public int getNumeroVendasPMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.vendasP[mes-1][j];
        	}
        }
        return count;
    }


    /**
     * Funcao que devolve a quantidade total vendida.
     * @return quantidade vendida total.
     */
    public int getQuantidadeVendidaTotal(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += (this.quantidadeN[i][j] + this.quantidadeP[i][j]);
			}
        }
        return count;
    }
    

    /**
     * Funcao que devolve a quantidade total vendida em modo Normal.
     * @return quantidade vendida total em modo Normal.
     */
    public int getQuantidadeVendidaN(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeN[i][j];
        	}
        }
        return count;
    }
    

    /**
     * Funcao que devolve a quantidade total vendida em modo Promocao.
     * @return quantidade vendida total em modo Promocao.
     */
    public int getQuantidadeVendidaP(){
        int count = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeP[i][j];
        	}
    	}
        return count;
    }
    

    /**
     * Funcao que devolve a quantidade total vendida num dado mes.
     * @param mes Mes para o qual se pretende saber a quantidade vendida.
     * @return quantidade vendida nesse mes.
     */
    public int getQuantidadeVendidaMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += (this.quantidadeN[mes-1][j] + this.quantidadeP[mes-1][j]);
        	}
        }
        return count;
    }
    
    

    /**
     * Funcao que devolve a quantidade total vendida num dado mes em modo Normal.
     * @param mes Mes para o qual se pretende saber a quantidade vendida.
     * @return quantidade vendida em modo Normal nesse mes.
     */
    public int getQuantidadeNMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeN[mes-1][j];
        	}
        }
        return count;
    }
    
    

    /**
     * Funcao que devolve a quantidade total vendida num dado mes em modo Promocao.
     * @param mes Mes para o qual se pretende saber a quantidade vendida.
     * @return quantidade vendida em modo Promocao nesse mes.
     */
    public int getQuantidadePMes(int mes){
        int count = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		count += this.quantidadeP[mes-1][j];
        	}
        }
        return count;
    }
    

    /**
     * Funcao que devolve o total faturado.
     * @return total faturado.
     */
    public double getTotalFaturado(){
        double fact = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		fact += (faturadoN[i][j]+faturadoP[i][j]);
        	}
        }
        return fact;
    }
    

    /**
     * Funcao que devolve o total faturado em modo Normal.
     * @return total faturado Normal.
     */
    public double getTotalFaturadoN(){
        double fact = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoN[i][j];
        	}
        }
        return fact;
    }
    

    /**
     * Funcao que devolve o total faturado em modo Promocao.
     * @return total faturado Promocao.
     */
    public double getTotalFaturadoP(){
        double fact = 0;
        for(int i = 0; i<12; i++){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoP[i][j];
        	}
        }
        return fact;
    }
    

    /**
     * Funcao que devolve o total faturado num dado mes.
     * @param mes Mes para o qual se pretende saber o total faturado.
     * @return total faturado nesse mes.
     */
    public double getTotalFaturadoMes(int mes){
        double fact = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoN[mes-1][j]+faturadoP[mes-1][j];
        	}
        }
        return fact;
    }
    

    /**
     * Funcao que devolve o total faturado em modo Normal num dado mes.
     * @param mes Mes para o qual se pretende saber o total faturado.
     * @return total faturado em modo Normal nesse mes.
     */
    public double getFaturadoNMes(int mes){
        double fact = 0;
        if(mes>=1 && mes <= 12){
        	for (int j = 0; j < 3; j++) {
        		fact += faturadoN[mes-1][j];
        	}
        }
        return fact;
    }
    

    /**
     * Funcao que devolve o total faturado em modo Promocao num dado mes.
     * @param mes Mes para o qual se pretende saber o total faturado.
     * @return total faturado em modo Promocao nesse mes.
     */
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

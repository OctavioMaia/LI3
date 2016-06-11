package source;

import java.io.Serializable;

/**
 * Representa uma venda. E formada pelos codigos de produto e
 * cliente, preco, quantidade, tipo (normal/promocao), mes e filial.
 */
public class Venda{
    private String produto;
    private String cliente;
    private double preco;
    private int quantidade;
    private char tipo;
    private int mes;
    private int filial;

    /**
     * Construtor vazio da classe Venda.
     */
    public Venda() {
        this.produto = "";
        this.cliente = "";
        this.preco = 0;
        this.quantidade = 0;
        this.tipo = ' ';
        this.mes = 0;
        this.filial = 0;
    }
    
    /**
     * Construtor parametrizado da classe Venda.
     * @param produto Codigo do produto.
	 * @param preco Preco do produto.
	 * @param quantidade Numero de produto vendidos.
	 * @param tipo Tipo do produto (N ou P).
	 * @param cliente Codigo do cliente que realizou a compra.
	 * @param mes Mes relativo a venda.
	 * @param filial Filial em que foi realizada a venda.
	 */   
    public Venda(String produto, double preco, int quantidade, char tipo, String cliente, int mes, int filial) {
        this.produto = produto;
        this.cliente = cliente;
        this.preco = preco;
        this.quantidade = quantidade;
        this.tipo = tipo;
        this.mes = mes;
        this.filial = filial;
    }
    
   
    /**
    * Construtor por copia da classe Venda.
    * @param v Venda a copiar.
    */
    public Venda(Venda v) {
        this.produto = v.getProduto();
        this.cliente = v.getCliente();
        this.preco = v.getPreco();
        this.quantidade = v.getQuantidade();
        this.tipo = v.getTipo();
        this.mes = v.getMes();
        this.filial = v.getFilial(); 
    }
    
    /**
     * Função que devolve o codigo do produto.
     * @return codigo do produto.
     */
    public String getProduto() { return this.produto; } 
    
    /**
     * Funcao que devolve o codigo do cliente.
     * @return codigo do cliente.
     */
    public String getCliente() { return this.cliente; }
    
    /**
     * Funcao que devolve o preco de um produto.
     * @return preco do produto.
     */
    public double getPreco() { return this.preco; }
    
    /**
     * Funcao que devolve o numero de produtos vendidos. 
     * @return numero de produtos vendidos.
     */
    public int getQuantidade() { return this.quantidade;}
    
    /**
     * Funcao que devolve o tipo do produto.
     * @return tipo da venda (Normal ou Promocao).
     */
    public char getTipo() { return this.tipo; }
    
    /**
     * Funcao que devolve o mes da venda.
     * @return mes relativo a venda.
     */
    public int getMes() {return this.mes;}
    
    /**
     * Funcao que devolve a filial onde foi realizada a venda.
     * @param numero relativo a filial.
     */
    public int getFilial(){return this.filial; }
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Produto: "+this.produto);
        sb.append(" Cliente: "+this.cliente);
        sb.append(" Preco: "+String.format("%.2f",this.preco));
        sb.append(" Quantidade: "+this.quantidade);
        sb.append(" Tipo: "+this.tipo);
        sb.append(" Mês: "+this.mes);
        sb.append(" Filial: "+this.filial + "\n");
        return sb.toString();
    }
    
    public boolean equals(Object o) {
        if (this == o) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;
        Venda v = (Venda) o;
        return this.produto.equals(v.getProduto()) &&
               this.cliente.equals(v.getCliente()) &&
               this.preco == v.getPreco()          &&
               this.quantidade == v.getQuantidade()&&
               this.tipo == v.getTipo()            &&
               this.mes == v.getMes()			   &&
               this.filial == v.getFilial();
    }
    
    public Venda clone(){
        return new Venda(this);
    }
}
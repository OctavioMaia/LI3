package source;

import java.io.Serializable;

/**
 * Representa uma venda. � formada pelos c�digos de produto e
 * cliente, pre�o, quantidade, tipo (normal/promo��o), m�s e filial.
 */
public class Venda implements Serializable{
    private String produto;
    private String cliente;
    private double preco;
    private int quantidade;
    private char tipo;
    private int mes;
    private int filial;

    public Venda() {
        this.produto = "";
        this.cliente = "";
        this.preco = 0;
        this.quantidade = 0;
        this.tipo = ' ';
        this.mes = 0;
        this.filial = 0;
    }
    
    public Venda(String produto, double preco, int quantidade, char tipo, String cliente, int mes, int filial) {
        this.produto = produto;
        this.cliente = cliente;
        this.preco = preco;
        this.quantidade = quantidade;
        this.tipo = tipo;
        this.mes = mes;
        this.filial = filial;
    }
    
    public Venda(Venda v) {
        this.produto = v.getProduto();
        this.cliente = v.getCliente();
        this.preco = v.getPreco();
        this.quantidade = v.getQuantidade();
        this.tipo = v.getTipo();
        this.mes = v.getMes();
        this.filial = v.getFilial(); 
    }
    
    public String getProduto() { return this.produto; } 
    public String getCliente() { return this.cliente; }
    public double getPreco() { return this.preco; }
    public int getQuantidade() { return this.quantidade;}
    public char getTipo() { return this.tipo; }
    public int getMes() {return this.mes;}
    public int getFilial(){return this.filial; }
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Produto: "+this.produto);
        sb.append("\nCliente: "+this.cliente);
        sb.append("\nPreco: "+String.format("%.2f",this.preco));
        sb.append("\nQuantidade: "+this.quantidade);
        sb.append("\nTipo: "+this.tipo);
        sb.append("\nMês: "+this.mes);
        sb.append("\nFilial: "+this.filial + "\n");
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
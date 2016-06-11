package source;

import java.util.*;
/**
 * Catálogo de clientes e produtos.
 */
public class Catalogo {
    private TreeSet<String> catalogo;

    /**
     * Construtor vazio da classe Catalogo.
     */
    public Catalogo () {
        this.catalogo = new TreeSet<String>();
    }
    
    /**
     * Construtor parametrizado da classe Catalogo.
     * @param cat Lista de strings a adicionar ao catalogo.
     */
    public Catalogo (List<String> cat) {
        this.catalogo = new TreeSet<String>();
        for(String s: cat) 
        	this.catalogo.add(s);
    }
    
    /**
     * Construtor por copia da classe Catalogo.
     * @param c Catalogo a copiar
     */
    public Catalogo (Catalogo c) {
        this.catalogo = c.getCatalogo();
    }
    
    /**
     * Função que retorna todas as strings do catalogo.
     * @return TreeSet que inclui todos as strings desse catalogo.
     */
    public TreeSet<String> getCatalogo() {
        TreeSet<String> cat = new TreeSet<String>();
        for (String s : this.catalogo)
        	cat.add(s);
        
        return cat;
    }
    
    /**
     * Função que retorna um ArrayList contendo todos as strings começadas pelo parametro dado.
     * @param ch Letra para filtrar as strings.
     * @return lista com todos os codigos começados pela dada letra.
     */
    public ArrayList<String> getCodigosLetra(char ch) {
    	ArrayList<String> cat = new ArrayList<String>();
        for (String s : this.catalogo)
        	if(s.charAt(0)==ch)
        		cat.add(s);
        
        return cat;
    }
    
    /**
     * Função que adiciona uma string ao catalogo.
     * @param codigo String a remover.
     */
    public void add(String codigo){
        this.catalogo.add(codigo);
    }
    
    /**
     * Função que remove uma string do catalogo.
     * @param codigo String a remover.
     */
    public void remove(String codigo){
        this.catalogo.remove(codigo);
    }
    
    /**
     * Função que verifica se uma string pertence ao catalogo.
     * @param codigo String a verificar.
     */
    public boolean contains(String codigo){
        return this.catalogo.contains(codigo);
    }
    
    /**
     * Calcula o tamanho do catalogo.
     * @return Retorna o tamanho do catalogo.
     */
    public int size(){
    	return this.catalogo.size();
    }
    
    public boolean equals(Object o) {
        if (this == o)
        	return true;
        if ((o == null) || (this.getClass() != o.getClass()))
        	return false;
        
        Catalogo catalogo = (Catalogo) o;
        return this.catalogo.equals(catalogo.getCatalogo());
    }
    
    public Catalogo clone() {
        return new Catalogo(this);
    }
    
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (String s: this.catalogo)
        	sb.append(s);
        
        return sb.toString();
    }   
}
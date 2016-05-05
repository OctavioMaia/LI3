package source;

import java.io.Serializable;
import java.util.*;
/**
 * Catálogo de clientes e produtos.
 */
public class Catalogo implements Serializable{
    private TreeSet<String> catalogo;

    public Catalogo () {
        this.catalogo = new TreeSet<String>();
    }
    
    public Catalogo (List<String> cat) {
        this.catalogo = new TreeSet<String>();
        for(String s: cat) 
        	this.catalogo.add(s);
    }
    
    public Catalogo (Catalogo c) {
        this.catalogo = c.getCatalogo();
    }
    
    public TreeSet<String> getCatalogo() {
        TreeSet<String> cat = new TreeSet<String>();
        for (String s : this.catalogo)
        	cat.add(s);
        return cat;
    }
    
    public void add(String codigo){
        this.catalogo.add(codigo);
    }
    
    public void remove(String codigo){
        this.catalogo.remove(codigo);
    }
    
    public boolean contains(String codigo){
        return this.catalogo.contains(codigo);
    }
    
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
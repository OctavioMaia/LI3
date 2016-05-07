package exceptions;

public class ProdutoInvalidoException extends Exception{
    public ProdutoInvalidoException(){
        super();
    }
    public ProdutoInvalidoException(String msg){
        super(msg);
    }
}

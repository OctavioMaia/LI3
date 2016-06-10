package source;
import java.io.*;

public class Persistencia implements Serializable{

   public void guardarEstado(Hipermercado e) throws IOException{
       FileOutputStream fos = new FileOutputStream("hipermercado.dat");
       ObjectOutputStream oos = new ObjectOutputStream(fos);
        
       oos.writeObject(e);
       oos.close();
   }
    
 
   public Hipermercado carregarEstado() throws IOException,ClassNotFoundException{
       ObjectInputStream ois = new ObjectInputStream(new FileInputStream("hipermercado.dat"));

       Hipermercado novoState = (Hipermercado) ois.readObject();      
       ois.close();
       
       return novoState;
   } 
}
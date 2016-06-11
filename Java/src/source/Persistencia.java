package source;
import java.io.*;

public class Persistencia implements Serializable{

   public void guardarEstado(Hipermercado e, String path) throws IOException{
       FileOutputStream fos = new FileOutputStream(path);
       ObjectOutputStream oos = new ObjectOutputStream(fos);
        
       oos.writeObject(e);
       oos.close();
   }
    
 
   public Hipermercado carregarEstado(String path) throws IOException,ClassNotFoundException{
       ObjectInputStream ois = new ObjectInputStream(new FileInputStream(path));

       Hipermercado novoState = (Hipermercado) ois.readObject();      
       ois.close();
       
       return novoState;
   } 
}
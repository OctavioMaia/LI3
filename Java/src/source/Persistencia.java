package source;

import java.io.*;

public class Persistencia implements Serializable {

	/**
	 * Função responsável por guardar o estado do programa.
	 * @param e Instancia a guardar.
	 * @param path Nome do ficheiro a guardar.
	 * @throws IOException 
	 */
	public void guardarEstado(Hipermercado e, String path) throws IOException {
		FileOutputStream fos = new FileOutputStream(path);
		ObjectOutputStream oos = new ObjectOutputStream(fos);

		oos.writeObject(e);
		oos.close();
	}

	/**
	 * Função responsável por carregar o estado do programa.
	 * @param path ficheiro a carregar.
	 * @return Instancia Hipermercado carregada a partir do ficheiro.
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	public Hipermercado carregarEstado(String path) throws IOException, ClassNotFoundException {
		ObjectInputStream ois = new ObjectInputStream(new FileInputStream(path));

		Hipermercado novoState = (Hipermercado) ois.readObject();
		ois.close();

		return novoState;
	}
}
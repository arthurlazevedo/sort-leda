import java.util.Arrays;
import java.util.Random;

public class Bubble {

  public static void main(String[] args) {
    Random random = new Random();

    int[] lista1 = random.ints(10000, 0, 100000).toArray();
    int[] lista2 = Arrays.copyOf(lista1, lista1.length);

    Arrays.sort(lista1);
    inPlace(lista2);

    assert Arrays.equals(lista1, lista2);
  }

  private static void inPlace(int[] v) {
    boolean ordenado = false;
    while (!ordenado) {
      ordenado = true;
      for (int i = 0; i < v.length - 1; i++) {
        if (v[i] > v[i + 1]) {
          swap(v, i, i + 1);
          ordenado = false;
        }
      }
    }
  }

  private static void swap(int[] v, int i, int j) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
  }
}
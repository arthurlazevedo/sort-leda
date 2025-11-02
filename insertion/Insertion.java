import java.util.Arrays;
import java.util.Random;

public class Insertion {

    public static void main(String[] args) {
        Random random = new Random();
        int[] lista1 = random.ints(10000, 0, 100000).toArray();

        int[] ordenado = outPlace(lista1);
        System.out.println(Arrays.toString(ordenado));

        int[] lista2 = Arrays.copyOf(lista1, lista1.length);
        inPlace(lista2);
        System.out.println(Arrays.toString(lista2));

        System.out.println(Arrays.equals(ordenado, lista2));
    }

    private static void inPlace(int[] v) {
        for (int i = 0; i < v.length; i++) {
            int j = i;
            while (j > 0 && v[j] < v[j - 1]) {
                swap(v, j, j - 1);
                j--;
            }
        }
    }

    private static int[] outPlace(int[] original) {
        int[] ordenado = new int[original.length];
        ordenado[0] = original[0];

        for (int i = 0; i < original.length; i++) {
            ordenado[i] = original[i];
            int j = i;
            while (j > 0 && ordenado[j] < ordenado[j - 1]) {
                swap(ordenado, j, j - 1);
                j--;
            }
        }

        return ordenado;
    }

    private static void swap(int[] v, int i, int j) {
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}
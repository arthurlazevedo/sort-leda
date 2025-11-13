import java.util.Arrays;
import java.util.Random;

public class Counting {
    public static void main(String[] args) {
        Random random = new Random();
        int[] lista1 = random.ints(10201, -100, 100000).toArray();

        int[] lista2 = Arrays.copyOf(lista1, lista1.length);
        int[] ordenado = outPlace(lista1);
        inPlace(lista2);

        assert Arrays.equals(ordenado, lista2);
        assert estaOrdenado(lista2);
    }


    public static void inPlace(int[] a) {
        int[] mm = maiorMenor(a);
        int maior = mm[0];
        int menor = mm[1];

        int[] c = new int[maior - menor + 1];
        for (int i = 0; i < a.length; i++) {
            c[a[i] - menor]++;
        }

        for (int i = 1; i < c.length; i++) {
            c[i] += c[i - 1];
        }

        int[] b = Arrays.copyOf(a, a.length);
        for (int i = b.length - 1; i >= 0; i--) {
            a[c[b[i] - menor] - 1] = b[i];
            c[b[i] - menor]--;
        }
    }


    public static int[] outPlace(int[] a) {
        int[] mm = maiorMenor(a);
        int maior = mm[0];
        int menor = mm[1];

        int[] c = new int[maior - menor + 1];
        for (int i = 0; i < a.length; i++) {
            c[a[i] - menor]++;
        }

        for (int i = 1; i < c.length; i++) {
            c[i] += c[i - 1];
        }

        int[] b = new int[a.length];
        for (int i = a.length - 1; i >= 0; i--) {
            b[c[a[i] - menor] - 1] = a[i];
            c[a[i] - menor]--;
        }

        return b;
    }


    private static int[] maiorMenor(int[] a) {
        if (a.length == 0) return new int[] {0, 0};

        int maior = a[0];
        int menor = a[0];

        for (int i = 0; i < a.length; i++) {
            if (a[i] > maior) maior = a[i];
            if (a[i] < menor) menor = a[i];
        }
        return new int[] {maior, menor};
    }


    private static boolean estaOrdenado(int[] v) {
        for (int i = 0; i < v.length - 1; i++) {
            if (v[i] > v[i + 1]) return false;
        }
        return true;
    }
}
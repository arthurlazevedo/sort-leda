import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Random;

public class Quick {
    public static void main(String[] args) {
        Random random = new Random();

        int[] lista1 = random.ints(230597, 0, 100000).toArray();
        int[] lista2 = Arrays.copyOf(lista1, lista1.length);

        Arrays.sort(lista1);
        // recursivo(lista2, 0, lista2.length - 1);
        iterativo(lista2);

        assert Arrays.equals(lista1, lista2);
    }


    public static void recursivo(int[] v, int ini, int fim) {
        if (ini < fim) {
            int indicePivot = particionaLomuto(v, ini, fim);
            recursivo(v, ini, indicePivot - 1);
            recursivo(v, indicePivot + 1, fim);
        }
    }


    public static void iterativo(int[] v) {
        ArrayDeque<Integer> fila = new ArrayDeque<>(); // TODO: implementação própria pra funcionar com inteiros seria legal, melhora uso de memória

        fila.add(0);
        fila.add(v.length - 1);

        while (!fila.isEmpty()) {
            int ini = fila.pollFirst();
            int fim = fila.pollFirst();

            int indicePivot = particionaHoare(v, ini, fim);
            if (ini < indicePivot - 1) {
                fila.addLast(ini);
                fila.addLast(indicePivot - 1);
            }

            if (indicePivot + 1 < fim) {
                fila.addLast(indicePivot + 1);
                fila.addLast(fim);
            }
        }
    }


    public static int particionaLomuto(int[] v, int ini, int fim) {
        int med = medianaDeTres(v, ini, fim);
        swap(v, ini, med);

        int pivot = v[ini];
        int i = ini;

        for (int j = i + 1; j <= fim; j++) {
            if (v[j] <= pivot) {
                swap(v, ++i, j);
            }
        }

        swap(v, ini, i);
        return i;
    }


    public static int particionaHoare(int[] v, int ini, int fim) {
        int med = medianaDeTres(v, ini, fim);
        swap(v, ini, med);

        int pivot = v[ini];
        int i = ini;
        int j = fim;

        while (i <= j) {
            while (i <= j && v[i] <= pivot) i++;
            while (i <= j && v[j] > pivot) j--;

            if (i < j) swap(v, i, j);
        }

        swap(v, ini, j);
        return j;
    }


    private static int medianaDeTres(int[] v, int ini, int fim) {
        int meio = (ini + fim) / 2;

        int[] med = {v[ini], v[meio], v[fim]};
        Arrays.sort(med);

        if (med[1] == v[ini]) return ini;
        if (med[1] == v[meio]) return meio;
        return fim;
    }


    private static void swap(int[] v, int i, int j) {
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}
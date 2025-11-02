
import java.util.Arrays;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class Selection {

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

    private static void inPlace(int[] lista) {
        for (int i = 0; i < lista.length; i++) {
                int menorIndice = i;
                for (int j = i + 1; j < lista.length; j++) {
                        if (lista[j] < lista[menorIndice]) {
                            menorIndice = j;
                        }
                }
                int antigo = lista[i];
                lista[i] = lista[menorIndice];
                lista[menorIndice] = antigo;
        }
    }

    private static int[] outPlace(int[] lista) {
        int[] ordenado = new int[lista.length];
        Set<Integer> vistos = new HashSet<>();

        int maiorIndice = maiorIdx(lista);
        for (int i = 0; i < lista.length; i++) {
            int menorIndice = maiorIndice;
            for (int j = 0; j < lista.length; j++) {
                    if (lista[j] <= lista[menorIndice] && !vistos.contains(j)) {
                        menorIndice = j;
                    }
            }
            vistos.add(menorIndice);
            ordenado[i] = lista[menorIndice];
        }

        return ordenado;
    }

    private static int maiorIdx(int[] lista) {
        if (lista.length == 0) return Integer.MIN_VALUE;
        int maior = 0;
        for (int i = 1; i < lista.length; i++) {
                if (lista[i] > lista[maior]) {
                    maior = i;
                }
        }
        return maior;
    }
}
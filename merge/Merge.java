import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

public class Merge {

    public static void main(String[] args) {
        Random random = new Random();

        int[] lista1 = random.ints(601301, 0, 100000).toArray();
        int[] lista2 = Arrays.copyOf(lista1, lista1.length);

        Arrays.sort(lista1);
        // recursivo(lista2, 0, lista2.length - 1);
        iterativo(lista2);

        assert Arrays.equals(lista1, lista2);
    }


    @SuppressWarnings("unused")
    private static void recursivo(int[] v, int ini, int fim) {
        if (ini < fim) {
            int meio = (ini + fim) / 2;
            recursivo(v, ini, meio);
            recursivo(v, meio + 1, fim);
            mergeOutPlace(v, ini, meio, fim);
        }
    }


    @SuppressWarnings("unused")
    private static void iterativo(int[] v) {
        int faixa = 2;
        int tamanho = v.length;

        while (faixa <= tamanho) {
            for (int i = 0; i < tamanho; i += faixa) {
                int fim = Math.min(i + faixa, tamanho) - 1;
                int meio = (i + fim) / 2;
                mergeOutPlace(v, i, meio, fim);
            }

            faixa *= 2;
        }

        ArrayList<Integer> potencias = new ArrayList<>();
        int parteFudida = tamanho - faixa / 2;

        if (parteFudida == 0) return;

        while (parteFudida > 0) {
            int potencia = 1;
            while (potencia <= parteFudida) {
                potencia *= 2;
            }

            potencia = Math.max(potencia / 2, 1);
            potencias.add(potencia);
            parteFudida -= potencia;
        }

        int meio = tamanho - 1;
        for (int i = potencias.size() - 1; i > 0; i--) {
            meio -= potencias.get(i);
            int ini = meio - potencias.get(i - 1) + 1;
            mergeOutPlace(v, ini, meio, tamanho - 1);
        }

        meio -= potencias.get(0);
        mergeOutPlace(v, 0, meio, tamanho - 1);
    }


    @SuppressWarnings("unused")
    private static void mergeOutPlace(int[] v, int ini, int meio, int fim) {
        int[] aux = new int[fim - ini + 1];
        for (int i = ini; i <= fim; i++) {
                aux[i - ini] = v[i];
        }

        int meioAux = meio - ini;
        int i = 0;
        int k = ini;
        int j = meioAux + 1;

        while (i <= meioAux && j < aux.length) { // CUIDADO! Aqui tem que ir até aux.length, não fim, tinha errado isso
            if (aux[i] < aux[j]) v[k] = aux[i++];
            else v[k] = aux[j++];

            k++;
        }

        while (i <= meioAux) {
            v[k++] = aux[i++];
        }
    }


    @SuppressWarnings("unused")
    private static void mergeInPlace(int[] v, int ini, int meio, int fim) { // lento pra caralho pqp
        int i = ini;
        int j = Math.min(meio + 1, v.length - 1);
        char lastSwap = 'i';

        while (i <= meio) {
            if (v[j] < v[i]) {
                swap(v, i, j);
                insereOrdenado(v, j, fim); // culpa dessa porra aqui
                lastSwap = 'j';
            } else if (v[j] == v[i]) {
                if (lastSwap == 'j') swap(v, i, j);
            } else {
                lastSwap = 'i';
            }

            i++;
        }
    }

    private static void insereOrdenado(int[] v, int ini, int fim) {
        for (int i = ini; i < fim; i++) {
            if (v[i] > v[i + 1]) swap(v, i, i + 1);
            else break;
        }
    }

    private static void swap(int[] v, int i, int j) {
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}
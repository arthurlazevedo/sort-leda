#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


void print_lista(int* lista, int tamanho)
{
    printf("[");
    for (int i = 0; i < tamanho - 1; i++) {
        printf("%d, ", lista[i]);
    }
    if (tamanho > 0) printf("%d", lista[tamanho - 1]);
    printf("]\n");
}


int min(int a, int b)
{
    return a > b ? b : a;
}


void swap(int* v, int i, int j)
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}


void insere_ordenado(int* v, int ini, int fim)
{
    for (int i = ini; i < fim; i++) {
        if (v[i] > v[i + 1]) swap(v, i, i + 1);
        else break;
    }
}


void merge_out_place(int* v, int ini, int meio, int fim) // TODO: iterativo e merge_in_place
{
    int tamanho_aux = fim - ini + 1;
    int aux[tamanho_aux];
    for (int i = ini; i <= fim; i++) {
        aux[i - ini] = v[i];
    }

    int meio_aux = meio - ini;
    int i = 0;
    int k = ini;
    int j = meio_aux + 1;

    while (i <= meio_aux && j < tamanho_aux) {
        if (aux[i] <= aux[j]) v[k] = aux[i++];
        else v[k] = aux[j++];

        k++;
    }

    while (i <= meio_aux) {
        v[k++] = aux[i++];
    }
}


void merge_in_place(int* v, int ini, int meio, int fim)
{
    int i = ini;
    int j = min(meio + 1, fim);
    char ultimo_swap = 'i';

    while (i <= meio) {
        if (v[j] < v[i]) {
            swap(v, i, j);
            insere_ordenado(v, j, fim);
            ultimo_swap = 'j';
        } else if (v[i] == v[j]) {
            if (ultimo_swap == 'j') {
                swap(v, i, j);
            }
        } else {
            ultimo_swap = 'i';
        }
        i++;
    }
}


void recursivo(int* v, int ini, int fim) {
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        recursivo(v, ini, meio);
        recursivo(v, meio + 1, fim);
        merge_in_place(v, ini, meio, fim);
    }
}


void iterativo(int* v, size_t tamanho)
{
    size_t faixa = 2;

    while (faixa <= tamanho) {
        for (size_t i = 0; i < tamanho; i += faixa) {
            int fim = min(i + faixa, tamanho) - 1;
            int meio = (i + fim) / 2;
            merge_out_place(v, i, meio, fim);

            if (i + faixa > tamanho) {
                merge_out_place(v, i - faixa, i - 1, tamanho - 1);
            }
        }

        faixa *= 2;
    }
}


bool ordenado(int* v, size_t tamanho)
{
    for (size_t i = 0; i < tamanho - 1; i++) {
        if (v[i] > v[i + 1]) return false;
    }
    return true;
}


int main(void)
{
    size_t tamanho = 30011;

    int poggers[tamanho];
    for (int i = 0; i < tamanho; i++) {
        poggers[i] = random();
    }

    // iterativo(poggers, tamanho);
    recursivo(poggers, 0, tamanho - 1);
    assert(ordenado(poggers, tamanho));

    return 0;
}
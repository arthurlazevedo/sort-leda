#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


int comparador(const void* a, const void* b)
{
    return *(int* )a - *(int* )b;
}


int mediana_tres(int* v, int ini, int fim)
{
    int meio = (ini + fim) / 2;
    int med[] = { v[ini], v[meio], v[fim] };

    qsort(med, 3, sizeof(int), comparador);

    if (med[1] == v[ini]) return ini;
    if (med[1] == v[meio]) return meio;
    return fim;
}


void swap(int* v, int i, int j)
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}


int lomuto(int* v, int ini, int fim)
{
    int med = mediana_tres(v, ini, fim);
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


int hoare(int* v, int ini, int fim)
{
    int med = mediana_tres(v, ini, fim);
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


void recursivo(int* v, int ini, int fim)
{
    if (ini < fim) {
        int idx_pivot = hoare(v, ini, fim);
        recursivo(v, ini, idx_pivot - 1);
        recursivo(v, idx_pivot + 1, fim);
    }
}


void iterativo(int* v, size_t tamanho)
{
    int pilha[tamanho]; // na teoria não cresce mais do que log2(tamanho)? não consegui usar a função por algum motivo então enfim
    int top = 0;

    pilha[top++] = 0;
    pilha[top++] = tamanho - 1;

    while (top > 0) {
        int fim = pilha[--top]; // tem que ser assim pra ele voltar pro anterior válido
        int ini = pilha[--top];

        int idx_pivot = hoare(v, ini, fim);
        if (ini < idx_pivot - 1) {
            pilha[top++] = ini;
            pilha[top++] = idx_pivot - 1;
        }

        if (idx_pivot + 1 < fim) {
            pilha[top++] = idx_pivot + 1;
            pilha[top++] = fim;
        }
    }
}


void print_lista(int* lista, size_t tamanho)
{
    printf("[");
    for (int i = 0; i < tamanho - 1; i++) {
        printf("%d, ", lista[i]);
    }
    if (tamanho > 0) printf("%d", lista[tamanho - 1]);
    printf("]\n");
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
    size_t tamanho = 321547;

    int poggers[tamanho];
    for (int i = 0; i < tamanho; i++) {
        poggers[i] = rand();
    }

    iterativo(poggers, tamanho);
    // recursivo(poggers, 0, tamanho - 1);
    assert(ordenado(poggers, tamanho));

    return 0;
}
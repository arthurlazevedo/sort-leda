#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>


typedef struct {
    int maior;
    int menor;
} Maior_Menor;


Maior_Menor* maior_menor(int* v, int tamanho)
{
    Maior_Menor* mm = malloc(sizeof(Maior_Menor));
    memset(mm, 0, sizeof(Maior_Menor));

    if (tamanho > 0) {
        mm->maior = v[0];
        mm->menor = v[0];

        for (int i = 0; i < tamanho; i++) {
            if (v[i] > mm->maior) mm->maior = v[i];
            else if (v[i] < mm->menor) mm->menor = v[i];
        }
    }

    return mm;
}


void copy(int* a, int* b, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        b[i] = a[i];
    }
}


int* out_place(int* a, int tamanho)
{
    Maior_Menor* mm = maior_menor(a, tamanho);
    int tamanho_c = mm->maior - mm->menor + 1;

    int c[tamanho_c];
    memset(c, 0, sizeof(c));

    int menor = mm->menor;

    for (int i = 0; i < tamanho; i++) {
        c[a[i] - menor]++;
    }

    for (int i = 1; i < tamanho_c; i++) {
        c[i] += c[i - 1];
    }

    int* b = malloc(tamanho * sizeof(int));
    for (int i = tamanho - 1; i >= 0; i--) {
        b[c[a[i] - menor] - 1] = a[i];
        c[a[i] - menor]--;
    }

    return b;
}


void in_place(int* a, int tamanho)
{
    Maior_Menor* mm = maior_menor(a, tamanho);
    int tamanho_c = mm->maior - mm->menor + 1;

    int c[tamanho_c];
    memset(c, 0, sizeof(c));

    int menor = mm->menor;

    for (int i = 0; i < tamanho; i++) {
        c[a[i] - menor]++;
    }

    for (int i = 1; i < tamanho_c; i++) {
        c[i] += c[i - 1];
    }

    int b[tamanho];
    copy(a, b, tamanho);

    for (int i = tamanho - 1; i >= 0; i--) {
        a[c[b[i] - menor] - 1] = b[i];
        c[b[i] - menor]--;
    }
}


bool ordenado(int* v, int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++) {
        if (v[i] > v[i + 1]) return false;
    }
    return true;
}


int main(void)
{
    size_t tamanho = 58034;

    int poggers[tamanho];
    for (int i = 0; i < tamanho; i++) {
        // inteiro entre -10000 e 100000
        poggers[i] = (int) (drand48() * (100000 + 10000) - 10000);
    }

    int* pepega = out_place(poggers, tamanho);
    in_place(poggers, tamanho);


    assert(ordenado(poggers, tamanho));
    assert(ordenado(pepega, tamanho));

    free(pepega);
    return 0;
}
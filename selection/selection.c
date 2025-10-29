#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_lista(int* lista, size_t tamanho)
{
  printf("[");
  for (size_t i = 0; i < tamanho - 1; i++) {
    printf("%d, ", lista[i]);
  }
  if (tamanho > 0) printf("%d", lista[tamanho - 1]);
  printf("]\n");
}

void swap(int* v, int i, int j)
{
  int aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

void in_place(int* lista, size_t tamanho)
{
  for (size_t i = 0; i < tamanho; ++i) {
    size_t menor_indice = i;
    for (size_t j = i; j < tamanho; ++j) {
      if (lista[j] < lista[menor_indice]) {
        menor_indice = j;
      }
    }
    swap(lista, i, menor_indice);
  }
}

int primeiro_idx_zerado(size_t* vistos, size_t tamanho)
{
  for (size_t i = 0; i < tamanho; i++) {
    if (vistos[i] == 0) return i;
  }

  return 0;
}

int* out_place(int* original, size_t tamanho)
{
  int* receptor = malloc(sizeof(int) * tamanho);
  size_t vistos[tamanho];
  memset(vistos, 0, sizeof(size_t) * tamanho); // anotação para o futuro: usar memset para um array de inteiros não dá certo se for para uma parte dele, teria que fazer um loop percorrendo mesmo

  for (size_t i = 0; i < tamanho; i++) {
    size_t i_menor = primeiro_idx_zerado(vistos, tamanho);
    for (size_t j = 0; j < tamanho; j++) {
      if (original[j] < original[i_menor] && vistos[j] != 1) {
        i_menor = j;
      }
    }
    receptor[i] = original[i_menor];
    vistos[i_menor] = 1;
  }

  return receptor;
}

int main(void)
{
  size_t tamanho = 19;

  printf("==== TESTE ALEATÓRIO ====\n");
  int poggers[] = {258, 52386, 9586, 96824, 9859865, 98398036, 839086, 721, 905879508, 67, 958, 670987, 21, 90870, 934, 3620, 6530, 94, 76};
  
  int* pog = out_place(poggers, tamanho);
  print_lista(pog, tamanho);

  in_place(poggers, tamanho);
  print_lista(poggers, tamanho);

  printf("\n\n==== TESTE ORDEM REVERSA ====\n");
  int poggers2[] = {905879508, 98398036, 9859865, 839086, 670987, 96824, 90870, 52386, 9586, 6530, 3620, 958, 934, 721, 258, 94, 76, 67, 21};
  
  int* pog2 = out_place(poggers2, tamanho);
  print_lista(pog2, tamanho);

  in_place(poggers2, tamanho);
  print_lista(poggers2, tamanho);
  
  free(pog);
  free(pog2);

  return 0;
}
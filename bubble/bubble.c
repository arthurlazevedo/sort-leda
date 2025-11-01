#include <stdio.h>
#include <stdbool.h>

void swap(int* v, int i, int j) {
  int aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

void print_lista(int* lista, int tamanho)
{
  printf("[");
  for (int i = 0; i < tamanho - 1; i++) {
    printf("%d, ", lista[i]);
  }
  if (tamanho > 0) printf("%d", lista[tamanho - 1]);
  printf("]\n");
}

void in_place(int* v, size_t tamanho)
{
  bool ordenado = false;
  while (!ordenado) {
    ordenado = true;
    for (size_t i = 0; i < tamanho - 1; i++) {
      if (v[i] > v[i + 1]) {
        swap(v, i, i + 1);
        ordenado = false;
      }
    }
  }
}

int main(void)
{
  size_t tamanho = 19;

  printf("==== TESTE ALEATÓRIO ====\n");
  int poggers[] = {258, 52386, 9586, 96824, 9859865, 98398036, 839086, 721, 905879508, 67, 958, 670987, 21, 90870, 934, 3620, 6530, 94, 76};
  
  in_place(poggers, tamanho);
  print_lista(poggers, tamanho);

  printf("\n\n==== TESTE ORDEM REVERSA ====\n");
  int poggers2[] = {905879508, 98398036, 9859865, 839086, 670987, 96824, 90870, 52386, 9586, 6530, 3620, 958, 934, 721, 258, 94, 76, 67, 21};
  
  in_place(poggers2, tamanho);
  print_lista(poggers2, tamanho);

  return 0;
}
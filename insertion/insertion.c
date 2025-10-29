#include <stdio.h>
#include <stdlib.h>

void swap(int* v, int i, int j)
{
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

void in_place(int* lista, int tamanho)
{
  for (int i = 0; i < tamanho; i++) {
    int j = i;
    while (j > 0 && lista[j] < lista[j - 1]) {
      swap(lista, j, j - 1);
      j--;
    }
  }
}

int* out_place(int* original, int tamanho)
{
  int* ordenado = malloc(sizeof(int) * tamanho); // calloc?

  for (int i = 0; i < tamanho; i++) {
    ordenado[i] = original[i];
    int j = i;
    while (j > 0 && ordenado[j] < ordenado[j - 1]) {
      swap(ordenado, j, j - 1); // anotação: acho que isso aqui só dá certo fazendo com indexação, 
      // se for por aritmética de ponteiro provavelmente daria errado já que iria com um offset errado pra função 
      j--;
    }
  }

  return ordenado;
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

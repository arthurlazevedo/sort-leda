from random import randint
from itertools import repeat

def in_place(lista):
    for i in range(len(lista)):
        menor_ind = i
        for j in range(i + 1, len(lista)):
            if lista[j] < lista[menor_ind]:
                menor_ind = j
        lista[menor_ind], lista[i] = lista[i], lista[menor_ind]


def out_place(lista):
    ordenado = []
    copia = lista.copy()

    while copia:
        menor_ind = 0
        for i in range(len(copia)):
            if copia[i] < copia[menor_ind]:
                menor_ind = i
        ordenado.append(copia.pop(menor_ind))

    return ordenado


if __name__ == '__main__':
    lista1 = [randint(0, 10000) for _ in repeat(None, 1000)]
    print(out_place(lista1))

    lista2 = lista1.copy()
    in_place(lista2)
    print(lista2)

    lista3 = lista1.copy()
    lista3.sort()
    assert lista2 == lista3
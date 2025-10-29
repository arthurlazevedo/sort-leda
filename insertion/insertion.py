import random
from itertools import repeat

def in_place(lista):
    for i in range(1, len(lista)):
        j = i
        while j > 0 and lista[j] < lista[j - 1]:
            lista[j], lista[j - 1] = lista[j - 1], lista[j]
            j -= 1


def out_place(lista):
    ordenado = []
    ordenado.append(lista[0])
    for i in range(1, len(lista)):
        ordenado.append(lista[i])
        j = i
        while j > 0 and ordenado[j] < ordenado[j - 1]:
            ordenado[j], ordenado[j - 1] = ordenado[j - 1], ordenado[j]
            j -= 1
    return ordenado

if __name__ == '__main__':
    lista1 = [random.randrange(100000) for _ in repeat(None, 100)] + [-100000]

    lista2 = out_place(lista1)
    print(lista2)

    in_place(lista1)
    print(lista1)

    assert lista1 == list(sorted(lista1)) == lista2
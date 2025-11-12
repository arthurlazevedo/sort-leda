from random import randint
from itertools import repeat
from collections import deque


def swap(v, i, j):
    v[i], v[j] = v[j], v[i]


def mediana_tres(v, ini, fim):
    meio = (ini + fim) // 2

    med = [v[ini], v[meio], v[fim]]
    med.sort()

    if (med[1] == v[ini]):
        return ini
    if (med[1] == v[meio]):
        return meio
    return fim


def lomuto(v, ini, fim):
    med = mediana_tres(v, ini, fim)
    swap(v, ini, med)

    pivot = v[ini]
    i = ini

    for j in range(ini + 1, fim + 1): # tinha errado isso, tem que ser de ini + 1, não ini
        if v[j] <= pivot:
            i += 1
            swap(v, i, j)
    
    swap(v, i, ini)
    return i


def hoare(v, ini, fim):
    med = mediana_tres(v, ini, fim)
    swap(v, ini, med)

    pivot = v[ini]
    i = ini + 1
    j = fim

    while i <= j:
        while i <= j and v[i] <= pivot:
            i += 1
        while i <= j and v[j] > pivot:
            j -= 1
        
        if i < j:
            swap(v, i, j)

    swap(v, j, ini)
    return j


def iterativo(v): # performance ta peso aqui mas funcionou, usando deque melhorou eu acho?
    fila = deque() # isso não é pilha pai

    fila.append(0)
    fila.append(len(v) - 1)

    while len(fila) > 0:
        i = fila.popleft()
        f = fila.popleft()

        i_pivot = hoare(v, i, f)

        if i < i_pivot - 1:
            fila.append(i)
            fila.append(i_pivot - 1)
        if i_pivot + 1 < f:
            fila.append(i_pivot + 1)
            fila.append(f)


def recursivo(v, ini, fim):
    if ini < fim:
        i_pivot = hoare(v, ini, fim)
        recursivo(v, ini, i_pivot - 1)
        recursivo(v, i_pivot + 1, fim)


def ordenado(v):
    for i in range(len(v) - 1):
        if v[i] > v[i+1]:
            return False
    return True


if __name__ == '__main__':
    a = [randint(0, 100000) for _ in repeat(None, 1001001)]
    # recursivo(a, 0, len(a) - 1)
    iterativo(a)
    assert ordenado(a)
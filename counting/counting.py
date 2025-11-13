from random import randrange
from itertools import repeat

def maior_menor(v):
    if len(v) == 0:
        return 0, 0

    maior = v[0]
    menor = v[0]

    for e in v:
        if e > maior:
            maior = e
        if e < menor:
            menor = e

    return maior, menor


def out_place(a):
    maior, menor = maior_menor(a)
    c = [0] * (maior - menor + 1)

    for i in range(len(a)):
        c[a[i] - menor] += 1

    for i in range(1, len(c)):
        c[i] += c[i - 1]

    b = [0] * len(a)
    for i in range(len(a) - 1, -1, -1):
        b[c[a[i] - menor] - 1] = a[i]
        c[a[i] - menor] -= 1

    return b


def in_place(a): # in-place no sentido que altera os elementos no próprio array, é impossível fazer um realmente in-place, possivelmente daria pra não usar um array auxiliar sem ser o de contagem, enfim
    maior, menor = maior_menor(a)
    c = [0] * (maior - menor + 1)

    for i in range(len(a)):
        c[a[i] - menor] += 1

    for i in range(1, len(c)):
        c[i] += c[i - 1]

    b = a.copy()

    for i in range(len(b) - 1, -1, -1):
        a[c[b[i] - menor] - 1] = b[i]
        c[b[i] - menor] -= 1

if __name__ == '__main__':
    lista1 = [randrange(100000) for _ in repeat(None, 100)] + [-1000]

    lista2 = out_place(lista1)
    print(lista2)

    in_place(lista1)
    print(lista1)

    assert lista1 == list(sorted(lista1)) == lista2
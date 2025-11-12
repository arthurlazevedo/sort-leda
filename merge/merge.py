from random import randint
from itertools import repeat


def insere_ordenado(v, ini, fim):
    for i in range(ini, fim):
        if v[i] > v[i + 1]:
            v[i], v[i + 1] = v[i + 1], v[i]
        else:
            break


def merge_out_place(v, ini, meio, fim):
    aux = []
    for i in range(ini, fim + 1):
        aux.append(v[i])

    # meio_aux = (len(aux) - 1) // 2 => IMPORTANTE: lembrar que tem que fazer assim, caso não seja passado o "meio"
    meio_aux = meio - ini

    i = 0
    k = ini
    j = meio_aux + 1

    while i <= meio_aux and j < len(aux):
        if aux[i] < aux[j]:
            v[k] = aux[i]
            i += 1
        else:
            v[k] = aux[j]
            j += 1
        k += 1

    while i <= meio_aux:
        v[k] = aux[i]
        i += 1
        k += 1


def merge_in_place(v, ini, meio, fim): # lento pra porra pqp
    i = ini
    j = min(meio + 1, len(v) - 1)
    last_swap = 'i'

    while i <= meio:
        if v[j] < v[i]:
            v[j], v[i] = v[i], v[j]
            insere_ordenado(v, j, fim)
            last_swap = 'j'
        elif v[j] == v[i]:
            if last_swap == 'j':
                v[j], v[i] = v[i], v[j]
        else:
            last_swap = 'i'

        i += 1


def recursivo(v, ini, fim):
    if ini < fim:
        meio = (ini + fim) // 2

        recursivo(v, ini, meio)
        recursivo(v, meio + 1, fim)
        merge_out_place(v, ini, meio, fim)


def iterativo(v):
    faixa = 2
    tamanho = len(v)

    while faixa <= tamanho:
        for i in range(0, tamanho, faixa):

            fim = min(i + faixa, tamanho) - 1
            meio = (i + fim) // 2
            merge_out_place(v, i, meio, fim)

        faixa *= 2

    # é aqui que mora o problema. Algumas faixas ultrapassaram o tamanho e então ele está ordenado até (int)faixa/2
    # depois disso tem que ver quais foram as últimas potências que ele ultrapassou o tamanho e ir ordenando daí, provavelmente tem uma maneira melhor de fazer isso, mas foi essa que eu pensei.
    # PS: no código em c, eu achei uma maneira de fazer isso melhor
    junta_pedacos_menor_maior(v, faixa // 2)


def junta_pedacos_maior_menor(v, faixa): # na minha cabeça utiliza mais memória, melhor fazer do outro jeito
    potencias = []
    parte_fudida = len(v) - faixa # parte que possui pedaços ordenados, mas não por completo

    while parte_fudida > 0: # coleto potências de 2 menores, que eu sei que são as partes que estão ordenadas
        potencia = 1
        while potencia <= parte_fudida:
            potencia *= 2

        potencia = potencia // 2 or 1 # tem que voltar 1 aqui
        potencias.append(potencia)
        parte_fudida -= potencia

    meio = faixa - 1
    for i in range(len(potencias)):
        merge_out_place(v, 0, meio, meio + potencias[i])
        meio += potencias[i]


def junta_pedacos_menor_maior(v, faixa): # caminho contrário, que não precisa fazer uma cópia tão grande do array
    potencias = []
    tamanho = len(v)
    parte_fudida = tamanho - faixa # parte que tem apenas alguns pedaços ordenados

    while parte_fudida > 0:
        potencia_atual = 1
        while potencia_atual <= parte_fudida:
            potencia_atual *= 2

        potencia_atual = potencia_atual // 2 or 1
        potencias.append(potencia_atual)
        parte_fudida -= potencia_atual

    if len(potencias) == 0:
        return

    meio = tamanho - 1
    for i in range(len(potencias) - 1, 0, -1):
        meio -= potencias[i]
        ini = meio - potencias[i - 1] + 1
        merge_out_place(v, ini, meio, tamanho - 1)

    meio -= potencias[0]
    merge_out_place(v, 0, meio, tamanho - 1)


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
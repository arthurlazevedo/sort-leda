def in_place(lista):
    while True:
        trocou = False
        for i in range(len(lista) - 1):
            if lista[i] > lista[i + 1]:
                lista[i], lista[i + 1] = lista[i + 1], lista[i]
                trocou = True
        if not trocou:
            break

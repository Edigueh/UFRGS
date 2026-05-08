"""
Brief: Soma de Subconjuntos
Author: André Schaidhauer Luckmann
Matricula: 00601117
Date: 07/05/2026
"""
import sys

def menor_soma_nao_formavel(v):
    """
    Ordena o vetor e mantém 'soma' = maior valor formável contiguamente a partir de 1.

      Todo valor em [1, soma] é formável por algum subconjunto dos
      elementos já processados. Quando um elemento x quebra a condição (x > soma + 1), nenhum
      subconjunto dos elementos restantes (todos >= x) pode preencher o gap, pois qualquer
      subconjunto que os inclua soma pelo menos x > soma + 1. Logo, soma + 1 é globalmente
      não formável e, por ser o menor inteiro fora do alcance, é a resposta.
    """
    v.sort()
    soma = 0
    for x in v:
        if x > soma + 1: # gap encontrado: soma + 1 não é formável
            break
        soma += x # expande o alcance de somas formáveis para [1, soma + x]
    return soma + 1


def main():
    dados = list(map(int, sys.stdin.buffer.read().split()))

    t = dados[0]
    i = 1
    respostas = []

    for _ in range(t):
        n = dados[i]
        i += 1

        v = dados[i:i+n]
        i += n

        respostas.append(str(menor_soma_nao_formavel(v)))

    print("\n".join(respostas))


if __name__ == "__main__":
    main()

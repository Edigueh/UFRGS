import sys

def menor_soma_nao_formavel(v):
    # [1], [2], [5], [1, 2], [1, 5], [2, 5], [1, 2, 5] = 1,1,1,1,2,2,2,2,5,5,5,5 -> 
    # [1] = 1 -> 2: soma + 1
    # [2] = 2 -> 1: x > soma + 1
    soma = 0
    v.sort()
    for i in v:
        if i > soma + 1:
            break
        soma += i
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

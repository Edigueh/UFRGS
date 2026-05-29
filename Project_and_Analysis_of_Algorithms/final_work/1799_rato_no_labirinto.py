"""
    Autor: André Schaidhauer Luckmann
    Data: 28/05/2026
    Resumo: Beecrowd 1799 - O Rato no Labirinto
    Descrição:
        Em 1942, um estudo feito por Robert Tryon concluiu que os traços genéticos frequentemente podem contribuir para o comportamento,
        independente do meio ambiente. Para fazer isso Tryon criou uma experiência que testou a proficiência de gerações sucessivas de
        ratos em completar um labirinto, separando os que fizeram os menores números de erros em "brilhantes", e aqueles com mais erros
        em "medíocres". Dando continuidade a este processo durante sete gerações ele criou duas raças distintas de ratos: "brilhantes"
        e "medíocres".

        O ratinho IBO é descendente da linhagem de ratos "brilhante", sendo o melhor de todos no desempenho deste experimento. Ele consegue
        entrar, pegar o queijo e sair de qualquer labirinto sem se perder, e sempre faz o caminho mais curto possível.

        Sua tarefa neste problema é, dado o desenho do Labirinto e a posição do queijo, determinar por quantos pontos estrategicamente marcados
        por letras do alfabeto (ou palavras contendo somente letras) IBO deve passar para pegar o queijo (indicado pelo caractere '*') e sair,
        sempre partindo do ponto Entrada e terminando em Saida (sem acento). No exemplo abaixo, a sequência de IBO à partir da Entrada seria:
        A, F, J, *, I, M, K e Saida, o que resultaria em 8, que é a quantidade mínima de pontos pelos quais IBO deve passar para cumprir a sua tarefa.
        Se IBO tiver que passar por um ponto duas vezes (uma indo para o queijo e outra indo para a saída) isso conta como dois pontos visitados.

    Entrada:
        A primeira linha de entrada contém dois inteiros Pontos (4 ≤ Pontos ≤ 4000) e Ligacoes (4 ≤ Ligacoes ≤ 5000) representando respectivamente o
        número de pontos estrategicamente marcados no labirinto e quantidade de ligações existentes entre estes pontos. Seguem as linhas que indicam
        cada uma das ligações entre estes pontos. As ligação entre dois pontos indica que qualquer um dos dois pode ser a origem.

    Saída:
        Imprima um valor inteiro identificando a quantidade mínima de pontos do labirinto pelos quais IBO deve passar para cumprir a sua tarefa.
"""
from collections import deque
from typing import Deque, Dict, Hashable, List

Node = Hashable
Graph = Dict[Node, List[Node]]


def build_graph_from_input() -> Graph:
    """
        Lê as entradas, devolvendo somente os dados necessários (o grafo).
    """
    # Leitura da primeira linha.
    _, edges = map(int, input().split())
    graph: Graph = {}
    # Custo O(|E|), sendo |E| o número de arestas do grafo.
    for _ in range(edges):
        node, neighbour = input().split()

        # Preenche o grafo.
        graph.setdefault(node, []).append(neighbour)
        graph.setdefault(neighbour, []).append(node)

    return graph


def bfs_distance(graph: Graph, start_node: Node, target_node: Node) -> int:
    """
        Retorna a menor distância do nodo inicial para o nodo alvo no grafo.
        Utiliza do algoritmo de BFS iterativo no grafo.
        Se o nodo alvo não está no grafo, retorna -1.
    """
    # Inicializa dicionário de nodos visitados. Indica se um nodo (chave),
    # já foi visitado ou não por meio de um valor booleano.
    visited: Dict[Node, bool] = dict.fromkeys(graph, False)

    # Nodo inicial já é marcado como visitado.
    visited[start_node] = True

    # Inicializa a fila a ser usada no BFS com o nodo inicial.
    queue: Deque[Node] = deque([start_node])

    # Inicializa dicionário de distâncias dos nodos, considerando que as arestas
    # não são valoradas, ou seja todas terão peso 1.
    # Distância do nodo inicial até ele mesmo é 0.
    distances: Dict[Node, int] = visited.copy()
    distances[start_node] = 0

    # As inicializações acima tem custo O(|V|), sendo |V| o número de nodos do grafo.

    # Custo O(2|E|), sendo |E| o número de arestas do grafo.
    while len(queue) > 0: # Enquanto houver nodos na fila.
        cur_node: Node = queue.popleft() # Remove um nodo da fila.
        for neighbour in graph[cur_node]: # Para cada vizinho desse nodo.
            if not visited[neighbour]: # Se o vizinho desse nodo não foi visitado.
                if neighbour == target_node:
                    # Se vizinho desse nodo for o nodo alvo, retorna a distância
                    # até o nodo atual + 1.
                    return distances[cur_node] + 1

                queue.append(neighbour) # Adiciona vizinho na fila.
                visited[neighbour] = True # Marca vizinho como visitado.
                distances[neighbour] = distances[cur_node] + 1 # Computa distância até vizinho.

    return -1


# Objetivo: Calcular o comprimento do menor caminho que comece em Entrada e termine em saída e que passe por '*'.
# Passar pelo mesmo ponto duas vezes uma, indo e outra voltando, conta como dois pontos visitados.
# Seja V: conjunto de vértices do grafo, |V| é o número de vértices do grafo.
# Seja E: conjunto de arestas do grafo, |E| é o número de arestas do grafo.
# Custo de tempo: O(|V| + |E|).
def main() -> None:
    # Constrói o grafo a partir da entrada.
    # O(|E|)
    graph: Graph = build_graph_from_input()

    CHEESE: Node = "*"

    # Resposta: Soma das menores distâncias entre "Entrada"->"*" e "*"->"Saida" no grafo.
    # O(2 * (|V| + |E|)) => O(|V| + |E|).
    print(
        # O(|V| + |E|).
        bfs_distance(graph, start_node="Entrada", target_node=CHEESE)
        +
        # O(|V| + |E|).
        bfs_distance(graph, start_node=CHEESE, target_node="Saida")
    )


if __name__ == "__main__":
    main()

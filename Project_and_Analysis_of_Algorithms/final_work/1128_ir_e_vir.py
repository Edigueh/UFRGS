"""
    Autor: André Schaidhauer Luckmann
    Data: 28/05/2026
    Resumo: Beecrowd 1128 - Ir e Vir
    Descrição:
        Numa certa cidade há N intersecções ligadas por ruas de mão única e ruas com mão dupla de direcão. É uma cidade moderna,
        de forma que muitas ruas atravessam túneis ou têm viadutos. Evidentemente é necessário que se possa viajar entre quaisquer
        duas intersecções, isto é, dadas duas intersecções V e W, deve ser possível viajar de V para W e de W para V.

        Sua tarefa é escrever um programa que leia a descrição do sistema de tráfego de uma cidade e determine se o requisito de
        conexidade é satisfeito ou não.

    Entrada:
        A entrada contém vários casos de teste. A primeira linha de um caso de teste contém dois números inteiros N e M, separados
        por um espaço em branco, indicando respectivamente o número de intersecções (2 ≤ N ≤ 2000) e o número de ruas
        (2 ≤ M ≤ N(N−1)/2). O caso de teste tem ainda mais M linhas, que contêm, cada uma, uma descrição de cada uma das M ruas.
        A descrição consiste de três inteiros V, W e P, separados por um espaço em branco, onde V e W são identificadores distintos
        de intersecções (1 ≤ V, W ≤ N , V ≠ W ) e P pode ser 1 ou 2; se P = 1 então a rua é de mão única, e vai de V para W;
        se P = 2 então a rua é de mão dupla, liga V e W. Não existe duas ruas ligando as mesmas intersecções.

        O ultimo caso de teste é seguido por uma linha que contém apenas dois números zero separados por um espaço em branco.

    Saida:
        Para cada caso de teste seu programa deve imprimir uma linha contendo um inteiro G, onde G é igual a 1 se o requisito de
        conexidade está satisfeito, ou G é igual a 0, caso contrário.

    Notas: para todos os comentários do código, considere a seguinte notação:
        - n: número de vértices do grafo.
        - m: número de arestas do grafo.
"""
from typing import Dict, Hashable, List

Node = Hashable
Graph = Dict[Node, List[Node]]


# O(m).
def build_graph_from_input(m: int) -> Graph:
    """
        Dado um número 'm' de ruas(linhas de entrada), constrói o grafo a partir dos dados da entrada.
        Respeita a regra de vias de mão única ou mão dupla baseado no valor de 'p'.
    """
    graph: Graph = {}
    for _ in range(m):
        v, w, p = map(int, input().split())
        graph.setdefault(v, []).append(w)
        graph.setdefault(w, [])

        # Se a rua é de mão dupla liga w a v também.
        if p == 2:
            graph[w].append(v)

    return graph


# Custo: O(n + m).
def reverse_graph(graph: Graph) -> Graph:
    """Dado um dígrafo, retorna um dígrafo com todas as direções das arestas invertidas."""
    rev_g: Graph = {node: [] for node in graph.keys()}

    # O(n + m).
    for node, neighbours in graph.items():
        for neighbour in neighbours:
            rev_g.setdefault(neighbour, []).append(node)
    return rev_g


# O(n + m).
def dfs_toposort(graph: Graph) -> list[Node]:
    """Ordenamento topológico por DFS."""
    # O(n).
    visited: Dict[Node, bool] = dict.fromkeys(graph, False)
    order: list[Node] = []

    def dfs_rec(graph: Graph, start_node: Node, visited: Dict[Node, bool], order: list[Node]):
        visited[start_node] = True
        for neighbour in graph[start_node]:
            if not visited[neighbour]:
                dfs_rec(graph, neighbour, visited, order)
        order.append(start_node)

    # O(n + m).
    for node in graph.keys():
        if not visited[node]:
            dfs_rec(graph, node, visited, order)

    order.reverse()
    return order

# O(n + m).
def is_connected(graph: Graph) -> int:
    """
        Usa o Algoritmo de Kosaraju-Shamir para encontrar componentes fortemente conexos em um dígrafo.
        Requisito de conexidade: É possível viajar de quaisquer duas intersecções V e W em ambos sentidos V<->W no dígrafo.
        Retorna 1 se o requisito de conexidade é satisfeito no grafo.
        Retorna 0 se o requisito de conexidade não é satisfeito no grafo.
    """
    # O(n + m).
    rev_g: Graph = reverse_graph(graph)

    # O(n + m).
    order: list[Node] = dfs_toposort(rev_g)

    # O(n).
    visited: Dict[Node, bool] = dict.fromkeys(graph, False)
    connected_components: int = 0

    def dfs(graph: Graph, start_node: Node, visited: Dict[Node, bool]):
        visited[start_node] = True
        for neighbour in graph[start_node]:
            if not visited[neighbour]:
                dfs(graph=graph, start_node=neighbour, visited=visited)
    
    # O(n + m).
    for node in order:
        if not visited[node]:
            dfs(graph=graph, start_node=node, visited=visited)
            if connected_components < 1: 
                connected_components += 1
            else:
                return 0

    return 1

# Objetivo: Determinar se o dígrafo contém somente um componente fortemente conexo que contém todos os nodos do grafo.
# Componente fortemente conexo é um subconjunto do dígrafo em que todos os nodos conseguem chegar a todos os nodos.
def main() -> None:
    # Seja t o número de casos de teste, o custo do código é O(t * (n + m)).
    while True:
        n, m = map(int, input().split())
        
        if n == m == 0:
            break
        # O(n + m).
        print(is_connected(build_graph_from_input(m)))
    return None


if __name__ == "__main__":
    main()

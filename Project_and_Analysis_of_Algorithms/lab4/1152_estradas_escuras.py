"""
	Brief: Beecrowd 1152 - Estradas Escuras
    Desc: Dado um grafo, retorne a diferença entre o peso total da soma das arestas entre
    o grafo completo e a árvore geradora miníma deste grafo.
	Author: André Schaidhauer Luckmann
    Matricula: 00601117
"""

from typing import List, Dict, Tuple

class UnionFind:
    """Estrutura de dados Union-Find (Disjoint Set Union) para auxiliar o algoritmo de Kruskal."""

    def __init__(self, elements: List[int]):
        """Inicializa a estrutura Union-Find com os elementos fornecidos.
            O(n), onde n é o número de elementos.
        """
        self.parent = {v: v for v in elements}  # Cada elemento é inicialmente seu próprio pai (representante do conjunto)
        self.rank = {v: 0 for v in elements}    # Rank para otimizar a união dos conjuntos

    def find(self, v):
        """Encontra o representante do conjunto ao qual o elemento v pertence, aplicando compressão de caminho.
            Amortizado O(α(n)), onde α é a função inversa de Ackermann, que cresce muito lentamente e é praticamente constante para todos os valores de n encontrados na prática.
        """
        if self.parent[v] != v:
            self.parent[v] = self.find(self.parent[v])  # Path compression
        return self.parent[v]
    
    def union(self, u, v):
        """Une os conjuntos aos quais os elementos u e v pertencem, utilizando a técnica de união por rank.
            Amortizado O(α(n)), onde α é a função inversa de Ackermann, que cresce muito lentamente e é praticamente constante para todos os valores de n encontrados na prática.
        """
        root_u = self.find(u)
        root_v = self.find(v)
        if root_u != root_v:
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1

def kruskal(edges: List[Tuple[int, int, int]], nodes: List[int]) -> int:
    """Algoritmo de Kruskal para encontrar a árvore geradora mínima de um grafo valorado.

    Complexidade: O(|E| log |E|) devido à ordenação das arestas, onde E é o conjunto de arestas no grafo.
    
    Args:
        edges: lista de tuplas que indicam uma aresta valorada que liga dois nodos.
        nodes: lista de nodos pertencentes ao grafo
    
    Returns:
        O custo total da árvore geradora mínima.
    """
    # Ordenar as arestas pelo peso
    edges.sort(key=lambda x: x[2])
    
    disjoint_set = UnionFind(list(nodes))
    mst_edges = []  # Lista para armazenar as arestas da árvore geradora mínima
    custo = 0  # Variável para acumular o custo total da árvore geradora mínima
    num_edges = 0  # Contador para o número de arestas adicionadas à árvore geradora mínima

    for u, v, weight in edges:
        if disjoint_set.find(u) != disjoint_set.find(v):  # Verificar se os nodos u e v estão em conjuntos disjuntos
            disjoint_set.union(u, v)
            mst_edges.append((u, v, weight))

            custo += weight
            num_edges += 1

            if num_edges == len(nodes) - 1:  # A árvore geradora mínima terá exatamente |V| - 1 arestas
                break

    return custo

if __name__ == "__main__":
    while True:
        m, n = map(int, input().split())

        if m == 0 and n == 0:
            break

        answer = 0
        total_cost = 0
        edges: List[Tuple[int, int, int]] = []
        nodes: List[int] = {x for x in range(m)}

        for _ in range(n):
            x, y, z = map(int, input().split())
            edges.append((x, y, z))
            total_cost += z

        print(total_cost - kruskal(edges, nodes))

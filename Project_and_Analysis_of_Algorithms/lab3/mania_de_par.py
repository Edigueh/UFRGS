"""
Brief: Mania de Par
Author: André Schaidhauer Luckmann
Matricula: 00601117
Date: 07/05/2026
"""
import heapq # para usar heap em Python

# Dica: Você precisa modificar o algoritmo de dijkstra abaixo para resolver o problema!

def dijkstra(graph, source):
    """
    Dijkstra O((|E| + |V|) log |V|) com heap binário.

    Parâmetros:
      graph: dicionário (lista de adjacência) representando grafo valorado com arestas não-negativas.
      source: nó de origem.

    Retorna:
      dist: dicionário com a menor distância da origem para cada nó.
            Para nós inalcançáveis, distância = float('inf').
      parent: dicionário com o predecessor imediato no caminho mínimo
              (None para a origem e para nós inalcançáveis).
    """

    dist = {v : [float('inf'), float('inf')] for v in graph.keys()}
    dist[source][0] = 0      # 0 = par
                             # 1 = ímpar
    fila = [(0, source, 0)]  # (dist, node, parity)
    parent = {v : None for v in graph.keys()}

    while fila:  # enquanto fila não for vazia
        du, u, parity = heapq.heappop(fila)  # extrai nodo com menor distância na fila, assim como a sua paridade (levada em conta na heapq)

        if du > dist[u][parity]: # se a distancia retirada é maior que a distancia atual para a mesma paridade, pula
            continue

        for v, wv in graph[u]:    # para cada vizinho v de u
            new_parity = 1 - parity # troca a paridade desse caminho
            novo_dv = du + wv     # distância até u mais peso da aresta u-v
            if novo_dv < dist[v][new_parity]: # se distância menor que a atual
                dist[v][new_parity] = novo_dv
                parent[v] = u
                heapq.heappush(fila, (novo_dv, v, new_parity)) # insere a nova distancia minima para o nodo v com a nova paridade

    return dist, parent

# Leitura da entrada:
c, v = (int(x) for x in input().split())
graph = {i : [] for i in range(1, c + 1)}
for _ in range(v):
    c1, c2, g = (int(x) for x in input().split())
    
    graph[c1].append((c2,g))
    graph[c2].append((c1,g))

dist, parent = dijkstra(graph=graph, source=1)

# dist[c][0] é a distância par(0) até o nodo c.
ans = int(dist[c][0]) if dist[c][0] != float('inf') else -1

print(ans)

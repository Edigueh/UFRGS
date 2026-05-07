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
    dist[source][0] = 0      # 0 = pair
                             # 1 = odd
    fila = [(0, source, 0)]  # (dist, node, parity)
    parent = {v : None for v in graph.keys()}

    while fila:  # enquanto fila não for vazia
        du, u, parity = heapq.heappop(fila)  # extrai nodo com menor distância na fila

        if du > dist[u][parity]:
            continue

        for v, wv in graph[u]:    # para cada vizinho v de u
            new_parity = 1 - parity
            novo_dv = du + wv     # distância até u mais peso da aresta u-v
            if novo_dv < dist[v][new_parity]: # se distância menor que a atual
                dist[v][new_parity] = novo_dv
                parent[v] = u
                heapq.heappush(fila, (novo_dv, v, new_parity))

    return dist, parent

# Leitura da entrada:
c, v = (int(x) for x in input().split())
graph = {i : [] for i in range(1, c + 1)}
for _ in range(v):
    c1, c2, g = (int(x) for x in input().split())
    
    graph[c1].append((c2,g))
    graph[c2].append((c1,g))

dist, parent = dijkstra(graph=graph, source=1)

ans = int(dist[c][0]) if dist[c][0] != float('inf') else -1

print(ans)

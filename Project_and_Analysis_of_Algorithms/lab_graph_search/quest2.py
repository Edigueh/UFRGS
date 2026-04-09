"""
Brief: Connected Components
Author: André Schaidhauer Luckmann
Date: 09/05/2026
"""

from collections import deque

def init_visited(graph: list[str, list[str]]) -> dict[str, bool]:
    """Maps all nodes as unvisited."""
    return {node: False for node in graph.keys()}

def bfs(graph: list[str, list[str]], start_node: str, visited: dict[str, bool]) -> list[str]:
    """Iterative Breadth First Search starting from the start node using a queue.
    Returns the list of nodes in this connected component."""
    queue = deque([start_node])
    visited[start_node] = True
    component = [start_node]

    while len(queue) > 0:
        cur_node: str = queue.popleft()
        for neighbour in graph[cur_node]:
            if not visited[neighbour]:
                queue.append(neighbour)
                visited[neighbour] = True
                component.append(neighbour)
    return component


N = int(input())

alpha = "abcdefghijklmnopqrstuvwxyz"

for i in range(1, N + 1):
    v, e = (int(x) for x in input().split())
    graph = {i : [] for i in alpha[:v]}  # grafo contendo n nodos (a partir da letra "a")
    for _ in range(e):
        a, b = (x for x in input().split())

        graph[a].append(b)
        graph[b].append(a)

    visited = init_visited(graph)
    components = []
    for node in graph.keys():
        if not visited[node]:
            component = bfs(graph, node, visited)
            components.append(sorted(component))

    print(f"Case #{i}:")
    for comp in components:
        for a in comp:
            print(f"{a},", end="")
        print()
    print(f"{len(components)} connected components")
    print()

"""
Brief: Quest1: Separate Rooms
Author: André Schaidhauer Luckmann
Date: 09/05/2026
"""

from collections import deque

def is_bipartite(g: dict[int, list[int]]):
    visited: dict[int, bool] = {node: False for node in g.keys()}
    color: dict[int, bool] = visited.copy()
    # Choose a node for each component.
    for node in g.keys():
        if not(visited[node]):
            # Starts the search queue in the choosen node.
            queue = deque([node])
            # Attribute the color 1 to the node.
            color[node] = True
            visited[node] = True
            while len(queue) > 0:
                curNode: int = queue.popleft()
                for neighbour in graph[curNode]:
                    if visited[neighbour] and color[curNode] == color[neighbour]:
                        # Found an odd cycle.
                        return False
                    elif not visited[neighbour]:
                        queue.append(neighbour)
                        visited[neighbour] = True
                        # Atrributes inverse color.
                        color[neighbour] = not(color[curNode])

    # There is no odd cycle.
    return True


n = int(input())
while n != 0:
    graph = {i : [] for i in range(1, n+1)}
    for _ in range(n):
        id = int(input())
        neighbours = [int(x) for x in input().split()]
        graph[id] = neighbours
        for node in neighbours:
            graph[node].append(id)


    if is_bipartite(graph):
        print("SIM")
    else:
        print("NAO")

    n = int(input())

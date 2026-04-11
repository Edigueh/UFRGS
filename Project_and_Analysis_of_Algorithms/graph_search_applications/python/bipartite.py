from graphs import G2
from collections import deque

def bipartite(graph: dict[str, list[str]]) -> dict[str, bool] | bool:
    """Bipartite test using BFS."""
    visited: dict[str, bool] = {node: False for node in graph.keys()}
    color: dict[str, bool] = visited.copy()
    for node in graph.keys():
        queue: deque[str] = deque([node])
        while (len(queue) > 0):
            cur_node: str = queue.popleft()
            for neighbour in graph[cur_node]:
                if not visited[neighbour]:
                    queue.append(neighbour)
                    visited[neighbour] = True
                    color[neighbour] = not(color[cur_node])
                elif color[cur_node] == color[neighbour]:
                    return False

    return color


def main():
    print(bipartite(graph=G2))
    return


if __name__ == "__main__":
    main()

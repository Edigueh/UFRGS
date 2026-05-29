from collections import deque
from graphs import G1, init_visited

def bfs_distance(graph: dict[str, list[str]], start_node: str, visited: dict[str, bool]) -> dict[str, int]:
    """Returns the distances from start_node to every other node in the graph using BFS."""
    queue = deque([start_node])
    visited[start_node] = True
    distances: dict[str, int] = visited.copy()
    distances[start_node] = 0

    while len(queue) > 0:
        cur_node: str = queue.popleft()
        for neighbour in graph[cur_node]:
            if not visited[neighbour]:
                queue.append(neighbour)
                visited[neighbour] = True
                distances[neighbour] = distances[cur_node] + 1

    return distances


def main():
    print(bfs_distance(graph=G1, start_node="B", visited=init_visited(graph=G1)))
    return


if __name__ == "__main__":
    main()

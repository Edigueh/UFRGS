"""Breadth First Search"""

from collections import deque
from graphs import G1

def init_visited(graph: list[str, list[str]]) -> dict[str, bool]:
    """Maps all nodes as unvisited."""
    return {node: False for node in graph.keys()}


def bfs(graph: list[str, list[str]], start_node: str, visited: dict[str, bool]):
    """Iterative Breadth First Search starting from the start node using a queue."""
    queue = deque(start_node)
    visited[start_node] = True

    while len(queue) > 0:
        cur_node: str = queue.popleft()
        print(cur_node) # Process
        for neighbour in graph[cur_node]:
            if not visited[neighbour]:
                queue.append(neighbour)
                visited[neighbour] = True


def main():
    bfs(graph=G1, start_node="A", visited=init_visited(G1))


if __name__ == "__main__":
    main()

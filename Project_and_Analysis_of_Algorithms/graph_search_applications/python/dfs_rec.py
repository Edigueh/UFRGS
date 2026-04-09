"""Recursive Depth First Search"""

from graphs import G1

def init_visited(graph: list[str, list[str]]) -> dict[str, bool]:
    """Maps all nodes as unvisited."""
    return {node: False for node in graph.keys()}


def dfs(graph: list[str, list[str]], start_node: str, visited: dict[str, bool]):
    """Recursive Depth First Search starting from the start node using a queue."""
    visited[start_node] = True
    print(start_node) # Process
    for neighbour in graph[start_node]:
        if not visited[neighbour]:
            dfs(graph, neighbour, visited)


def main():
    dfs(graph=G1, start_node="A", visited=init_visited(G1))


if __name__ == "__main__":
    main()

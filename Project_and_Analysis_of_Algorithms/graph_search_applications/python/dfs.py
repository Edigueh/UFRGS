"""Depth First Search"""

from graphs import G1, init_visited


def dfs(graph: list[str, list[str]], start_node: str, visited: dict[str, bool]):
    """Iterative Depth First Search starting from the start node using a queue."""
    stack = [start_node]
    visited[start_node] = True

    while len(stack) > 0:
        cur_node: str = stack.pop(-1)
        print(cur_node) # Process.
        for neighbour in graph[cur_node]:
            if not visited[neighbour]:
                stack.append(neighbour)
                visited[neighbour] = True


def main():
    dfs(graph=G1, start_node="A", visited=init_visited(G1))


if __name__ == "__main__":
    main()

"""Depth First Search with Iterative Tree"""

from graphs import G1

def init_visited(graph: list[str, list[str]]) -> dict[str, bool]:
    """Maps all nodes as unvisited."""
    return {node: False for node in graph.keys()}

def dfs_iter_tree(graph: list[str, list[str]], start_node: str) -> dict[str, str]:
    """Iterative Depth First Search starting from the start node using an iterative tree.
    This returns a dict mapping each node to its parent in the search.
    """
    antecesor_tree = {node: node for node in graph.keys()}
    visited = init_visited(graph)
    stack = [start_node]
    visited[start_node] = True

    while len(stack) > 0:
        node = stack.pop()
        for neighbour in graph[node]:
            if not visited[neighbour]:
                stack.append(neighbour)
                antecesor_tree[neighbour] = node
                visited[neighbour] = True

    return antecesor_tree


def main():
    ant_tree = dfs_iter_tree(graph=G1, start_node="A")
    
    for node in ant_tree.keys():
        print(f"Node: {node}, Parent: {ant_tree[node]}")


if __name__ == "__main__":
    main()

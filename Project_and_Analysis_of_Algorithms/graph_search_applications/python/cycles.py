from graphs import G1, G3, init_visited
from toposrt import toposort_kahn


def has_cycle(g: dict[str, list[str]]) -> bool:
    """Detects if a given simple undirected graph has a cycle using DFS."""
    visited: dict[str, bool] = init_visited(graph=g)

    def dfs(node: str, parent: str) -> bool:
        visited[node] = True
        for neighbour in g[node]:
            if not visited[neighbour]:
                if dfs(neighbour, node):
                    return True
            elif neighbour != parent:
                return True
        return False

    for node in g.keys():
        if not visited[node]:
            if dfs(node, -1):
                return True

    return False


def has_cycle_kahn(g: dict[str, list[str]]) -> bool:
    """Cycle detection in a digraph using Kahn's algorithm."""
    return True if len(toposort_kahn(g)) != len(g.keys()) else False


def main():
    print(has_cycle(G1))
    print(has_cycle_kahn(G1))
    print(has_cycle_kahn(G3))


if __name__ == "__main__":
    main()

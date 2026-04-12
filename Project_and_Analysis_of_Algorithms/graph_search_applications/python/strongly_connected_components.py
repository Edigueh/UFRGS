from graphs import G4, init_visited
from toposrt import dfs_toposort


def reverse_graph(g: dict[int, list[int]]) -> dict[int, list[int]]:
    """Given a digraph, returns a digraph with the direction of all edges inverted."""
    rev_g: dict[int, list[int]] = {node: [] for node in g.keys()}
    for node, neighbours in g.items():
        for neighbour in neighbours:
            rev_g[neighbour].append(node)
    return rev_g


def kosaraju_shamir(g: dict[int, list[int]]) -> dict[int, int]:
    """Kosaraju-Shamir algorithm to find strongly connected components in a Digraph."""
    rev_g: dict[int, list[int]] = reverse_graph(g)
    order: list[int] = dfs_toposort(g=rev_g)

    visited: dict[int, bool] = init_visited(graph=g)
    components: dict[int, int] = {}
    c: int = 0

    def dfs(g: dict[int, list[int]], start_node: int, visited: dict[int, bool], components: dict[int, int], c: int):
        visited[start_node] = True
        components[start_node] = c
        for neighbour in g[start_node]:
            if not visited[neighbour]:
                dfs(g=g, start_node=neighbour, visited=visited, components=components, c=c)

    for node in order:
        if not visited[node]:
            dfs(g=g, start_node=node, visited=visited, components=components, c=c)
            c += 1

    return components


def main():
    print(kosaraju_shamir(G4))


if __name__ == "__main__":
    main()

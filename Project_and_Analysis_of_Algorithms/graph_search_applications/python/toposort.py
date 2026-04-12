from graphs import G1, G4, init_visited
from collections import deque

def toposort_kahn(g: dict[str, list[str]]) -> list[str]:
    """Topological sort for DAGs using BGS (Kahn algorithm)."""
    in_deg: dict[str, int] = {node: 0 for node in g.keys()} # Input degrees.

    for node in g.keys():
        for neighbour in g[node]:
            in_deg[neighbour] += 1 # Node inputs at neighbour.

    q: deque[str] = deque() # Source nodes list.
    order: list[str] = [] # Output nodes order.

    for node in g.keys():
        if in_deg[node] == 0:
            q.append(node) # Inits q with nodes with input degree equals 0.

    while len(q) > 0:
        cur_node: str = q.popleft() 
        order.append(cur_node)
        for neighbour in g[cur_node]:
            in_deg[neighbour] -= 1
            if in_deg[neighbour] == 0: # If input degree is 0, it will be a source node.
                q.append(neighbour)

    return order


def dfs_toposort(g: dict[str, list[str]]) -> list[str]:
    """DFS topological sort."""
    visited: dict[str, bool] = init_visited(g)
    order: list[str] = []

    def dfs_rec(g: dict[str, list[str]], start_node: str, visited: dict[str, bool], order: list[str]):
        visited[start_node] = True
        for neighbour in g[start_node]:
            if not visited[neighbour]:
                dfs_rec(g, neighbour, visited, order)
        order.append(start_node)

    for node in g.keys():
        if not visited[node]:
            dfs_rec(g, node, visited, order)

    order.reverse()
    return order


def main():
    print(toposort_kahn(G1))
    print("--------------")
    print(dfs_toposort(G4))


if __name__ == "__main__":
    main()

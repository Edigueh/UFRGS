from graphs import G2

def components(graph: dict[str, list[str]]) -> dict[str, int]:
    """Returns the connected components in a simple graph."""
    def dfs(graph: dict[str, list[str]], start_node: str, visited: dict[str, bool], comp: list[str], c: int):
        visited[start_node] = True
        comp[start_node] = c
        for neighbour in graph[start_node]:
            if not visited[neighbour]:
                dfs(graph=graph, start_node=neighbour, visited=visited, comp=comp, c=c)
    
    comp: dict[str, int] = {}
    c: int = 0
    visited: dict[str, bool] = {i: False for i in graph.keys()}
    for node in graph.keys():
        if not visited[node]:
            dfs(graph=graph, start_node=node, visited=visited, comp=comp, c=c)
            c += 1

    return comp


def main():
    print(components(graph=G2))
    return


if __name__ == "__main__":
    main()

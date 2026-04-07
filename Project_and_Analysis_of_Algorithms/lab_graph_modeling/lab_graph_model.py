adj = {
    0: [1, 2],
    1: [0, 2],
    2: [0, 1],
    3: []
}

matriz = [
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0]
]

# Θ(n * deg(m))
def adj_list_to_adj_matrix(adj: dict[int, list[int]], matrix: list[list[int]]) -> list[list[int]]:
    """
        adj_list_to_adj_matrix returns the corresponding matrix from a given adjacency list representing a graph.
    """
    for k in adj.keys():
        for val in adj[k]:
            matrix[k][val] = 1
            matrix[val][k] = 1

    return matrix

for i in adj_list_to_adj_matrix(adj, matriz):
    print(i)

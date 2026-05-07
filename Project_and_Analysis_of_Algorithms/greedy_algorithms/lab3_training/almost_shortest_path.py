from typing import Dict, Hashable, List, Tuple, Optional
import heapq
import sys

input = sys.stdin.readline

Weight = int
Node = Hashable
Graph = Dict[Node, List[Tuple[Node, Weight]]]

def dijkstra(graph: Graph, source: Node) -> Tuple[Dict[Node, Weight], Dict[Node, Optional[Node]]]:
    """
    Dijkstra with a binary heap priority queue.
    Time complexity: O(|E| + |V| log |V|) for standard adjacency-list graphs with non-negative weights.

    Parameters
    ----------
    graph : Adj
        Adjacency dictionary where graph[u] is a list of (v, w) edges.
    source : Node
        Source node.

    Returns
    -------
    dist : Dict[Node, Weight]
        Shortest-path distance from source to each node (float('inf') if unreachable).
    parent : Dict[Node, Optional[Node]]
        Predecessor on a shortest path tree (None for source and unreachable nodes).

    Notes
    -----
    - Requires non-negative edge weights.
    - This version uses a min-heap (heapq). We allow multiple entries per node
      in the heap and skip "stale" ones by checking if the popped distance
      matches the current dist[u].
    """

    # Ensure the soure exists as a key.
    if source not in graph:
        graph = {**graph, source: graph.get(source, [])}

    # Collect all nodes (include those that only appear as targets).
    nodes = set(graph.keys())
    for _, neighbours in graph.items():
        for neighbour, _ in neighbours:
            nodes.add(neighbour)
    dist: Dict[Node, Weight] = {node: sys.maxsize for node in nodes}
    parent: Dict[Node, Optional[Node]] = {node: None for node in nodes}
    dist[source] = 0

    # Min-heap of (distance, node).
    heap: List[Tuple[Weight, Node]] = [(0, source)]
    heapq.heapify(heap)

    visited = set()

    while heap:
        distance_to_node, node = heapq.heappop(heap)
        if node in visited:
            continue

        # Skip stale pair (lazy decrease-key)
        if distance_to_node != dist[node]:
            continue

        visited.add(node)

        # Relax outgoing edges.
        for neighbour, weight_to_neighbour in graph.get(node, []):
            if weight_to_neighbour < 0:
                raise ValueError("Dijkstra requires non-negative weights.")
            
            new_distance: Weight = distance_to_node + weight_to_neighbour
            if new_distance < dist[neighbour]:
                dist[neighbour] = new_distance
                parent[neighbour] = node
                heapq.heappush(heap, (new_distance, neighbour))

    return dist, parent


def remove_edges_in_shortest_paths(
        graph: Graph,
        dest: Node, 
        dist_from_src: Tuple[Dict[Node, Weight]],
        dist_from_dest: Tuple[Dict[Node, Weight]]
) -> Graph:
    new_graph: Graph = {}
    for u, neighbours in graph.items():
        new_graph[u] = [
            (v, w) for v, w in neighbours
            if dist_from_src[u] + w + dist_from_dest[v] != dist_from_src[dest]
        ]

    return new_graph


def reverse_graph(graph: Graph) -> Graph:
    reversed_graph: Graph = {node: [] for node in graph}
    for u, neighbours in graph.items():
        for v, w in neighbours:
            reversed_graph[v].append((u,w))
    return reversed_graph


def solve(n: int, m: int):
    """
    Solution Idea

    1. Run Dijkstra from S — compute dist_from_S[v] for all vertices.
    2. Run Dijkstra from D on the reversed graph — compute dist_from_D[v] (i.e., shortest distance from any node to D in the original graph).
    3. Mark and remove edges on shortest paths — An edge (u, v, w) belongs to a shortest path from S to D if:
    dist_from_S[u] + w + dist_from_D[v] == dist_from_S[D]
    3. Remove (or ignore) all such edges.
    4. Run Dijkstra from S again on the remaining graph — the answer is the new dist[D]. If D is unreachable, output -1.
    """
    graph: Graph = {}
    graph = {node: [] for node in range(n)}
    src, dest = map(int, input().split())
    for i in range(m):
        u, v, p = map(int, input().split())
        graph[u].append((v,p))

    dist_from_src, _ = dijkstra(graph=graph, source=src)
    dist_from_dest, _ = dijkstra(graph=reverse_graph(graph), source=dest)

    graph = remove_edges_in_shortest_paths(graph, dest, dist_from_src, dist_from_dest)

    almost_shortest_dist_from_src, _ = dijkstra(graph=graph, source=src)

    ans: int = almost_shortest_dist_from_src[dest]
    
    print(ans if ans != sys.maxsize else -1)


if __name__== "__main__":
    while True:
        n, m = map(int, input().split())
        if n == 0 and m == 0:
            break
        solve(n, m)

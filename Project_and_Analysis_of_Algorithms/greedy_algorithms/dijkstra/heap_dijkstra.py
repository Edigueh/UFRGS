from typing import Dict, Hashable, List, Tuple, Optional
import heapq
import time

Weight = float
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
    dist: Dict[Node, Weight] = {node: float("inf") for node in nodes}
    parent: Dict[Node, Optional[Node]] = {node: None for node in nodes}
    dist[source] = 0.0

    # Min-heap of (distance, node).
    heap: List[Tuple[Weight, Node]] = [(0.0, source)]
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


def reconstruct_path(parent: Dict[Node, Optional[Node]], dist: Dict[Node, Weight], target: Node) -> List[Node]:
    """
    Reconstructs the path to 'target' using 'parent'.
    Returns [] if 'target' is unreachable.
    """
    # Unreachable (and not the source) if distance is inf
    if dist.get(target, float('inf')) == float('inf'):
        return []

    path: List[Node] = []
    cur: Optional[Node] = target
    while cur is not None:
        path.append(cur)
        cur = parent[cur]
    path.reverse()
    return path


if __name__ == "__main__":
    # Directed example
    if False:
        G = {
            's': [('a', 1), ('b', 4)],
            'a': [('b', 2), ('c', 5)],
            'b': [('c', 1)],
            'c': []
        }
        dist, parent = dijkstra(G, 's')
        print("dist:", dist)
        print("parent:", parent)
        print("caminho s->c:", reconstruct_path(parent, dist, 'c'))
        print('\n\n\n')

    if True:
        GExemp = {
            'S': [('A', 1), ('B', 3)],
            'A': [('S', 1), ('D', 5), ('C', 4)],
            'B': [('S', 3), ('D', 4), ('C', 1)],
            'C': [('B', 1), ('A', 4), ('E', 6)],
            'D': [('A', 5), ('B', 4), ('E', 2)],
            'E': [('D', 2), ('C', 6)],
            'F': [],
        }

        print("graph:", GExemp)
        dist, parent = dijkstra(GExemp, 'S')
        print("dist:", dist)
        print("parent:", parent)
        print("caminho S->E:", reconstruct_path(parent, dist, 'E'))
        print("caminho S->S:", reconstruct_path(parent, dist, 'S'))
        print("caminho S->F:", reconstruct_path(parent, dist, 'F'))
        print('\n\n\n')

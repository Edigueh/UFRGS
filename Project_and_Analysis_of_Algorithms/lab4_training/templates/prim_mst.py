"""
Brief: Prim for Minimum Spanning Tree using a binary heap (lazy deletion).

API:
  prim(adj, n, source=0) -> (total_weight, mst_edges)
    adj: adjacency list, adj[u] = [(weight, v), ...]
    n:   number of vertices (0..n-1)

Complexity: O((n+m) log n).
Correctness: cut property.
"""

import heapq
from typing import List, Tuple


def prim(adj: List[List[Tuple[int, int]]], n: int, source: int = 0) -> Tuple[int, List[Tuple[int, int, int]]]:
    in_tree = [False] * n
    total_weight = 0
    mst_edges: List[Tuple[int, int, int]] = []
    # Each heap entry: (weight, neighbor, origin). origin=-1 for the seed.
    heap: List[Tuple[int, int, int]] = [(0, source, -1)]
    while heap and len(mst_edges) < n - 1 + 1:
        w, u, parent = heapq.heappop(heap)
        if in_tree[u]:
            continue
        in_tree[u] = True
        if parent != -1:
            mst_edges.append((w, parent, u))
            total_weight += w
        for nw, v in adj[u]:
            if not in_tree[v]:
                heapq.heappush(heap, (nw, v, u))
    return total_weight, mst_edges


if __name__ == "__main__":
    n = 5
    edges = [
        (1, 0, 1),
        (4, 0, 2),
        (3, 1, 2),
        (2, 1, 3),
        (4, 2, 3),
        (5, 2, 4),
        (7, 3, 4),
    ]
    adj: List[List[Tuple[int, int]]] = [[] for _ in range(n)]
    for w, u, v in edges:
        adj[u].append((w, v))
        adj[v].append((w, u))
    total, mst = prim(adj, n)
    print(f"total weight = {total}")
    for w, u, v in mst:
        print(f"  {u}-{v} ({w})")
    assert total == 11
    print("prim_mst OK")

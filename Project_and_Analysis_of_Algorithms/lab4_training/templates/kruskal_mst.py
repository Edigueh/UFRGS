"""
Brief: Kruskal for Minimum Spanning Tree using Union-Find (DSU).

API:
  kruskal(n, edges) -> (total_weight, mst_edges)
    n: number of vertices (labeled 0..n-1)
    edges: list of tuples (weight, u, v)

Complexity: O(m log m) due to edge sorting + O(m * alpha(n))
for the Union-Find operations.
Correctness: cut property.
"""

from typing import List, Tuple


def kruskal(n: int, edges: List[Tuple[int, int, int]]) -> Tuple[int, List[Tuple[int, int, int]]]:
    # Sort edges in increasing order of cost.
    edges_sorted = sorted(edges)

    parent = list(range(n))
    rank_ = [0] * n

    def find(x: int) -> int:
        root = x
        while parent[root] != root:
            root = parent[root]
        while parent[x] != root:
            parent[x], x = root, parent[x]
        return root

    def union(x: int, y: int) -> bool:
        rx, ry = find(x), find(y)
        if rx == ry:
            return False
        if rank_[rx] < rank_[ry]:
            rx, ry = ry, rx
        parent[ry] = rx
        if rank_[rx] == rank_[ry]:
            rank_[rx] += 1
        return True

    total_weight = 0
    mst_edges: List[Tuple[int, int, int]] = []
    for w, u, v in edges_sorted:
        if union(u, v):
            mst_edges.append((w, u, v))
            total_weight += w
            if len(mst_edges) == n - 1:
                break
    return total_weight, mst_edges


if __name__ == "__main__":
    edges = [
        (1, 0, 1),
        (4, 0, 2),
        (3, 1, 2),
        (2, 1, 3),
        (4, 2, 3),
        (5, 2, 4),
        (7, 3, 4),
    ]
    total, mst = kruskal(5, edges)
    print(f"total weight = {total}")
    for w, u, v in mst:
        print(f"  {u}-{v} ({w})")
    assert total == 11  # 1 + 2 + 3 + 5
    print("kruskal_mst OK")

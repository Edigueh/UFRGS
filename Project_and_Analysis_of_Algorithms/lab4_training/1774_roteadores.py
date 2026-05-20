"""
Brief: beecrowd 1774 - Roteadores. Classical MST via Kruskal.
       Connect R routers with minimum cost choosing among C cables.

Format:
  Line 1: R C   (3 <= R <= 60, R-1 <= C <= 200)
  Then C lines: V W P  (cable between routers V and W with cost P).

Output: minimum total cost of the spanning tree.

Algorithm: Kruskal with Union-Find. Sort edges by weight, union components
until R-1 edges are selected.
"""

import sys
from typing import List, Tuple


def solve(n: int, edges: List[Tuple[int, int, int]]) -> int:
    edges_sorted = sorted(edges)
    parent = list(range(n + 1))  # 1-indexed
    rank_ = [0] * (n + 1)

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

    total = 0
    used = 0
    for w, u, v in edges_sorted:
        if union(u, v):
            total += w
            used += 1
            if used == n - 1:
                break
    return total


def main() -> None:
    data = sys.stdin.buffer.read().split()
    idx = 0
    out: List[str] = []
    while idx < len(data):
        try:
            R = int(data[idx])
            idx += 1
            C = int(data[idx])
            idx += 1
        except (IndexError, ValueError):
            break
        edges: List[Tuple[int, int, int]] = []
        for _ in range(C):
            v = int(data[idx])
            idx += 1
            w = int(data[idx])
            idx += 1
            p = int(data[idx])
            idx += 1
            edges.append((p, v, w))
        out.append(str(solve(R, edges)))
    sys.stdout.write('\n'.join(out))
    if out:
        sys.stdout.write('\n')


if __name__ == "__main__":
    main()

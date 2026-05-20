"""
Brief: Union-Find (DSU) data structure with path compression and union by rank.

Operations:
  find(x)    -> representative of x's component (with path compression)
  union(x,y) -> unites the components; returns True if it actually united

Amortized cost: O(alpha(n)) per operation, practically constant.
"""

from typing import List


class UnionFind:
    def __init__(self, n: int) -> None:
        # Indexing 0..n-1; for problems 1..n just create UnionFind(n+1).
        self.parent: List[int] = list(range(n))
        self.rank: List[int] = [0] * n
        self.num_components: int = n

    def find(self, x: int) -> int:
        # Iterative path compression (avoids stack overflow on long trees).
        root = x
        while self.parent[root] != root:
            root = self.parent[root]
        while self.parent[x] != root:
            self.parent[x], x = root, self.parent[x]
        return root

    def union(self, x: int, y: int) -> bool:
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False
        # Union by rank: smaller tree points to the larger one.
        if self.rank[rx] < self.rank[ry]:
            rx, ry = ry, rx
        self.parent[ry] = rx
        if self.rank[rx] == self.rank[ry]:
            self.rank[rx] += 1
        self.num_components -= 1
        return True

    def connected(self, x: int, y: int) -> bool:
        return self.find(x) == self.find(y)


if __name__ == "__main__":
    # Smoke test: 6 vertices, 5 unions -> 1 component
    uf = UnionFind(6)
    for u, v in [(0, 1), (2, 3), (1, 2), (4, 5), (3, 4)]:
        uf.union(u, v)
    assert uf.num_components == 1
    assert all(uf.connected(0, i) for i in range(6))
    print("union_find OK")

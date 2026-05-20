"""
Brief: Prufer code -- Cayley's bijection between labeled trees and integer
       sequences of size n-2.

Encoding API:
  prufer_encode(adj_list)        -> O(n log n)

Decoding API:
  prufer_decode(seq)             -> O(n log n)

Input convention: adj_list is a dict or list of lists where the labels are
integers 1..n. Encoding returns a list of size n-2 (empty if n <= 2).
Decoding takes such a sequence and returns a list of n-1 edges (u, v).

Decoding algorithm:
  Sequence s of size n-2 with labels in 1..n.
  For i = 1..n-2:
    f = smallest label that does not appear in s[i..n-2] and was not used as a leaf
    edge {f, s[i]}
    "remove" f
  The two remaining labels form the last edge.
"""

import heapq
from typing import Dict, List, Tuple


def prufer_encode(adj: Dict[int, List[int]]) -> List[int]:
    n = len(adj)
    if n <= 2:
        return []
    deg = {v: len(neigh) for v, neigh in adj.items()}
    adj_local: Dict[int, List[int]] = {v: list(neigh) for v, neigh in adj.items()}
    # Heap with current leaves only
    heap: List[int] = [v for v in adj_local if deg[v] == 1]
    heapq.heapify(heap)
    code: List[int] = []
    for _ in range(n - 2):
        leaf = heapq.heappop(heap)
        # Find the only neighbor still alive
        neighbor = next(u for u in adj_local[leaf] if deg[u] > 0)
        code.append(neighbor)
        deg[neighbor] -= 1
        deg[leaf] = 0
        if deg[neighbor] == 1:
            heapq.heappush(heap, neighbor)
    return code


def prufer_decode(seq: List[int]) -> List[Tuple[int, int]]:
    n = len(seq) + 2
    if n == 1:
        return []
    if n == 2:
        return [(1, 2)]
    # deg[v] = how many times v appears in seq, +1 (because every eventual leaf
    # has degree 1 in the final tree). Initial leaves: vertices with degree 1.
    deg = [1] * (n + 1)  # deg[0] unused
    for v in seq:
        deg[v] += 1
    leaves: List[int] = [v for v in range(1, n + 1) if deg[v] == 1]
    heapq.heapify(leaves)
    edges: List[Tuple[int, int]] = []
    for s in seq:
        f = heapq.heappop(leaves)
        edges.append((f, s))
        deg[f] -= 1
        deg[s] -= 1
        if deg[s] == 1:
            heapq.heappush(leaves, s)
    # The two final labels
    u = heapq.heappop(leaves)
    v = heapq.heappop(leaves)
    edges.append((u, v))
    return edges


if __name__ == "__main__":
    # tree (2 (3) (5 (1) (4)) (6 (7)) (8 (9))) -> "5 2 5 2 6 2 8"
    adj: Dict[int, List[int]] = {
        1: [5],
        2: [3, 5, 6, 8],
        3: [2],
        4: [5],
        5: [1, 2, 4],
        6: [2, 7],
        7: [6],
        8: [2, 9],
        9: [8],
    }
    expected = [5, 2, 5, 2, 6, 2, 8]
    assert prufer_encode(adj) == expected

    # Round-trip: decode the sequence and verify a connected tree on n=9 vertices
    edges = prufer_decode(expected)
    n = len(expected) + 2  # 9
    assert len(edges) == n - 1
    rebuilt = {v: [] for v in range(1, n + 1)}
    for u, v in edges:
        rebuilt[u].append(v)
        rebuilt[v].append(u)
    seen = {1}
    stack = [1]
    while stack:
        x = stack.pop()
        for y in rebuilt[x]:
            if y not in seen:
                seen.add(y)
                stack.append(y)
    assert len(seen) == n
    print("prufer OK -> ", edges)

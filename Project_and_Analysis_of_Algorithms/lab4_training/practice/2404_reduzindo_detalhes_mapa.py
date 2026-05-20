"""
Brief: beecrowd 2404 - Reduzindo Detalhes em um Mapa. MST via Kruskal (templates).
       Keep connectivity between N cities with minimum sum of road weights.

Format:
  Line 1: N M  (N cities, M connections). Terminates with "0 0" or EOF.
  Then M lines: city1 city2 cost  (1-indexed cities).

Output: for each case, the MST weight.

Algorithm: classical Kruskal.
"""

import sys
from pathlib import Path
from typing import List, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from templates.kruskal_mst import kruskal


def main() -> None:
    data = sys.stdin.buffer.read().split()
    idx = 0
    out: List[str] = []
    while idx < len(data):
        N = int(data[idx])
        idx += 1
        M = int(data[idx])
        idx += 1
        if N == 0 and M == 0:
            break
        edges: List[Tuple[int, int, int]] = []
        for _ in range(M):
            c1 = int(data[idx])
            idx += 1
            c2 = int(data[idx])
            idx += 1
            cost = int(data[idx])
            idx += 1
            edges.append((cost, c1 - 1, c2 - 1))
        mst_weight, _mst = kruskal(N, edges)
        out.append(str(mst_weight))
    sys.stdout.write('\n'.join(out))
    if out:
        sys.stdout.write('\n')


if __name__ == "__main__":
    main()

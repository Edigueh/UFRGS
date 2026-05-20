"""
Brief: beecrowd 1764 - Itinerario do Papai Noel. MST via Kruskal (templates).
       Connect all cities with minimum total cost.

Format:
  Line 1: N M  (N cities, M segments). Terminates with "0 0".
  Then M lines: X Y Z  (segment between X and Y with cost Z; 1-indexed cities).

Output: for each case, the MST weight (minimum total cost).

Algorithm: classical Kruskal. Maps cities 1..N to 0..N-1 (subtract 1).
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
            x = int(data[idx])
            idx += 1
            y = int(data[idx])
            idx += 1
            z = int(data[idx])
            idx += 1
            # 1-indexed -> 0-indexed to match the template's API.
            edges.append((z, x - 1, y - 1))
        mst_weight, _mst = kruskal(N, edges)
        out.append(str(mst_weight))
    sys.stdout.write('\n'.join(out))
    if out:
        sys.stdout.write('\n')


if __name__ == "__main__":
    main()

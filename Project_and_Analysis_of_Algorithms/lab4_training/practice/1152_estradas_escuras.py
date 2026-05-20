"""
Brief: beecrowd 1152 - Estradas Escuras. MST via Kruskal (templates).
       Maximize savings by turning off roads while keeping connectivity:
       answer = total_sum_of_weights - weight_of_MST.

Format:
  Line 1: m n  (m houses, n roads). Terminates with "0 0".
  Then n lines: x y z  (road between x and y of weight z; 0-indexed vertices).

Output: for each case, the maximum possible savings.

Algorithm: sum all edge weights, compute MST with Kruskal,
print total_sum - MST_weight.
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
        m = int(data[idx])
        idx += 1
        n = int(data[idx])
        idx += 1
        if m == 0 and n == 0:
            break
        edges: List[Tuple[int, int, int]] = []
        total_sum = 0
        for _ in range(n):
            x = int(data[idx])
            idx += 1
            y = int(data[idx])
            idx += 1
            z = int(data[idx])
            idx += 1
            edges.append((z, x, y))
            total_sum += z
        mst_weight, _mst = kruskal(m, edges)
        out.append(str(total_sum - mst_weight))
    sys.stdout.write('\n'.join(out))
    if out:
        sys.stdout.write('\n')


if __name__ == "__main__":
    main()

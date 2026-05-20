"""
Brief: beecrowd 1735 - Codifique a Arvore.
       Reads a labeled tree in `(N S)` notation and prints the Prufer code.

Algorithm:
  1) Recursive parser for the grammar T ::= "(" N S ")", S ::= T*  (N integer 1..n).
  2) Builds the adjacency list.
  3) Prufer encode: while more than 2 vertices remain, remove the lowest-labeled leaf
     and record its neighbor.

Complexity: n <= 50 -> O(n^2) is sufficient.
Edge cases:
  - Single-vertex tree: empty code -> blank line.
  - Multiple test cases in the input: read until EOF.
"""

import sys
from typing import Dict, List


def parse_tree(tokens: List[str]) -> Dict[int, List[int]]:
    """Recursive parser. Returns a 1-indexed adjacency list."""
    adj: Dict[int, List[int]] = {}
    pos = 0

    def parse_node() -> int:
        nonlocal pos
        # Expect '('
        assert tokens[pos] == '('
        pos += 1
        # Read label
        label = int(tokens[pos])
        pos += 1
        if label not in adj:
            adj[label] = []
        # Children: while the next token is '('
        while tokens[pos] == '(':
            child = parse_node()
            adj[label].append(child)
            adj[child].append(label)
        # Expect ')'
        assert tokens[pos] == ')'
        pos += 1
        return label

    parse_node()
    return adj


def prufer_encode(adj: Dict[int, List[int]]) -> List[int]:
    n = len(adj)
    # For n=1, the code is empty.
    if n <= 1:
        return []
    deg = {v: len(neigh) for v, neigh in adj.items()}
    adj_local: Dict[int, List[int]] = {v: list(neigh) for v, neigh in adj.items()}
    code: List[int] = []
    for _ in range(n - 1):
        leaf = min(v for v in adj_local if deg[v] == 1)
        neighbor = next(u for u in adj_local[leaf] if deg[u] > 0)
        code.append(neighbor)
        deg[neighbor] -= 1
        deg[leaf] = 0
    return code


def main() -> None:
    raw = sys.stdin.buffer.read().decode()
    # Insert spaces around '(' and ')' for simple tokenization
    spaced = raw.replace('(', ' ( ').replace(')', ' ) ')
    tokens = spaced.split()
    out: List[str] = []
    pos = 0
    while pos < len(tokens):
        # Find the start of the next case (next '(')
        if tokens[pos] != '(':
            pos += 1
            continue
        # Collect tokens until the case closes (parenthesis balancing)
        depth = 0
        start = pos
        while pos < len(tokens):
            if tokens[pos] == '(':
                depth += 1
            elif tokens[pos] == ')':
                depth -= 1
                if depth == 0:
                    pos += 1
                    break
            pos += 1
        case_tokens = tokens[start:pos]
        adj = parse_tree(case_tokens)
        code = prufer_encode(adj)
        out.append(' '.join(map(str, code)))
    # One line per case, with a trailing newline on each.
    for line in out:
        sys.stdout.write(line)
        sys.stdout.write('\n')


if __name__ == "__main__":
    main()

"""
Brief: Huffman coding -- tree construction, code generation,
       encoding and decoding.

Tree representation:
    leaf:     ('leaf', symbol)
    internal: ('node', left_subtree, right_subtree)

API:
  build_huffman(freqs)        -> tree
  build_codes(tree)           -> dict {symbol: '01...'}
  encode(s, codes)            -> bit string
  decode(bits, tree)          -> original string

Complexity: O(n log n) using a binary heap.
"""

import heapq
from typing import Dict, Tuple, Any, List

Tree = Tuple  # ('leaf', sym) | ('node', Tree, Tree)


def build_huffman(freqs: Dict[Any, int]) -> Tree:
    # Degenerate case: single-symbol alphabet -> tree with only one leaf.
    # To ensure a non-empty code the caller may treat this as a special case.
    heap: List[Tuple[int, int, Tree]] = []
    counter = 0  # deterministic tiebreak
    for sym, f in freqs.items():
        heapq.heappush(heap, (f, counter, ('leaf', sym)))
        counter += 1
    if len(heap) == 1:
        f, _, t = heapq.heappop(heap)
        return ('node', t, t)  # forces depth 1
    while len(heap) > 1:
        f1, _, t1 = heapq.heappop(heap)
        f2, _, t2 = heapq.heappop(heap)
        merged: Tree = ('node', t1, t2)
        heapq.heappush(heap, (f1 + f2, counter, merged))
        counter += 1
    return heap[0][2]


def build_codes(tree: Tree) -> Dict[Any, str]:
    codes: Dict[Any, str] = {}

    def walk(node: Tree, path: str) -> None:
        if node[0] == 'leaf':
            codes[node[1]] = path or '0'  # single symbol -> code "0"
            return
        walk(node[1], path + '0')
        walk(node[2], path + '1')

    walk(tree, '')
    return codes


def encode(s: str, codes: Dict[Any, str]) -> str:
    return ''.join(codes[c] for c in s)


def decode(bits: str, tree: Tree) -> str:
    out: List[str] = []
    node = tree
    for b in bits:
        node = node[1] if b == '0' else node[2]
        if node[0] == 'leaf':
            out.append(node[1])
            node = tree
    return ''.join(out)


if __name__ == "__main__":
    freqs = {'a': 5, 'b': 9, 'c': 12, 'd': 13, 'e': 16, 'f': 45}
    tree = build_huffman(freqs)
    codes = build_codes(tree)
    print("codes:", codes)
    msg = "facebead"
    bits = encode(msg, codes)
    rec = decode(bits, tree)
    print(f"{msg!r} -> {bits} -> {rec!r}")
    assert rec == msg
    # Expected total cost: sum(freq * len(code))
    total = sum(freqs[c] * len(codes[c]) for c in freqs)
    assert total == 224  # classical value from the example
    print("huffman OK")

"""Graphs / Digraphs as adjacency lists."""

# Acyclic digraph.
G1 = {
    "A": ["B", "E"],
    "B": ["E", "F"],
    "C": ["D"],
    "D": [],
    "E": ["C", "F"],
    "F": ["D", "G"],
    "G": [],
}

# Simple graph (cyclic, not bipartite, three connected components)
G2 = {
    "A": ["B"],
    "B": ["A", "D", "E"],
    "C": [],
    "D": ["B", "E"],
    "E": ["B", "D", "F"],
    "F": ["E"],
    "G": ["H"],
    "H": ["G"],
}

# Digraph (cyclic)
G3 = {
    "A": ["B", "E"],
    "B": ["E"],
    "C": ["D"],
    "D": [],
    "E": ["C", "F"],
    "F": ["B", "D", "G"],
    "G": [],
}


# Digraph (cyclic, four strongly connected components)
G4 = {
    1: [3],
    2: [4, 10],
    3: [5, 11],
    4: [7],
    5: [1, 7, 9],
    6: [10],
    7: [9],
    8: [6],
    9: [2, 4, 8],
    10: [8],
    11: [6, 8],
}


# Digraph (acyclic)
G5 = {
    "A": ["B"],
    "B": ["C", "F"],
    "C": ["D"],
    "D": ["E"],
    "E": [],
    "F": ["E"],
    "G": ["H", "I"],
    "H": ["I", "F"],
    "I": [],
}


# Simple graph (cube, bipartite, connected)
G6 = {
    "000": ["100", "010", "001"],
    "001": ["101", "011", "000"],
    "010": ["110", "000", "011"],
    "100": ["000", "110", "101"],
    "011": ["111", "001", "010"],
    "101": ["001", "111", "100"],
    "110": ["010", "100", "111"],
    "111": ["011", "101", "110"],
}

# Digraph (cyclic)
G7 = {
    "A": ["B"],
    "B": ["C", "F"],
    "C": ["D"],
    "D": ["E"],
    "E": [],
    "F": ["E"],
    "G": ["H"],
    "H": ["I", "F"],
    "I": ["G"],
}

def init_visited(graph: list[str, list[str]]) -> dict[str, bool]:
    """Maps all nodes as unvisited."""
    return {node: False for node in graph.keys()}

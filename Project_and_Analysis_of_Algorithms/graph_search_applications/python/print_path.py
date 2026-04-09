from dfs_iter_tree import dfs_iter_tree
from graphs import G1

def print_path(tree: dict[str, str], target: str) -> list[str]:
    """Given an antecessor tree and a target, prints the path to target until its ultimate antecessor."""
    node: str = target
    path: list[str] = [node]
    while node != tree[node]:
        node = tree[node]
        path.append(node)

    print(list(reversed(path)))

def main():
    print_path(tree=dfs_iter_tree(G1, "A"), target="G")
    return


if __name__ == "__main__":
    main()

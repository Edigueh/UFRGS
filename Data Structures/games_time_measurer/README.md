# Game Time Metrics

This project compares how different tree data structures perform when looking up game playtime data. It reads a CSV file of Steam games with their average playtime, loads them into various tree structures, and measures how long it takes to search for games in a wishlist.

## The data structures

Three tree implementations are included:

- **Binary Search Tree (BST)** - Simple but can become unbalanced with sorted data
- **AVL Tree** - Self-balancing with strict height constraints
- **Red-Black Tree** - Self-balancing with looser constraints than AVL

All trees are case-insensitive when comparing game names.

## Building the project

You need GCC and Make installed. To compile:

```bash
make
```

This creates the `measurer.o` executable.

To clean up build artifacts:

```bash
make clean
```

## Running it

The program takes three command-line arguments:

```bash
./measurer.o <games_csv> <player_list_txt> <output_txt>
```

Example:

```bash
./measurer.o dataset/dataset.csv dataset/player_list.txt output/results.txt
```

**Input files:**

- `games_csv` - CSV file with game names and average hours (format: `Game Name,Hours`)
- `player_list_txt` - Text file with one game name per line

**Output:**
The program writes statistics about the trees and results to the output file.

## Visualizing the trees

If you have Graphviz installed, you can generate visual representations:

```bash
make visualize
```

This creates SVG files in the `visualization/` directory showing the structure of each tree type.

## Project structure

```
├── src/             # Implementation files
│   ├── main.c       # Main program
│   ├── bst.c        # Binary Search Tree
│   ├── avl.c        # AVL Tree  
│   ├── rbt.c        # Red-Black Tree
│   ├── utils.c      # File I/O and utilities
│   └── visualizer.c # Graphviz generation
├── include/         # Header files
├── dataset/         # Sample CSV files with game data
├── output/          # Results directory
├── visualization/   # Tree diagrams (after make visualize)
└── report/          # Final analysis report
```

## Authors

[André Schaidhauer Luckmann](https://github.com/Edigueh)

[Vitor da Cunha Pimentel da Rosa](https://github.com/VitorPimentel17)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "bst.h"
#include "rbt.h"
#include "visualizer.h"

#define READ_ACCESS "r"
#define WRITE_ACCESS "w"
#define EXPECTED_INPUTS 4
#define MAX_LINE_LENGTH 90

void buildTrees(FILE *dataset, BstNode **bst, AvlNode **avl, RbtNode **rbt) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, dataset) != NULL) {
        NodeInfo newInfo;
        bool ok;

        char *name = strtok(line, ",");
        float time = strtof(strtok(NULL, ","), NULL);

        newInfo.name = strdup(name);
        newInfo.avg_play_time = time;

        *bst = insertBstNode(*bst, newInfo);
        *avl = insertAvlNode(*avl, newInfo, &ok);
        *rbt = insertRbtNode(*rbt, newInfo);
    }
}

/*
    int argc: counts the number of given parameters.
    char *argv[]: stores the strings of given parameters.
*/
int main(int argc, char *argv[]) {
    if (argc != EXPECTED_INPUTS) {
        printf("Expected %d parameters but found %d.\n  Correct usage: <dataset.csv> <player_wishlist.txt> <output.txt>\n", EXPECTED_INPUTS, argc);
        return EXIT_FAILURE;
    }

    FILE *dataset = fopen(argv[1], READ_ACCESS), *player_wishlist = fopen(argv[2], READ_ACCESS);
    if (dataset == NULL || player_wishlist == NULL) {
        printf("Error on opening one input files, please check %s or %s!\n", argv[1], argv[2]);
        return EXIT_FAILURE;
    }

    BstNode *bst = newBinSearchTree();
    AvlNode *avl = newAvlTree();
    RbtNode *rbt = newRedBlackTree();

    buildTrees(dataset, &bst, &avl, &rbt);

    // printf("====BST PRINT START====\n");
    // bstPreOrderTraversalPrint(bst);
    // printf("====BST PRINT END====\n");


    // printf("====AVL PRINT START====\n");
    // avlPreOrderTraversalPrint(avl);
    // printf("====AVL PRINT END====\n");

    // printf("====RBT PRINT START====\n");
    // rbtPreOrderTraversalPrint(rbt);
    // printf("====RBT PRINT END====\n");

    printf("\nGenerating DOT files for visualization...\n");
    
    bstGenerateDotFile(bst, "visualization/bst.dot");
    avlGenerateDotFile(avl, "visualization/avl.dot");
    rbtGenerateDotFile(rbt, "visualization/rbt.dot");

    printf("Generated bst.dot, avl.dot, and rbt.dot\n");
    printf("Use a Graphviz tool to view them (e.g., 'dot -Tpng bst.dot -o bst.png')\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "bst.h"

#define READ_ACCESS "r"
#define WRITE_ACCESS "w"
#define EXPECTED_INPUTS 4
#define MAX_LINE_LENGTH 90



BstNode* buildBst(FILE *dataset) {
    char line[MAX_LINE_LENGTH];
    BstNode* bst = newBinSearchTree();
    while (fgets(line, MAX_LINE_LENGTH, dataset) != NULL) {
        NodeInfo newInfo;
        char *name = strtok(line, ",");
        float time = strtof(strtok(NULL, ","), NULL);
        bst = insertBstNode(bst, (NodeInfo){strdup(name), time});
    }

    return bst;
}

AvlNode* buildAvlTree(FILE *dataset) {
    char line[MAX_LINE_LENGTH];
    AvlNode* avl = newAvlTree();
    while (fgets(line, MAX_LINE_LENGTH, dataset) != NULL) {
        char *name = strtok(line, ",");
        float time = strtof(strtok(NULL, ","), NULL);
        bool ok;
        avl = insertAvlNode(avl, (NodeInfo){strdup(name), time}, &ok);
    }

    return avl;
}

/*
    int argc: counts the number of given parameters.
    char *argv[]: stores the strings of given parameters.
*/
int main(int argc, char *argv[]) {
    if (argc != EXPECTED_INPUTS) {
        printf("Expected %d parameters but found %d.\n Correct usage: <dataset.csv> <player_wishlist.txt> <output.txt>\n", EXPECTED_INPUTS, argc);
        return EXIT_FAILURE;
    }

    FILE *dataset = fopen(argv[1], READ_ACCESS), *player_wishlist = fopen(argv[2], READ_ACCESS);
    if (dataset == NULL || player_wishlist == NULL) {
        printf("Error on opening one input files, please check %s or %s!\n", argv[1], argv[2]);
        return EXIT_FAILURE;
    }

    BstNode *bst = buildBst(dataset);
    rewind(dataset);
    AvlNode *avl = buildAvlTree(dataset);
    printf("====BST PRINT START====\n");
    bstPreOrderTraversalPrint(bst);
    printf("====BST PRINT END====\n");


    printf("====AVL PRINT START====\n");
    avlPreOrderTraversalPrint(avl);
    printf("====AVL PRINT END====\n");
}

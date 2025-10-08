#include <stdlib.h>
#include "BinarySearchTree.h"

int main(void) {
    printf("=======TEST COUNT BEGIN=======\n");
    Node *bst = newBinSearchTree();
    bst = insertNode(bst, 8);
    bst = insertNode(bst, 4);
    bst = insertNode(bst, 9);
    bst = insertNode(bst, 2);
    bst = insertNode(bst, 6);
    bst = insertNode(bst, 1);

    printf("Node Count: %d\n", countBSTNodes(bst));
    printf("=======TEST COUNT END=======\n");
    printf("=======TEST PRINT BEGIN=======\n");
    preOrderTraversalPrint(bst);
    printf("=======TEST PRINT END=======\n");
    return EXIT_SUCCESS;
}

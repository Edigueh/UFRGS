#include "AVLTrees.h"

int main(void) {
    printf("===TEST_A_INIT===\n");
    Node *a = newBinSearchTree();
    a = insertNode(a, 12);
    a = insertNode(a, 8);
    a = insertNode(a, 20);
    a = insertNode(a, 4);
    a = insertNode(a, 10);
    a = insertNode(a, 2);
    a = insertNode(a, 6);
    a = insertNode(a, 9);
    a = insertNode(a, 11);
    a = insertNode(a, 18);
    a = insertNode(a, 26);
    a = insertNode(a, 14);
    a = insertNode(a, 19);
    a = insertNode(a, 22);
    a = insertNode(a, 28);
    preOrderTraversalPrint(a);
    printf("Balance factor of the tree is: %d\n", getTreeBalanceFactor(a));
    printf("===TEST_A_END===\n\n");

    printf("===TEST_B_INIT===\n");
    
    Node *b = newBinSearchTree();
    b = insertNode(b, 12);
    b = insertNode(b, 8);
    b = insertNode(b, 20);
    b = insertNode(b, 4);
    b = insertNode(b, 10);
    b = insertNode(b, 2);
    b = insertNode(b, 6);
    b = insertNode(b, 9);
    b = insertNode(b, 18);
    b = insertNode(b, 26);
    b = insertNode(b, 14);
    b = insertNode(b, 19);
    b = insertNode(b, 22);
    b = insertNode(b, 28);
    preOrderTraversalPrint(b);
    printf("Balance factor of the tree is: %d\n", getTreeBalanceFactor(b));
    printf("===TEST_B_END===\n\n");

    printf("===TEST_C_INIT===\n");

    Node *c = newBinSearchTree();
    c = insertNode(c, 12);
    c = insertNode(c, 8);
    c = insertNode(c, 20);
    c = insertNode(c, 4);
    c = insertNode(c, 10);
    c = insertNode(c, 2);
    c = insertNode(c, 6);
    c = insertNode(c, 18);
    c = insertNode(c, 14);
    c = insertNode(c, 19);
    preOrderTraversalPrint(c);
    printf("Balance factor of the tree is: %d\n", getTreeBalanceFactor(c));
    printf("===TEST_C_END===\n\n");

    printf("===TEST_D_INIT===\n");
    Node *d = newBinSearchTree();
    d = insertNode(d, 12);
    d = insertNode(d, 20);
    d = insertNode(d, 18);
    d = insertNode(d, 14);
    d = insertNode(d, 19);
    preOrderTraversalPrint(d);
    printf("Balance factor of the tree is: %d\n", getTreeBalanceFactor(d));
    printf("===TEST_D_END===\n\n");
    return EXIT_SUCCESS;
}

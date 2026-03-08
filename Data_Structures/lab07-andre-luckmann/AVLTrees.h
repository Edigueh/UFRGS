#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Node represents a node from a balanced AVL BST.
typedef struct Node {
    int info;
    int bf;
    struct Node *left;
    struct Node *right;
} Node;

// newBinSearchTree initializes an empty binary search tree.
Node* newBinSearchTree(void);

// singleRightRotate is used when a node is inserted into the left subtree of the left child,
// causing the balance factor to become more than +1.
Node* singleRightRotate(Node *r);

// singleLeftRotate is used when a node is inserted into the right subtree of the right child,
// making the balance factor less than -1.
Node* singleLeftRotate(Node *r);

// doubleRightRotate is used when a node is inserted into the right subtree of the left child,
// which disturbs the balance factor of an ancestor node, making it left-heavy.
// It performs a left rotation on the left child, followed by a right rotation on the node.
Node* doubleRightRotate(Node *r);

// doubleLeftRotate is used when a node is inserted into the left subtree of the right child,
// which disturbs the balance factor of an ancestor node, making it right-heavy.
// It performs a right rotation on the right child, followed by a left rotation on the node.
Node* doubleLeftRotate(Node *r);

// insertNode inserts a new node with newInfo in the given *r binary search tree.
Node* insertNode(Node *r, int newInfo);

// insertNode inserts a node in an AVL tree.
Node* insertNodeAVL(Node *r, int newInfo, bool *ok);

// height returns the height of the given node.
int height(Node *r);

// preOrderTraversalPrint prints the given binary tree in following the Pre Order Traversal algorithm.
void preOrderTraversalPrint(Node *r);

// getBalanceFactor returns the balance factor of the given node.
// this is given by leftHeight - rightHeight.
int getBalanceFactor(Node *r);

// getTreeBalanceFactor returns the balance factor of the tree, which is the biggest balance factor of the tree's nodes.
int getTreeBalanceFactor(Node *r);

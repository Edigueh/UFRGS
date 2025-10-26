#include "info.h"

// BstNode represents a node in a binary tree.
typedef struct BstNode {
    NodeInfo info;
    struct BstNode *left, *right;
} BstNode;

// newBinSearchTree initializes an empty binary search tree.
BstNode* newBinSearchTree(void);

// iterativeBSTQuery iteratively queries the given binary search tree for the target value.
// Returns the desired node containing this value, otherwise returns NULL.
BstNode* iterativeBSTQuery(BstNode *r, char *target);

// recursiveBSTQuery recursively queries the given binary search tree for the target value.
// Returns the desired node containing this value, otherwise returns NULL.
BstNode* recursiveBSTQuery(BstNode *r, char *target);

// insertNode inserts a new node with newInfo in the given *r binary search tree.
BstNode* insertBstNode(BstNode *r, NodeInfo newInfo);

// removeNode removes the first node found containing the target node in the given *r binary search tree. 
// If the node is not found in the given tree, returns NULL.
BstNode* removeBstNode(BstNode *r, char *target);

// preOrderTraversalPrint prints the given binary tree in following the Pre Order Traversal algorithm.
void bstPreOrderTraversalPrint(BstNode *r);

// countBSTNodes counts the nodes in the given binary tree.
int countBSTNodes(BstNode *r);

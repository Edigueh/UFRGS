#include <stdbool.h>

#include "info.h"

// AvlNode represents a node from a balanced AVL Tree.
typedef struct AvlNode {
    NodeInfo info;
    int bf;
    struct AvlNode *left;
    struct AvlNode *right;
} AvlNode;

// singleRightRotate is used when a node is inserted into the left subtree of the left child,
// causing the balance factor to become more than +1.
AvlNode* singleRightRotate(AvlNode *r);

// singleLeftRotate is used when a node is inserted into the right subtree of the right child,
// making the balance factor less than -1.
AvlNode* singleLeftRotate(AvlNode *r);

// doubleRightRotate is used when a node is inserted into the right subtree of the left child,
// which disturbs the balance factor of an ancestor node, making it left-heavy.
// It performs a left rotation on the left child, followed by a right rotation on the node.
AvlNode* doubleRightRotate(AvlNode *r);

// doubleLeftRotate is used when a node is inserted into the left subtree of the right child,
// which disturbs the balance factor of an ancestor node, making it right-heavy.
// It performs a right rotation on the right child, followed by a left rotation on the node.
AvlNode* doubleLeftRotate(AvlNode *r);

// insertNode inserts a node in an AVL tree.
AvlNode* insertAvlNode(AvlNode *r, NodeInfo newInfo, bool *ok);

// height returns the height of the given node.
int height(AvlNode *r);

// preOrderTraversalPrint prints the given binary tree in following the Pre Order Traversal algorithm.
void preOrderTraversalPrint(AvlNode *r);

// getBalanceFactor returns the balance factor of the given node.
// this is given by leftHeight - rightHeight.
int getBalanceFactor(AvlNode *r);

// getTreeBalanceFactor returns the balance factor of the tree, which is the biggest balance factor of the tree's nodes.
int getTreeBalanceFactor(AvlNode *r);

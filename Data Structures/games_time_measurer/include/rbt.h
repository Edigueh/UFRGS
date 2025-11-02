#ifndef RBT_H
#define RBT_H
#include <stdbool.h>

#include "info.h"

#define BLACK false
#define RED true

/*
* 1. Every node is either red or black.
* 2. All null nodes are considered black.
* 3. A red node does not have a red child.
* 4. Every path from a given node to any of its leaf nodes (that is, to any descendant null node) goes through the same number of black nodes.
* 5. (Conclusion) If a node N has exactly one child, the child must be red. If the child were black, its leaves would sit at a different black depth 
*    than N's null node (which is considered black by rule 2), violating requirement 4.
*/
typedef struct RbtNode {
    NodeInfo info;
    bool color;
    struct RbtNode *left, *right;
} RbtNode;

// newRedBlackTree initializes an empty red black tree.
RbtNode* newRedBlackTree(void);

// insertRBT inserts a new node with newInfo and re-balances the tree
// to maintain RBT properties.
RbtNode* insertRbtNode(RbtNode *r, NodeInfo newInfo);

// isRed tells if a node is red or black.
bool isRed(RbtNode *n);

// preOrderTraversalPrint prints the given binary tree in following the Pre Order Traversal algorithm.
void rbtPreOrderTraversalPrint(RbtNode *r);
#endif

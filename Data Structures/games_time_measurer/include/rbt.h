#include <stdbool.h>

#include "info.h"

#define BLACK false
#define RED true

// RbtNode represents a node in a binary tree.
typedef struct RbtNode {
    NodeInfo info;
    bool color;
    struct RbtNode *left, *right;
} RbtNode;

// newRedBlackTree initializes an empty red black tree.
RbtNode* newRedBlackTree(void);

// // iterativeRBTQuery iteratively queries the given red black tree for the target value.
// // Returns the desired node containing this value, otherwise returns NULL.
// RbtNode* iterativeRBTQuery(RbtNode *r, int target);

// // recursiveRBTQuery recursively queries the given red black tree for the target value.
// // Returns the desired node containing this value, otherwise returns NULL.
// RbtNode* recursiveRBTQuery(RbtNode *r, int target);

// insertRBT inserts a new node with newInfo and re-balances the tree
// to maintain RBT properties.
RbtNode* insertRbtNode(RbtNode *r, NodeInfo newInfo);

// isRed tells if a node is red or black.
bool isRed(RbtNode *n);

// preOrderTraversalPrint prints the given binary tree in following the Pre Order Traversal algorithm.
void rbtPreOrderTraversalPrint(RbtNode *r);

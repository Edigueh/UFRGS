#include <stdbool.h>

#define BLACK false
#define RED true

// Node represents a node in a binary tree.
typedef struct Node {
    int info;
    struct Node *left, *right;
    bool color;
} Node;

// newRedBlackTree initializes an empty red black tree.
Node* newRedBlackTree(void);

// iterativeRBTQuery iteratively queries the given red black tree for the target value.
// Returns the desired node containing this value, otherwise returns NULL.
Node* iterativeRBTQuery(Node *r, int target);

// recursiveRBTQuery recursively queries the given red black tree for the target value.
// Returns the desired node containing this value, otherwise returns NULL.
Node* recursiveRBTQuery(Node *r, int target);

// insertRBT inserts a new node with newInfo and re-balances the tree
// to maintain RBT properties.
Node* insertRBT(Node *r, int newInfo);

// removeRBT is a placeholder. A true RBT deletion is extremely complex.
// This version just calls the standard BST removeNode.
Node* removeRBT(Node *r, int target);

#include <stdbool.h>

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

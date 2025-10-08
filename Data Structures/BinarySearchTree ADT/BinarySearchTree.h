
typedef struct Node {
    int info;
    struct Node *left, *right;
} Node;

// newBinSearchTree initializes an empty binary search tree.
Node* newBinSearchTree(void);

// iterativeBSTQuery iteratively queries the given binary search tree for the target value.
// Returns the desired node containing this value, otherwise returns NULL.
Node* iterativeBSTQuery(Node *r, int target);

// recursiveBSTQuery recursively queries the given binary search tree for the target value.
// Returns the desired node containing this value, otherwise returns NULL.
Node* recursiveBSTQuery(Node *r, int target);

// insertNode inserts a new node with newInfo in the given *r binary search tree.
Node* insertNode(Node *r, int newInfo);

// removeNode removes the first node found containing the target node in the given *r binary search tree. 
// If the node is not found in the given tree, returns NULL.
Node* removeNode(Node *r, int target);

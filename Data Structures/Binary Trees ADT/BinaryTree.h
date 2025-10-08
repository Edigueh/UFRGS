
typedef struct Node {
    int info;
    struct Node *left, *right;
} Node;

// newTree initializes an empty binary tree.
Node* newBinTree(void);

// insertRoot allocates the root node and inserts the info into it.
Node* insertRoot(Node *root, int info);

// insertLeft inserts a node in the subtree at left of the given node.
Node* insertLeft(Node *node, int info, int parentInfo);

// insertRight inserts a node in the subtree at right of the given node.
Node* insertRight(Node *node, int info, int parentInfo);

// preOrderTraversal traverses a binary tree following the Pre Order Traversal algorithm.
void preOrderTraversal(Node *r);

// inOrderTraversal traverses a binary tree following the In Order Traversal algorithm.
void inOrderTraversal(Node *r);

// postOrderTraversal traverses a binary tree following the Post Order Traversal algorithm.
void postOrderTraversal(Node *r);

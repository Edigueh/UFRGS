#include <stdlib.h>
#include "RedBlackTree.h"

Node* newRedBlackTree(void) {
    return NULL;
}

Node* iterativeRBTQuery(Node *r, int target) {
    while (r != NULL) {
        if (r->info == target) {
            return r;
        }

        if (r->info > target) {
            r = r->left;
        } else {
            r = r->right;
        }
    }

    return NULL;
}

Node* recursiveRBTQuery(Node *r, int target) {
    if (r == NULL) {
        return NULL;
    }

    if (r->info == target) {
        return r;
    }

    if (r->info > target) {
        return recursiveBSTQuery(r->left, target);
    }

    return recursiveBSTQuery(r->right, target);
}

// Helper function to find the biggest node (in-order predecessor).
Node* biggest(Node *r) {
    if (r != NULL) {
        while (r->right != NULL) {
            r = r->right;
        }
    }

    return r;
}

// Helper: smallest node (in-order successor)
Node* smallest(Node *r) {
    if (r != NULL) {
        while (r->left != NULL) r = r->left;
    }
    return r;
}

// A helper to check color, treating NULL nodes as BLACK
bool isRed(Node *n) {
    if (n == NULL) {
        return BLACK;
    }
    return n->color == RED;
}

Node* singleLeftRotate(Node *r) {
    Node *newRoot = r->right;
    r->right = newRoot->left;
    newRoot->left = r;

    newRoot->color = r->color;
    r->color = RED;

    return newRoot;
}

Node* singleRightRotate(Node *r) {
    Node *newRoot = r->left;
    r->left = newRoot->right;
    newRoot->right = r;

    newRoot->color = r->color; 
    r->color = RED;

    return newRoot;
}

void flipColors(Node *r) {
    r->color = RED;
    r->left->color = BLACK;
    r->right->color = BLACK;
}

Node* balance(Node *r) {
    // Case 1: Right child is RED (fix left-leaning).
    if (isRed(r->right) && !isRed(r->left)) {
        r = singleLeftRotate(r);
    }

    // Case 2: Left child and Left-Left child are RED (fix 4-node).
    if (isRed(r->left) && isRed(r->left->left)) {
        r = singleRightRotate(r);
    }

    // Case 3: Both children are RED (split 4-node).
    if(isRed(r->left) && isRed(r->right)) {
        flipColors(r);
    }

    return r;
}

// moveRedLeft: Assuming r is RED and both r->left and r->left->left
// are BLACK, make r->left or one of its children RED.
Node* moveRedLeft(Node *r) {
    flipColors(r);

    if (r->right && isRed(r->right->left)) {
        r->right = singleRightRotate(r->right);
        r = singleLeftRotate(r);
        flipColors(r);
    }

    return r;
}

// moveRedRight: Assuming r is RED and both r->right and r->right->left
// are BLACK, make r->right or one of its children RED.
Node* moveRedRight(Node *r) {
    flipColors(r);

    if(r->left && isRed(r->left->left)) {
        r = singleRightRotate(r);
        flipColors(r);
    }
    
    return r;
}

Node* deleteMin(Node* r) {
    if (r->left == NULL) {
        free(r);
        return NULL;
    }

    if (!isRed(r->left) && !isRed(r->left->left)) {
        r = moveRedLeft(r);
    }

    r->left = deleteMin(r->left);

    return balance(r);
}

Node* insertRBTRecursive(Node *r, int newInfo) {
    if (r == NULL) {
        r = (Node*)malloc(sizeof(Node));
        r->info = newInfo;
        r->left = NULL;
        r->right = NULL;
        r->color = RED;
        return r;
    }

    if (r->info < newInfo) {
        r->right = insertRBTRecursive(r->right, newInfo);
    } else {
        r->left = insertRBTRecursive(r->left, newInfo);
    }

    return balance(r);
}

Node* insertRBT(Node *r, int newInfo) {
    r = insertRBTRecursive(r, newInfo);
    r->color = BLACK;
    return r;
}

Node* removeRBTRecursive(Node *r, int target) {
    if (r == NULL) {
        return NULL;
    }

    if (target < r->info) {
        // If left child is not a 3-node, make it one.
        if (!isRed(r->left) && r->left && !isRed(r->left->left)) {
            r = moveRedLeft(r);
        }

        r->left = removeRBTRecursive(r->left, target);
    } else {
        // Make sure left-leaning property is OK.
        if (isRed(r->left)) {
            r = singleRightRotate(r);
        }

        // If this is the node to delete AND its right child is NULL,
        // it means this node is a leaf (or has one left child,
        // which has been rotated right). Since RED has been pushed down,
        // this node must be RED. So, just delete it.
        if (target == r->info && r->right == NULL) {
            free(r);
            return NULL;
        }

        // If right child is not a 3-node, make it one.
        if (!isRed(r->right) && r->right && !isRed(r->right->left)) {
            r = moveRedRight(r);
        }

        if (target == r->info) {
            // Found the node, but it has two children.
            // Find the successor (smallest in the right subtree).
            Node *successor = smallest(r->right);

            // Replace this node's info with the successor's.
            r->info = successor->info;

            // Now, delete the successor from the right subtree.
            r->right = deleteMin(r->right);
        } else {
            // Not the node, continue searching right.
            r->right = removeRBTRecursive(r->right, target);
        }
    }

    // After the recursive call returns, fix any violations.
    return balance(r);
}

Node* removeRBT(Node *r, int target) {
    if (r == NULL) {
        return NULL;
    }

    r = removeRBTRecursive(r, target);

    if (r != NULL) {
        r->color = BLACK;
    }

    return r;
}

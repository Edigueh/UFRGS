#include <stdlib.h>
#include "BinarySearchTree.h"

Node* newBinSearchTree(void) {
    return NULL;
}

Node* iterativeBSTQuery(Node *r, int target) {
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

Node* recursiveBSTQuery(Node *r, int target) {
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

Node* insertNode(Node *r, int newInfo) {
    // Base case: given node is empty.
    if (r == NULL) {
        r = (Node*)malloc(sizeof(Node));
        r->info = newInfo;
        r->left = NULL;
        r->right = NULL;
    } else {
        if (newInfo < r->info) {
            // Repeat for the subtree on the left.
            r->left = insertNode(r->left, newInfo);
        } else {
            // Repeat for the subtree on the right.
            r->right = insertNode(r->right, newInfo);
        }
    }

    return r;
}

Node* biggest(Node *r) {
    if (r != NULL) {
        while (r->right != NULL) {
            r = r->right;
        }
    }

    return r;
}

Node* removeNode(Node *r, int target) {
    // Base case: given node is empty.
    if (r == NULL) {
        printf("Target not found.\n");
    } else if (r->info > target) {
        // Repeat for the subtree on the left.
        r->left = removeNode(r->left, target);
    } else if (r->info < target) {
        // Repeat for the subtree on the right.
        r->right = removeNode(r->right, target);
    } else { // Target node is found.
        Node *tmpNode;
        if (r->left && r->right) { // Target has two subtrees.
            // Replace it with the biggest value from the left subtree (biggest of the smallests).

            // Find biggest node in left subtree.
            tmpNode = biggest(r->left);

            // Replace the target node with the biggest value from the left subtree.
            r->info = tmpNode->info;

            // Remove the duplicated biggest value from the left subtree.
            r->left = removeNode(r->left, r->info);
        } else { // Target has one or none subtree.
            tmpNode = r;
            if (r->left == NULL) {
                // Replace with the right child, if it has no childrens, replace with NULL.
                r = r->right;
            } else if (r->right == NULL) {
                // Replace with left child.
                r = r->left;
            }
            free(tmpNode);
        }
    }

    return r;
}

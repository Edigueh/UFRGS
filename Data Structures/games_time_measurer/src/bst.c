#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bst.h"

BstNode* newBinSearchTree(void) {
    return NULL;
}

BstNode* iterativeBSTQuery(BstNode *r, char *target) {
    while (r != NULL) {
        if (strcasecmp(r->info.name, target) == 0) {
            return r;
        }

        if (strcasecmp(r->info.name, target) > 0) {
            r = r->left;
        } else {
            r = r->right;
        }
    }

    return NULL;
}

BstNode* recursiveBSTQuery(BstNode *r, char *target) {
    if (r == NULL) {
        return NULL;
    }

    if (strcasecmp(r->info.name, target) == 0) {
        return r;
    }

    if (strcasecmp(r->info.name, target) > 0) {
        return recursiveBSTQuery(r->left, target);
    }

    return recursiveBSTQuery(r->right, target);
}

BstNode* insertBstNode(BstNode *r, NodeInfo newInfo) {
    // Base case: given node is empty.
    if (r == NULL) {
        r = (BstNode*)malloc(sizeof(BstNode));
        r->info = newInfo;
        r->left = NULL;
        r->right = NULL;
    } else {
        if (strcasecmp(newInfo.name, r->info.name) < 0) {
            // Repeat for the subtree on the left.
            r->left = insertBstNode(r->left, newInfo);
        } else {
            // Repeat for the subtree on the right.
            r->right = insertBstNode(r->right, newInfo);
        }
    }

    return r;
}

BstNode* biggest(BstNode *r) {
    if (r != NULL) {
        while (r->right != NULL) {
            r = r->right;
        }
    }

    return r;
}

BstNode* removeBstNode(BstNode *r, char *target) {
    // Base case: given node is empty.
    if (r == NULL) {
        printf("Target not found.\n");
    } else if (strcasecmp(r->info.name, target) > 0) {
        // Repeat for the subtree on the left.
        r->left = removeBstNode(r->left, target);
    } else if (strcasecmp(r->info.name, target) < 0) {
        // Repeat for the subtree on the right.
        r->right = removeBstNode(r->right, target);
    } else { // Target node is found.
        BstNode *tmpNode;
        if (r->left && r->right) { // Target has two subtrees.
            // Replace it with the biggest value from the left subtree (biggest of the smallests).

            // Find biggest node in left subtree.
            tmpNode = biggest(r->left);

            // Replace the target node with the biggest value from the left subtree.
            r->info = tmpNode->info;

            // Remove the duplicated biggest value from the left subtree.
            r->left = removeBstNode(r->left, r->info.name);
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

void bstPreOrderTraversalIndented(BstNode *r, int level) {
    if (r != NULL) {
        for (int i = 0; i < level; i++) {
            printf("=");
        }
        printf("%s\n", r->info.name);
        bstPreOrderTraversalIndented(r->left, level + 1);
        bstPreOrderTraversalIndented(r->right, level + 1);
    }
}

void bstPreOrderTraversalPrint(BstNode *r) {
    bstPreOrderTraversalIndented(r, 1);
}

int countBSTNodes(BstNode *r) {
    if (r == NULL) {
        return 0;
    }

    return 1 + countBSTNodes(r->left) + countBSTNodes(r->right);
}
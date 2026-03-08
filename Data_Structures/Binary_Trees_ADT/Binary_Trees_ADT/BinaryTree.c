#include <stdlib.h>
#include "BinaryTree.h"

Node* newBinTree(void) {
    return NULL;
}

Node* insertRoot(Node *root, int info) {
    if (root == NULL) {
        root = (Node*) malloc(sizeof(Node));
        root->info = info;
        root->left = NULL;
        root->right = NULL;
    }

    return root;
}

void preOrderTraversal(Node *r) {
    if (r != NULL) {
        printf("%d\n", r->info);
        preOrderTraversal(r->left);
        preOrderTraversal(r->right);
    }
}

void inOrderTraversal(Node *r) {
    if (r != NULL) {
        preOrderTraversal(r->left);
        printf("%d\n", r->info);
        preOrderTraversal(r->right);
    }
}

void postOrderTraversal(Node *r) {
    if (r != NULL) {
        preOrderTraversal(r->left);
        preOrderTraversal(r->right);
        printf("%d\n", r->info);
    }
}
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rbt.h"
#include "utils.h"

int rbtComp = 0, rbtRotations = 0;

RbtNode* newRedBlackTree(void) {
    return NULL;
}

bool isRed(RbtNode *n) {
    if (n == NULL) {
        return BLACK;
    }
    return n->color == RED;
}

RbtNode* rotateLeft(RbtNode *r) {
    RbtNode *newRoot = r->right;
    r->right = newRoot->left;
    newRoot->left = r;

    newRoot->color = r->color;
    r->color = RED;

    return newRoot;
}

RbtNode* rotateRight(RbtNode *r) {
    RbtNode *newRoot = r->left;
    r->left = newRoot->right;
    newRoot->right = r;

    newRoot->color = r->color; 
    r->color = RED;

    return newRoot;
}

void flipColors(RbtNode *r) {
    r->color = RED;
    r->left->color = BLACK;
    r->right->color = BLACK;
}

RbtNode* balance(RbtNode *r) {
    // Case 1: Right child is RED (fix left-leaning).
    if (isRed(r->right) && !isRed(r->left)) {
        rbtRotations++;
        r = rotateLeft(r);
    }

    // Case 2: Left child and Left-Left child are RED (fix 4-node).
    if (isRed(r->left) && isRed(r->left->left)) {
        rbtRotations++;
        r = rotateRight(r);
    }

    // Case 3: Both children are RED (split 4-node).
    if(isRed(r->left) && isRed(r->right)) {
        flipColors(r);
    }

    return r;
}

RbtNode* insertRBTRecursive(RbtNode *r, NodeInfo newInfo) {
    if (r == NULL) {
        r = (RbtNode*)malloc(sizeof(RbtNode));
        r->info = newInfo;
        r->left = NULL;
        r->right = NULL;
        r->color = RED;
        return r;
    }

    if (strcasecmp(newInfo.name, r->info.name) < 0) {
        r->left = insertRBTRecursive(r->left, newInfo);
    } else {
        r->right = insertRBTRecursive(r->right, newInfo);
    }

    return balance(r);
}

RbtNode* insertRbtNode(RbtNode *r, NodeInfo newInfo) {
    r = insertRBTRecursive(r, newInfo);
    r->color = BLACK;
    return r;
}

void rbtPreOrderTraversalIndented(RbtNode *r, int level) {
    if (r != NULL) {
        for (int i = 0; i < level; i++) {
            printf("=");
        }
        printf("%s\n", r->info.name);
        rbtPreOrderTraversalIndented(r->left, level + 1);
        rbtPreOrderTraversalIndented(r->right, level + 1);
    }
}

void rbtPreOrderTraversalPrint(RbtNode *r) {
    rbtPreOrderTraversalIndented(r, 1);
}

int countRbtNodes(RbtNode *r) {
    if (r == NULL) {
        return 0;
    }

    return 1 + countRbtNodes(r->left) + countRbtNodes(r->right);
}

int rbtHeight(RbtNode *r) {
    if (r == NULL) {
        return 0;
    }

    int leftHeight = rbtHeight(r->left);
    int rightHeight = rbtHeight(r->right);

    return 1 + max(leftHeight, rightHeight);
}

void rbtWriteStats(FILE *output, RbtNode *r) {
    fprintf(output, "============ RBT STATS ============\n");
    fprintf(output, "Node count: %d\n", countRbtNodes(r));
    fprintf(output, "Height: %d\n", rbtHeight(r));
    fprintf(output, "Rotation count: %d\n", rbtRotations);
    fprintf(output, "Comparisons: %d\n", rbtComp);
    fprintf(output, "===================================\n");
    return;
}

RbtNode* queryRbt(RbtNode *r, char *target) {
    while (r != NULL){
        rbtComp++;
        if (!strcasecmp(r->info.name, target)){
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

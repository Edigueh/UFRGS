#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "avl.h"

// max is a helper function that returns the max value between two integers.
int max(int a, int b) {
    return (a > b) ? a : b;
}

AvlNode* newAvlTree(void) {
    return NULL;
}

// rebalanceLeft handles a left-heavy imbalance at node r.
AvlNode* rebalanceLeft(AvlNode *r, bool *ok) {
    AvlNode *leftTree = r->left;

    if (leftTree->bf == 1) {
        // Left-Left case (- -).
        r = singleRightRotate(r);
    } else {
        // Left-Right case (- +).
        r = doubleRightRotate(r);
    }

    *ok = false;
    return r;
}

// rebalanceRight handles a right-heavy imbalance at node r.
AvlNode* rebalanceRight(AvlNode *r, bool *ok) {
    AvlNode *rightTree = r->right;

    if (rightTree->bf == -1) {
        // Right-Right case (+ +).
        r = singleLeftRotate(r);
    } else {
        // Right-Left case (+ -).
        r = doubleLeftRotate(r);
    }

    *ok = false;
    return r;
}

AvlNode* singleRightRotate(AvlNode *r) {
    AvlNode *newRoot = r->left;
    r->left = newRoot->right;
    newRoot->right = r;

    // A single rotation during insertion always results in two balanced nodes.
    r->bf = 0;
    newRoot->bf = 0;

    return newRoot;
}

AvlNode* singleLeftRotate(AvlNode *r) {
    AvlNode *newRoot = r->right;
    r->right = newRoot->left;
    newRoot->left = r;

    // A single rotation during insertion always results in two balanced nodes.
    r->bf = 0;
    newRoot->bf = 0;

    return newRoot;
}

AvlNode* doubleRightRotate(AvlNode *r) {
    AvlNode *leftTree = r->left;
    AvlNode *newRoot = leftTree->right;

    // Left rotation on the left child.
    leftTree->right = newRoot->left;
    newRoot->left = leftTree;

    // Right rotation on the node.
    r->left = newRoot->right;
    newRoot->right = r;

    // Update balance factors for all three affected nodes.
    if (newRoot->bf == 1) r->bf = -1; else r->bf = 0;
    if (newRoot->bf == -1) leftTree->bf = 1; else leftTree->bf = 0;
    newRoot->bf = 0; // New root is always balanced.

    return newRoot;
}

AvlNode* doubleLeftRotate(AvlNode *r) {
    AvlNode *rightTree = r->right;
    AvlNode *newRoot = rightTree->left;

    // Right rotation on the right child.
    rightTree->left = newRoot->right;
    newRoot->right = rightTree;

    // Left rotation on the node.
    r->right = newRoot->left;
    newRoot->left = r;

    // Update balance factors for all three affected nodes.
    if (newRoot->bf == -1) r->bf = 1; else r->bf = 0;
    if (newRoot->bf == 1) rightTree->bf = -1; else rightTree->bf = 0;
    newRoot->bf = 0; // New root is always balanced.

    return newRoot;
}

AvlNode* insertAvlNode(AvlNode *r, NodeInfo newInfo, bool *ok) {
    if (r == NULL) {
        r = (AvlNode*)malloc(sizeof(AvlNode));
        r->info = newInfo;
        r->left = NULL;
        r->right = NULL;
        r->bf = 0;
        *ok = true; // Sign that height has increased.
    } else if (strcasecmp(newInfo.name, r->info.name) < 0) {
        r->left = insertAvlNode(r->left, newInfo, ok);
        if (*ok) { // If left subtree grew...
            switch (r->bf) {
                case -1: r->bf = 0; *ok = false; break;  // Was right-heavy, now balanced.
                case 0: r->bf = 1; break;                // Was balanced, now left-heavy.
                case 1: r = rebalanceLeft(r, ok); break; // Was left-heavy, now imbalanced.
            }
        }
    } else {
        r->right = insertAvlNode(r->right, newInfo, ok);
        if (*ok) { // If right subtree grew...
            switch (r->bf) {
                case 1: r->bf = 0; *ok = false; break;     // Was left-heavy, now balanced.
                case 0: r->bf = -1; break;                 // Was balanced, now right-heavy.
                case -1: r = rebalanceRight(r, ok); break; // Was right-heavy, now imbalanced.
            }
        }
    }

    return r;
}

int height(AvlNode *r) {
    if (r == NULL) {
        return 0;
    }

    int leftHeight = height(r->left);
    int rightHeight = height(r->right);

    return 1 + max(leftHeight, rightHeight);
}

void avlPreOrderTraversalIndented(AvlNode *r, int level) {
    if (r != NULL) {
        for (int i = 0; i < level; i++) {
            printf("=");
        }
        printf("%s\n", r->info.name);
        avlPreOrderTraversalIndented(r->left, level + 1);
        avlPreOrderTraversalIndented(r->right, level + 1);
    }
}

void avlPreOrderTraversalPrint(AvlNode *r) {
    avlPreOrderTraversalIndented(r, 1);
}

int getBalanceFactor(AvlNode *r) {
    if (r == NULL) {
        return 0;
    }

    return abs(height(r->left) - height(r->right));
}

int getTreeBalanceFactor(AvlNode *r) {
    if (r == NULL) {
        return 0;
    }

    int rootBf = getBalanceFactor(r);
    int rightBf = getTreeBalanceFactor(r->right);
    int leftBf = getTreeBalanceFactor(r->left);

    return max(max(rightBf, leftBf), rootBf);
}

#include "avl.h"
#include "bst.h"
#include "rbt.h"

// Public wrapper function to create the .dot file for AVL Trees.
void avlGenerateDotFile(AvlNode *r, char *filename);

// Public wrapper function to create the .dot file for BSTrees.
void bstGenerateDotFile(BstNode *r, char *filename);

// Public wrapper function to create the .dot file for RBTrees.
void rbtGenerateDotFile(RbtNode *r, char *filename);

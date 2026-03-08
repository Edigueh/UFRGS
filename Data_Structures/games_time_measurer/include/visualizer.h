#ifndef VISUALIZER_H
#define VISUALIZER_H
#include "avl.h"
#include "bst.h"
#include "rbt.h"

#define ENABLE_GENERATE_DOT_FILES false

// generateDotFiles generates the dot files for all trees if enabled to.
void generateDotFiles(BstNode *bst, AvlNode *avl, RbtNode *rbt);
#endif

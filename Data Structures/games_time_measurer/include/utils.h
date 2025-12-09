#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
#include "avl.h"
#include "rbt.h"
// max is a helper function that returns the max value between two integers.
int max(int a, int b);

// buildTrees is a function that build the trees reading the given dataset.
void buildTrees(FILE *dataset, BstNode **bst, AvlNode **avl, RbtNode **rbt);

// isEqualNodeInfo compares 3 nodes from different trees structures 
// and return true if their informations are equal, otherwise false.
bool isEqualNodeInfo(NodeInfo bstInfo, NodeInfo avlInfo, NodeInfo rbtInfo);

// queryTrees queries the given games from playerWishlist in the given trees.
// It returns the total estimate time for playing all games in wishlist.
float queryTrees(FILE *playerWishlist, BstNode **bst, AvlNode **avl, RbtNode **rbt);
#endif

#include "avl.h"
#include "bst.h"
#include "rbt.h"
#include "visualizer.h"
#include "utils.h"

#define READ_ACCESS "r"
#define WRITE_ACCESS "w"
#define EXPECTED_INPUTS 4

/*
    int argc: counts the number of given parameters.
    char *argv[]: stores the strings of given parameters.
*/
int main(int argc, char *argv[]) {
    if (argc != EXPECTED_INPUTS) {
        printf("Expected %d parameters but found %d.\n  Correct usage: <dataset.csv> <player_wishlist.txt> <output.txt>\n", EXPECTED_INPUTS, argc);
        return EXIT_FAILURE;
    }

    FILE *dataset        = fopen(argv[1], READ_ACCESS),
         *playerWishlist = fopen(argv[2], READ_ACCESS),
         *output         = fopen(argv[3], WRITE_ACCESS);

    if (dataset == NULL || playerWishlist == NULL || output == NULL) {
        printf("Error on opening one or more files, please check %s, %s or %s!\n", argv[1], argv[2], argv[3]);
        return EXIT_FAILURE;
    }
    
    BstNode *bst = newBinSearchTree();
    AvlNode *avl = newAvlTree();
    RbtNode *rbt = newRedBlackTree();

    buildTrees(dataset, &bst, &avl, &rbt);

    if (ENABLE_GENERATE_DOT_FILES) {
        generateDotFiles(bst, avl, rbt);
    }

    fprintf(output, "Total estimated time for playing all games: %.1f hours\n\n", queryTrees(playerWishlist, &bst, &avl, &rbt));

    bstWriteStats(output, bst);
    avlWriteStats(output, avl);
    rbtWriteStats(output, rbt);

    fclose(dataset);
    fclose(playerWishlist);
    fclose(output);
}

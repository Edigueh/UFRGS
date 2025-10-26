#include <stdio.h>
#include <stdlib.h>

#include "includes/avl.h"
#include "includes/bst.h"

#define READ_ACCESS "r"
#define WRITE_ACCESS "w"
#define EXPECTED_INPUTS 4

/*
    int argc: counts the number of given parameters.
    char *argv[]: stores the strings of given parameters.
*/
int main(int argc, char *argv[]) {
    if (argc != EXPECTED_INPUTS) {
        printf("Expected %d parameters but found %d.\n Correct usage: <dataset.csv> <player_wishlist.txt> <output.txt>\n", EXPECTED_INPUTS, argc);
        return EXIT_FAILURE;
    }

    FILE *dataset = fopen(argv[1], READ_ACCESS), *player_wishlist = fopen(argv[2], READ_ACCESS);
    if (dataset == NULL || player_wishlist == NULL) {
        printf("Error on opening one input files, please check %s or %s!\n", argv[1], argv[2]);
        return EXIT_FAILURE;
    }


}

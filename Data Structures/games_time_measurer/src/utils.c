#include "utils.h"
#include "info.h"

#define MAX_LINE_LENGTH_DATASET 90
#define MAX_LINE_LENGTH_WISHLIST 57

int max(int a, int b) {
    return (a > b) ? a : b;
}

void buildTrees(FILE *dataset, BstNode **bst, AvlNode **avl, RbtNode **rbt) {
    char line[MAX_LINE_LENGTH_DATASET];
    while (fgets(line, MAX_LINE_LENGTH_DATASET, dataset) != NULL) {
        NodeInfo newInfo;
        bool ok;

        char *name = strtok(line, ",");
        float time = strtof(strtok(NULL, ","), NULL);

        newInfo.name = strdup(name);
        newInfo.avg_play_time = time;

        *bst = insertBstNode(*bst, newInfo);
        *avl = insertAvlNode(*avl, newInfo, &ok);
        *rbt = insertRbtNode(*rbt, newInfo);
    }
}

bool isEqualNodeInfo(NodeInfo bstInfo, NodeInfo avlInfo, NodeInfo rbtInfo) {
    bool namesEqual = (!strcasecmp(bstInfo.name, avlInfo.name)) && (!strcasecmp(avlInfo.name, rbtInfo.name));

    bool timesEqual = (bstInfo.avg_play_time == avlInfo.avg_play_time) && (avlInfo.avg_play_time == rbtInfo.avg_play_time);

    return namesEqual && timesEqual;
}

float queryTrees(FILE *playerWishlist, BstNode **bst, AvlNode **avl, RbtNode **rbt) {
    char line[MAX_LINE_LENGTH_WISHLIST];
    int totalEstimateTime = 0;
    while (fgets(line, MAX_LINE_LENGTH_WISHLIST, playerWishlist) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        char *gameName = line;
        size_t len = strlen(gameName);
        if (len >= 2 && gameName[0] == '"' && gameName[len-1] == '"') {
            gameName[len-1] = '\0';
            gameName++;
        }

        BstNode *bstResult = queryBst(*bst, gameName);
        AvlNode *avlResult = queryAvl(*avl, gameName);
        RbtNode *rbtResult = queryRbt(*rbt, gameName);

        if (bstResult == NULL || avlResult == NULL || rbtResult == NULL) {
            printf("WARN: Game '%s' not found in one or more trees!\n", gameName);
            continue;
        }

        if (isEqualNodeInfo(bstResult->info, avlResult->info, rbtResult->info)){
            totalEstimateTime += bstResult->info.avg_play_time;
        }
    }
    return totalEstimateTime;
}

#ifndef INFO_H
#define INFO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// NodeInfo defines the domain specific information that each node will contain.
typedef struct NodeInfo {
    char *name;
    float avg_play_time;
} NodeInfo;
#endif

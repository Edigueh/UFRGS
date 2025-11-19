#include <stdlib.h>
#include "Queue.h"

Queue* initQueue(void) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last = NULL;

    return queue;
}

bool isEmpty(Queue *queue) {
    if (!queue) {
        return -1;
    } else if (queue->first == NULL) {
        return true;
    }

    return false;
}

bool enqueue(Queue **queue, int newInfo) {
    Node *new;
    if (*queue) {
        new = (Node*)malloc(sizeof(Node));
        new->info = newInfo;
        new->next = NULL;
        if (isEmpty(*queue)) {
            (*queue)->first = new;
        } else {
            (*queue)->last->next = new;
        }

        (*queue)->last = new;
        return true;
    }

    return false;
}

bool dequeue(Queue **queue, int *data) {
    Node *curr;
    if (*queue) {
        if (!isEmpty(*queue)){
            curr = (*queue)->first;
            *data = (*queue)->first->info;
            (*queue)->first = (*queue)->first->next;
            free(curr);
            if ((*queue)->first == NULL) {
                (*queue)->last = NULL;
            }

            return true;
        }
    }

    return false;
}

int queryQueue(Queue *queue) {
    if (isEmpty(queue)) {
        return -1;
    }

    return queue->first->info;
}

void destroyQueue(Queue **queue) {
    Node *curr;
    if (*queue) {
        while (!isEmpty(*queue)){
            curr = (*queue)->first;
            (*queue)->first = (*queue)->first->next;
            free(curr);
        }
        free(*queue);
        *queue = NULL;
    }
}

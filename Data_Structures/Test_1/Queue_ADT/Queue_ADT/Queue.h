#include <stdbool.h>
#include "Info/Info.h"

typedef struct Queue{
    Node *first, *last;
} Queue;

// initQueue creates an empty queue.
Queue* initQueue(void);

// isEmpty checks if the given stack is empty.
bool isEmptyQueue(Queue *queue);

// enqueue inserts a node in the end of the queue.
bool enqueue(Queue **queue, Info newInfo);

// dequeue removes the node in the beginning of the queue.
bool dequeue(Queue **queue, Info *data);

// queryQueue retorns the info at the first of the queue.
Info queryQueue(Queue *queue);

// destroyQueue destroys the queue.
void destroyQueue(Queue **queue);

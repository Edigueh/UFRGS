#include <stdbool.h>

typedef struct Node {
    int info;
    struct Node *next;
} Node;

typedef struct Queue{
    Node *first, *last;
} Queue;

// initQueue creates an empty queue.
Queue* initQueue(void);

// isEmpty checks if the given stack is empty.
bool isEmpty(Queue *queue);

// enqueue inserts a node in the end of the queue.
bool enqueue(Queue **queue, int newInfo);

// dequeue removes the node in the beginning of the queue.
bool dequeue(Queue **queue, int *data);

// queryQueue retorns the info at the first of the queue.
int queryQueue(Queue *queue);

// destroyQueue destroys the queue.
void destroyQueue(Queue **queue);

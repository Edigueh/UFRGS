#include <stdbool.h>

typedef struct {
    int id;
} Info;

typedef struct Node {
    Info info;
    struct Node* next;
} Node;

typedef struct Queue{
    Node *first, *last;
} Queue;

// initQueue creates an empty queue.
Queue* initQueue(void);

// isEmpty checks if the given stack is empty.
bool isEmpty(Queue *queue);

// push inserts a node in the end of the queue.
bool push(Queue **queue, Info newInfo);

// pop removes the node in the beginning of the queue.
bool pop(Queue **queue, Info *data);

// queryQueue retorns the info at the first of the queue.
Info queryQueue(Queue *queue);

// destroyQueue destroys the queue.
void destroyQueue(Queue **queue);

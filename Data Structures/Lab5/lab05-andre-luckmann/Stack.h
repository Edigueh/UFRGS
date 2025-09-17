#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
} Info;

typedef struct Node {
    Info info;
    struct Node *next;
} Node;

typedef struct Node Stack;

// initStack creates an empty stack.
Stack* initStack(void);

// isEmpty checks if the given stack is empty.
bool isEmpty(Stack *top);

// push inserts a node in the top of the stack.
Stack* push(Stack *top, Info newInfo);

// pop removes the node in the top of the stack.
bool pop(Stack **top, Info *data);

// queryStack retorns the info at the top of the stack.
Info queryStack(Stack *top);

// destroyStack destroys the stack.
Stack* destroyStack(Stack *top);

// printStack prints a stack.
void printStack(Stack *top);

// equal compares two stacks, returns true if they are equal, otherwise false.
bool equal(Stack *s1, Stack *s2);

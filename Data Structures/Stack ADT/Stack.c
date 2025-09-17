#include <stdlib.h>
#include "Stack.h"

Stack* initStack(void) {
    return NULL;
}

bool isEmpty(Stack *top) {
    if (top == NULL) {
        return true;
    }
    return false;
}

Stack* push(Stack *top, Info newInfo) {
    Stack *new = (Stack*)malloc(sizeof(Stack));

    new->info = newInfo;
    new->next = top;

    return new;
}

bool pop(Stack **top, Info *data) {
    if (isEmpty(*top)) {
        return false; 
    }

    Stack* curr;

    *data = (*top)->info;
    curr = *top;
    *top = (*top)->next;
    free(curr);
    curr=NULL;

    return true;
}

Info queryStack(Stack *top) {
    if (isEmpty(top)) {
        return (Info){-1};
    }

    return top->info;
}

Stack* destroyStack(Stack *top) {
    Stack *curr;
    while (top != NULL) {
        curr = top;
        top = top->next;
        free(curr);
    }

    return NULL;
}

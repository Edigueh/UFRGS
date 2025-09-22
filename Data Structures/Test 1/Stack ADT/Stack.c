#include <stdlib.h>
#include "Stack.h"

Stack* initStack(void) {
    return NULL;
}

bool isEmptyStack(Stack *top) {
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

    Stack *curr;

    *data = (*top)->info;
    curr = *top;
    *top = (*top)->next;
    free(curr);
    curr = NULL;

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

void printStack(Stack *top) {
     Stack *curr;

    if (top != NULL) {
        puts("---Printing stack---");
        for (curr=top; curr!=NULL; curr=curr->next) printf("%d\n",curr->info);
        puts("-------End of Stack------");
    } else {
        puts("Pilha vazia");
    }
}

bool equal(Stack *s1, Stack *s2) {
    Info s1Info, s2Info;
    while(pop(&s1, &s1Info) && pop(&s2, &s2Info)) {
        if (s1Info.id != s2Info.id) {
            return false;
        }
    }

    return true;
}
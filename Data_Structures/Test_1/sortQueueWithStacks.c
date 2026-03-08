#include <stdlib.h>
#include "Info/Info.h"
#include "Queue ADT/Queue.h"
#include "Stack ADT/Stack.h"


void sortQueueWithStacks(Queue **q) {
    if (isEmptyQueue(&q)) {
        return;
    }
    
    Stack *s1 = initStack(), *s2 = initStack();
    
    Info data, removal;
    
    // Insert all elements from the queue to the stack 1.
    while(!isEmptyQueue(&q)) {
        dequeue(q, &data);
        s1 = push(s1, data);
    }

    // Iterate through stack 1, removing all its elements.
    while(!isEmptyStack(s1)) {
        pop(&s1, &data);

        // Enquanto a pilha s2 não for vazia e o topo de s2 for maior que o elemento de s1,
        // tira o elemento de s2 e coloca em s1 de volta, para ter a s2 ordenada.
        while(!isEmptyStack(s2) && queryStack(s2).id > data.id) {
            pop(&s2, &removal);
            push(s1, removal);
        }

        // Coloca o elemento em s2 na ordem correta.
        s2 = push(s2, data);
    }

    // Depois, é só tirar os elementos de s2 (já ordenada) e colocar na fila de volta.
    while(!isEmptyStack(s2)) {
        pop(&s2, &data);
        enqueue(q, data);
    }
}

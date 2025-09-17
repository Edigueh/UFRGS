#include "Stack.h"

int main(void) {
    Stack *p1 = initStack(), *p2 = initStack(), *p3 = initStack(), *p4 = initStack();
    Info i1, i2, i3, i4;
    i1.id = 1;
    i2.id = 2;
    i3.id = 3;
    i4.id = 4;

    p1 = push(p1, i1);
    p1 = push(p1, i2);
    p1 = push(p1, i3);
    p1 = push(p1, i4);
    printf("Printando p1:\n");

    printStack(p1);

    p2 = push(p2, i2);
    p2 = push(p2, i3);
    p2 = push(p2, i4);

    printf("Printando p2:\n");
    printStack(p2);

    p3 = push(p3, i4);
    p3 = push(p3, i3);
    p3 = push(p3, i2);
    p3 = push(p3, i1);

    printf("Printando p3:\n");
    printStack(p3);

    p4 = push(p4, i4);
    p4 = push(p4, i3);
    p4 = push(p4, i2);
    p4 = push(p4, i1);

    printf("Printando p4:\n");
    printStack(p4);

    printf("Comparação entre P1 e P2: %d\n", equal(p1, p2));
    printf("Comparação entre P3 e P4: %d\n", equal(p3, p4));
}

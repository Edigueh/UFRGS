#include <stdio.h>
#include "LinkedList.h"

int main(void) {
    Node* list = initLinkedList();

    NodeInfo n = {9};
    list = insertAtHead(list, n);

    printList(list);

    n.id = 3;
    list = insertAtHead(list, n);

    printList(list);

    n.id = 2;
    list = insertAtTail(list, n);

    printList(list);

    n.id = 7;
    list = insertAtMiddle(list, n, 9);

    printList(list);

    n.id = 6;
    list = insertAtMiddle(list, n, 3);

    printList(list);

    Node* foundNode = queryList(list, 2);
    printf("Found node with id: %d\n", foundNode->nodeInfo.id);

    list = removeNodeById(list, 7);

    printList(list);

    list = removeNodeById(list, 9);

    printList(list);

    list = destroyLinkedList(list);

    printList(list);
}

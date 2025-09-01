#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

Node* initLinkedList(void) {
    return NULL;
}

void printList(Node* head) {
    printf("----------------------------\n");
    if (head == NULL) {
        printf("Empty list\n");
        printf("----------------------------\n");
        return;
    }

    for(Node* currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        printf("Código: %d\n", currNode->product.id);
        printf("Nome: %s\n", currNode->product.name);
        printf("Preço: %.2f\n", currNode->product.price);
        printf("\n");
    }
    printf("----------------------------\n");
}

Node* insertProduct(Node* head, Product newProduct) {
    Node* newNode = (Node*)malloc(sizeof(Product));
    newNode->product = newProduct;
    newNode->nextNode = NULL;
    Node *prevNode, *currNode = head;

    if (head == NULL || newNode->product.id < head->product.id) {
        newNode->nextNode = head;
        head = newNode;
        return head;
    }

    while(currNode != NULL && newProduct.id > currNode->product.id) {
        // Update previous node.
        prevNode = currNode;

        // Updates the current node.
        currNode = currNode->nextNode;
    }

    newNode->nextNode = currNode;
    prevNode->nextNode = newNode;

    return head;
}

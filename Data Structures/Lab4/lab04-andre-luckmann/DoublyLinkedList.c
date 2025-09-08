#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"

Node* initLinkedList(void) {
    return NULL;
}

void printList(Node* head) {
    printf("------------Lista-----------\n");
    if (head == NULL) {
        printf("Empty list\n");
        printf("----------------------------\n");
        return;
    }

    for(Node* currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        printf("Código: %d\n", currNode->product.id);
        printf("Nome: %s", currNode->product.name);
        printf("Preço: %.2f\n", currNode->product.price);
        printf("\n");
    }
    printf("----------------------------\n");
}

void printListReverse(Node* head) {
    printf("--------ListaReversa--------\n");
    if (head == NULL) {
        printf("Empty list\n");
        printf("----------------------------\n");
        return;
    }

    Node* tail = head;
    while (tail->nextNode != NULL) {
        tail = tail->nextNode;
    }

    for (Node *currNode = tail; currNode != NULL; currNode = currNode->prevNode) {
        printf("Código: %d\n", currNode->product.id);
        printf("Nome: %s", currNode->product.name);
        printf("Preço: %.2f\n", currNode->product.price);
        printf("\n");
    }
    printf("----------------------------\n");
}

Node* removeProductById(Node* head, int targetId) {
    Node *currNode = head;

    while(currNode != NULL && currNode->product.id != targetId) {
        currNode = currNode->nextNode;
    }

    if (currNode == NULL) {
        // Node was not found in the list.
        return head;
    } else if (currNode->prevNode == NULL){
        // First node is removed.
        head = currNode->nextNode;
    } else {
        // Node is at the middle or the end of the list.
        currNode->prevNode->nextNode = currNode->nextNode;
        currNode->nextNode->prevNode = currNode->prevNode;
    }

    free(currNode);
    return head;
}

Node* destroyLinkedList(Node* head) {
    Node* current = head;
    
    while (current != NULL) {
        Node* nextNode = current->nextNode;
        free(current);
        current = nextNode;
    }

    return NULL;
}

Node* insertProduct(Node* head, Product newProduct) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->product = newProduct;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    if (head == NULL) {
        return newNode;
    }

    if (newNode->product.id < head->product.id) {
        newNode->nextNode = head;
        head->prevNode = newNode;
        return newNode;
    }

    Node *currNode = head;
    while (currNode->nextNode != NULL && newProduct.id > currNode->nextNode->product.id) {
        currNode = currNode->nextNode;
    }
    
    newNode->nextNode = currNode->nextNode;
    if (currNode->nextNode != NULL) {
        currNode->nextNode->prevNode = newNode;
    }
    currNode->nextNode = newNode;
    newNode->prevNode = currNode;
    
    return head;
}

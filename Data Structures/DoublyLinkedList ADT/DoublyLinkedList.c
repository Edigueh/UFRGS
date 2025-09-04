#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"

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

    Node* currNode;
    int i = 1;
    for(currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        printf("Element %d has id=%d\n", i, currNode->nodeInfo.id);
        i++;
    }
    printf("----------------------------\n");
}

Node* queryList(Node* head, int targetId) {
    if (head == NULL) {
        printf("Empty list\n");
        return NULL;
    }

    Node* currNode;
    for(currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        if (currNode->nodeInfo.id == targetId) {
            return currNode;
        }
    }

    return NULL;
}

Node* insertAtHead(Node* head, NodeInfo newNodeInfo) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->nodeInfo = newNodeInfo;
    newNode->nextNode = head;
    newNode->prevNode = NULL;

    if (head != NULL) {
        head->prevNode = newNode;
    }

    return newNode;
}

Node* insertAtTail(Node* head, NodeInfo newNodeInfo) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->nodeInfo = newNodeInfo;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;
    
    if (head == NULL) {
        return newNode;
    }

    Node* currNode = head;
    while (currNode->nextNode != NULL) {
        currNode = currNode->nextNode;
    }

    currNode->nextNode = newNode;
    newNode->prevNode = currNode;

    return head;
}

Node* removeNodeById(Node* head, int targetId) {
    Node *currNode = head;

    while(currNode != NULL && currNode->nodeInfo.id != targetId) {
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

Node* insertSorted(Node* head, NodeInfo newNodeInfo) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->nodeInfo = newNodeInfo;
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;

    if (head == NULL) {
        return newNode;
    }

    if (newNode->nodeInfo.id < head->nodeInfo.id) {
        newNode->nextNode = head;
        head->prevNode = newNode;
        return newNode;
    }

    Node *currNode = head;
    while(currNode != NULL && newNodeInfo.id > currNode->nextNode->nodeInfo.id) {
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

int listLength(Node* head) {
    int i = 0;
    
    for (Node* currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        i++;
    }

    return i;
}

int biggest(Node* head) {
    int max;
    if (head == NULL) {
        return -1;
    }

    max = head->nodeInfo.id;

    for (Node* currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        if (currNode->nodeInfo.id > max) {
            max = currNode->nodeInfo.id;
        }
    }

    return max;
}

Node* removeDuplicates(Node* head) {
    if (head == NULL) {
        return head;
    }

    Node* currNode = head;
    while (currNode != NULL) {
        Node* nodeCheck = currNode->nextNode;
        Node* prevNode = currNode;

        while (nodeCheck != NULL) {
            if (nodeCheck->nodeInfo.id == currNode->nodeInfo.id) {
                Node* nodeToRemove = nodeCheck;

                prevNode->nextNode = nodeToRemove->nextNode;

                if (nodeToRemove->nextNode != NULL) {
                    nodeToRemove->nextNode->prevNode = prevNode;
                }

                nodeCheck = nodeToRemove->nextNode;
                free(nodeToRemove);

            } else {
                prevNode = nodeCheck;
                nodeCheck = nodeCheck->nextNode;
            }
        }
        
        currNode = currNode->nextNode;
    }

    return head;
}

Node* removeOddNumbers(Node* head) {
    if (head == NULL) {
        return head;
    }

    Node* currNode = head;
    while (currNode != NULL) {
        Node* nextNode = currNode->nextNode;

        if (currNode->nodeInfo.id % 2 != 0) {
            if (currNode->prevNode == NULL) {
                head = nextNode;
            } else {
                currNode->prevNode->nextNode = nextNode;
            }

            if (nextNode != NULL) {
                nextNode->prevNode = currNode->prevNode;
            }

            free(currNode);
        }
        
        currNode = nextNode;
    }

    return head;
}

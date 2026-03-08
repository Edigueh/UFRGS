#include <stdio.h>
#include <stdlib.h>
#include "SinglyLinkedList.h"

Node* initLinkedList(void) {
    return NULL;
}

void printList(Node* head) {
    printf("List: ");
    for (Node *n = head; n != NULL; n = n->nextNode) {
        printf("[%d] -> ", n->nodeInfo.id);
    }
    printf("NULL\n");
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
    head = newNode;
    return head;
}

Node* insertAtTail(Node* head, NodeInfo newNodeInfo) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->nodeInfo = newNodeInfo;
    newNode->nextNode = NULL;
    
    if (head == NULL) {
        head = newNode;
        return head;
    }

    Node* currLastNode = head;
    while (currLastNode->nextNode != NULL) {
        currLastNode = currLastNode->nextNode;
    }

    currLastNode->nextNode = newNode;
    return head;
}

Node* insertAtMiddle(Node* head, NodeInfo newNodeInfo, int previousNodeId) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->nodeInfo = newNodeInfo;
    newNode->nextNode = NULL;

    if (head == NULL) {
        head = newNode;
        return head;
    }

    Node* currNode = head;
    while (currNode->nodeInfo.id != previousNodeId && currNode->nextNode != NULL) currNode = currNode->nextNode;

    if (currNode->nextNode == NULL) {
        currNode->nextNode = newNode;
    } else {
        newNode->nextNode = currNode->nextNode;
        currNode->nextNode = newNode;
    }

    return head;
}

Node* removeNodeById(Node* head, int targetId) {
    Node *prevNode = NULL, *currNode = head;

    while(currNode != NULL && currNode->nodeInfo.id != targetId) {
        prevNode = currNode;
        currNode = currNode->nextNode;
    }

    if (currNode == NULL) {
        // Node was not found in the list.
        return head;
    } else if (prevNode == NULL){
        // First node is removed.
        head = currNode->nextNode;
    } else {
        // Node is at the middle or the end of the list.
        prevNode->nextNode = currNode->nextNode;
    }

    free(currNode);
    return head;
}

Node* destroyLinkedList(Node* head) {
    Node* currNode = head;

    while (head != NULL) {
        currNode = head;
        head = currNode->nextNode;
        free(currNode);
    }

    free(head);
    return NULL;
}

Node* insertSorted(Node* head, NodeInfo newNodeInfo) {
    Node* newNode = (Node*)malloc(sizeof(NodeInfo));
    newNode->nodeInfo = newNodeInfo;
    newNode->nextNode = NULL;
    Node *prevNode, *currNode = head;

    if (head == NULL || newNode->nodeInfo.id < head->nodeInfo.id) {
        newNode->nextNode = head;
        head = newNode;
        return head;
    }

    while(currNode != NULL && newNodeInfo.id > currNode->nodeInfo.id) {
        prevNode = currNode;
        currNode = currNode->nextNode;
    }

    newNode->nextNode = currNode;
    prevNode->nextNode = newNode;

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
    
    Node *currNode = head, *prevNode;
    while (currNode != NULL) {
        Node* nodeCheck = currNode->nextNode;
        prevNode = currNode;
        while (nodeCheck != NULL && nodeCheck->nodeInfo.id != currNode->nodeInfo.id) {
            prevNode = nodeCheck;
            nodeCheck = nodeCheck->nextNode;
        }

        if (nodeCheck != NULL && nodeCheck->nodeInfo.id == currNode->nodeInfo.id) {
            prevNode->nextNode = nodeCheck->nextNode;
            free(nodeCheck);
        } else {
            currNode = currNode->nextNode;
        }
    }

    return head;
}

Node* removeOddNumbers(Node* head) {
    Node *currNode = head, *prevNode = NULL;
    while (currNode != NULL) {
        Node* nextNode = currNode->nextNode;
        if (currNode->nodeInfo.id % 2 != 0) {
            if (prevNode == NULL) {
                head = nextNode;
            } else {
                prevNode->nextNode = nextNode;
            }
            free(currNode);
        } else {
            prevNode = currNode;
        }
        currNode = nextNode;
    }

    return head;
}

void splitByParity(Node* head, Node **evens, Node **odds) {
    *evens = NULL;
    *odds = NULL;

    for (Node* currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        if (currNode->nodeInfo.id % 2 == 0){
            *evens = insertSorted(*evens, currNode->nodeInfo);
        } else {
            *odds = insertSorted(*odds, currNode->nodeInfo);
        }
    }
}

bool equalLists(Node *l1, Node *l2) {
    while(l1 != NULL && l2 != NULL) {
        if (l1->nodeInfo.id != l2->nodeInfo.id) {
            return false;
        }
        l1 = l1->nextNode;
        l2 = l2->nextNode;
    }

    return l1 == NULL && l2 == NULL;
}

Node* overwriteValue(Node *head, int targetValue, int newValue) {
    for (Node *currNode = head; currNode != NULL; currNode = currNode->nextNode) {
        if (currNode->nodeInfo.id == targetValue) {
            currNode->nodeInfo.id = newValue;
        }
    }

    return head;
}

void reverseListIterative(Node** head) {
    Node *prev = NULL, *curr = *head, *next = NULL;

    while (curr != NULL) {
        next = curr->nextNode;
        curr->nextNode = prev;
        prev = curr;
        curr = next;
    }

    *head = prev;
}

Node* reverseListRecursive(Node *head) {
    // Base: empty list or only one node.
    if (head == NULL || head->nextNode == NULL) {
        return head;
    }

    // Go to the end of the list. 'newHead' will be the original last node.
    Node *newHead = reverseListRecursive(head->nextNode);

    // After the recursive call returns, 'head' is the second-to-last node.
    // Make the original next node point back to the current head.
    head->nextNode->nextNode = head;
    
    // Set the current head's next pointer to NULL, breaking the original link.
    head->nextNode = NULL;

    // Propagate the new head all the way back up the call stack.
    return newHead;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "DoublyLinkedList.h"

#define TC_LIST_LENGTH 1
#define TC_BIGGEST 2
#define TC_DUPLICATES_REMOVAL 3
#define TC_ODDS_REMOVAL 4

void runTestCase(int tc);

int main(void) {
    int tc;

    printf("Type the test case you'd like to run: \n");
    printf("%d - int listLength(Node* head)\n", TC_LIST_LENGTH);
    printf("%d - int biggest(Node* head)\n", TC_BIGGEST);
    printf("%d - Node* removeDuplicates(Node* head)\n", TC_DUPLICATES_REMOVAL);
    printf("%d - Node* removeOddNumbers(Node* head)\n", TC_ODDS_REMOVAL);
    printf("\n");

    if (scanf("%d", &tc) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("\n");

    runTestCase(tc);
    return 0;
}

// --- Test Case Runner ---
void runTestCase(int tc) {
    switch (tc) {
    case TC_LIST_LENGTH: {
        printf("--- Testing listLength ---\n");
        // given
        Node* ll = NULL;
        ll = insertSorted(ll, (NodeInfo){1});
        ll = insertSorted(ll, (NodeInfo){2});
        ll = insertSorted(ll, (NodeInfo){3});
        
        // assert
        if (listLength(ll) == 3) {
            printf("List with elements count: ✅\n");
        } else {
            printf("List with elements count: ❌\n");
        }
        
        // given
        Node* el = NULL;

        // assert
        if (listLength(el) == 0) {
            printf("Empty list is 0: ✅\n");
        } else {
            printf("Empty list is 0: ❌\n");
        }

        destroyLinkedList(ll);
        destroyLinkedList(el);
        break;
    }
    case TC_BIGGEST: {
        printf("--- Testing biggest ---\n");
        // given
        Node* el = NULL;

        // assert
        if (biggest(el) == -1) {
            printf("Empty list returns -1: ✅\n");
        } else {
            printf("Empty list returns -1: ❌\n");
        }

        // given
        Node* ll = NULL;
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){4});
        ll = insertAtHead(ll, (NodeInfo){6});

        // assert
        if (biggest(ll) == 6) {
            printf("Max number is found: ✅\n");
        } else {
            printf("Max number is found: ❌\n");
        }
        destroyLinkedList(ll);
        destroyLinkedList(el);
        break;
    }
    case TC_DUPLICATES_REMOVAL: {
        printf("--- Testing removeDuplicates ---\n");
        // given
        Node* ll = NULL;
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){4});
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){2});
        
        printf("Original list:\n");
        printList(ll);

        // when
        ll = removeDuplicates(ll);
        printf("After removing duplicates:\n");
        printList(ll);
        printListReverse(ll);

        // assert: Check forward, backward, and boundary pointers
        bool structureOK = ll != NULL &&
                           ll->nodeInfo.id == 2 &&
                           ll->prevNode == NULL &&
                           ll->nextNode != NULL &&
                           ll->nextNode->nodeInfo.id == 4 &&
                           ll->nextNode->prevNode == ll &&
                           ll->nextNode->nextNode == NULL;

        if (structureOK) {
            printf("Removed duplicates: ✅\n");
        } else {
            printf("Removed duplicates: ❌\n");
        }
        destroyLinkedList(ll);
        break;
    }
    case TC_ODDS_REMOVAL: {
        printf("--- Testing removeOddNumbers ---\n");
        // given
        Node* ll = NULL;
        ll = insertAtHead(ll, (NodeInfo){1});
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){3});
        ll = insertAtHead(ll, (NodeInfo){4});
        ll = insertAtHead(ll, (NodeInfo){5});
        ll = insertAtHead(ll, (NodeInfo){6});
        
        printf("Original list:\n");
        printList(ll);

        // when
        ll = removeOddNumbers(ll);
        printf("After removing odds:\n");
        printList(ll);
        printListReverse(ll);


        // assert: Traverse forward to check for odds
        bool oddFound = false;
        for (Node *n = ll; n != NULL; n = n->nextNode) {
            if (n->nodeInfo.id % 2 != 0) {
                oddFound = true;
                break;
            }
        }
        
        // assert: Traverse backward to check for list integrity
        bool backwardLinkBroken = false;
        if(ll != NULL) {
            Node* tail = ll;
            while(tail->nextNode != NULL) tail = tail->nextNode; // find tail
            while(tail != NULL) {
                if(tail->nextNode != NULL && tail->nextNode->prevNode != tail) {
                    backwardLinkBroken = true;
                    break;
                }
                if (tail->prevNode == NULL && tail != ll) { // Should only be NULL at head
                    backwardLinkBroken = true;
                    break;
                }
                tail = tail->prevNode;
            }
        }


        if (!oddFound && !backwardLinkBroken) {
            printf("Removed odds and list is intact: ✅\n");
        } else {
            printf("Removed odds and list is intact: ❌\n");
        }
        destroyLinkedList(ll);
        break;
    }
    default:
        printf("Invalid test case selected.\n");
        break;
    }
}

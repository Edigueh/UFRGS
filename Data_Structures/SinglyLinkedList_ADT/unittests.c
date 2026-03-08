#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "SinglyLinkedList.h"

#define TC_LIST_LENGTH 1
#define TC_BIGGEST 2
#define TC_DUPLICATES_REMOVAL 3
#define TC_ODDS_REMOVAL 4
#define TC_SPLIT_BY_PARITY 5
#define TC_EQUAL_LISTS 6
#define TC_OVERWRITE_TARGET 7
#define TC_INVERT_LIST 8

void runTestCase(int tc);

int main(void) {
    int tc;

    printf("Type the test case you'd like to run: \n");
    printf("%d - int listLength(Node* head)\n", TC_LIST_LENGTH);
    printf("%d - int biggest(Node* head)\n", TC_BIGGEST);
    printf("%d - Node* removeDuplicates(Node* head)\n", TC_DUPLICATES_REMOVAL);
    printf("%d - Node* removeOddNumbers(Node* head)\n", TC_ODDS_REMOVAL);
    printf("%d - void splitByParity(Node* head, Node **evens, Node **odds)\n", TC_SPLIT_BY_PARITY);
    printf("%d - bool equalLists(Node *l1, Node *l2)\n", TC_EQUAL_LISTS);
    printf("%d - Node* overwriteValue(Node *head, int target, int new)\n", TC_OVERWRITE_TARGET);
    printf("%d - Node* invertList(Node* head)\n", TC_INVERT_LIST);
    printf("\n");

    if (scanf("%d", &tc) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    printf("\n");

    runTestCase(tc);
    return 0;
}

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

        // Cleanup
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
        ll = insertAtHead(ll, (NodeInfo){6});
        ll = insertAtHead(ll, (NodeInfo){4});

        // assert
        if (biggest(ll) == 6) {
            printf("Max number is found: ✅\n");
        } else {
            printf("Max number is found: ❌\n");
        }
        
        // Cleanup
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

        // assert
        bool structureOK = ll != NULL &&
                           ll->nodeInfo.id == 2 &&
                           ll->nextNode != NULL &&
                           ll->nextNode->nodeInfo.id == 4 &&
                           ll->nextNode->nextNode == NULL;

        if (structureOK) {
            printf("Removed duplicates: ✅\n");
        } else {
            printf("Removed duplicates: ❌\n");
        }

        // Cleanup
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

        // assert
        bool oddFound = false;
        for (Node *n = ll; n != NULL; n = n->nextNode) {
            if (n->nodeInfo.id % 2 != 0) {
                oddFound = true;
                break;
            }
        }

        if (!oddFound) {
            printf("Removed odds: ✅\n");
        } else {
            printf("Removed odds: ❌\n");
        }

        // Cleanup
        destroyLinkedList(ll);
        break;
    }
    case TC_SPLIT_BY_PARITY: {
        printf("--- Testing splitByParity ---\n");
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

        Node *evens = initLinkedList();
        Node *odds = initLinkedList();

        // when
        splitByParity(ll, &evens, &odds);
        printf("Evens:\n");
        printList(evens);
        printf("Odds:\n");
        printList(odds);

        // assert
        bool evenListPass = true;
        for (Node *n = evens; n != NULL; n = n->nextNode) {
            if (n->nodeInfo.id % 2 != 0) {
                evenListPass = false;
                break;
            }
        }

        bool oddListPass = true;
        for (Node *n = odds; n != NULL; n = n->nextNode) {
            if (n->nodeInfo.id % 2 == 0) {
                oddListPass = false;
                break;
            }
        }

        if (evenListPass && oddListPass) {
            printf("Split by parity: ✅\n");
        } else {
            printf("Split by parity: ❌\n");
        }

        // Cleanup
        destroyLinkedList(ll);
        destroyLinkedList(evens);
        destroyLinkedList(odds);
        break;
    }
    case TC_EQUAL_LISTS: {
        // given
        Node* l1 = NULL;
        l1 = insertAtHead(l1, (NodeInfo){1});
        l1 = insertAtHead(l1, (NodeInfo){2});
        l1 = insertAtHead(l1, (NodeInfo){3});

        Node* l2 = NULL;
        l2 = insertAtHead(l2, (NodeInfo){1});
        l2 = insertAtHead(l2, (NodeInfo){2});
        l2 = insertAtHead(l2, (NodeInfo){4});

        Node* l3 = NULL;
        l3 = insertAtHead(l3, (NodeInfo){1});
        l3 = insertAtHead(l3, (NodeInfo){2});
        l3 = insertAtHead(l3, (NodeInfo){3});

        // when

        bool l1eql2 = equalLists(l1, l2);
        bool l1eql3 = equalLists(l1, l3);

        if (!l1eql2 && l1eql3) {
            printf("Equal lists: ✅\n");
        } else {
            printf("Equal lists: ❌\n");
        }

        destroyLinkedList(l1);
        destroyLinkedList(l2);
        destroyLinkedList(l3);
        break;
    }
    case TC_OVERWRITE_TARGET: {
        // given
        Node *ll = initLinkedList();
        ll = insertAtHead(ll, (NodeInfo){0});
        ll = insertAtHead(ll, (NodeInfo){1});
        ll = insertAtHead(ll, (NodeInfo){1});
        ll = insertAtHead(ll, (NodeInfo){0});
        ll = insertAtHead(ll, (NodeInfo){1});
        ll = insertAtHead(ll, (NodeInfo){0});

        // when
        ll = overwriteValue(ll, 0, 1);

        bool pass = true;
        for (Node* n = ll; n != NULL; n = n->nextNode) {
            if (n->nodeInfo.id != 1) {
                pass = false;
            }
        }

        // assert
        if (pass) {
            printf("Overwrite values: ✅\n");
        } else {
            printf("Overwrite values: ❌\n");
        }

        destroyLinkedList(ll);
        break;
    }
    case TC_INVERT_LIST: {
        // given
        Node *ll = initLinkedList();
        ll = insertAtHead(ll, (NodeInfo){1});
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){3});
        ll = insertAtHead(ll, (NodeInfo){4});
        ll = insertAtHead(ll, (NodeInfo){5});
        ll = insertAtHead(ll, (NodeInfo){6});

        Node *rl = initLinkedList();
        rl = insertAtHead(rl, (NodeInfo){6});
        rl = insertAtHead(rl, (NodeInfo){5});
        rl = insertAtHead(rl, (NodeInfo){4});
        rl = insertAtHead(rl, (NodeInfo){3});
        rl = insertAtHead(rl, (NodeInfo){2});
        rl = insertAtHead(rl, (NodeInfo){1});

        // when
        printList(ll);
        reverseListIterative(&ll);
        printList(ll);

        // then
        if(equalLists(ll, rl)){
            printf("Invert list: ✅\n");
        } else {
            printf("Invert list: ❌\n");
        }

        printList(ll);
        ll = reverseListRecursive(ll);
        printList(ll);
        destroyLinkedList(ll);
        destroyLinkedList(rl);
        break;
    }
    default:
        printf("Invalid test case selected.\n");
        break;
    }
}

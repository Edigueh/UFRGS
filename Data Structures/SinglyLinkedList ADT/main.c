#include <stdbool.h>
#include <stdio.h>
#include "SinglyLinkedList.h"

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

    scanf("%d", &tc);
    printf("\n");

    runTestCase(tc);
}

void runTestCase(int tc) {
    switch (tc) {
    case TC_LIST_LENGTH: {
        // given
        Node* ll = initLinkedList();
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
        Node* el = initLinkedList();

        // assert
        if (listLength(el) == 0) {
            printf("Empty list is 0: ✅\n");
        } else {
            printf("Empty list is 0: ❌\n");
        }

        break;
    }
    case TC_BIGGEST: {
        // given
        Node* el = initLinkedList();

        // assert
        if (biggest(el) == -1) {
            printf("Empty list returns -1: ✅\n");
        } else {
            printf("Empty list returns -1: ❌\n");
        }

        // given
        Node* ll = initLinkedList();
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){4});
        ll = insertAtHead(ll, (NodeInfo){6});

        // assert
        if (biggest(ll) == 6) {
            printf("Max number is found: ✅\n");
        } else {
            printf("Max number is found: ❌\n");
        }
        break;
    }
    case TC_DUPLICATES_REMOVAL: {
        // given
        Node* el = initLinkedList();

        // assert
        if (removeDuplicates(el) == NULL) {
            printf("Empty list returns NULL: ✅\n");
        } else {
            printf("Empty list returns NULL: ❌\n");
        }

        // given
        Node* ll = initLinkedList();
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){4});
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){2});
        
        // when
        ll = removeDuplicates(ll);

        // assert
        if (ll->nodeInfo.id == 2 && ll->nextNode->nodeInfo.id == 4 && ll->nextNode->nextNode == NULL) {
            printf("Removed duplicates: ✅\n");
        } else {
            printf("Removed duplicates: ❌\n");
        }
        break;
    }
    case TC_ODDS_REMOVAL: {
        // given
        Node* ll = initLinkedList();
        ll = insertAtHead(ll, (NodeInfo){1});
        ll = insertAtHead(ll, (NodeInfo){2});
        ll = insertAtHead(ll, (NodeInfo){3});
        ll = insertAtHead(ll, (NodeInfo){4});
        ll = insertAtHead(ll, (NodeInfo){5});
        ll = insertAtHead(ll, (NodeInfo){6});
        ll = insertAtHead(ll, (NodeInfo){8});
        ll = insertAtHead(ll, (NodeInfo){7});
        ll = insertAtHead(ll, (NodeInfo){9});
        
        // when
        ll = removeOddNumbers(ll);

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
        break;
    }
    default:
        break;
    }
}

#include <stdbool.h>
#define MAX_CHAR 20

typedef struct {
    int id;
} NodeInfo;

typedef struct Node {
    NodeInfo nodeInfo;
    struct Node* nextNode;
} Node;

// initList initialize a new empty linked list.
Node* initLinkedList(void);

// printList prints all elements contained inside the linked list.
void printList(Node* head);

// queryList queries the list for a determined element,
// returns the element if found, otherwise returns NULL.
Node* queryList(Node* head, int targetId);

// insertAtHead inserts a new node at the head of the list.
// Returns the updated list.
Node* insertAtHead(Node* head, NodeInfo newNodeInfo);

// insertAtTail inserts a new node at the tail of the list.
// Returns the updated list.
Node* insertAtTail(Node* head, NodeInfo newNodeInfo);

// insertAtMiddle inserts a new node at the middle of the list.
// Returns the updated list.
Node* insertAtMiddle(Node* head, NodeInfo newNodeInfo, int previousNodeId);

// removeNodeById removes a node from the list by its id.
Node* removeNodeById(Node* head, int targetId);

// destroyLinkedList disallocate the memory alllocated for it and returns an empty list.
Node* destroyLinkedList(Node* head);

// insertSorted inserts a new element in the list in the right position by sorting it by the id of the new element.
Node* insertSorted(Node* head, NodeInfo newNodeInfo);

/*
Exercises:
1) Create a function that receives a pointer to a linked list and returns the number of elements in it.
    int listLength(Node* head) ✅;

2) Create a function that receives a pointer to a linked list of integers and return the biggest value in it.
    int biggest(Node* head) ✅;

3) Create a function that iterates over a linked list and removes the duplicated elements.
    Node* removeDuplicates(Node* head) ✅;
*/

// listLength receives a pointer to a linked list and returns the number of elements in it.
int listLength(Node* head);

// biggest receives a pointer to a linked list of integers and return the biggest value in it.
int biggest(Node* head);

// removeDuplicates iterates over a linked list and removes the duplicated elements.
Node* removeDuplicates(Node* head);

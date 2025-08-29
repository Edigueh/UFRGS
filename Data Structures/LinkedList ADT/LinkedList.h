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

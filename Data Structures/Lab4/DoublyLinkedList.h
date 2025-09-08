#include <stdbool.h>
#define MAX_CHAR 50

typedef struct {
    int id;
    char name[MAX_CHAR];
    float price;
} Product;

typedef struct Node {
    struct Node* prevNode;
    Product product;
    struct Node* nextNode;
} Node;

// initList initialize a new empty linked list.
Node* initLinkedList(void);

// printList prints all elements contained inside the linked list.
void printList(Node* head);

// printListReverse prints all elements contained inside the linked list in reverse order.
void printListReverse(Node* head);

// removeProductById removes a node from the list by its id.
Node* removeProductById(Node* head, int targetId);

// destroyLinkedList disallocate the memory alllocated for it and returns an empty list.
Node* destroyLinkedList(Node* head);

// insertProduct inserts a new product in the list in the right position by sorting it by the id of the new element.
Node* insertProduct(Node* head, Product newNodeInfo);

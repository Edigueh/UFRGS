#define MAX_NAME_CHARS 30

typedef struct {
    int id;
    char name[MAX_NAME_CHARS];
    float price;
} Product;

typedef struct Node {
    Product product;
    struct Node* nextNode;
} Node;

// initList initialize a new empty linked list.
Node* initLinkedList(void);

// printList prints all elements contained inside the linked list.
void printList(Node* head);

// insertProduct inserts the given product at the right position (based on id) in the list.
Node* insertProduct(Node* head, Product newProduct);

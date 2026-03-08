typedef struct {
    int id;
} Info;

typedef struct Node {
    Info info;
    struct Node *next;
} Node;

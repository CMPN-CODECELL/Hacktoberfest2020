#ifndef LIST_H
#define LIST_H

typedef union NodeInfo {
    int intValue;
    char *stringValue;
    double realVavlue;
    void *pointerValue;
} NodeInfo;

typedef struct Node {
    NodeInfo info;
    struct Node *next;
} Node;

// CONSTRUCTOR (head creation)
Node* list_create();

// Getting an item
NodeInfo list_getLast(Node *head);
NodeInfo list_getFirst(Node *head);
NodeInfo list_get(Node* head, int index);

// Pop an item
NodeInfo list_popLast(Node *head);
NodeInfo list_popFirst(Node *head);
NodeInfo list_pop(Node* head, int index);

// Add an item
void list_insertLast(Node *head, NodeInfo data);
void list_insertFirst(Node *head, NodeInfo data);
void list_insert(Node* head, int index, NodeInfo data);

// The list size:
int list_size(Node *head);

// Delete:
void list_removeList(Node **head);
void list_remove(Node *head, int index);

NodeInfo* list_toArray(Node *head);

int list_isEmpty(Node *head);

#endif //LIST_H

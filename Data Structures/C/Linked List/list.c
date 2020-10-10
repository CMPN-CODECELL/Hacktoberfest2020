#include <stdlib.h>
#include "list.h"

#define true 1
#define false 0


/**
 * Creating a list head
 * @return Pointer to the created head
 */
Node* list_create() {
    Node *el = (Node*) malloc(sizeof(Node));
    el->next = NULL;
    return el;
}
/**
 * Check list for empty
 * @param head - Pointer to the head of the list
 * @return 1 is list is empty, else - 0
 */
int list_isEmpty(Node *head) {
    return (head == NULL) || (head->next == NULL) ? true : false;
}

/**
 * Getting the number of list items
 * @param head - Pointer to the head of the list
 * @return size
 */
int list_size(Node *head) {
    if(list_isEmpty(head)) return 0;

    Node *tmp = head->next;

    int size = 0;
    while(tmp) {
        size++;
        tmp = tmp->next;
    }

    return size;
}

/**
 * List to array conversion
 * @param head - Pointer to the head of the list
 * @return array
 */
NodeInfo* list_toArray(Node *head) {
    int length = list_size(head);
    if(length == 0) return malloc(0);

    // Create array:
    NodeInfo *arr = malloc(length * sizeof(NodeInfo));

    Node *tmp = head->next;
    int i = 0;
    while(tmp) {
        arr[i++] = tmp->info;
        tmp = tmp->next;
    }

    return arr;
}


/* ### GET ITEM ### */

/**
 * Returns Nth item
 * @param head - Pointer to the head of the list
 * @param index - The index of the desired item (Starting from zero, the head is not considered)
 * @warning In the case of accessing a non-existent element, the program will be immediately terminated with the code -1
 * @return Nth item
 */
NodeInfo list_get(Node* head, int index) {
    if (list_isEmpty(head) || (index < 0)) exit(-1);

    int i = 0;
    Node *tmp = head->next;
    while((i++ < index) && tmp) {
        tmp = tmp->next;
    }
    if(tmp == NULL) exit(-1);

    return tmp->info;
}

/**
 * Gets the last item in the list.
 * @param head - Pointer to the head of the list
 * @warning In the case of accessing a non-existent element, the program will be immediately terminated with the code -1
 * @return last item
 */
NodeInfo list_getLast(Node *head) {
    if(list_isEmpty(head)) exit(-1);

    Node *tmp = head;
    while(tmp->next) {
        tmp = tmp->next;
    }
    return tmp->info;
}

/**
 * Gets the first item in the list.
 * @param head - Pointer to the head of the list
 * @warning In the case of accessing a non-existent element, the program will be immediately terminated with the code -1
 * @return first item
 */
NodeInfo list_getFirst(Node *head) {
    if(list_isEmpty(head)) exit(-1);
    return head->next->info;
}


/*  ### POP ITEM ### */

/**
 * Gets and removes the last item in the list.
 * @param head - Pointer to the head of the list
 * @warning In the case of accessing a non-existent element, the program will be immediately terminated with the code -1
 * @return deleted last item
 */
NodeInfo list_popLast(Node *head) {
    if (list_isEmpty(head)) exit(-1);

    Node *prev = head; // Preview item
    Node *curr = head->next;  // Current item;
    while(curr->next) {
        prev = curr;
        curr = curr->next;
    }
    NodeInfo result = curr->info;
    prev->next = NULL; // Remove last item
    free(curr); // Free memory
    return result;
}

/**
 * Gets and removes the Nth item in the list.
 * @param head - Pointer to the head of the list
 * @warning In the case of accessing a non-existent element, the program will be immediately terminated with the code -1
 * @return deleted Nth item
 */
NodeInfo list_pop(Node* head, int index) {
    if (list_isEmpty(head)) exit(-1);

    int i = 0;
    Node *curr = head->next;
    Node *prev = head;
    while((i++ < index) && curr) {
        prev = curr;
        curr = curr->next;

    }
    if(curr == NULL) exit(-1);

    NodeInfo result = curr->info;

    // Remove item:
    prev->next = curr->next;
    free(curr);


    return result;
}


/**
 * Gets and removes the first item in the list.
 * @param head - Pointer to the head of the list
 * @warning In the case of accessing a non-existent element, the program will be immediately terminated with the code -1
 * @return deleted first item
 */
NodeInfo list_popFirst(Node *head) {
    if (list_isEmpty(head)) exit(-1);

    Node *tmp = head->next;

    NodeInfo result = tmp->info;

    head->next = tmp->next;
    free(tmp);

    return result;
}



/*  ### INSERT ITEM ### */

Node* list_createElement(NodeInfo data) {
    Node *el = (Node*) malloc(sizeof(Node));
    el->info = data;
    el->next = NULL;
    return el;
}

/**
 * Adds an item to the end of the list.
 * @param head - Pointer to the head of the list
 * @param data - Element information structure
 */
void list_insertLast(Node *head, NodeInfo data) {
    Node *tmp = head;
    while(tmp->next) {
        tmp = tmp->next;
    }

    tmp->next = NULL;
    tmp->next = list_createElement(data);
}

/**
 * Adds an item to the top of the list.
 * @param head - Pointer to the head of the list
 * @param data - Element information structure
 */
void list_insertFirst(Node *head, NodeInfo data) {
    Node *nextEl = head->next; // Current first item, will become the second
    Node *newEl = list_createElement(data); // New first item
    newEl->next = nextEl;
    head->next = newEl;
}

/**
 * Adds an item to Nth position of the list.
 * @param head - Pointer to the head of the list
 * @param data - Element information structure
 * @warning In the case of accessing a non-existent element, the program will be immediately terminated with the code -1
 */
void list_insert(Node* head, int index, NodeInfo data) {
    int i = 0;
    Node *tmp = head->next;
    while((i++ < index-1) && tmp) {
        tmp = tmp->next;
    }
    if((tmp == NULL) || (tmp->next == NULL)) exit(-1);

    // tmp - element after which you want to insert an element
    Node *newEl = list_createElement(data);
    newEl->next = tmp->next;
    tmp->next = newEl;
}

/* ### REMOVE ITEMS || LIST ### */

/**
 * Remove all items of the list
 * @param head  - Pointer to the pointer to the head of the list (Need use: list_removeList(&head))
 */
void list_removeList(Node **head) {
    Node *tmp = *head;
    while(tmp) {
        Node *next = tmp->next;
        free(tmp);
        tmp = next;
    }
    *head = NULL; // Set null pointer to the head
}

/**
 * Remove Nth item of the list
 * @param head  - Pointer to the head of the list
 * @param index - The index of the item to be deleted.
 */
void list_remove(Node *head, int index) {
    list_pop(head, index);
}
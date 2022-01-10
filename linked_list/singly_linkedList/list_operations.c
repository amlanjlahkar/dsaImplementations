/* TODO
add other operations: insert_rear, free_rear, search, sort */

#include <stdio.h>
#include <stdlib.h>

typedef struct node_info {
    int data;
    struct node_info *next;
} Node;
Node *head = NULL;

void insert_front(int node_data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = node_data;
    new_node->next = head;
    head = new_node;
}

void free_front() {
    if (head == NULL) {
        puts("\nlist is empty.");
        return;
    }
    Node *getnode = head;
    head = getnode->next;
    free(getnode);
}

void printList() {
    if (head == NULL) {
        puts("\nlist is empty.");
        return;
    }
    Node *getnode = head;
    printf("\n");
    while(getnode->next != NULL) {
        printf("[ %d ] ---> ", getnode->data);
        getnode = getnode->next;
    }
    if (getnode->next == NULL)
        printf("[ %d ]\n", getnode->data);
}

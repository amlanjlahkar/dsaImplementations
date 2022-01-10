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
    Node *ptr = (Node*) malloc(sizeof(Node));
    ptr->data = node_data;
    ptr->next = head;
    head = ptr;
}

void free_front() {
    if (head == NULL) {
        puts("\nlist is empty.");
        return;
    }
    Node *ptr;
    ptr = head;
    head = ptr->next;
    free(ptr);
}

void printList() {
    if (head == NULL) {
        puts("\nlist is empty.");
        return;
    }
    Node *ptr = head;
    printf("\n");
    while(ptr->next != NULL) {
        printf("[ %d ] ---> ", ptr->data);
        ptr = ptr->next;
    }
    if (ptr->next == NULL)
        printf("[ %d ]\n", ptr->data);
}

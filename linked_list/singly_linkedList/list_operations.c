/* TODO
add other operations: insert_after */

#include <stdio.h>
#include <stdlib.h>

typedef struct node_info {
    int data;
    struct node_info *next;
} Node;
Node *head = NULL;

int is_empty() {
    return((head == NULL) ? 1 : 0);
}

// insertion
void insert_front(int node_data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = node_data;
    new_node->next = head;
    head = new_node;
}

void insert_rear(int node_data) {
    if (is_empty()) {
        insert_front(node_data);
        return;
    }
    Node *seek = head;
    while(seek->next != NULL)
        seek = seek->next;
    Node *new_node = (Node*) malloc(sizeof(Node));
    seek->next = new_node;
    new_node->data = node_data;
    new_node->next = NULL;
}

// deletion
int free_front() {
    if (!is_empty()) {
        Node *getnode = head;
        int freed_data = getnode->data;
        head = getnode->next;
        free(getnode);
        return freed_data;
    }
    return 0;
}

int free_rear() {
    if (!is_empty()) {
        if (head->next == NULL)
            return(free_front());
        Node *seek = head;
        // traverse until the node before last node is reached
        while((seek->next)->next != NULL)
            seek = seek->next;
        // target the last node
        Node *getnode = seek->next;
        if (head->next == getnode) {
            int freed_data = getnode->data;
            head->next = NULL;
            free(getnode);
            return freed_data;
        } else {
            int freed_data = getnode->data;
            seek->next = NULL;
            free(getnode);
            return freed_data;
        }
    }
    return 0;
}

int search(int node_data) {
    if (!is_empty()) {
        int count = 1, is_available = 0;
        Node *seek = head;
        // if the only remaining node is the searched node
        if (seek->next == NULL && seek->data == node_data) {
            is_available = 1;
            return count;
        } else {
            while(seek->next != NULL) {
                if (seek->data == node_data) {
                    is_available = 1;
                    break;
                }
                count++;
                seek = seek->next;
            }
            // if the last node is the searched node
            if (seek->data == node_data) {
                is_available = 1;
                return count;
            }
            else
                return 0;
        }
    }
    return 0;
}

void printList() {
    if (is_empty()) {
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

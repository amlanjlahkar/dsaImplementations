#include "list_operations.h"
#include <stdio.h>
#include <stdlib.h>

// head points to the first node in the list
Node* head = NULL;

void insert_front(int node_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = node_data;
    new_node->next = head;
    head = new_node;
}

void insert_after(int prev_node_data, int new_node_data) {
    if (!is_empty() && search(prev_node_data)) {
        Node* getnode = head;
        while (getnode->next != NULL && getnode->data != prev_node_data) {
            getnode = getnode->next;
        }
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = new_node_data;
        new_node->next = getnode->next;
        getnode->next = new_node;
    }
    return;
}

void insert_rear(int node_data) {
    if (is_empty()) {
        insert_front(node_data);
        return;
    }
    Node* seek = head;
    while (seek->next != NULL) {
        seek = seek->next;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    seek->next = new_node;
    new_node->data = node_data;
    new_node->next = NULL;
}

int free_front() {
    if (!is_empty()) {
        Node* getnode = head;
        int freed_data = getnode->data;
        head = getnode->next;
        free(getnode);
        return freed_data;
    }
    return 0;
}

void free_node(int node_data) {
    if (!is_empty()) {
        Node* getnode = head;
        if (getnode->data == node_data) {
            free_front();
            printf("\nnode containing \'%d\' has been freed.\n"
                   "(number of nodes remaining in the list = %d)\n",
                   node_data, list_size());
            return;
        }
        while (getnode->next != NULL && (getnode->next)->data != node_data) {
            getnode = getnode->next;
        }
        if (getnode->next == NULL) {
            printf("Node containing data of %d doesn't exist in the list.\n",
                   node_data);
            return;
        } else {
            Node* target = getnode->next;
            int freed_data = target->data;
            getnode->next = target->next;
            free(target);
            printf("node containing \'%d\' has been freed.\n"
                   "(number of node(s) remaining in the list = %d)\n",
                   freed_data, list_size());
            return;
        }
    }
    return;
}

int free_rear() {
    if (!is_empty()) {
        if (head->next == NULL) {
            return (free_front());
        }
        Node* seek = head;
        // traverse until "the node before last node" is reached
        while ((seek->next)->next != NULL) {
            seek = seek->next;
        }
        // target the last node
        Node* getnode = seek->next;
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

int is_empty() { return ((head == NULL) ? 1 : 0); }

int list_size() {
    if (!is_empty()) {
        Node* getnode = head;
        int size = 1;
        while (getnode->next != NULL) {
            getnode = getnode->next;
            size++;
        }
        return size;
    }
    return 0;
}

int search(int node_data) {
    if (!is_empty()) {
        int index = 1;
        Node* seek = head;
        // if the only remaining node is the searched node
        if (seek->next == NULL && seek->data == node_data) {
            return index;
        } else {
            while (seek->next != NULL) {
                if (seek->data == node_data) {
                    break;
                }
                index++;
                seek = seek->next;
            }
            // if the last node is the searched node
            if (seek->data == node_data) {
                return index;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

void printList() {
    if (is_empty()) {
        puts("\nlist is empty!");
        return;
    }
    Node* getnode = head;
    printf("\n");
    while (getnode->next != NULL) {
        if (getnode == head) {
            printf("front : [ %d ] ---> ", getnode->data);
            getnode = getnode->next;
        } else {
            printf("[ %d ] ---> ", getnode->data);
            getnode = getnode->next;
        }
    }
    if (getnode->next == NULL) {
        printf("[ %d ]\n", getnode->data);
    }
}

void resetList() {
    if (!is_empty()) {
        for (int size = list_size(); size >= 1; size--) {
            free_front();
        }
    }
    return;
}

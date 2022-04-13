#include "list_operations.h"
#include <stdio.h>
#include <stdlib.h>

Node *head = NULL;

void insert_front(int node_data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = node_data;
  new_node->prev = NULL;
  new_node->next = head;
  if (head != NULL)
    head->prev = new_node;
  head = new_node;
}

void insertBy_node_position(int position, int node_data) {
  if (head != NULL && position <= list_size()) {
    int init = 1;
    Node *ptr = head;
    while (init != position && ptr->next != NULL) {
      init++;
      ptr = ptr->next;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = node_data;
    new_node->next = ptr;
    if (ptr->prev != NULL) {
      (ptr->prev)->next = new_node;
      ptr->prev = new_node;
      new_node->prev = (ptr->prev)->prev;
    } else {
      head->prev = new_node;
      head = new_node;
      new_node->prev = NULL;
    }
    ptr = NULL;
  }
  return;
}

void deleteBy_node_data(int node_data) {
  if (head != NULL) {
    Node *ptr = head;
    if (ptr->data == node_data) {
      head = ptr->next;
      ptr = NULL;
    } else {
      while (ptr->next != NULL && (ptr->next)->data != node_data)
        ptr = ptr->next;
      if (ptr->next != NULL) {
        Node *target = ptr->next;
        ptr->next = target->next;
        ptr->prev = target->prev;
        free(target);
        ptr = NULL;
      } else {
        printf("Node doesn't exist(or cude emrror).\n");
        ptr = NULL;
      }
    }
  }
  return;
}

int deleteBy_node_position(int position) {
  if (head != NULL && position <= list_size()) {
    int init = 0;
    Node *ptr = head;
    while (init != position - 1 && ptr->next != NULL) {
      init++;
      ptr = ptr->next;
    }
    int freed_node_data = ptr->data;
    if (ptr->prev != NULL)
      (ptr->prev)->next = ptr->next;
    else
      head = ptr->next;
    if (ptr->next != NULL)
      (ptr->next)->prev = ptr->prev;
    free(ptr);
    return freed_node_data;
  }
  return 0;
}

int list_size() {
  if (head != NULL) {
    Node *ptr = head;
    int size = 1;
    while (ptr->next != NULL) {
      ptr = ptr->next;
      size++;
    }
    return size;
  }
  return 0;
}

void print_list() {
  Node *ptr = head;
  while (ptr->next != NULL) {
    printf("%d ", ptr->data);
    ptr = ptr->next;
  }
  printf("%d\n", ptr->data);
  ptr = NULL;
}


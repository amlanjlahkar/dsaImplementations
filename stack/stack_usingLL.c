/* program to implement a stack of FIFO mechanism
   using singly linked list structure */

#include <stdio.h>
#include <stdlib.h>

typedef struct node_info {
  int data;
  struct node_info *next;
} Node;
Node *head = NULL;

void push(Node *head_ptr, int node_data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = node_data;
  new_node->next = head;
  head = new_node;
}

int pop(Node *head_ptr) {
  Node *ptr = head;
  int deleted_node_data = ptr->data;
  head = ptr->next;
  ptr = NULL;
  return deleted_node_data;
}

void print_stack(Node *head_ptr) {
  if (head != NULL) {
    Node *ptr = head;
    while (ptr->next != NULL) {
      printf("%d\t", ptr->data);
      ptr = ptr->next;
    }
    printf("%d\n", ptr->data);
    ptr = NULL;
  } else
    return;
}

int main(void) {
  push(head, 1);
  push(head, 2);
  push(head, 3);
  push(head, 4);

  printf("initial stack\n");
  print_stack(head);
  int get_deleted_data = pop(head);
  printf("node containing data %d freed from the stack.\n", get_deleted_data);
  print_stack(head);
}

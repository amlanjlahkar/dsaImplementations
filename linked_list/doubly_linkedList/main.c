#include "list_operations.c"
#include <stdio.h>

int main(void) {
  insert_front(5);
  insert_front(6);
  insert_front(7);
  insert_front(8);

  print_list();
  int position = 1;
  int node_data = 12;
  if (position > 0 && position <= list_size()) {
    insertBy_node_position(position, node_data);
    printf("inserted node containing data %d at position %d.\n", node_data,
           position);
  } else
    printf("invalid position.\n");
  print_list();

  return 0;
}

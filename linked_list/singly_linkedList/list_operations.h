/* c program to implement a singly linked list containing integers
to be test with standard input/output */

// node structure
typedef struct node_info {
  int data;
  struct node_info *next;
} Node;

/* list operations */
// insertion
void insert_front(int node_data);
void insert_after(int prev_node_data, int new_node_data);
void insert_rear(int node_data);

// deletion
int free_front();
void free_node(int node_data);
int free_rear();

// other
int is_empty();
int list_size();
int search(int node_data);
void printList();
void resetList();

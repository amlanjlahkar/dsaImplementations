typedef struct node_info {
  int data;
  struct node_info *prev;
  struct node_info *next;
} Node;

// list operations
void insert_front(int node_data);
void insertBy_node_position(int position, int node_data);
void deleteBy_node_data(int node_data);
int deleteBy_node_position(int position);

// other
int list_size();
void print_list();

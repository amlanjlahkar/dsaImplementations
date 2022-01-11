/* function prototypes */
int is_empty();
// insertion
void insert_front(int node_data);
void insert_after(int prev_node_data, int new_node_data);
void insert_rear(int node_data);
// deletion
int free_front();
int free_after(int prev_node_data);
int free_rear();
// other
int search(int node_data);
void printList();

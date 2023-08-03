#include <stdbool.h>

typedef struct node {
    int value;
    struct node* left;
    struct node* right;
} bst_node;

typedef struct {
    bst_node* root;
} bst;

bst* bst_new();

bst_node* bst_search_node(bst_node* root, int node_value);

void bst_insert_node(bst_node** root, int node_value);

void bst_delete_node(bst_node** root, int node_value);

void bst_free(bst_node* root);

void bst_print(bst_node* root, unsigned level);

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    bst* t = bst_new();

    bst_insert_node(&(t->root), 11);
    bst_insert_node(&(t->root), 9);
    bst_insert_node(&(t->root), 12);
    bst_insert_node(&(t->root), 32);
    bst_insert_node(&(t->root), -12);
    bst_insert_node(&(t->root), -6);
    bst_insert_node(&(t->root), -8);
    bst_insert_node(&(t->root), -80);
    bst_insert_node(&(t->root), 22);

    bst_print(t->root, 0);

    if (argc == 2) {
        bst_node* node;
        if ((node = bst_search_node(t->root, strtol(argv[1], NULL, 10))) && node != NULL) {
            bst_delete_node(&(t->root), node->value);
            printf("After deletion\n");
            bst_print(t->root, 0);
        } else {
            puts("node is not present in tree");
        }
    }

    bst_free(t->root);
    free(t);

    return EXIT_SUCCESS;
}

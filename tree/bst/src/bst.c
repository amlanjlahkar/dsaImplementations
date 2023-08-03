#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

bst* bst_new() {
    bst* tree = malloc(sizeof(bst));
    tree->root = NULL;
    return tree;
}

bst_node* bst_new_node(int value) {
    bst_node* node = malloc(sizeof(bst_node));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

void bst_insert_node(bst_node** root, int node_value) {
    bst_node* target = *root;

    if (target == NULL) {
        *root = bst_new_node(node_value);
        return;
    }

    int root_value = target->value;

    if (node_value == root_value) {
        return;
    }

    if (node_value < root_value) {
        return bst_insert_node(&(target->left), node_value);
    } else {
        return bst_insert_node(&(target->right), node_value);
    }
}

bst_node* bst_search_node(bst_node* root, int node_value) {
    if (root == NULL) {
        return NULL;
    }

    if (root->value == node_value) {
        return root;
    }

    if (node_value < root->value) {
        return bst_search_node(root->left, node_value);
    } else {
        return bst_search_node(root->right, node_value);
    }
}

void bst_delete_node(bst_node** root, int node_value) {
    bst_node* target = *root;

    if (target == NULL) {
        return;
    }

    if (node_value < target->value) {
        bst_delete_node(&(target->left), node_value);
    } else if (node_value > target->value) {
        bst_delete_node(&(target->right), node_value);
    } else {
        if (target->left) {
            bst_node* max = target->left;
            while (max->right != NULL) {
                max = max->right;
            }
            target->value = max->value;
            bst_delete_node(&(target->left), max->value);
        } else if (target->right) {
            bst_node* min = target->right;
            while (min->left != NULL) {
                min = min->left;
            }
            target->value = min->value;
            bst_delete_node(&(target->right), min->value);
        } else {
            free(target);
            *root = NULL;
        }
    }
}

void bst_free(bst_node* root) {
    if (root != NULL) {
        bst_free(root->left);
        bst_free(root->right);
    }
    free(root);
}

void bst_print(bst_node* root, unsigned level) {
    if (root == NULL) {
        return;
    }

    for (unsigned i = 0; i < level; i++) {
        printf(i == level - 1 ? "󱞩 " : "  ");
    }

    printf("%d\n", root->value);
    bst_print(root->left, level + 1);
    bst_print(root->right, level + 1);
}

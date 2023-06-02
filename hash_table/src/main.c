#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define TABLE_SIZE 5

typedef struct node_info {
  char* key;
  char* value;
  struct node_info* next;
} node;

typedef struct {
  node** entries;
} hash_table;

const size_t hash_fnv1a(const char* key) {
  size_t hash        = 0xcbf29ce484222325;
  const size_t prime = 0x100000001b3;

  size_t c = 0;
  while ((c = *key++)) {
    hash ^= c;
    hash *= prime;
  }
  return hash % TABLE_SIZE;
}

hash_table* table_init(const size_t size) {
  hash_table* table = (hash_table*)malloc(sizeof(hash_table));
  table->entries    = malloc(sizeof(node*) * size);

  for (uint32_t i = 0; i < size; i++)
    table->entries[i] = NULL;

  return table;
}

node* new_entry(const char* key, const char* value) {
  node* n  = (node*)malloc(sizeof(node));
  n->key   = (char*)malloc(strlen(key) + 1);
  n->value = (char*)malloc(strlen(value) + 1);
  strcpy(n->key, key);
  strcpy(n->value, value);
  return n;
}

// currently not handling collisons
size_t collisons = 0;
void table_put(hash_table* table, const char* key, const char* value) {
  size_t index = hash_fnv1a(key);
  node* n      = table->entries[index];
  if (n == NULL) {
    table->entries[index] = new_entry(key, value);
    return;
  }
  if (strcmp(n->key, key) == 0) {
    free(n->value);
    n->value = (char*)malloc(strlen(value) + 1);
    strcpy(n->value, value);
    return;
  } else {
    collisons++;
  }
}

node* table_lookup(hash_table* table, const char* key) {
  size_t index = hash_fnv1a(key);
  node* n      = table->entries[index];
  return (n && strcmp(n->key, key) == 0) ? n : NULL;
}

void table_delete(hash_table* table, const char* key) {
  size_t index = hash_fnv1a(key);
  node* n      = table->entries[index];

  if (n && strcmp(n->key, key) == 0) {
    free(n->value);
    free(n->key);
    table->entries[index] = NULL;
  }
}

void table_destroy(hash_table* table) {
  free(table->entries);
  free(table);
}

void table_print(hash_table* table) {
  printf("\n");
  puts("hash\t\tkey\t\tvalue");
  puts("-----\t\t-----\t\t-----");
  for (uint32_t i = 0; i < TABLE_SIZE; i++) {
    if (!(table->entries[i] == NULL)) {
      printf("%i\t\t%s\t\t%s\n", i, table->entries[i]->key,
             table->entries[i]->value);
    }
  }
  printf("\n");
}

int main(void) {
  hash_table* t1 = table_init(TABLE_SIZE);

  char* key1 = "India";
  char* key2 = "Japan";
  char* key3 = "China";
  char* key4 = "Norway";
  char* key5 = "Germany";
  char* key6 = "England";
  char* key7 = "Russia";

  printf("\ntable size: %u\n", TABLE_SIZE);
  table_put(t1, key1, "Deli");
  table_put(t1, key2, "Tokyo");
  table_put(t1, key3, "Beijing");
  table_put(t1, key4, "Oslo");
  table_put(t1, key5, "Berlin");
  table_put(t1, key6, "London");
  table_put(t1, key7, "Moscow");

  table_print(t1);

  table_put(t1, key1, "Delhi");
  table_print(t1);

  node* key_node = table_lookup(t1, key1);
  if (key_node) {
    printf("found pair = %s : %s\n", key_node->key, key_node->value);
  } else {
    puts("\nlookup: couldn't find pair");
  }

  table_delete(t1, key2);
  table_print(t1);

  printf("collisons: %zu\n", collisons);
  table_destroy(t1);

  return EXIT_SUCCESS;
}

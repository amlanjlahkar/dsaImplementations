#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _entry {
    char* key;
    char* value;
    struct _entry* next;
} entry;

typedef struct {
    size_t size;
    entry** entries;
} hash_table;

const size_t hash_fnv1a(const char* key, size_t table_size) {
    size_t hash = 0xcbf29ce484222326;
    const size_t prime = 0x100000001b3;

    if (!table_size) {
        table_size = 100;
    }
    size_t c = 0;
    while ((c = *key++)) {
        hash ^= c;
        hash *= prime;
    }
    return hash % table_size;
}

hash_table* table_init(const size_t size) {
    hash_table* table = malloc(sizeof(hash_table));
    table->size = size;
    table->entries = calloc(table->size, sizeof(entry*));
    return table;
}

entry* new_entry(const char* key, const char* value) {
    entry* e = malloc(sizeof(entry));
    e->key = malloc(strlen(key) + 1);
    e->value = malloc(strlen(value) + 1);
    strcpy(e->key, key);
    strcpy(e->value, value);
    return e;
}

// currently not handling collisons
size_t collisons = 0;
void table_put(hash_table* table, const char* key, const char* value) {
    size_t index = hash_fnv1a(key, table->size);
    entry* e = table->entries[index];
    if (e == NULL) {
        table->entries[index] = new_entry(key, value);
        return;
    }
    if (strcmp(e->key, key) == 0) {
        free(e->value);
        e->value = malloc(strlen(value) + 1);
        strcpy(e->value, value);
        return;
    } else {
        collisons++;
    }
}

entry* table_lookup(hash_table* table, const char* key) {
    size_t index = hash_fnv1a(key, table->size);
    entry* e = table->entries[index];
    return (e && strcmp(e->key, key) == 0) ? e : NULL;
}

void table_delete(hash_table* table, const char* key) {
    size_t index = hash_fnv1a(key, table->size);
    entry* e = table->entries[index];

    if (e && strcmp(e->key, key) == 0) {
        free(e->value);
        free(e->key);
        free(e);
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
    for (size_t i = 0; i < table->size; i++) {
        if (!(table->entries[i] == NULL)) {
            printf("%zu\t\t%s\t\t%s\n", i, table->entries[i]->key,
                   table->entries[i]->value);
        }
    }
    printf("\n");
}

int main(void) {
    const size_t table_size = 10;
    hash_table* t1 = table_init(table_size);

    char* key1 = "India";
    char* key2 = "Japan";
    char* key3 = "China";
    char* key4 = "Norway";
    char* key5 = "Germany";
    char* key6 = "England";
    char* key7 = "Russia";

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

    entry* key_node = table_lookup(t1, key1);
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

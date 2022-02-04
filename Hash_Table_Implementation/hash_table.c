#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

hash_table* new_ht(void) {
    hash_table* ht = (hash_table*) malloc(sizeof(hash_table));

    if(ht == NULL){
        printf("Memory not allocated for new hash table.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if malloc returned null
    }
    else{
        printf("Memory allocated for new hash table successfully.\n");
        printf("The address of the hash table is: %u\n", ht);
    }

    ht->size = 53; // starts with 53 by default
    ht->count = 0;
    ht->items = (ht_item**) calloc((size_t)ht->size, sizeof(ht_item*));

    return ht;
}

//
static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

//
hash_table* ht_new() {
    hash_table* ht = malloc(sizeof(hash_table));

    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

/* Internal Function helper for clear_table function
   It frees memory for the passed in ht_item struct */
static void clear_item(ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

/* Clears the hash table and frees the memory, resets hash table */
hash_table* clear_table(hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            clear_item(item);
        }
    }
    free(ht->items);
    free(ht);
    return new_ht(void);
}

// Hash Function used to get the index of the key
static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

//
static int contains(){

}

// Double hashing for collisions
static int get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

//
void ht_insert(hash_table* ht, const char* key, const char* value) {
    // Check if key is unique (does not already exist in the hash Table)

    // If key is unique, find hash index, add to hash table

    // Else if key is not unique (already exists), update the value of that key

    ht_item* item = ht_new_item(key, value);
    int index = get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        index = get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

//
char* ht_search(hash_table* ht, const char* key) {
    int index = get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        index = get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

//
void remove_item(hash_table* ht, const char* key) {
    int index = get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

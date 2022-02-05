#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

hash_table* new_ht(void) {
    hash_table* ht = (hash_table*) malloc(sizeof(hash_table));

    if(ht == NULL){
        printf("Unable to allocate memory for new hash table.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if malloc returned null
    }

    ht->size = 53; // starts with 53 by default
    ht->count = 0;
    ht->items = (ht_item**) calloc((size_t)ht->size, sizeof(ht_item*));

    if(ht->items == NULL){
        printf("Unable to allocate memory for array of items for the hash table.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if calloc returned null
    }

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
static int ht_hash(const char* key, const int a, const int m) {
    long hash = 0;
    const int key_length = strlen(key);
    for (int i = 0; i < key_length; i++) {
        hash += (long)pow(a, key_length - (i+1)) * key[i];
        hash = hash % m;
    }
    return (int)hash;
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

/* Checks if the key (given the item [key-value pair]) exists in the hash table
   @param int index: the index of the hash table for the key after hashing
   @param ht_item* item: the ht_item struct which contains the key-value pair
   Returns 1 if true and 0 if false */
static int contains_key(int index, ht_item* item){
    // If ht_item is null then no item exists for that index which means the key does not exist
    if(item == NULL){
        return 0; // return 0, 0=false the key does not exist in the hash table
    }

    // else item exists at index, check if key is the same key passed into function
    if(strcmp(item->key, key) == 0){
        return 1; // return 1, 1=true the key exists in the hash table
    }

    return 0; // return 0, 0=false the key does not exist in the hash table
}

/* Remove item (key-value pair) in the hash table
   If item does not exist in the hash table then it will
   just print a message to the user*/
void remove_item(hash_table* ht, const char* key) {
    // Get the hash index for the given key
    int index = get_hash(key, ht->size);

    // Get the ht_item from the hash table at the index after hashing
    ht_item* item = ht->items[index];

    // Check if key exists in the hash table
    int key_exists = contains_key(index, item); // 1 = true, 0 = false

    // If it does not exist, print message to user, exit function
    if(key_exists == 0){
        printf("Key does not exist in the hash table.\n");
        return; // terminate the function, continue the program
    }
    else if(key_exists == 1){ // Else it exists, remove it (free memory too)
        clear_item(item); // free the memory for that item (key-value pair)
        ht->items[index] = &HT_DELETED_ITEM; // mark this index in hash table as "deleted"
        ht->num_items--; // decrement the num_items in hash table since we removed an item
    }
}

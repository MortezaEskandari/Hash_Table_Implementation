#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "prime.c"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static hash_table* ht_new_sized(const int base_size) {

    hash_table* ht = (hash_table*) malloc(sizeof(hash_table));

    if(ht == NULL){
        printf("Unable to allocate memory for new hash table.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if malloc returned null
    }

    ht->table_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = xcalloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

hash_table* new_ht(void) {

    hash_table* ht = (hash_table*) malloc(sizeof(hash_table));

    if(ht == NULL){
        printf("Unable to allocate memory for new hash table.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if malloc returned null
    }

    ht->table_size = HT_INITIAL_SIZE; // starts with 17 by default
    ht->num_items = 0;
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

    ht_item* item = malloc(sizeof(ht_item));

    if(item == NULL){
        printf("Unable to allocate memory for new item (key-value) pair.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if malloc returned null
    }

    item->key = strdup(k);
    item->value = strdup(v);
    return item;
}

/* Internal Function helper for clear_table function
   It frees memory for the passed in ht_item struct */
static void free_item(ht_item* item) {

    free(item->key);
    free(item->value);
    free(item);
}

/* Clears the hash table and frees the memory, resets hash table */
hash_table* clear_table(hash_table* ht) {

    for (int i = 0; i < ht->table_size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            free_item(item);
        }
    }
    free(ht->items);
    free(ht);
    return new_ht(void);
}

// Hash Function used to get the index of the key
static int ht_hash(const char* k, const int prime_num, const int table_size) {

    long hash = 0;
    const int key_length = strlen(key);
    for (int i = 0; i < key_length; i++) {
        hash += (long)pow(prime_num, key_length - (i+1)) * k[i];
        hash = hash % table_size;
    }
    return (int)hash;
}

// Double hashing for collisions
static int get_hash(const char* k, const int table_size, const int attempt) {

    if(attempt == 0){
        const int hash_a = ht_hash(k, HT_PRIME_1, table_size);
        return hash_a % table_size;
    }
    else{
        const int hash_a = ht_hash(k, HT_PRIME_1, table_size);
        const int hash_b = ht_hash(k, HT_PRIME_2, table_size);
        return (hash_a + (attempt * (hash_b + 1))) % table_size;
    }
}

//
void ht_insert(hash_table* ht, const char* key, const char* value) {

    // initialize the item struct to insert into the hash table
    ht_item* item = ht_new_item(key, value);

    // get the hash index the item (key-value pair) will be inserted at
    int index = get_hash(item->key, ht->table_size, 0);

    // check for collisions and keep double hashing until spot found
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        if(strcmp(cur_item->key, key) == 0){
            free_item(cur_item);
            ht->items[index] = item;
            return;
        }
        index = get_hash(item->key, ht->table_size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->num_items++;
}

//
char* ht_search(hash_table* ht, const char* key) {

    if(ht->num_items == 0){
        printf("n\Hash table is empty, no items to find.\n");
    }

    int index = get_hash(key, ht->table_size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if(item != &HT_DELETED_ITEM){
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = get_hash(key, ht->table_size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

/* Remove item (key-value pair) in the hash table
   If item does not exist in the hash table then it will
   just print a message to the user*/
void remove_item(hash_table* ht, const char* key) {

    // Check if hash table is empty
    if(ht->num_items == 0){
        printf("n\Hash table is empty, no items to remove.\n");
    }

    // Get the hash index for the given key
    int index = get_hash(key, ht->table_size, 0);

    // Get the ht_item from the hash table at the index after hashing
    ht_item* item = ht->items[index];

    // Loop and find item to delete, if it exists
    int i = 1;
    while(item != NULL){ // Loop until you get item == NULL, end of chain, item does not exist
        if(item != &HT_DELETED_ITEM){
            if(strcmp(item->key, key) == 0){
                free_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
                ht->num_items--;
                printf("\nItem successfully removed from the hash table.\n");
                return;
            }
        }
        index = get_hash(key, ht->table_size, i);
        item = ht->items[index];
        i++;
    }
}

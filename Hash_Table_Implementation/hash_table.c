#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "prime.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static hash_table* ht_new_sized(const int new_table_size) {

    hash_table* ht = (hash_table*) malloc(sizeof(hash_table));

    if(ht == NULL){
        printf("Unable to allocate memory for new hash table.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if malloc returned null
    }

    ht->table_size = new_table_size; // starts with 17 by default if calling ht_new
    ht->num_items = 0;
    ht->items = (ht_item**) calloc((size_t)ht->table_size, sizeof(ht_item*));

    if(ht->items == NULL){
        printf("Unable to allocate memory for array of items for the hash table.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if calloc returned null
    }

    return ht;
}

hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_SIZE);
}

//
static ht_item* ht_new_item(const char* key, const char* value) {

    ht_item* item = (ht_item*) malloc(sizeof(ht_item));

    if(item == NULL){
        printf("Unable to allocate memory for new item (key-value) pair.\n");
        printf("Quitting program...\n");
        exit(0); // abort program if malloc returned null
    }

    item->key = strdup(key);
    item->value = strdup(value);

    return item;
}

/* Internal Function helper for free_table function
   It frees memory for the passed in ht_item struct */
static void ht_free_item(ht_item* item) {

    free(item->key);
    free(item->value);
    free(item);
}

/* Clears the hash table and frees the memory, resets hash table */
void ht_free_table(hash_table* ht) {

    for (int i = 0; i < ht->table_size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_free_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

// Hash Function used to get the index of the key
static int ht_hash(const char* key, int prime_num, int table_size) {

    long hash = 0;
    const int key_length = strlen(key);
    for (int i = 0; i < key_length; i++) {
        hash += (long)pow(prime_num, key_length - (i+1)) * key[i];
        hash = hash % table_size;
    }
    return (int)hash;
}

// Double hashing for collisions
static int ht_get_hash(const char* key, int table_size, int attempt) {

    if(attempt == 0){
        const int hash_a = ht_hash(key, HT_PRIME_1, table_size);
        return hash_a % table_size;
    }
    else{
        const int hash_a = ht_hash(key, HT_PRIME_1, table_size);
        const int hash_b = ht_hash(key, HT_PRIME_2, table_size);
        return (hash_a + (attempt * (hash_b + 1))) % table_size;
    }
}

static void ht_resize(hash_table* ht, int new_table_size){
    if(new_table_size < HT_INITIAL_SIZE){
        return;
    }

    hash_table* new_ht = ht_new_sized(new_table_size);
    for (int i = 0; i < ht->table_size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_put_item(new_ht, item->key, item->value);
        }
    }

    ht->num_items = new_ht->num_items;

    const int temp_size = ht->table_size;
    ht->table_size = new_ht->table_size;
    new_ht->table_size = temp_size;

    ht_item** temp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = temp_items;

    ht_free_table(new_ht);
}

static void ht_resize_up(hash_table* ht){
    const int new_table_size = next_prime(ht->table_size * 2);
    ht_resize(ht, new_table_size);
}

static void ht_resize_down(hash_table* ht){
    const int new_table_size = next_prime(ht->table_size / 2);
    ht_resize(ht, new_table_size);
}

//
void ht_put_item(hash_table* ht, const char* key, const char* value) {

    const int load = ht->num_items * 100 / ht->table_size;
    if(load > 70){
        ht_resize_up(ht);
    }

    // initialize the item struct to insert into the hash table
    ht_item* item = ht_new_item(key, value);

    // get the hash index the item (key-value pair) will be inserted at
    int index = ht_get_hash(item->key, ht->table_size, 0);

    // check for collisions and keep double hashing until spot found
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        if(strcmp(cur_item->key, key) == 0){
            ht_free_item(cur_item);
            ht->items[index] = item;
            return;
        }
        index = ht_get_hash(item->key, ht->table_size, i);
        cur_item = ht->items[index];
        i++;
    }

    ht->items[index] = item;
    ht->num_items++;
}

//
char* ht_get_item(hash_table* ht, const char* key) {

    if(ht->num_items == 0){
        printf("n\Hash table is empty, no items to find.\n");
    }

    int index = ht_get_hash(key, ht->table_size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if(item != &HT_DELETED_ITEM){
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = ht_get_hash(key, ht->table_size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}

/* Remove item (key-value pair) in the hash table
   If item does not exist in the hash table then it will
   just print a message to the user*/
void ht_remove_item(hash_table* ht, const char* key) {

    const int load = ht->num_items * 100 / ht->table_size;
    if (load < 10) {
        ht_resize_down(ht);
    }

    // Check if hash table is empty
    if(ht->num_items == 0){
        printf("\nHash table is empty, no items to remove.\n");
        return;
    }

    // Get the hash index for the given key
    int index = ht_get_hash(key, ht->table_size, 0);

    // Get the ht_item from the hash table at the index after hashing
    ht_item* item = ht->items[index];

    // Loop and find item to delete, if it exists
    int i = 1;
    while(item != NULL){ // Loop until you get item == NULL, end of chain, item does not exist
        if(item != &HT_DELETED_ITEM){
            if(strcmp(item->key, key) == 0){
                ht_free_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
                ht->num_items--;
                printf("\nItem successfully removed from the hash table.\n");
                return;
            }
        }
        index = ht_get_hash(key, ht->table_size, i);
        item = ht->items[index];
        i++;
    }

    printf("\nItem does not exist in hash table.\n");
}

void print_hash_table(hash_table* ht){
    for(int i = 0; i < ht->table_size; i++){
        ht_item* item = ht->items[i];
        if(item != NULL){
            if(item != &HT_DELETED_ITEM){
                printf("%d)\tMemory: %p\tKey: %s\tValue: %s\n",i, item, item->key, item->value);
            }
            else if(item == &HT_DELETED_ITEM){
                printf("%d)\tMemory: %p\tDELETED ITEM\n",i, item);
            }
        }
        else{
            printf("%d)\tMemory: %p\tNULL\n",i, item);
        }
    }
}

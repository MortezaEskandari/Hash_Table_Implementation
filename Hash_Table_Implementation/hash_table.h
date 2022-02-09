#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

#define HT_INITIAL_SIZE

/* hash table item (holds the key-value pair) struct
   hash table will be an array of these key-value pairs
   both key-value pairs will be of type string for this project
   all the concepts of hash table are the same in this project for any type however */
typedef struct {
    char* key; // the key (string data type) used for the hash table
    char* value; // the value (string data type) used for the hash table
} ht_item;

/* the hash table struct */
typedef struct {
    int table_size; // the current table size (default start is 17)
    int num_items; // number of items in the hash table or the "size" of the hash table
    ht_item** items; // array of pointers to each (key-value) pairs
} hash_table;

/* Initialize an empty hash table and return its pointer to it */
hash_table* new_ht(void);

/* Return the size (current capacity) of the hash table */
int get_size(hash_table* ht);

/* Clears the hash table and frees the memory */
void free_table(hash_table* ht);

/* put item (key-value pair) into the hash table, if it does not already exist
   else do nothing and print a message to let user know */
void put_item(hash_table* ht, const char* k, const char* v);

/* get item (key-value pair) from the hash  table, if it exists
   Return: the pointer to ht_item (key-value pair), else null if not exist */
ht_item* get_item(hash_table* ht, const char* k);

/* Remove item (key-value pair) in the hash table
   If item does not exist in the hash table then it will
   just print a message to the user*/
void remove_item(hash_table* ht, const char* k);

#endif // HASH_TABLE_H_INCLUDED

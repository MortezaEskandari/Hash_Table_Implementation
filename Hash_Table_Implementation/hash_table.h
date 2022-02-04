#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

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
    int capacity; // the current capacity of the hash table (default start is 53)
    int numItems; // number of items in the hash table or the "size" of the hash table
    ht_item** items; // array of pointers to each (key-value) pairs
} hash_table;

/* Initialize an empty hash table and return its pointer to it */
hash_table* new_ht(void);

/* Return the size (current capacity) of the hash table */
int get_size(hash_table* ht);

/* Clears the hash table and frees the memory, resets hash table
   Returns a brand new hash table by calling new_ht function */
hash_table* clear_table(hash_table* ht);

/* put item (key-value pair) into the hash table, if it does not already exist
   else do nothing and print a message to let user know */
void put_item(hash_table* ht, const char* key, const char* value);

/* get item (key-value pair) from the hash  table, if it exists
   Return: the pointer to value of the (key-value pair) else null if not exist */
char* get_item(hash_table* ht, const char* key);

/* Delete item (key-value pair) in hash table, if it exists else do nothing */
ht_item* remove_item(hash_table* ht, const char* key);

#endif // HASH_TABLE_H_INCLUDED

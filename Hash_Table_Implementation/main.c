#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "prime.h"

hash_table* ht;

int main()
{
    int loop = 1; // loop = 1 (continue loop) , loop = 0 (end loop)
    int option = 0; // stores the option user choses
    int validOption = 0; // uses to check if the user input is a valid option (an int)
    char *key, *value;
//    char* value; // Above error when only putting * for key and not for value also other wise separate line for value like this line

     ht = ht_new(); // The hash table initialization

    // Loop until user choses Quit then end loop and program
    while(loop != 0){

        // get a valid user input
        do{
            // Give user options to choose from
            printf("Please select an option below.\n");
            printf("1) Print Hash Table.\n");
            printf("2) Add Item.\n");
            printf("3) Remove Item.\n");
            printf("4) Get Item.\n");
            printf("5) Clear Hash Table.\n");
            printf("6) Quit.\n");
            printf("\nEnter Option (1-6): ");

            // Get user input
            validOption = scanf("%d", &option);

            if(validOption != 1){
                printf("\nInvalid option. Choose between 1-6.\n\n");
                scanf("%*[^\n]");
            }
        } while(validOption != 1);

        // process user input
        switch(option){
            case 1:
                printf("\n");
                print_hash_table(ht);
                printf("\n");
                break;
            case 2:
                printf("\nAdd Key-Value pair\n");

                key = (char*) malloc(sizeof(char)*256);

                if(key == NULL){
                    printf("Unable to allocate memory for key.\n");
                    printf("Quitting program...\n");
                    exit(0); // abort program if malloc returned null
                }

                value = (char*) malloc(sizeof(char)*256);

                if(value == NULL){
                    printf("Unable to allocate memory for value.\n");
                    printf("Quitting program...\n");
                    exit(0); // abort program if malloc returned null
                }

                printf("Enter key: ");
                scanf("%255s",key);

                printf("Enter value: ");
                scanf("%255s",value);

                ht_put_item(ht, key, value);

                printf("\n");

                free(key);
                free(value);
                break;
            case 3:
                printf("\nRemove Key-Value pair\n");

                key = (char*) malloc(sizeof(char)*256);

                if(key == NULL){
                    printf("Unable to allocate memory for key.\n");
                    printf("Quitting program...\n");
                    exit(0); // abort program if malloc returned null
                }

                printf("Enter key: ");
                scanf("%255s",key);

                ht_remove_item(ht, key);

                printf("\n");

                free(key);
                break;
            case 4:
                printf("\nSearch for Key-Value pair\n");

                key = (char*) malloc(sizeof(char)*256);

                if(key == NULL){
                    printf("Unable to allocate memory for key.\n");
                    printf("Quitting program...\n");
                    exit(0); // abort program if malloc returned null
                }

                printf("Enter key: ");
                scanf("%255s",key);

                if(ht_get_item(ht, key) != NULL){
                    printf("\nKey: %s\tValue: %s\n\n",key, ht_get_item(ht, key));
                }

                free(key);
                break;
            case 5:
                printf("\Clearing the hash table...\n");

                ht = ht_free_table(ht, 1);

                if(ht != NULL){
                    printf("\nSuccessfully cleared the hash table\n\n");
                    print_hash_table(ht);
                    printf("\n");
                }
                else{
                    printf("\nError occurred trying to clear hash table...\n");
                    printf("Quitting program...\n");
                    exit(0); // abort program if malloc returned null
                }

                break;
            case 6:
                printf("\nQuitting program...\n");
                loop = 0;
                break;
            default:
                printf("\nInvalid option. Chose between 1-6.\n\n");
                break;
        }
    }


    return 0;
}

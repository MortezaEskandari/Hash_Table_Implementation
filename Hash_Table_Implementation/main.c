#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "prime.h"

int main()
{
    int loop = 1; // loop = 1 (continue loop) , loop = 0 (end loop)
    int option = 0; // stores the option user choses
    int validOption = 0; // uses to check if the user input is a valid option (an int)
    char* key;
    char* value;

    hash_table* ht = ht_new(); // The hash table initialization

    // Loop until user choses Quit then end loop and program
    while(loop != 0){

        // get a valid user input
        do{
            // Give user options to choose from
            printf("Please select an option below.\n");
            printf("1) Print Hash Table.\n");
            printf("2) Add Item.\n");
            printf("3) Delete Item.\n");
            printf("4) Search for Item.\n");
            printf("5) Print size of Hash Table.\n");
            printf("6) Clear Hash Table.\n");
            printf("7) Quit.\n");
            printf("\nEnter Option (1-7): ");

            // Get user input
            validOption = scanf("%d", &option);

            if(validOption != 1){
                printf("\nInvalid option. Choose between 1-7.\n\n");
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
                printf("Not implemented yet.\n");
                break;
            case 4:
                printf("Not implemented yet.\n");
                break;
            case 5:
                printf("Not implemented yet.\n");
                break;
            case 6:
                printf("Not implemented yet.\n");
                break;
            case 7:
                printf("\nQuitting program...\n");
                loop = 0;
                break;
            default:
                printf("\nInvalid option. Chose between 1-7.\n\n");
                break;
        }
    }


    return 0;
}

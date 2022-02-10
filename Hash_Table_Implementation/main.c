#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "prime.h"

int main()
{
    int loop = 1; // loop = 1 (continue loop) , loop = 0 (end loop)
    int option = 0; // stores the option user choses
    int validOption = 0; // uses to check if the user input is a valid option (an int)

    hash_table* ht = ht_new(void); // The hash table initialization

    // Loop until user choses Quit then end loop and program
    while(loop != 0){

        // get a valid user input
        do{
            // Give user options to choose from
            printf("Please select an option below.\n\n");
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
                printf("Not implemented yet.\n");
                break;
            case 2:
                char* key, value;
                printf("Enter key: ");
                scanf("%d", )
                ht_put_item(ht, key, value);
                break;
            case 3:
                break;
            case 4:
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

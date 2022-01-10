#include <stdio.h>
#include "list_operations.h"

int main() {
    int input = 0; int data;
    while(1) {
        puts("\n1) insert node at the front"
             "\n2) free node from the front"
             "\n3) print the list"
             "\n4) exit\n");

        printf("Enter your input: ");
        scanf("%d", &input);
        if (input < 1 || input > 4) {
            puts("\nPlease provide a valid input.");
            continue;
        } else if (input == 4) {
            puts("\nterminated.\n");
            break;
        }

        switch(input) {
            case 1 : {
                printf("Enter an integer: ");
                scanf("%d", &data);
                insert_front(data);
                puts("node has been inserted at the front of the list.");
                break;
            }
            case 2 : {
                free_front();
                puts("node has been removed from the front of the list.");
                break;
            }
            case 3 : {
                printList();
                break;
            }
        }
    }
}

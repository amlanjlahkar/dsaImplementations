#include <stdio.h>
#include <stdlib.h>
#include "list_operations.h"

// ensures successful reading of single integer from stdin
void warn(int *si);

int main() {
    int input = 0; int data;
    while(1) {
        puts("\n1) insert node at the front"
             "\n2) insert node at the end"
             "\n3) free node from the front"
             "\n4) free node from the end"
             "\n5) search for node info in the list"
             "\n6) print the list"
             "\n7) exit\n");

        printf("Enter your input: ");
        warn(&input);
        if (input < 1 || input > 7) {
            puts("\nPlease provide a valid input.");
            continue;
        } else if (input == 7) {
            puts("\nterminated.\n");
            break;
        }

        switch(input) {
            case 1 : {
                printf("Enter an integer: ");
                warn(&data);
                insert_front(data);
                puts("node has been inserted at the front of the list.");
                break;
            }
            case 2 : {
                printf("Enter an integer: ");
                warn(&data);
                insert_rear(data);
                puts("node has been inserted at the end of the list.");
                break;
            }
            case 3 : {
                int data = 0;
                if (is_empty()) {
                    puts("\nlist is empty.");
                    break;
                }
                data = free_front();
                printf("node containing \'%d\' has been removed from the front of the list.\n", data);
                break;
            }
            case 4 : {
                int data = 0;
                if (is_empty()) {
                    puts("\nlist is empty.");
                    break;
                }
                data = free_rear();
                printf("node containing \'%d\' has been removed from the end of the list.\n", data);
                break;
            }
            case 5 : {
                if (is_empty()) {
                    puts("\nlist is empty.");
                    break;
                }
                printf("Enter integer to search for in the list: ");
                warn(&data);
                int step = 0;
                if ((step = search(data))) {
                    if (step == 1)
                        printf("The integer \'%d\' is available at the very front of the list.\n", data);
                    else
                        printf("The integer \'%d\' is available at the distance of %d node(s) from head.\n", data, step);
                }
                else
                    printf("The integer \'%d\' is not in the list.\n", data);
                break;
            }
            case 6 : {
                printList();
                break;
            }
        }
    }
}

void warn(int *si) {
    if (scanf(" %d", si) != 1) {
        puts("\nError reading input\n"
        "(please re-run the compiled output)\n");
        exit(1);
    }
}


#include <stdio.h>
#include <stdlib.h>
#include "list_operations.h"

// ensures successful reading of single integer from stdin
void warn(int *si);

int main() {
    int input = 0; int data;
    while(1) {
        puts("\n1) insert node at the front"
             "\n2) insert node after another exisiting node"
             "\n3) insert node at the end"
             "\n4) free node from the front"
             "\n5) free an intermediate node in the list"
             "\n6) free node from the end"
             "\n7) search for node data in the list"
             "\n8) print the list"
             "\n9) reset the list"
             "\n10) exit\n");

        printf("enter your input: ");
        warn(&input);
        if (input < 1 || input > 10) {
            puts("\nplease provide a valid input.");
            continue;
        } else if (input == 10) {
            puts("\nterminated.\n");
            break;
        }

        switch(input) {
            case 1 : {
                printf("enter data(integer) to be stored in the new node: ");
                warn(&data);
                insert_front(data);
                printf("new node containing \'%d\' has been inserted at the front of the list.\n"
                       "(new number of node(s) in the list = %d)\n", data, list_size());
                break;
            }
            case 2 : {
                if(is_empty()) {
                    puts("\nlist is empty!");
                    break;
                }
                int data_prev = 0, data_new = 0;
                printf("enter the data(integer) of the preceding node: ");
                warn(&data_prev);
                if (!search(data_prev)) {
                    printf("\ninvalid insertion!\n(node containing \'%d\' doesn't exist in the list)\n", data_prev);
                    break;
                }
                printf("enter data(integer) to be stored in the new node: ");
                warn(&data_new);
                insert_after(data_prev, data_new);
                printf("new node containg \'%d\' has been inserted in the list.\n"
                       "(new number of node(s) in the list = %d)\n", data_new, list_size());
                break;
            }
            case 3 : {
                printf("enter data(integer) to be stored in the new node: ");
                warn(&data);
                insert_rear(data);
                printf("new node containing \'%d\' has been inserted at the end of the list.\n"
                       "(new number of node(s) in the list = %d)\n", data, list_size());
                break;
            }
            case 4 : {
                if (is_empty()) {
                    puts("\nlist is empty!");
                    break;
                }
                int data = 0;
                data = free_front();
                printf("node containing \'%d\' has been freed from the front of the list.\n"
                       "(number of node(s) remaining in the list = %d)\n", data, list_size());
                break;
            }
            case 5 : {
                if (is_empty()) {
                    puts("\nlist is empty!");
                    break;
                }
                int data_prev = 0;
                printf("enter the data(integer) of the preceding node: ");
                warn(&data_prev);
                free_after(data_prev);
                break;
            }
            case 6 : {
                if (is_empty()) {
                    puts("\nlist is empty!");
                    break;
                }
                int data = 0;
                data = free_rear();
                printf("node containing \'%d\' has been freed from the end of the list.\n"
                       "(number of node(s) remaining in the list = %d)\n", data, list_size());
                break;
            }
            case 7 : {
                if (is_empty()) {
                    puts("\nlist is empty!");
                    break;
                }
                printf("enter the data(integer) of a node to search for in the list: ");
                warn(&data);
                int index = 0;
                if ((index = search(data))) {
                    if (index == 1)
                        printf("the node containing \'%d\' is available at the very front of the list.\n", data);
                    else
                        printf("the node containing \'%d\' is available at the distance of %d node(s) from head.\n", data, index);
                }
                else
                    printf("the node containing \'%d\' doesn't exist in the list.\n", data);
                break;
            }
            case 8 : {
                printList();
                break;
            }
            case 9 : {
                if (!is_empty()) {
                resetList();
                puts("list has been reset.");
                break;
                }
                puts("\nlist is already empty!");
                break;
            }
        }
    }
}

void warn(int *si) {
    if (scanf(" %d", si) != 1) {
        puts("\nerror reading input!\n"
        "(please re-run the compiled output)\n");
        exit(1);
    }
}


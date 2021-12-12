/* implementing a simple stack of FILO mechanism containing integers,
 * that is, the first integer(if using array then the element at index 0) to enter the stack
 * will be the last integer to be removed from the stack.
 *
 * AUTHOR: Amlanjyoti Lahkar
 */

#include <stdio.h>
#include <stdlib.h>

// for colored printing of critical warnings/errors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TRUE  1
#define FALSE 0

#define STACKSIZE 5
typedef struct {
    int topindex;
    int members[STACKSIZE];
} stackrec;
/* index of the top of the stack element is set to -1
 * so that upon first entry, -1 + 1 = 0,
 * which is the first element of the array containing the stack items
 */
stackrec stack = { .topindex = -1 };

// stack functions
int isEmpty(stackrec *);
int push(stackrec *, int);
int pop(stackrec *);

// miscellaneous
void warn(int *);

int main(void) {
    int input = 0, topitem = 0, pusheditem = 0, poppeditem = 0;
    printf("\nThe stack can contain atmost %d items and is currently empty.\n"
    "Below are some operations available to perform on it.\n", STACKSIZE);

    // printig the menu infinitely until the specified condition is met
    while(1) {
        puts("\n--------------------------------------------------");
        puts("\n1) isEmpty (indicates either TRUE or FALSE)\n"
        "2) push (insert a new item on top of the stack)\n"
        "3) pop (remove an item from the top of the stack)\n"
        "4) tos (print out the item on top of the stack)\n"
        "5) peek (get an overview of current items in the stack)\n"
        "6) exit\n");
        puts("--------------------------------------------------");

        printf("\nEnter your input(1,2,3,4,5 or 6): ");
        warn(&input);
        if (input < 1 || input > 6) {
            puts(ANSI_COLOR_RED "\nPlease provide a valid input." ANSI_COLOR_RESET);
            continue;
        } else if (input == 6) {
            puts("\nProgram terminated.\n");
            break;
        }

        switch(input) {
            case 1 :
                puts((isEmpty(&stack)) ? "\nTRUE" : "\nFALSE");
                break;
            case 2 :
                if (stack.topindex == (STACKSIZE - 1)) {
                    puts(ANSI_COLOR_RED "\nStack is already full"
                    " and attempting to add more items to it will cause overflow." ANSI_COLOR_RESET);
                    break;
                }
                printf("\nEnter an item(number): ");
                warn(&pusheditem);
                topitem = push(&stack, pusheditem);
                if (stack.topindex < (STACKSIZE - 1))
                    printf("\nA new item has been inserted into the stack.\n"
                    "it now contains %d item(s).\n", (stack.topindex)+1);
                else if (stack.topindex < STACKSIZE)
                    printf("\nA new item has been inserted into the stack.\n"
                    "The stack is now full.\n");
                break;
            case 3 :
                if ((poppeditem = pop(&stack))) {
                    topitem = stack.members[stack.topindex];
                    if (stack.topindex != -1)
                        printf("\nThe item \'%d\' at the top of the stack has been removed.\n"
                        "The stack now contains %d item(s).\n", poppeditem, (stack.topindex)+1);
                    else
                        printf("\nThe last item \'%d\' of the stack has been removed.\n"
                        "The stack is now empty!\n", poppeditem);
                }
                break;
            case 4 :
                if (isEmpty(&stack))
                    puts("\nThe stack is empty!");
                else
                    printf("\nThe item currently at the top of the stack is %d.\n", topitem);
                break;
            case 5 :
                if (isEmpty(&stack))
                    puts("\nThe stack is empty!");
                else {
                    puts("\nThe item(s) currently in the stack are: \n");
                    for (int i = stack.topindex; i >= 0; i--) {
                        if (i == stack.topindex)
                            printf("%7d\t<--- top of the stack\n", stack.members[i]);
                        else if (i == 0)
                            printf("%7d\t<--- bottom of the stack\n", stack.members[i]);
                        else
                            printf("%5d\n", stack.members[i]);
                    }
                }
                break;
        }
    }
}

// function definitions
int isEmpty(stackrec *ptr) {
    if (ptr->topindex == -1)
        return(TRUE);
    else
        return(FALSE);
}

// push() is used for inserting item in the stack
int push(stackrec *ptr, int topelement) {
    if (ptr->topindex == (STACKSIZE - 1)) {
        puts(ANSI_COLOR_RED "\nStack is already full"
        " and attempting to add more items to it will cause overflow." ANSI_COLOR_RESET);
        return(FALSE);
    }
    ptr->topindex += 1;
    ptr->members[ptr->topindex] = topelement;
    return(topelement);
}

// pop() is used for removing item from the stack
int pop(stackrec *ptr) {
    if (isEmpty(ptr)) {
        puts(ANSI_COLOR_RED "\nStack is already empty"
        " and attempting to access item from it will cause underflow." ANSI_COLOR_RESET);
        return(FALSE);
    }
    return(ptr->members[ptr->topindex--]);
}

// warn() ensures succefull reading of single integer from stdin
void warn(int *a) {
    if (scanf(" %d", a) != 1) {
        puts(ANSI_COLOR_RED "\nError reading input\n" ANSI_COLOR_RESET
        "(please re-run the compiled program)\n");
        exit(1);
    }
}

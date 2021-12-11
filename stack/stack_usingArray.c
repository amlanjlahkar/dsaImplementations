/* implementing a simple stack of FILO mechanism containing integers,
 * that is, the first integer(if using array then the element at index 0) to enter the stack
 * will be the last integer to be removed from the stack.
 *
 * AUTHOR: Amlanjyoti Lahkar
 */

#include <stdio.h>
#include <stdlib.h>

// defining macros
// for colored printing of critical warnings/errors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* for better understanding of code
 * when returning integers(0 or 1) from user-defined functions
 * for boolean testing
 */
#define TRUE  1
#define FALSE 0

// defining maximum size of the stack
#define STACKSIZE 10

/* structure used for holding the items of the stack using an array
 * and an integer to indicate the index of the top element within the array
 */
typedef struct {
    /* integer topindex is for determining the index of the element in top of stack
     * such that topindex + 1 = total number of items in the stack
     */
    int topindex;
    int members[STACKSIZE];
} stackrec;


/* index of the top of the stack element is set to -1
 * so that upon first entry, -1 + 1 = 0,
 * which is the first element of the array containing the stack items
 */
stackrec stack = { .topindex = -1 };

// declaring functions for operations to be performed on the stack
int isEmpty(stackrec *);
int pop(stackrec *);
int push(stackrec *, int);

// miscellaneous function
void warn(int *);

int main(void) {
    int input = 0, topitem = 0, pusheditem = 0, poppeditem = 0;
    printf("\nThe stack can contain atmost %d items and is currently empty.\n"
    "Below are some operations available to perform on it.\n", STACKSIZE);

    // printig the menu infinitely until the specified condition is met
    while(1) {
        puts("\n--------------------------------------------------");
        puts("\n1) isEmpty (indicates either TRUE or FALSE)\n"
        "2) pop (remove an item from the top of the stack)\n"
        "3) push (insert a new item on top of the stack)\n"
        "4) tos (print out the item on top of the stack)\n"
        "5) stackInfo (print out all the items currently in the stack)\n"
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
                puts((isEmpty(&stack)) ? "\nTrue" : "\nFALSE");
                break;
            case 2 :
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
            case 3 :
                if (stack.topindex == (STACKSIZE - 1)) {
                    puts(ANSI_COLOR_RED "\nStack is already full"
                    " and attempting to add more item to it will cause overflow." ANSI_COLOR_RESET);
                    break;
                }
                printf("\nEnter an item(number): ");
                warn(&pusheditem);
                topitem = push(&stack, pusheditem);
                if (!isEmpty(&stack) && stack.topindex < (STACKSIZE - 1))
                    printf("\nA new item has been inserted into the stack.\n"
                    "it now contains %d item(s).\n", (stack.topindex)+1);
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

// function/operation definitions
// isEmpty() is used for determining the state of the stack
int isEmpty(stackrec *ptr) {
    if (ptr -> topindex == -1)
        return(TRUE);
    else
        return(FALSE);
}

// pop() is used for removing item from the stack
int pop(stackrec *ptr) {
    if (isEmpty(ptr)) {
        puts(ANSI_COLOR_RED "\nStack is already empty and attempting to access item from it will cause underflow." ANSI_COLOR_RESET);
        return(FALSE);
    }
    return(ptr -> members[ptr -> topindex--]);
}

// push() is used for inserting item in the stack
int push(stackrec *ptr, int topelement) {
    if (ptr -> topindex == STACKSIZE - 1) {
        puts(ANSI_COLOR_RED "\nStack is already full and attempting to add more item to it will cause overflow." ANSI_COLOR_RESET);
        return(FALSE);
    }
    ptr -> topindex += 1;
    ptr -> members[ptr -> topindex] = topelement;
    return(topelement);
}

// warn() ensures succefull reading of integers from stdin
void warn(int *a) {
    if (scanf(" %d", a) != 1) {
        puts(ANSI_COLOR_RED "\nError reading input\n" ANSI_COLOR_RESET "(please re-run the compiled program)\n");
        exit(1);
    }
}


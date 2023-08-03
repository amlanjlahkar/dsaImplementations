/* implementing a simple stack of FILO mechanism containing integers,
 * that is, the first integer(if using array then the element at index 0) to
 * enter the stack will be the last integer to be removed from the stack.
 */

#include <stdio.h>
#include <stdlib.h>

static unsigned int STACKSIZE = 0;
typedef struct {
    int topindex;
    int* members;
} stackrec;
/* index of the top of the stack element is set to -1
 * so that upon first entry, -1 + 1 = 0,
 * which is the first element of the array containing the stack items
 */
stackrec stack = {.topindex = -1};

// stack functions
int isEmpty(stackrec*);
void push(stackrec*, int);
int pop(stackrec*);

// miscellaneous
void warn(int*);

int main(void) {
    int input = 0, topitem = 0, poppeditem = 0;
    printf("\nEnter stack size: ");
    scanf("%d", &STACKSIZE);
    stack.members = (int*)malloc(STACKSIZE * sizeof(int));
    printf("\n(stack capacity = %d)\n", STACKSIZE);
    while (1) {
        puts("\n1) push a new item to the stack"
             "\n2) pop an item from the stack"
             "\n3) print the item on top of the stack"
             "\n4) print out the stack items"
             "\n5) exit");

        printf("\nenter your input: ");
        warn(&input);
        if (input < 1 || input > 5) {
            puts("\nplease provide a valid input.");
            continue;
        } else if (input == 5) {
            free(stack.members);
            puts("\nterminated.\n");
            break;
        }

        switch (input) {
            case 1:
                {
                    if (stack.topindex == (STACKSIZE - 1)) {
                        puts("stack is already full"
                             " and attempting to add more items to it will "
                             "cause overflow.");
                        break;
                    }
                    printf("\nenter the value(integer) for the item: ");
                    warn(&topitem);
                    push(&stack, topitem);
                    if (stack.topindex < (STACKSIZE - 1)) {
                        printf(
                            "item has been placed at the top of stack.\n"
                            "(current number of item(s) in the stack = %d)\n",
                            (stack.topindex) + 1);
                    } else if (stack.topindex < STACKSIZE) {
                        printf("item has been placed at the top of the stack.\n"
                               "the stack is now full.\n");
                    }
                    break;
                }
            case 2:
                {
                    if ((poppeditem = pop(&stack))) {
                        topitem = stack.members[stack.topindex];
                        if (stack.topindex != -1) {
                            printf("\nitem \'%d\' from top of the stack has "
                                   "been removed.\n"
                                   "(number of item(s) remaining in the stack "
                                   "= %d\n",
                                   poppeditem, (stack.topindex) + 1);
                        } else {
                            printf("\nitem \'%d\' from top of the stack has "
                                   "been removed.\n"
                                   "the stack is now empty!\n",
                                   poppeditem);
                        }
                    }
                    break;
                }
            case 3:
                {
                    if (isEmpty(&stack)) {
                        puts("\nthe stack is empty!");
                    } else {
                        printf("the item currently at the top of the stack is "
                               "%d.\n",
                               topitem);
                    }
                    break;
                }
            case 4:
                {
                    if (isEmpty(&stack)) {
                        puts("\nthe stack is empty!");
                    } else {
                        printf("\n");
                        for (int i = stack.topindex; i >= 0; i--) {
                            if (i == stack.topindex) {
                                printf("%7d\t<--- top of the stack\n",
                                       stack.members[i]);
                            } else if (i == 0) {
                                printf("%7d\t<--- bottom of the stack\n",
                                       stack.members[i]);
                            } else {
                                printf("%5d\n", stack.members[i]);
                            }
                        }
                    }
                    break;
                }
        }
    }
}

int isEmpty(stackrec* ptr) { return ((ptr->topindex) == -1 ? 1 : 0); }

void push(stackrec* ptr, int topelement) {
    if (!(ptr->topindex == (STACKSIZE - 1))) {
        ptr->topindex += 1;
        ptr->members[ptr->topindex] = topelement;
    }
    return;
}

int pop(stackrec* ptr) {
    if (isEmpty(ptr)) {
        puts("\nstack is already empty"
             " and attempting to access item from it will cause underflow.");
        return 0;
    }
    return (ptr->members[ptr->topindex--]);
}

// warn() ensures succefull reading of single integer from stdin
void warn(int* a) {
    if (scanf(" %d", a) != 1) {
        puts("\nerror reading input!\n"
             "(please re-run the compiled program)\n");
        exit(1);
    }
}

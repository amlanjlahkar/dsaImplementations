/* implementing a "problematic" queue of FIFO mechanism -
 * that is the first item to enter the queue
 * is the first item to be removed from the queue -
 * containing integers, using array.
 *
 * AUTHOR: Amlanjyoti Lahkar
 */

#include <stdio.h>
#include <stdlib.h>

// for colored printing of critical warnings/errors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define QUEUESIZE 5
typedef struct {
    int frontindex, rearindex;
    int members[];
} queuerec;
// frontindex > rearindex when empty
queuerec queue = { .frontindex = 0, .rearindex = -1 };

// queue functions
int isEmpty(queuerec *);
int deQueue(queuerec *);
int enQueue(queuerec *, int);
// miscellaneous
void warn(int *);

int main(void) {
    int item = 0, input = 0, enqueued = 0, dequeued = 0;
    printf("\nThe queue can contain atmost %d items and is currently empty.\n"
    "Below are some operations available to perform on it.\n", QUEUESIZE);

    // printig the menu infinitely until the specified condition is met
    while(1) {
        puts("\n--------------------------------------------------");
        puts("\n1) isEmpty (indicates either TRUE or FALSE)\n"
        "2) enqueue (insert a new item at the end of the queue)\n"
        "3) dequeue (remove an item from the front of the queue)\n"
        "4) peek (get an overview of current items in the queue)\n"
        "5) exit\n");
        puts("--------------------------------------------------");

        printf("\nEnter your input(1,2,3,4 or 5): ");
        warn(&input);
        if (input < 1 || input > 5) {
            puts(ANSI_COLOR_RED "\nPlease provide a valid input." ANSI_COLOR_RESET);
            continue;
        } else if (input == 5) {
            puts("\nProgram terminated.\n");
            break;
        }

        switch(input) {
            case 1 :
                puts((isEmpty(&queue)) ? "\nTRUE" : "\nFALSE");
                break;
            case 2 :
                if (queue.rearindex == (QUEUESIZE - 1)) {
                    puts(ANSI_COLOR_RED "\nqueue overflow!" ANSI_COLOR_RESET);
                    break;
                }
                printf("\nEnter an item(integer): ");
                warn(&enqueued);
                enQueue(&queue, enqueued);
                if (queue.rearindex < (QUEUESIZE - 1))
                    printf("\nA new item has been inserted at the rear of the queue.\n"
                    "it now contains %d item(s).\n", (queue.rearindex - queue.frontindex)+1);
                else if (queue.rearindex < QUEUESIZE)
                    printf("\nA new item has been inserted at the rear of the queue.\n"
                    "The queue is now full.\n");
                break;
            case 3 :
                if ((dequeued = deQueue(&queue))) {
                    printf("\nThe item \'%d\' from the front of the queue has been removed\n"
                    "it now contains %d item(s).\n", dequeued, (queue.rearindex - queue.frontindex)+1);
                    break;
                }
                break;
            case 4 :
                if (isEmpty(&queue))
                    puts("\nThe queue is empty!");
                else {
                    puts("\nThe item(s) current in the queue are:\n");
                        for (int i = 0; i <= queue.rearindex; i++) {
                            if (i == queue.frontindex)
                                printf("%7d\t<--- front\n", queue.members[i]);
                            else if (i == queue.rearindex)
                                printf("%7d\t<--- rear\n", queue.members[i]);
                            else
                                printf("%5d\n", queue.members[i]);
                        }
                }
                break;
        }
    }
}

/* function definitions */
int isEmpty(queuerec *ptr) {
    return((ptr->frontindex > ptr->rearindex) ? 1 : 0);
}

int enQueue(queuerec *ptr, int rearelement) {
    if (ptr->rearindex == (QUEUESIZE - 1)) {
        puts(ANSI_COLOR_RED "\nqueue overflow!" ANSI_COLOR_RESET);
        return 0;
    }
    ptr->members[++(ptr->rearindex)] = rearelement;
    return(rearelement);
}

int deQueue(queuerec *ptr) {
    if(isEmpty(&queue)) {
        puts(ANSI_COLOR_RED "\nqueue underflow" ANSI_COLOR_RESET);
        return 0;
    }
    return(ptr->members[ptr->frontindex++]);
}

// warn() ensures successful reading of single integer from stdin
void warn(int *a) {
    if (scanf(" %d", a) != 1) {
        puts(ANSI_COLOR_RED "\nError reading input\n" ANSI_COLOR_RESET
        "(please re-run the compiled program)\n");
        exit(1);
    }
}

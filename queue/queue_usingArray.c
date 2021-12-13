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
queuerec q = { .frontindex = 0, .rearindex = -1 };

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
                puts((isEmpty(&q)) ? "\nTRUE" : "\nFALSE");
                break;
            case 2 :
                if (q.rearindex == (QUEUESIZE - 1)) {
                    puts(ANSI_COLOR_RED "\nQueue is already full!" ANSI_COLOR_RESET);
                    break;
                }
                printf("\nEnter an item(integer): ");
                warn(&enqueued);
                enQueue(&q, enqueued);
                if (q.rearindex == (QUEUESIZE - 1))
                    printf("\nA new item has been inserted at the rear of the queue.\n"
                    "The queue is now full.\n");
                else
                    printf("\nA new item has been inserted at the rear of the queue.\n"
                    "it now contains %d item(s).\n", (q.rearindex - q.frontindex)+1);
                break;
            case 3 :
                if ((dequeued = deQueue(&q))) {
                    // set the previous element value to 0 after shifting frontindex
                    q.members[(q.frontindex)-1] = 0;
                    if (q.frontindex == (q.rearindex)+1)
                        printf("\nThe last item \'%d\' of queue has been removed.\n"
                        "The queue is now empty.\n", dequeued);
                    else
                        printf("\nThe item \'%d\' from the front of the queue has been removed.\n"
                        "it now contains %d item(s).\n", dequeued, (q.rearindex - q.frontindex)+1);
                    break;
                }
                break;
            case 4 :
                if (isEmpty(&q))
                    puts("\nThe queue is empty!");
                else {
                    puts("\nThe item(s) current in the queue are:\n");
                        for (int i = 0; i <= q.rearindex; i++) {
                            if (i == q.frontindex)
                                printf("%7d\t<--- front\n", q.members[i]);
                            else if (i == q.rearindex)
                                printf("%7d\t<--- rear\n", q.members[i]);
                            else
                                printf("%5d\n", q.members[i]);
                        }
                }
                break;
        }
    }
}

// function definitions
int isEmpty(queuerec *ptr) {
    return((ptr->frontindex > ptr->rearindex) ? 1 : 0);
}

int enQueue(queuerec *ptr, int rearelement) {
    if (ptr->rearindex == (QUEUESIZE - 1)) {
        puts(ANSI_COLOR_RED "\nAttempting to add item to a non-empty queue"
        " will cause overflow!" ANSI_COLOR_RESET);
        return 0;
    }
    ptr->members[++(ptr->rearindex)] = rearelement;
    return(rearelement);
}

int deQueue(queuerec *ptr) {
    if(isEmpty(&q)) {
        puts(ANSI_COLOR_RED "\nAttempting to access item from an empty queue"
        " will cause underflow!" ANSI_COLOR_RESET);
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

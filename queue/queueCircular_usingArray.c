/* implementing a circular queue of FIFO mechanism -
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
    int members[QUEUESIZE];
} queuerec;
// initializing both front and rear index of the queue from -1
queuerec q = { .frontindex = -1, .rearindex = -1 };
// variables to test for empty queue
int TRUE = 1, FALSE = 0, *emptindi;


// queue function prototypes
int isEmpty(queuerec *);
int isFull(queuerec *);
void enQueue(queuerec *, int);
int deQueue(queuerec *);
int queueTotal(queuerec *);

// miscellaneous
void warn(int *);


int main(void) {
    int item = 0, input = 0, enqueued = 0, dequeued = 0;
    // point emptindi to true at the beginning
    emptindi = &TRUE;

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
            // is empty
            case 1 :
                puts((isEmpty(&q)) ? "\nTRUE" : "\nFALSE");
                break;
            // enqueue
            case 2 :
                if (isFull(&q)) {
                    puts(ANSI_COLOR_RED "\nQueue is already full!" ANSI_COLOR_RESET);
                    break;
                }
                printf("\nEnter an item(integer): ");
                warn(&enqueued);
                enQueue(&q, enqueued);
                if (isFull(&q))
                    printf("\nThe last remaining place in the queue\nhas been filled up"
                    " with the new item \'%d\'.\nThe queue is now full.\n", enqueued);
                else
                    printf("\nA new item \'%d\' has been inserted at the rear of the queue.\n"
                    "It now contains %d item(s).\n", enqueued, queueTotal(&q));
                break;
            // dequeue
            case 3 :
                if ((dequeued = deQueue(&q))) {
                    if (isEmpty(&q)) {
                        printf("\nThe last item \'%d\' of the queue has been removed.\n"
                        "The queue is now empty!\n", dequeued);
                    }
                    else
                        printf("\nThe item \'%d\' from the front of the queue has been removed.\n"
                        "It now contains %d item(s).\n", dequeued, queueTotal(&q));
                    break;
                }
                break;
            // peek
            case 4 :
                if (isEmpty(&q))
                    puts("\nThe queue is empty!");
                else {
                    puts("\nThe item(s) currently in the queue are:\n");
                        for (int i = 0; i < QUEUESIZE; i++) {
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
    return((ptr->frontindex == -1 || *emptindi == TRUE) ? 1 : 0);
}

int isFull(queuerec *ptr) {
    /* if the queue has to be full,
     * then rear will always have to be behind of front
     */
    int index_after_rear = (ptr->rearindex + 1) % QUEUESIZE;
    return((index_after_rear == ptr->frontindex) ? 1 : 0);
}

// shift rearindex to one index ahead when "inserting" item
void enQueue(queuerec *ptr, int rearelement) {
    if (isFull(ptr)) {
        puts(ANSI_COLOR_RED "\nAttempting to add item to a non-empty queue"
        " will cause overflow!" ANSI_COLOR_RESET);
        return;
    }
    else if (isEmpty(ptr))
        emptindi = &FALSE;
    if (ptr->frontindex == -1)
        ptr->frontindex = 0;
    ptr->rearindex = (ptr->rearindex + 1) % QUEUESIZE;
    ptr->members[ptr->rearindex] = rearelement;
}

// shift frontindex to one index ahead when "removing" item
int deQueue(queuerec *ptr) {
    if(isEmpty(ptr)) {
        puts(ANSI_COLOR_RED "\nAttempting to access item from an empty queue"
        " will cause underflow!" ANSI_COLOR_RESET);
        return 0;
    }
    // store the current element at frontinex in a temporary var for returning
    int prev_item = ptr->members[ptr->frontindex];
    if (ptr->frontindex != -1 && ptr->rearindex == ptr->frontindex)
        /* point emptindi to true and
         * reset front and rear index to -1 when dequeuing the last item
         */
        emptindi = &TRUE, ptr->frontindex = ptr->rearindex = -1;
    else
        ptr->frontindex = (ptr->frontindex + 1) % QUEUESIZE;
    return prev_item;
}

// return the number of total items in the queue
int queueTotal(queuerec *ptr) {
    if (isEmpty(ptr)) {
        int zero = 0;
        return zero;
    }
    else if (isFull(ptr))
        return QUEUESIZE;
    if (ptr->rearindex < ptr->frontindex) {
        // the number of "empty cells" in the queue
        int empty_total = (ptr->frontindex - ptr->rearindex) - 1;
        return (QUEUESIZE - empty_total);
    }
    else
        return ((ptr->rearindex - ptr->frontindex) + 1);
}

// warn() ensures successful reading of single integer from stdin
void warn(int *a) {
    if (scanf(" %d", a) != 1) {
        puts(ANSI_COLOR_RED "\nError reading input\n" ANSI_COLOR_RESET
        "(please re-run the compiled program)\n");
        exit(1);
    }
}

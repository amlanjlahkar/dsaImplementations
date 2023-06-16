/* implementing a circular queue of FIFO mechanism -
 * that is the first item to enter the queue
 * is the first item to be removed from the queue -
 * containing integers, using array.
 */

#include <stdio.h>
#include <stdlib.h>

#define QUEUESIZE 5
typedef struct {
    int frontindex, rearindex;
    int members[QUEUESIZE];
} queuerec;
// initializing both front and rear index of the queue from -1
queuerec q = {.frontindex = -1, .rearindex = -1};
// variables to test for empty queue
int TRUE = 1, FALSE = 0, *emptindi;

// queue functions
int isEmpty(queuerec*);
int isFull(queuerec*);
void enQueue(queuerec*, int);
int deQueue(queuerec*);
int queueTotal(queuerec*);

// miscellaneous
void warn(int*);

int main(void) {
    int item = 0, input = 0, enqueued = 0, dequeued = 0;
    // point emptindi to true at the beginning
    emptindi = &TRUE;

    printf("\n(queue capacity = %d)\n", QUEUESIZE);
    while (1) {
        puts("\n1) insert a new item to the queue"
             "\n2) remove an item from the queue"
             "\n3) print out the queue items"
             "\n4) exit\n");

        printf("\nenter your input: ");
        warn(&input);
        if (input < 1 || input > 4) {
            puts("\nplease provide a valid input.");
            continue;
        } else if (input == 4) {
            puts("\nterminated.\n");
            break;
        }

        switch (input) {
            case 1:
                {
                    if (!isFull(&q)) {
                        printf("\nenter a value(integer) for the item: ");
                        warn(&enqueued);
                        enQueue(&q, enqueued);
                        if (isFull(&q))
                            printf("item has been inserted at the end of the "
                                   "queue.\n"
                                   "the queue is now full!\n");
                        else
                            printf("item has been inserted at the end of the "
                                   "queue.\n"
                                   "(current number of item(s) remaining in "
                                   "the queue = %d)\n",
                                   queueTotal(&q));
                        break;
                    }
                    puts("\nqueue is already full");
                    break;
                }
            case 2:
                {
                    if ((dequeued = deQueue(&q))) {
                        if (isEmpty(&q)) {
                            printf("item \'%d\' from the front of the queue "
                                   "has been removed.\n"
                                   "the queue is now empty!\n",
                                   dequeued);
                        } else
                            printf("item \'%d\' from the front of the queue "
                                   "has been removed.\n"
                                   "(number of item(s) remaining in the queue "
                                   "= %d)\n",
                                   dequeued, queueTotal(&q));
                        break;
                    }
                    break;
                }
            case 3:
                {
                    if (isEmpty(&q))
                        puts("\nqueue is empty!");
                    else {
                        printf("\n");
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
}

int isEmpty(queuerec* ptr) {
    return ((ptr->frontindex == -1 || *emptindi == TRUE) ? 1 : 0);
}

int isFull(queuerec* ptr) {
    /* if the queue has to be full,
     * then rear will always have to be behind of front
     */
    int index_after_rear = (ptr->rearindex + 1) % QUEUESIZE;
    return ((index_after_rear == ptr->frontindex) ? 1 : 0);
}

void enQueue(queuerec* ptr, int rearelement) {
    if (!isFull(ptr)) {
        if (isEmpty(ptr))
            emptindi = &FALSE;
        if (ptr->frontindex == -1)
            ptr->frontindex = 0;
        ptr->rearindex               = (ptr->rearindex + 1) % QUEUESIZE;
        ptr->members[ptr->rearindex] = rearelement;
    }
    return;
}

int deQueue(queuerec* ptr) {
    if (isEmpty(ptr)) {
        puts("\nattempting to access item from an empty queue"
             " will cause underflow!");
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

int queueTotal(queuerec* ptr) {
    if (isEmpty(ptr)) {
        int zero = 0;
        return zero;
    } else if (isFull(ptr))
        return QUEUESIZE;
    if (ptr->rearindex < ptr->frontindex) {
        // the number of "empty cells" in the queue
        int empty_total = (ptr->frontindex - ptr->rearindex) - 1;
        return (QUEUESIZE - empty_total);
    } else
        return ((ptr->rearindex - ptr->frontindex) + 1);
}

// warn() ensures successful reading of single integer from stdin
void warn(int* a) {
    if (scanf(" %d", a) != 1) {
        puts("\nerror reading input\n"
             "(please re-run the compiled program)\n");
        exit(1);
    }
}

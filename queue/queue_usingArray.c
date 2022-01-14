/* implementing a "problematic" queue of FIFO mechanism -
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
// frontindex > rearindex when empty
queuerec q = { .frontindex = 0, .rearindex = -1 };

// queue functions
int isEmpty(queuerec *);
int deQueue(queuerec *);
void enQueue(queuerec *, int);

// miscellaneous
void warn(int *);

int main(void) {
    int item = 0, input = 0, enqueued = 0, dequeued = 0;

    printf("\n(queue capacity = %d)\n", QUEUESIZE);
    while(1) {
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

        switch(input) {
            case 1 : {
                if (q.rearindex == (QUEUESIZE - 1)) {
                    puts("queue is already full!");
                    break;
                }
                printf("enter a value(integer) for the item: ");
                warn(&enqueued);
                enQueue(&q, enqueued);
                if (q.rearindex == (QUEUESIZE - 1))
                    printf("item has been inserted at the end of the queue.\n"
                    "the queue is now full!\n");
                else
                    printf("item has been inserted at the end of the queue.\n"
                    "(current number of item(s) remaining in the queue = %d)\n", (q.rearindex - q.frontindex)+1);
                break;
            }
            case 2 : {
                if ((dequeued = deQueue(&q))) {
                    // set the previous element value to 0 after shifting frontindex
                    q.members[(q.frontindex)-1] = 0;
                    if (q.frontindex == (q.rearindex)+1)
                        printf("item \'%d\' from the front of the queue has been removed.\n"
                        "the queue is now empty!\n", dequeued);
                    else
                        printf("item \'%d\' from the front of the queue has been removed.\n"
                        "(number of item(s) remaining in the queue = %d)\n", dequeued, (q.rearindex - q.frontindex)+1);
                    break;
                }
                break;
            }
            case 3 : {
                if (isEmpty(&q))
                    puts("\nqueue is empty!");
                else {
                    printf("\n");
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
}

int isEmpty(queuerec *ptr) {
    return((ptr->frontindex > ptr->rearindex) ? 1 : 0);
}

void enQueue(queuerec *ptr, int rearelement) {
    if (ptr->rearindex == (QUEUESIZE - 1)) {
        puts("\nqueue is already full"
        "and attempting to add more item to it will cause overflow!");
        return;
    }
    ptr->members[++(ptr->rearindex)] = rearelement;
}

int deQueue(queuerec *ptr) {
    if(isEmpty(&q)) {
        puts("\nattempting to access item from an empty queue"
        " will cause underflow!");
        return 0;
    }
    return(ptr->members[ptr->frontindex++]);
}

// warn() ensures successful reading of single integer from stdin
void warn(int *a) {
    if (scanf(" %d", a) != 1) {
        puts("\nerror reading input!\n"
        "(please re-run the compiled program)\n");
        exit(1);
    }
}

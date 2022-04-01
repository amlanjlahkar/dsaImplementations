#include <stdio.h>

// swap fuction
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// function to generate two sub_arrays around a pivot element
// the pivot element then gets transferred to its final sorted index in the array
// such that left sub_array elements < pivot > right sub_array elements
int partition(int *sub_array, int low, int up) {
    int pivot = sub_array[low];
    int mark = low - 1;

    for (int i = low; i < up; i++) {
        if (sub_array[i] <= pivot) {
            mark++;
            /* at this point, if sub_array[mark] > sub_array[i]
             * then sub_array[i] gets closer to pivot when swapped,
             * else the element gets swapped with itself
             */
            swap(&sub_array[i], &sub_array[mark]);
        }
    }
    // swap the pivot element with the last marked smaller element
    swap(&sub_array[low], &sub_array[mark]);
    return mark;
}

// function to repeatedly create partitions
// until no further sub arrays can be generated
// that is, all elements are sorted
void quick_sort(int *array, int lb, int ub) {
    // when ther's single element left, lb = ub
    if (lb < ub) {
        int mark_pivot = partition(array, lb, ub);
        quick_sort(array, lb, mark_pivot-1);
        quick_sort(array, mark_pivot+1, ub);
    }
}

// test
int main(void) {
    int test_array[8] = {-1, 0, 2, 8, 4, 12, -9, 33};
    int lb = 0;
    int ub = sizeof(test_array)/sizeof(test_array[0]);
    quick_sort(test_array, lb, ub);
    for (int j = lb; j < ub; j++)
        printf("%d\t", test_array[j]);
    printf("\n");
}

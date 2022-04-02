#include <stdio.h>
#include "operations.c"

void selection_sort(int *array, int n) {
    for (int i = 0; i < n-1; i++) {
        int marked_index = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[marked_index])
                marked_index = j;
        }
        swap(&array[i], &array[marked_index]);
    }
}

int main(void) {
    int test_array[] = { -1, 0, 2, 8, 4, 12, -9, 33, 0, 21, 22, 1 };
    int lb = 0; int ub = sizeof(test_array)/sizeof(test_array[0]);

    printf("\norigin array:\t"); print_arr(test_array, lb, ub);
    selection_sort(test_array, ub);
    printf("\nafter sorting:\t"); print_arr(test_array, lb, ub);
    printf("\n");

    return 0;
}

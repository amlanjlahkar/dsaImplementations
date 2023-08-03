#include "operations/operations.c"

int partition(int sub_array[], int low, int up) {
    int pivot = sub_array[low];
    int mark = low - 1;

    for (int i = low; i <= up; i++) {
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

void quick_sort(int array[], int lb, int ub) {
    // when there's single element left, lb = ub
    if (lb < ub) {
        int mark_pivot = partition(array, lb, ub);
        quick_sort(array, lb, mark_pivot - 1);
        quick_sort(array, mark_pivot + 1, ub);
    }
}

int main(void) {
    int test_array[] = {-1, 0, 2, 8, 4, 12, -9, 33, 0, 21, 22, 1};
    int lb = 0;
    int ub = sizeof(test_array) / sizeof(test_array[0]);

    printf("\norigin array:\t");
    print_arr(test_array, lb, ub);
    quick_sort(test_array, lb, ub - 1);
    printf("\nafter sorting:\t");
    print_arr(test_array, lb, ub);
    printf("\n");

    return 0;
}

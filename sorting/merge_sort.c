#include "operations/operations.c"

void merge(int array[], int lb, int mid, int ub) {
    // creating left and right arrays based on mid
    int lsize = mid - lb + 1;
    int rsize = ub - mid;
    int left[lsize], right[rsize];

    // filling up the left and right arrays
    for (int a = 0; a < lsize || a < rsize; a++) {
        (a < lsize) ? left[a] = array[lb + a] : 0;
        (a < rsize) ? right[a] = array[mid + 1 + a] : 0;
    }

    int il = 0;
    int ir = 0;
    int is;
    for (is = lb; il < lsize && ir < rsize; is++) {
        if (left[il] <= right[ir]) {
            array[is] = left[il++];
        } else {
            array[is] = right[ir++];
        }
    }

    // assign remaing elements
    while (il < lsize || ir < rsize) {
        (il < lsize) ? array[is++] = left[il++] : 0;
        (ir < rsize) ? array[is++] = right[ir++] : 0;
    }
}

void merge_sort(int array[], int lb, int ub) {
    if (lb < ub) {
        int mid = (ub + lb) / 2;
        merge_sort(array, lb, mid);
        merge_sort(array, mid + 1, ub);
        merge(array, lb, mid, ub);
    }
}

int main(void) {
    int test_array[] = {-1, 0, 2, 8, 4, 12, -9, 33, 0, 21, 22, 1};
    int lb = 0;
    int ub = sizeof(test_array) / sizeof(test_array[0]);

    printf("\norigin array:\t");
    print_arr(test_array, lb, ub);
    merge_sort(test_array, lb, ub - 1);
    printf("\nafter sorting:\t");
    print_arr(test_array, lb, ub);
    printf("\n");

    return 0;
}

#include <stdio.h>

int binary_search(int array[], int lb, int ub, int element) {
    if (lb <= ub) {
        int mid = (lb + ub) / 2;
        if (array[mid] == element)
            return mid;
        else if (array[mid] > element)
            return binary_search(array, lb, mid - 1, element);
        else
            return binary_search(array, mid + 1, ub, element);
    }
    return -1;
}

int main(void) {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int element;
    printf("Enter element to search for in the array: ");
    scanf("%d", &element);

    int index = binary_search(array, 0, 9, element);
    if (index == -1)
        printf("The element %d is not present in the array.\n", element);
    else
        printf("The element %d is present at index %d in the array.\n", element,
               index);
    return 0;
}

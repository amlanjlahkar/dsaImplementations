#include <stdio.h>

int linear_search(int array[], int array_size, int element) {
    int index = 0;
    int check = 0;
    for (int i = 0; i < array_size; i++) {
        if (array[i] == element) {
            check++;
            break;
        } else {
            index++;
        }
    }
    return ((check == 0) ? -1 : index);
}

int main(void) {
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int element;
    printf("Enter element to search for in the array: ");
    scanf("%d", &element);

    int index = linear_search(array, 10, element);
    if (index == -1) {
        printf("The element %d is not present in the array.\n", element);
    } else {
        printf("The element %d is present at index %d in the array.\n", element,
               index);
    }
    return 0;
}

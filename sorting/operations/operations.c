#include "operations.h"
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a       = *b;
    *b       = temp;
}

void print_arr(int* array, int lower_bound, int upper_bound) {
    for (int i = lower_bound; i < upper_bound; i++) {
        printf("%d\t", array[i]);
    }
}

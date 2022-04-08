#include "operations/operations.c"

void insertion_sort(int array[], int n) {
  for (int i = 1; i < n; i++) {
    int key = array[i];
    int prev = i - 1;
    for (; prev >= 0 && array[prev] > key; prev--)
      array[prev + 1] = array[prev];
    array[prev + 1] = key;
  }
}

int main(void) {
  int test_array[] = {-1, 0, 2, 8, 4, 12, -9, 33, 0, 21, 22, 1};
  int lb = 0;
  int ub = sizeof(test_array) / sizeof(test_array[0]);

  printf("\norigin array:\t");
  print_arr(test_array, lb, ub);
  insertion_sort(test_array, ub);
  printf("\nafter sorting:\t");
  print_arr(test_array, lb, ub);
  printf("\n");

  return 0;
}

/*
 * Day 08 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>

void increment(int *n) { (*n)++; }

void multiply(const int *a, const int *b, int *result) { *result = (*a) * (*b); }

void array_reverse(int *arr, int n) {
    int *lo = arr, *hi = arr + n - 1;
    while (lo < hi) {
        int tmp = *lo; *lo = *hi; *hi = tmp;
        lo++; hi--;
    }
}

int main(void) {
    /* Ex 1 */
    int y = 77;
    int *py = &y;
    printf("Address: %p  Value: %d\n", (void*)py, *py);
    *py *= 2;
    printf("After double: %d\n", y);

    /* Ex 2 */
    int val = 10;
    increment(&val);
    printf("After increment: %d\n", val);

    /* Ex 3 */
    int arr[] = {3, 6, 9, 12, 15};
    int *end = arr + 4;
    printf("Reversed: ");
    while (end >= arr) { printf("%d ", *end); end--; }
    printf("\n");

    /* Ex 4 */
    int a = 6, b = 7, prod;
    multiply(&a, &b, &prod);
    printf("Product: %d\n", prod);

    /* Ex 5 */
    int data[] = {1, 2, 3, 4, 5};
    array_reverse(data, 5);
    printf("Reversed array: ");
    for (int i = 0; i < 5; i++) printf("%d ", data[i]);
    printf("\n");

    return 0;
}

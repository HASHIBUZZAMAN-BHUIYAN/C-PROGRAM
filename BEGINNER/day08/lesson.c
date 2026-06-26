/*
 * Day 08 — Pointers I
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void fill_with_squares(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        *(arr + i) = (i + 1) * (i + 1);   /* pointer arithmetic instead of arr[i] */
    }
}

int main(void) {
    printf("=== Day 08: Pointers I ===\n\n");

    /* --- Address-of and dereference --- */
    int x = 42;
    int *p = &x;   /* p holds the ADDRESS of x */

    printf("Value of x   : %d\n", x);
    printf("Address of x : %p\n", (void*)p);
    printf("Via pointer  : %d\n", *p);   /* dereference: read value at address */

    /* Modify x through the pointer */
    *p = 100;
    printf("After *p=100, x = %d\n", x);

    /* --- Pointer arithmetic --- */
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;   /* array name = address of first element */
    printf("\nArray traversal with pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("  ptr+%d = %p  value = %d\n", i, (void*)(ptr + i), *(ptr + i));
    }

    /* Pointer increment */
    printf("\nUsing ptr++ to walk array: ");
    for (ptr = arr; ptr < arr + 5; ptr++) {
        printf("%d ", *ptr);
    }
    printf("\n");

    /* --- Arrays and pointers equivalence --- */
    printf("\narr[2]       = %d\n", arr[2]);
    printf("*(arr + 2)   = %d\n", *(arr + 2));   /* identical */
    printf("2[arr]       = %d\n", 2[arr]);         /* legal but weird, same thing */

    /* --- Pass-by-pointer: swap --- */
    int a = 5, b = 9;
    printf("\nBefore swap: a=%d b=%d\n", a, b);
    swap(&a, &b);
    printf("After swap : a=%d b=%d\n", a, b);

    /* --- Fill array via pointer --- */
    int squares[6];
    fill_with_squares(squares, 6);
    printf("\nSquares via pointer: ");
    for (int i = 0; i < 6; i++) printf("%d ", squares[i]);
    printf("\n");

    /* --- NULL pointer --- */
    int *null_ptr = NULL;
    printf("\nnull_ptr = %p\n", (void*)null_ptr);
    /* Dereferencing NULL would crash — never do it without a check */
    if (null_ptr != NULL) {
        printf("Value: %d\n", *null_ptr);
    } else {
        printf("Pointer is NULL — not dereferenced (safe)\n");
    }

    return 0;
}

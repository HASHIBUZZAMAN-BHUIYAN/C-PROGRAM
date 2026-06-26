/*
 * Day 09 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>
#include <string.h>

void set_to_null(int **pp) { *pp = NULL; }
int square(int n) { return n * n; }
int double_val(int n) { return n * 2; }
int triple_val(int n) { return n * 3; }
int cube(int n)       { return n * n * n; }

int cmp_asc(const void *a, const void *b)  { return (*(int*)a - *(int*)b); }
int cmp_desc(const void *a, const void *b) { return (*(int*)b - *(int*)a); }

#include <stdlib.h>
void sort_and_print(int *arr, int n, int (*cmp)(const void*, const void*), const char *label) {
    int copy[16];
    memcpy(copy, arr, n * sizeof(int));
    qsort(copy, n, sizeof(int), cmp);
    printf("%s: ", label);
    for (int i = 0; i < n; i++) printf("%d ", copy[i]);
    printf("\n");
}

int main(void) {
    /* Ex 1 */
    int n = 5;
    int *p = &n;
    int **pp = &p;
    **pp = 50;
    printf("n = %d\n", n);

    /* Ex 2 */
    int val = 1;
    int *ptr = &val;
    set_to_null(&ptr);
    printf("ptr after set_to_null: %p\n", (void*)ptr);

    /* Ex 3 */
    int (*sq)(int) = square;
    printf("square(7) = %d\n", sq(7));

    /* Ex 4 */
    int (*fns[4])(int) = {double_val, triple_val, square, cube};
    const char *names[] = {"double","triple","square","cube"};
    for (int i = 0; i < 4; i++)
        printf("%s(5) = %d\n", names[i], fns[i](5));

    /* Ex 5 */
    int arr[] = {5, 2, 8, 1, 9, 3};
    sort_and_print(arr, 6, cmp_asc,  "Ascending ");
    sort_and_print(arr, 6, cmp_desc, "Descending");

    return 0;
}

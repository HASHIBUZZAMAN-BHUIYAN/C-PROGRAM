/*
 * Day 11 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dup_string(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (copy) strcpy(copy, s);
    return copy;
}

int int_cmp(const void *a, const void *b) { return *(int*)a - *(int*)b; }

int main(void) {
    /* Ex 1 */
    int n;
    printf("n: "); scanf("%d", &n);
    double *arr = malloc(n * sizeof(double));
    double sum = 0;
    for (int i = 0; i < n; i++) { arr[i] = 1.0/(i+1); sum += arr[i]; }
    printf("Sum = %.4f\n", sum);
    free(arr);

    /* Ex 2 */
    int rows = 3, cols = 4;
    int **m = malloc(rows * sizeof(int*));
    for (int r = 0; r < rows; r++) m[r] = malloc(cols * sizeof(int));
    for (int r = 0; r < rows; r++) for (int c = 0; c < cols; c++) m[r][c] = r+c;
    for (int r = 0; r < rows; r++) { for (int c = 0; c < cols; c++) printf("%3d", m[r][c]); printf("\n"); }
    for (int r = 0; r < rows; r++) free(m[r]);
    free(m);

    /* Ex 3 */
    char *copy = dup_string("hello world");
    printf("Copy: %s\n", copy);
    free(copy);

    /* Ex 4 */
    int cap = 2, size = 0;
    int *grow = malloc(cap * sizeof(int));
    for (int i = 0; i < 10; i++) {
        if (size == cap) { cap *= 2; grow = realloc(grow, cap * sizeof(int)); printf("Grew to cap=%d\n", cap); }
        grow[size++] = (i+1) * 3;
    }
    printf("Values: "); for (int i = 0; i < size; i++) printf("%d ", grow[i]); printf("\n");
    free(grow);

    /* Ex 5 */
    printf("How many integers? "); scanf("%d", &n);
    int *data = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) { printf("[%d]: ", i); scanf("%d", &data[i]); }
    qsort(data, n, sizeof(int), int_cmp);
    printf("Sorted: "); for (int i = 0; i < n; i++) printf("%d ", data[i]); printf("\n");
    free(data);

    return 0;
}

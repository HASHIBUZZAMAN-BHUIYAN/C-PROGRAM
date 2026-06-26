/*
 * Day 06 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>

int is_sorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) return 0;
    }
    return 1;
}

int main(void) {
    /* Ex 1 */
    int sq[10];
    for (int i = 0; i < 10; i++) sq[i] = (i+1)*(i+1);
    for (int i = 0; i < 10; i++) printf("%d ", sq[i]);
    printf("\n");

    /* Ex 2 */
    float a[5];
    printf("Enter 5 floats: ");
    for (int i = 0; i < 5; i++) scanf("%f", &a[i]);
    float mx = a[0], second = a[0] - 1e6f;
    for (int i = 1; i < 5; i++) {
        if (a[i] > mx) { second = mx; mx = a[i]; }
        else if (a[i] > second) second = a[i];
    }
    printf("Second largest: %.2f\n", second);

    /* Ex 3 */
    int sorted[] = {1, 3, 5, 7, 9};
    int unsorted[] = {3, 1, 4, 1, 5};
    printf("sorted:   %s\n", is_sorted(sorted,   5) ? "yes" : "no");
    printf("unsorted: %s\n", is_sorted(unsorted, 5) ? "yes" : "no");

    /* Ex 4 */
    int m[3][3];
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            m[r][c] = r * c;
    printf("Matrix:\n");
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) printf("%3d", m[r][c]);
        printf("\n");
    }
    printf("Transpose:\n");
    for (int c = 0; c < 3; c++) {
        for (int r = 0; r < 3; r++) printf("%3d", m[r][c]);
        printf("\n");
    }

    /* Ex 5 */
    int arr[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int n = 9, maxIdx = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    printf("Max at index %d (value %d)\n", maxIdx, arr[maxIdx]);

    return 0;
}

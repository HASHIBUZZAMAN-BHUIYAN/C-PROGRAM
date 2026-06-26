/*
 * Day 06 — Arrays (1D and 2D)
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>

#define SIZE 8

/* Function prototypes */
void   print_array(int arr[], int size);
int    array_sum(int arr[], int size);
double array_avg(int arr[], int size);
int    array_min(int arr[], int size);
int    array_max(int arr[], int size);
void   reverse_array(int arr[], int size);

int main(void) {
    printf("=== Day 06: Arrays ===\n\n");

    /* --- 1D array declaration and initialization --- */
    int scores[SIZE] = {82, 91, 67, 78, 95, 54, 88, 73};
    printf("Scores: ");
    print_array(scores, SIZE);

    printf("Sum    : %d\n", array_sum(scores, SIZE));
    printf("Average: %.2f\n", array_avg(scores, SIZE));
    printf("Min    : %d\n", array_min(scores, SIZE));
    printf("Max    : %d\n", array_max(scores, SIZE));

    /* --- Modify and reverse --- */
    printf("\nAfter reversing: ");
    reverse_array(scores, SIZE);
    print_array(scores, SIZE);

    /* --- Partial initialization (rest set to 0) --- */
    int partial[10] = {1, 2, 3};
    printf("\nPartial init: ");
    for (int i = 0; i < 10; i++) printf("%d ", partial[i]);
    printf("\n");

    /* --- 2D array: matrix --- */
    printf("\n--- 2D Array (3x3 Identity Matrix) ---\n");
    int identity[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            printf("%3d", identity[r][c]);
        }
        printf("\n");
    }

    /* --- Matrix multiplication example (2x2) --- */
    printf("\n--- 2x2 Matrix Multiplication ---\n");
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2] = {{0, 0}, {0, 0}};

    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 2; c++)
            for (int k = 0; k < 2; k++)
                C[r][c] += A[r][k] * B[k][c];

    printf("A*B:\n");
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) printf("%5d", C[r][c]);
        printf("\n");
    }

    return 0;
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

int array_sum(int arr[], int size) {
    int s = 0;
    for (int i = 0; i < size; i++) s += arr[i];
    return s;
}

double array_avg(int arr[], int size) {
    return (double)array_sum(arr, size) / size;
}

int array_min(int arr[], int size) {
    int m = arr[0];
    for (int i = 1; i < size; i++) if (arr[i] < m) m = arr[i];
    return m;
}

int array_max(int arr[], int size) {
    int m = arr[0];
    for (int i = 1; i < size; i++) if (arr[i] > m) m = arr[i];
    return m;
}

void reverse_array(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int tmp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = tmp;
    }
}

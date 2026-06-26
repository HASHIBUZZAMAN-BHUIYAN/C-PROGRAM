/*
 * Day 08 Mini-Project — Array statistics via pointers
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>

void array_stats(const int *arr, int n, int *out_min, int *out_max, double *out_avg) {
    *out_min = arr[0];
    *out_max = arr[0];
    long sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < *out_min) *out_min = arr[i];
        if (arr[i] > *out_max) *out_max = arr[i];
        sum += arr[i];
    }
    *out_avg = (double)sum / n;
}

int main(void) {
    int n;
    printf("=== Array Stats via Pointers ===\n");
    printf("How many integers? ");
    scanf("%d", &n);
    int arr[64];
    for (int i = 0; i < n && i < 64; i++) {
        printf("  [%d]: ", i);
        scanf("%d", &arr[i]);
    }

    int mn, mx;
    double avg;
    array_stats(arr, n, &mn, &mx, &avg);

    printf("Min: %d  Max: %d  Avg: %.2f\n", mn, mx, avg);
    return 0;
}

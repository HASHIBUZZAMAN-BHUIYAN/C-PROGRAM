/*
 * Intermediate Day 04 — Sorting Algorithms
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10000

void print_array(const int *a, int n) {
    for (int i = 0; i < n; i++) printf("%d%s", a[i], i<n-1?" ":"");
    printf("\n");
}

/* --- Bubble Sort O(n²) --- */
void bubble_sort(int *a, int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (a[j] > a[j+1]) { int t=a[j]; a[j]=a[j+1]; a[j+1]=t; }
}

/* --- Insertion Sort O(n²) --- */
void insertion_sort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j+1] = a[j]; j--; }
        a[j+1] = key;
    }
}

/* --- Quicksort O(n log n) avg --- */
int partition(int *a, int lo, int hi) {
    int pivot = a[hi], i = lo - 1;
    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot) { i++; int t=a[i]; a[i]=a[j]; a[j]=t; }
    int t = a[i+1]; a[i+1] = a[hi]; a[hi] = t;
    return i + 1;
}
void quicksort(int *a, int lo, int hi) {
    if (lo < hi) { int p = partition(a, lo, hi); quicksort(a, lo, p-1); quicksort(a, p+1, hi); }
}

/* --- Mergesort O(n log n) --- */
void merge(int *a, int l, int m, int r) {
    int nl = m-l+1, nr = r-m;
    int *L = malloc(nl*sizeof(int)), *R = malloc(nr*sizeof(int));
    memcpy(L, a+l, nl*sizeof(int)); memcpy(R, a+m+1, nr*sizeof(int));
    int i=0, j=0, k=l;
    while (i<nl && j<nr) a[k++] = L[i]<=R[j] ? L[i++] : R[j++];
    while (i<nl) a[k++]=L[i++];
    while (j<nr) a[k++]=R[j++];
    free(L); free(R);
}
void mergesort(int *a, int l, int r) {
    if (l < r) { int m=(l+r)/2; mergesort(a,l,m); mergesort(a,m+1,r); merge(a,l,m,r); }
}

double time_sort(void (*fn)(int*,int), int *src, int n) {
    int *copy = malloc(n * sizeof(int));
    memcpy(copy, src, n * sizeof(int));
    clock_t t0 = clock();
    fn(copy, n);
    double elapsed = (double)(clock() - t0) / CLOCKS_PER_SEC;
    free(copy);
    return elapsed;
}

void qs_wrap(int *a, int n) { quicksort(a, 0, n-1); }
void ms_wrap(int *a, int n) { mergesort(a, 0, n-1); }

int main(void) {
    printf("=== Intermediate Day 04: Sorting Algorithms ===\n\n");

    /* Demo on small array */
    int small[] = {64, 34, 25, 12, 22, 11, 90};
    int len = 7;
    int copy[7];

    memcpy(copy, small, sizeof(small));
    bubble_sort(copy, len);
    printf("Bubble    : "); print_array(copy, len);

    memcpy(copy, small, sizeof(small));
    insertion_sort(copy, len);
    printf("Insertion : "); print_array(copy, len);

    memcpy(copy, small, sizeof(small));
    quicksort(copy, 0, len-1);
    printf("Quick     : "); print_array(copy, len);

    memcpy(copy, small, sizeof(small));
    mergesort(copy, 0, len-1);
    printf("Merge     : "); print_array(copy, len);

    /* Performance comparison on large array */
    printf("\n--- Performance on %d elements ---\n", N);
    srand(42);
    int *big = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) big[i] = rand() % 100000;

    printf("Bubble    : %.4f s\n", time_sort(bubble_sort,    big, N));
    printf("Insertion : %.4f s\n", time_sort(insertion_sort, big, N));
    printf("Quicksort : %.4f s\n", time_sort(qs_wrap,        big, N));
    printf("Mergesort : %.4f s\n", time_sort(ms_wrap,        big, N));

    free(big);
    return 0;
}


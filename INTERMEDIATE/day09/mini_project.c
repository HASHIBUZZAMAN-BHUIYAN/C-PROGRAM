/*
 * Int Day 09 Mini-Project — Parallel array processing
 * Splits a large array across N threads for parallel sum
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define N        1000000
#define NTHREADS 4

static int   arr[N];
static long long partial_sums[NTHREADS];

typedef struct { int start, end, tid; } Range;

DWORD WINAPI sum_range(LPVOID arg) {
    Range *r = (Range*)arg;
    long long s = 0;
    for (int i = r->start; i < r->end; i++) s += arr[i];
    partial_sums[r->tid] = s;
    return 0;
}

int main(void) {
    for (int i = 0; i < N; i++) arr[i] = i + 1;  /* 1..N */
    long long expected = (long long)N*(N+1)/2;

    HANDLE threads[NTHREADS];
    Range  ranges[NTHREADS];
    int chunk = N / NTHREADS;

    for (int t = 0; t < NTHREADS; t++) {
        ranges[t].start = t * chunk;
        ranges[t].end   = (t == NTHREADS-1) ? N : (t+1)*chunk;
        ranges[t].tid   = t;
        threads[t] = CreateThread(NULL,0,sum_range,&ranges[t],0,NULL);
    }
    WaitForMultipleObjects(NTHREADS, threads, TRUE, INFINITE);
    for (int t=0;t<NTHREADS;t++) CloseHandle(threads[t]);

    long long total = 0;
    for (int t=0;t<NTHREADS;t++) { printf("Thread %d partial: %lld\n",t,partial_sums[t]); total+=partial_sums[t]; }
    printf("Total: %lld  Expected: %lld  %s\n", total, expected, total==expected?"OK":"MISMATCH");
    return 0;
}

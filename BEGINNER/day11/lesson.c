/*
 * Day 11 — Dynamic Memory Allocation
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("=== Day 11: Dynamic Memory ===\n\n");

    /* --- malloc: allocate n bytes, uninitialized --- */
    int n;
    printf("How many integers to allocate? ");
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "malloc failed!\n");
        return 1;
    }
    printf("Allocated %d ints at %p\n", n, (void*)arr);

    /* Initialize and use */
    for (int i = 0; i < n; i++) arr[i] = (i + 1) * 10;
    printf("Values: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    /* --- realloc: resize the array --- */
    int new_n = n * 2;
    int *bigger = realloc(arr, new_n * sizeof(int));
    if (bigger == NULL) {
        free(arr);   /* realloc failed, original ptr still valid */
        fprintf(stderr, "realloc failed!\n");
        return 1;
    }
    arr = bigger;

    /* Zero out the new portion */
    for (int i = n; i < new_n; i++) arr[i] = 0;
    printf("\nAfter realloc to %d ints: ", new_n);
    for (int i = 0; i < new_n; i++) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    arr = NULL;   /* good habit: null pointer after free */

    /* --- calloc: allocate and zero --- */
    int *zeroed = calloc(5, sizeof(int));
    if (!zeroed) { return 1; }
    printf("\ncalloc(5) values (all zero): ");
    for (int i = 0; i < 5; i++) printf("%d ", zeroed[i]);
    printf("\n");
    free(zeroed);

    /* --- Dynamic string --- */
    const char *src = "Hello, dynamic world!";
    char *dyn_str = malloc(strlen(src) + 1);   /* +1 for null terminator */
    if (dyn_str) {
        strcpy(dyn_str, src);
        printf("\nDynamic string: %s\n", dyn_str);
        free(dyn_str);
    }

    /* --- Dynamic array of structs --- */
    typedef struct { int id; float score; } Record;
    int count = 3;
    Record *records = calloc(count, sizeof(Record));
    if (records) {
        for (int i = 0; i < count; i++) {
            records[i].id    = i + 1;
            records[i].score = (float)(70 + i * 10);
        }
        printf("\nRecords:\n");
        for (int i = 0; i < count; i++)
            printf("  id=%d  score=%.1f\n", records[i].id, records[i].score);
        free(records);
    }

    printf("\nAll memory freed — no leaks!\n");
    return 0;
}

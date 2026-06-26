/*
 * Int Day 04 Mini-Project — Generic sort with function pointer + stability test
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char name[32]; int score; int original_idx; } Record;

int cmp_score_desc(const void *a, const void *b) {
    return ((Record*)b)->score - ((Record*)a)->score;
}
int cmp_name_asc(const void *a, const void *b) {
    return strcmp(((Record*)a)->name, ((Record*)b)->name);
}

void print_records(const Record *r, int n) {
    for (int i=0; i<n; i++) printf("  [orig %d] %-15s %d\n", r[i].original_idx, r[i].name, r[i].score);
}

int main(void) {
    Record r[] = {
        {"Alice",95,0},{"Bob",88,1},{"Carol",95,2},{"Dave",72,3},{"Eve",88,4}
    };
    int n = 5;
    printf("=== Sort Demo ===\nOriginal:\n"); print_records(r, n);

    Record copy[5]; memcpy(copy, r, sizeof(r));
    qsort(copy, n, sizeof(Record), cmp_score_desc);
    printf("By score desc:\n"); print_records(copy, n);

    memcpy(copy, r, sizeof(r));
    qsort(copy, n, sizeof(Record), cmp_name_asc);
    printf("By name asc:\n"); print_records(copy, n);
    return 0;
}

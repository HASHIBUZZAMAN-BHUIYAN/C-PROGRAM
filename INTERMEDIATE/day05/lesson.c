/*
 * Intermediate Day 05 — Searching Algorithms & Hash Tables
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ====== Linear Search ====== */
int linear_search(const int *a, int n, int key) {
    for (int i = 0; i < n; i++) if (a[i] == key) return i;
    return -1;
}

/* ====== Binary Search (array must be sorted) ====== */
int binary_search(const int *a, int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if      (a[mid] == key) return mid;
        else if (a[mid] <  key) lo = mid + 1;
        else                    hi = mid - 1;
    }
    return -1;
}

/* ====== Hash Table (separate chaining) ====== */
#define HT_SIZE 16

typedef struct HEntry {
    char        key[64];
    int         value;
    struct HEntry *next;
} HEntry;

typedef struct { HEntry *buckets[HT_SIZE]; } HashTable;

unsigned int hash_fn(const char *key) {
    unsigned int h = 5381;
    while (*key) h = h * 33 ^ (unsigned char)(*key++);
    return h % HT_SIZE;
}

void ht_set(HashTable *ht, const char *key, int val) {
    unsigned int idx = hash_fn(key);
    for (HEntry *e = ht->buckets[idx]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) { e->value = val; return; }
    }
    HEntry *e = malloc(sizeof(HEntry));
    strncpy(e->key, key, 63); e->value = val;
    e->next = ht->buckets[idx];
    ht->buckets[idx] = e;
}

int ht_get(const HashTable *ht, const char *key, int *out) {
    unsigned int idx = hash_fn(key);
    for (HEntry *e = ht->buckets[idx]; e; e = e->next) {
        if (strcmp(e->key, key) == 0) { *out = e->value; return 1; }
    }
    return 0;
}

void ht_free(HashTable *ht) {
    for (int i = 0; i < HT_SIZE; i++) {
        HEntry *e = ht->buckets[i];
        while (e) { HEntry *t = e->next; free(e); e = t; }
    }
}

void ht_print(const HashTable *ht) {
    for (int i = 0; i < HT_SIZE; i++) {
        if (!ht->buckets[i]) continue;
        printf("  [%2d] ", i);
        for (HEntry *e = ht->buckets[i]; e; e = e->next)
            printf("(%s=%d) ", e->key, e->value);
        printf("\n");
    }
}

int main(void) {
    printf("=== Intermediate Day 05: Searching & Hash Tables ===\n\n");

    int arr[] = {3,7,1,9,4,6,2,8,5,10,15,12,11,14,13};
    int n = 15;

    printf("--- Linear Search ---\n");
    printf("Search 9 in unsorted: index=%d\n", linear_search(arr, n, 9));
    printf("Search 99: index=%d (not found)\n", linear_search(arr, n, 99));

    /* Sort for binary search */
    int sorted[15]; memcpy(sorted, arr, sizeof(arr));
    for (int i=0;i<n-1;i++) for(int j=0;j<n-1-i;j++) if(sorted[j]>sorted[j+1]){int t=sorted[j];sorted[j]=sorted[j+1];sorted[j+1]=t;}

    printf("\n--- Binary Search (sorted array) ---\n");
    printf("Search 9: index=%d\n", binary_search(sorted, n, 9));
    printf("Search 99: index=%d\n", binary_search(sorted, n, 99));

    /* --- Hash Table --- */
    printf("\n--- Hash Table ---\n");
    HashTable ht = {0};
    const char *words[] = {"apple","banana","cherry","date","elderberry","fig","grape"};
    for (int i = 0; i < 7; i++) ht_set(&ht, words[i], (i+1)*10);

    printf("Hash table contents:\n"); ht_print(&ht);

    int v;
    printf("\nGet 'cherry': %s\n", ht_get(&ht,"cherry",&v) ? (printf("%d\n",v),"found") : "not found");
    ht_set(&ht, "cherry", 999);
    ht_get(&ht, "cherry", &v);
    printf("After update 'cherry': %d\n", v);
    printf("Get 'mango': %s\n", ht_get(&ht,"mango",&v) ? "found" : "not found");

    ht_free(&ht);
    return 0;
}

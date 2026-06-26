/*
 * Intermediate Day 06 — Recursion Deep Dive
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Factorial (recursive vs iterative) --- */
long long factorial_rec(int n) { return n<=1 ? 1 : n * factorial_rec(n-1); }
long long factorial_iter(int n) { long long r=1; for(int i=2;i<=n;i++) r*=i; return r; }

/* --- Fibonacci (naive O(2^n) vs memoized O(n)) --- */
long fib_naive(int n) { return n<=1 ? n : fib_naive(n-1)+fib_naive(n-2); }
static long memo[100];
long fib_memo(int n) {
    if (n<=1) return n;
    if (memo[n]) return memo[n];
    memo[n] = fib_memo(n-1) + fib_memo(n-2);
    return memo[n];
}

/* --- Towers of Hanoi --- */
int hanoi_moves = 0;
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) { printf("  Move disk 1: %c -> %c\n", from, to); hanoi_moves++; return; }
    hanoi(n-1, from, aux, to);
    printf("  Move disk %d: %c -> %c\n", n, from, to); hanoi_moves++;
    hanoi(n-1, aux, to, from);
}

/* --- N-Queens backtracking --- */
#define QUEENS 8
static int board[QUEENS];
static int solutions = 0;

int is_safe(int row, int col) {
    for (int r = 0; r < row; r++) {
        if (board[r]==col || abs(board[r]-col)==abs(r-row)) return 0;
    }
    return 1;
}
void solve_queens(int row) {
    if (row == QUEENS) { solutions++; return; }
    for (int col = 0; col < QUEENS; col++) {
        if (is_safe(row, col)) { board[row]=col; solve_queens(row+1); }
    }
}

/* --- Binary search (recursive) --- */
int bsearch_rec(const int *a, int lo, int hi, int key) {
    if (lo > hi) return -1;
    int mid = lo + (hi-lo)/2;
    if (a[mid]==key) return mid;
    return key < a[mid] ? bsearch_rec(a,lo,mid-1,key) : bsearch_rec(a,mid+1,hi,key);
}

/* --- Power set --- */
void power_set(int *set, int n, int idx, int *subset, int sublen) {
    if (idx == n) {
        printf("  {");
        for (int i=0;i<sublen;i++) printf("%d%s",subset[i],i<sublen-1?",":"");
        printf("}\n");
        return;
    }
    subset[sublen] = set[idx];
    power_set(set, n, idx+1, subset, sublen+1);  /* include */
    power_set(set, n, idx+1, subset, sublen);     /* exclude */
}

int main(void) {
    printf("=== Intermediate Day 06: Recursion ===\n\n");

    printf("--- Factorial ---\n");
    for (int i=0;i<=10;i++) printf("%d! = %lld\n", i, factorial_rec(i));

    printf("\n--- Fibonacci (memoized) ---\n");
    memset(memo, 0, sizeof(memo));
    printf("First 15: ");
    for (int i=0;i<15;i++) printf("%ld ", fib_memo(i));
    printf("\n");

    printf("\n--- Towers of Hanoi (3 disks) ---\n");
    hanoi(3, 'A', 'C', 'B');
    printf("Total moves for 3 disks: %d (2^n - 1 = %d)\n", hanoi_moves, (1<<3)-1);

    printf("\n--- N-Queens (%d x %d board) ---\n", QUEENS, QUEENS);
    solve_queens(0);
    printf("Solutions found: %d\n", solutions);

    printf("\n--- Power Set of {1,2,3} ---\n");
    int set[] = {1,2,3}; int sub[3];
    power_set(set, 3, 0, sub, 0);

    return 0;
}

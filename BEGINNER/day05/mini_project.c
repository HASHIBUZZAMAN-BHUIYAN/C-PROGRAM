/*
 * Day 05 Mini-Project — Number Properties Analyzer
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int is_perfect(int n) {
    if (n < 2) return 0;
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n/i) sum += n/i;
        }
    }
    return sum == n;
}

int digit_sum(int n) {
    int s = 0;
    while (n > 0) { s += n % 10; n /= 10; }
    return s;
}

int main(void) {
    int n;
    printf("=== Number Properties ===\nEnter a positive integer: ");
    scanf("%d", &n);
    printf("Prime:   %s\n", is_prime(n)   ? "yes" : "no");
    printf("Perfect: %s\n", is_perfect(n) ? "yes" : "no");
    printf("Digit sum: %d\n", digit_sum(n));
    printf("Even/odd: %s\n", (n % 2 == 0) ? "even" : "odd");
    return 0;
}

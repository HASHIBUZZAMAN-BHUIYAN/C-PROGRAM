/*
 * Day 05 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>

long long power(long long base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

double celsius_to_fahrenheit(double c) {
    return c * 9.0 / 5.0 + 32.0;
}

int max_of_three(int a, int b, int c) {
    int m = (a > b) ? a : b;
    return (m > c) ? m : c;
}

void print_stars(int n) {
    for (int i = 0; i < n; i++) printf("*");
    printf("\n");
}

int sum_digits(int n) {
    if (n < 10) return n;
    return (n % 10) + sum_digits(n / 10);
}

int main(void) {
    printf("2^10 = %lld\n", power(2, 10));
    printf("100C = %.1fF\n", celsius_to_fahrenheit(100.0));
    printf("max(3,9,6) = %d\n", max_of_three(3, 9, 6));
    print_stars(7);
    printf("sum_digits(9876) = %d\n", sum_digits(9876));
    return 0;
}

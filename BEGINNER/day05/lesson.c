/*
 * Day 05 — Functions
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>

/* --- Function prototypes (forward declarations) --- */
void   greet(const char *name);
int    add(int a, int b);
double average(double a, double b, double c);
int    factorial(int n);
int    is_prime(int n);
void   print_separator(void);

int main(void) {
    printf("=== Day 05: Functions ===\n\n");

    /* Calling void function */
    greet("Alice");
    greet("Bob");

    /* Calling function with return value */
    int sum = add(7, 13);
    printf("add(7, 13) = %d\n", sum);

    /* Calling with multiple args, float return */
    printf("average(10, 20, 30) = %.2f\n", average(10, 20, 30));

    print_separator();

    /* Recursive function: factorial */
    for (int i = 0; i <= 10; i++) {
        printf("%d! = %d\n", i, factorial(i));
    }

    print_separator();

    /* Prime checker */
    printf("Primes up to 30: ");
    for (int i = 2; i <= 30; i++) {
        if (is_prime(i)) printf("%d ", i);
    }
    printf("\n");

    return 0;
}

/* --- Function definitions --- */

void greet(const char *name) {
    printf("Hello, %s!\n", name);
}

int add(int a, int b) {
    return a + b;
}

double average(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

/* Recursive: n! = n * (n-1)! */
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

void print_separator(void) {
    printf("--------------------\n");
}

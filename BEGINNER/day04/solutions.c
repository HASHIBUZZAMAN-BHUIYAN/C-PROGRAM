/*
 * Day 04 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>
int main(void) {
    /* Exercise 1 */
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    long sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    printf("Sum 1..%d = %ld\n", n, sum);

    /* Exercise 2 */
    long number;
    printf("Enter a positive integer: ");
    scanf("%ld", &number);
    int digits = 0;
    long temp = number;
    if (temp == 0) digits = 1;
    while (temp > 0) { temp /= 10; digits++; }
    printf("%ld has %d digit(s)\n", number, digits);

    /* Exercise 3 */
    const int SECRET = 42;
    int guess;
    printf("Guess the secret number (1-100):\n");
    do {
        printf("> ");
        scanf("%d", &guess);
        if (guess < SECRET) printf("Too low!\n");
        else if (guess > SECRET) printf("Too high!\n");
    } while (guess != SECRET);
    printf("Correct!\n");

    /* Exercise 4 */
    long a = 0, b = 1;
    printf("First 20 Fibonacci: ");
    for (int i = 0; i < 20; i++) {
        printf("%ld ", a);
        long c = a + b;
        a = b;
        b = c;
    }
    printf("\n");

    /* Exercise 5 */
    int height;
    printf("Triangle height: ");
    scanf("%d", &height);
    for (int row = 1; row <= height; row++) {
        for (int col = 0; col < row; col++) printf("*");
        printf("\n");
    }

    return 0;
}

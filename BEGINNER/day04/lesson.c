/*
 * Day 04 — Loops: for, while, do-while, break, continue
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>

int main(void) {
    printf("=== Day 04: Loops ===\n\n");

    /* --- for loop --- */
    printf("for loop (1 to 5): ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    /* --- for loop with step --- */
    printf("Even numbers 2-10: ");
    for (int i = 2; i <= 10; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    /* --- while loop --- */
    printf("\nwhile loop - powers of 2 up to 1000:\n");
    int power = 1;
    while (power <= 1000) {
        printf("%d ", power);
        power *= 2;
    }
    printf("\n");

    /* --- do-while: always executes body at least once --- */
    int num;
    do {
        printf("\ndo-while: Enter a positive number: ");
        scanf("%d", &num);
        if (num <= 0) printf("  That's not positive! Try again.\n");
    } while (num <= 0);
    printf("You entered: %d\n", num);

    /* --- break: exit loop early --- */
    printf("\nbreak demo - find first multiple of 7 above 50:\n");
    for (int i = 51; i <= 200; i++) {
        if (i % 7 == 0) {
            printf("Found: %d\n", i);
            break;
        }
    }

    /* --- continue: skip current iteration --- */
    printf("\ncontinue demo - numbers 1-15 skipping multiples of 3:\n");
    for (int i = 1; i <= 15; i++) {
        if (i % 3 == 0) continue;
        printf("%d ", i);
    }
    printf("\n");

    /* --- Nested loops: multiplication table --- */
    int size;
    printf("\nEnter table size (e.g. 5): ");
    scanf("%d", &size);
    printf("\nMultiplication Table (%dx%d):\n", size, size);
    for (int row = 1; row <= size; row++) {
        for (int col = 1; col <= size; col++) {
            printf("%4d", row * col);
        }
        printf("\n");
    }

    return 0;
}

/*
 * Day 01 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>

int main(void) {

    /* Exercise 1 */
    int score = 95;
    printf("Score: %d\n", score);

    /* Exercise 2 */
    float temperature = 36.6f;
    printf("Temperature: %.1f\n", temperature);

    /* Exercise 3 */
    char initial = 'Z';
    printf("Initial: %c\n", initial);

    /* Exercise 4 */
    printf("Size of long      = %zu bytes\n", sizeof(long));
    printf("Size of long long = %zu bytes\n", sizeof(long long));

    /* Exercise 5 */
    int x, y;
    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);
    printf("Sum = %d\n", x + y);

    return 0;
}

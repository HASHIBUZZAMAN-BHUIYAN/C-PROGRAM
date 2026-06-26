/*
 * Day 02 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>
int main(void) {
    /* Exercise 1 */
    int a = 15, b = 4;
    printf("Integer division: %d\n", a / b);
    printf("Float division:   %.2f\n", (float)a / b);

    /* Exercise 2 */
    int n = 50;
    n -= 13;
    n *= 2;
    printf("n = %d\n", n);

    /* Exercise 3 */
    const int MAX = 255;
    printf("MAX = %d\n", MAX);

    /* Exercise 4 */
    float f = 9.99f;
    printf("float: %.2f  int: %d\n", f, (int)f);

    /* Exercise 5 */
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int inRange = (num >= 1) && (num <= 100);
    printf("%d is %s in range [1,100]\n", num, inRange ? "" : "NOT");

    return 0;
}

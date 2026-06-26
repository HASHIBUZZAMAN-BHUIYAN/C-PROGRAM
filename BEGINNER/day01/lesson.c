/*
 * Day 01 — C Basics: printf, scanf, variables, data types
 * Compile: gcc lesson.c -o lesson.exe
 * Run:     lesson.exe
 */
#include <stdio.h>

int main(void) {
    /* --- 1. Hello, World --- */
    printf("=== C Day 01: Basics ===\n\n");
    printf("Hello, World!\n");

    /* --- 2. Variable declaration and initialization --- */
    int    age       = 20;
    float  gpa       = 3.85f;
    double pi        = 3.14159265358979;
    char   grade     = 'A';
    char   name[]    = "Alice";   /* string = char array */

    /* --- 3. printf with format specifiers --- */
    printf("Name   : %s\n",  name);
    printf("Age    : %d\n",  age);
    printf("GPA    : %.2f\n", gpa);   /* .2f = 2 decimal places */
    printf("Pi     : %.6lf\n", pi);
    printf("Grade  : %c\n",  grade);

    /* --- 4. sizeof shows storage size in bytes --- */
    printf("\nData type sizes:\n");
    printf("  char   = %zu byte(s)\n", sizeof(char));
    printf("  int    = %zu byte(s)\n", sizeof(int));
    printf("  float  = %zu byte(s)\n", sizeof(float));
    printf("  double = %zu byte(s)\n", sizeof(double));

    /* --- 5. Reading user input with scanf --- */
    int user_age;
    printf("\nEnter your age: ");
    scanf("%d", &user_age);   /* & = address-of, scanf writes to the variable */
    printf("You entered: %d\n", user_age);

    /* --- 6. Integer arithmetic --- */
    int a = 10, b = 3;
    printf("\nInteger arithmetic with a=%d, b=%d:\n", a, b);
    printf("  a + b = %d\n", a + b);
    printf("  a - b = %d\n", a - b);
    printf("  a * b = %d\n", a * b);
    printf("  a / b = %d  (integer division, remainder lost)\n", a / b);
    printf("  a %% b = %d  (modulo = remainder)\n", a % b);

    return 0;   /* 0 means "success" to the operating system */
}

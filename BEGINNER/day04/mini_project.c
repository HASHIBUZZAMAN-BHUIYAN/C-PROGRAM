/*
 * Day 04 Mini-Project — FizzBuzz + Number Analysis
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
int main(void) {
    int limit;
    printf("=== FizzBuzz + Stats ===\n");
    printf("Enter upper limit: ");
    scanf("%d", &limit);

    int count_fizz = 0, count_buzz = 0, count_fizzbuzz = 0;

    for (int i = 1; i <= limit; i++) {
        if      (i % 15 == 0) { printf("FizzBuzz "); count_fizzbuzz++; }
        else if (i % 3  == 0) { printf("Fizz ");     count_fizz++;     }
        else if (i % 5  == 0) { printf("Buzz ");     count_buzz++;     }
        else                  { printf("%d ", i); }
    }
    printf("\n\nStats: Fizz=%d  Buzz=%d  FizzBuzz=%d\n",
           count_fizz, count_buzz, count_fizzbuzz);
    return 0;
}

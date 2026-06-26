/*
 * Day 03 — Conditionals: if/else, switch, ternary
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>

int main(void) {
    printf("=== Day 03: Conditionals ===\n\n");

    /* --- if / else --- */
    int score;
    printf("Enter a score (0-100): ");
    scanf("%d", &score);

    if (score >= 90) {
        printf("Grade: A\n");
    } else if (score >= 80) {
        printf("Grade: B\n");
    } else if (score >= 70) {
        printf("Grade: C\n");
    } else if (score >= 60) {
        printf("Grade: D\n");
    } else {
        printf("Grade: F\n");
    }

    /* --- Ternary operator --- */
    const char *result = (score >= 60) ? "PASS" : "FAIL";
    printf("Result: %s\n", result);

    /* --- switch statement --- */
    int day;
    printf("\nEnter day number (1=Mon...7=Sun): ");
    scanf("%d", &day);

    switch (day) {
        case 1: printf("Monday\n");    break;
        case 2: printf("Tuesday\n");   break;
        case 3: printf("Wednesday\n"); break;
        case 4: printf("Thursday\n");  break;
        case 5: printf("Friday\n");    break;
        case 6: printf("Saturday\n");  break;
        case 7: printf("Sunday\n");    break;
        default: printf("Invalid day (enter 1-7)\n"); break;
    }

    /* Demonstrating fall-through (intentional, no break) */
    printf("\nIs day %d a weekday? ", day);
    switch (day) {
        case 1: case 2: case 3: case 4: case 5:
            printf("Yes (weekday)\n");
            break;
        case 6: case 7:
            printf("No (weekend)\n");
            break;
        default:
            printf("Invalid\n");
    }

    /* --- Nested if --- */
    int age;
    printf("\nEnter age: ");
    scanf("%d", &age);
    if (age >= 18) {
        if (age >= 65) {
            printf("Senior citizen\n");
        } else {
            printf("Adult\n");
        }
    } else {
        printf("Minor\n");
    }

    return 0;
}

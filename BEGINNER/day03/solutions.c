/*
 * Day 03 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>
int main(void) {
    /* Exercise 1 */
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    if      (n > 0) printf("positive\n");
    else if (n < 0) printf("negative\n");
    else            printf("zero\n");

    /* Exercise 2 */
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    if      (a > b) printf("Larger: %d\n", a);
    else if (b > a) printf("Larger: %d\n", b);
    else            printf("Equal: %d\n", a);

    /* Exercise 3 */
    int month;
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    switch (month) {
        case 1:  printf("January\n");   break;
        case 2:  printf("February\n");  break;
        case 3:  printf("March\n");     break;
        case 4:  printf("April\n");     break;
        case 5:  printf("May\n");       break;
        case 6:  printf("June\n");      break;
        case 7:  printf("July\n");      break;
        case 8:  printf("August\n");    break;
        case 9:  printf("September\n"); break;
        case 10: printf("October\n");   break;
        case 11: printf("November\n");  break;
        case 12: printf("December\n");  break;
        default: printf("Invalid\n");
    }

    /* Exercise 4 */
    char ch;
    printf("Enter a character: ");
    scanf(" %c", &ch);
    if (ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'||
        ch=='A'||ch=='E'||ch=='I'||ch=='O'||ch=='U')
        printf("Vowel\n");
    else
        printf("Consonant\n");

    /* Exercise 5 */
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("%d is %s\n", num, (num % 2 == 0) ? "even" : "odd");

    return 0;
}

#include <stdio.h>
//Hashib
// Structure declaration
struct student {
    int number;
    char name[100];  // Increased buffer size
    double grade;
};

int main(void) {
    struct student s;

    // Input
    printf("Enter your student number: ");
    scanf("%d", &s.number);

    printf("Enter your name: ");
    scanf("%s", s.name);  // This reads only one word (up to whitespace)

    printf("Enter your grade: ");
    scanf("%lf", &s.grade);

    // Output
    printf("\nStudent number: %d\n", s.number);
    printf("Name: %s\n", s.name);
    printf("GPA: %.2f\n", s.grade);

    return 0;
}

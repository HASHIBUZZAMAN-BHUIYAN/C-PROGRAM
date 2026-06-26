#include <stdio.h>
//Hashib
struct student {
    int number;
    char name[20];  // Increased size to handle longer names
    double grade;
};

int main(void) {
    struct student s;

    printf("Enter student number: ");
    scanf("%d", &s.number);

    printf("Enter name: ");
    scanf("%s", s.name);  // Use fgets() if full names with spaces are needed

    printf("Enter grade: ");
    scanf("%lf", &s.grade);

    printf("\nStudent number: %d\n", s.number);
    printf("Name: %s\n", s.name);
    printf("GPA: %.2f\n", s.grade);

    return 0;
}

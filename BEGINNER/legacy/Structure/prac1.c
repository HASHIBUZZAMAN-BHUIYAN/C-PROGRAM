#include <stdio.h>
#include <string.h>
//Hashib
// Structure declaration
struct student {
    int number;
    char name[100];
    double grade;
};

int main(void) {
    // Declaring a structure variable
    struct student s;

    // Structure member references
    s.number = 20230001;
    strcpy(s.name, "Hong Gil-dong");
    s.grade = 4.3;

    // Output
    printf("Student number: %d\n", s.number);
    printf("Name: %s\n", s.name);
    printf("GPA: %.2f\n", s.grade);

    return 0;
}

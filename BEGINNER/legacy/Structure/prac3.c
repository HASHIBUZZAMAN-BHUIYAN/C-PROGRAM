#include <stdio.h>
//Hashib
#define SIZE 3

// Structure declaration
struct student {
    int number;
    char name[20];      // Allows up to 19 characters + null terminator
    double grade;
};

int main(void) {
    struct student list[SIZE];
    int i;

    // Input for each student
    for (i = 0; i < SIZE; i++) {
        printf("Enter student number: ");
        scanf("%d", &list[i].number);

        printf("Enter name: ");
        scanf("%s", list[i].name);  // Only reads one word!

        printf("Enter grade: ");
        scanf("%lf", &list[i].grade);
    }

    // Output
    for (i = 0; i < SIZE; i++) {
        printf("Student number: %d, Name: %s, Grade: %.2f\n",
               list[i].number, list[i].name, list[i].grade);
    }

    return 0;
}

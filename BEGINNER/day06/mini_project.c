/*
 * Day 06 Mini-Project — Student Grade Tracker
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#define MAX_STUDENTS 30

int main(void) {
    int n;
    printf("=== Student Grade Tracker ===\n");
    printf("How many students? (max %d): ", MAX_STUDENTS);
    scanf("%d", &n);
    if (n > MAX_STUDENTS) n = MAX_STUDENTS;

    float grades[MAX_STUDENTS];
    for (int i = 0; i < n; i++) {
        printf("Student %d grade: ", i + 1);
        scanf("%f", &grades[i]);
    }

    float sum = 0, min = grades[0], max = grades[0];
    for (int i = 0; i < n; i++) {
        sum += grades[i];
        if (grades[i] < min) min = grades[i];
        if (grades[i] > max) max = grades[i];
    }

    printf("\n--- Summary ---\n");
    printf("Average : %.2f\n", sum / n);
    printf("Highest : %.2f\n", max);
    printf("Lowest  : %.2f\n", min);

    printf("\n--- Grade Distribution ---\n");
    int a=0,b=0,c=0,d=0,f=0;
    for (int i = 0; i < n; i++) {
        if      (grades[i] >= 90) a++;
        else if (grades[i] >= 80) b++;
        else if (grades[i] >= 70) c++;
        else if (grades[i] >= 60) d++;
        else                      f++;
    }
    printf("A(90+): %d | B(80+): %d | C(70+): %d | D(60+): %d | F: %d\n",
           a, b, c, d, f);
    return 0;
}

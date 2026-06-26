#include <stdio.h>

#define ROWS 3
#define COLS 5

int main(void) {
    //holding grades and absences
    int a[ROWS][COLS] = { 
        {87, 98, 80, 76, 3},
        {99, 89, 90, 90, 0},
        {65, 68, 50, 49, 0}
    };

    int i;
    for (i = 0; i < ROWS; i++) {
        double final_score = a[i][0] * 0.3     // Midterm 30%
                           + a[i][1] * 0.4     // Final 40%
                           + a[i][2] * 0.2     // Homework 20%
                           + a[i][3] * 0.1     // Quiz 10%
                           - a[i][4];          // Deduct absences

        printf("Student #%d's final grade = %6.2f\n", i + 1, final_score);
    }

    return 0;
}

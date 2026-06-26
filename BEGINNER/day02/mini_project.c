/*
 * Day 02 Mini-Project — BMI Calculator
 * Demonstrates arithmetic, division, casting, and const.
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
int main(void) {
    const float UNDERWEIGHT = 18.5f;
    const float NORMAL_MAX  = 24.9f;
    const float OVERWEIGHT  = 29.9f;

    float weight_kg, height_m;
    printf("=== BMI Calculator ===\n");
    printf("Weight (kg): ");
    scanf("%f", &weight_kg);
    printf("Height (m) : ");
    scanf("%f", &height_m);

    float bmi = weight_kg / (height_m * height_m);
    printf("BMI = %.1f\n", bmi);

    if      (bmi < UNDERWEIGHT) printf("Category: Underweight\n");
    else if (bmi <= NORMAL_MAX) printf("Category: Normal\n");
    else if (bmi <= OVERWEIGHT) printf("Category: Overweight\n");
    else                        printf("Category: Obese\n");

    return 0;
}

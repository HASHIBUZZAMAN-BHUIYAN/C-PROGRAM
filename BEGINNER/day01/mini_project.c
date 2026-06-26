/*
 * Day 01 Mini-Project — Unit Converter
 * Converts Celsius to Fahrenheit and metres to feet.
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>

int main(void) {
    double celsius, metres;

    printf("=== Unit Converter ===\n");

    printf("Enter temperature in Celsius: ");
    scanf("%lf", &celsius);
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("%.2f C = %.2f F\n", celsius, fahrenheit);

    printf("Enter distance in metres: ");
    scanf("%lf", &metres);
    double feet = metres * 3.28084;
    printf("%.2f m = %.2f ft\n", metres, feet);

    return 0;
}

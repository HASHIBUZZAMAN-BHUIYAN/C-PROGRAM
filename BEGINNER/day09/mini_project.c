/*
 * Day 09 Mini-Project — Function-pointer-based calculator
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>

double do_add(double a, double b) { return a + b; }
double do_sub(double a, double b) { return a - b; }
double do_mul(double a, double b) { return a * b; }
double do_div(double a, double b) { return (b != 0) ? a / b : 0; }

int main(void) {
    double (*ops[4])(double, double) = {do_add, do_sub, do_mul, do_div};
    const char *labels[] = {"+", "-", "*", "/"};

    double x, y;
    int choice;
    printf("=== Function-Pointer Calculator ===\n");
    printf("x: "); scanf("%lf", &x);
    printf("y: "); scanf("%lf", &y);
    printf("Operation: 0=add 1=sub 2=mul 3=div: ");
    scanf("%d", &choice);

    if (choice < 0 || choice > 3) { printf("Invalid\n"); return 1; }
    if (choice == 3 && y == 0)    { printf("Division by zero\n"); return 1; }

    printf("%.4g %s %.4g = %.4g\n", x, labels[choice], y, ops[choice](x, y));
    return 0;
}

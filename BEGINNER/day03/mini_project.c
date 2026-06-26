/*
 * Day 03 Mini-Project — Simple Calculator with menu
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
int main(void) {
    double a, b;
    int op;
    printf("=== Simple Calculator ===\n");
    printf("Enter two numbers: ");
    scanf("%lf %lf", &a, &b);
    printf("Choose operation:\n  1) Add\n  2) Subtract\n  3) Multiply\n  4) Divide\n> ");
    scanf("%d", &op);
    switch (op) {
        case 1: printf("%.4g + %.4g = %.4g\n", a, b, a+b); break;
        case 2: printf("%.4g - %.4g = %.4g\n", a, b, a-b); break;
        case 3: printf("%.4g * %.4g = %.4g\n", a, b, a*b); break;
        case 4:
            if (b == 0.0) printf("Error: division by zero\n");
            else printf("%.4g / %.4g = %.4g\n", a, b, a/b);
            break;
        default: printf("Unknown operation\n");
    }
    return 0;
}

#include <stdio.h>
#include <math.h>
// Hashib Code
// Engineering calculator

// Menu function
int menu(void) {
    int n;
    printf("1. Factorial\n");
    printf("2. Sine\n");
    printf("3. Log (base 10)\n");
    printf("4. Square root\n");
    printf("5. Permutation (nPr)\n");
    printf("6. Combination (nCr)\n");
    printf("7. Cosine\n");
    printf("8. End\n");
    printf("Please select: ");
    scanf("%d", &n);
    return n;
}

// Factorial function
void factorial() {
    long long n, result = 1, i;
    printf("Enter an integer: ");
    scanf("%lld", &n);
    if (n < 0) {
        printf("Error: Factorial is undefined for negative numbers.\n\n");
        return;
    }
    for (i = 1; i <= n; i++)
        result *= i;
    printf("Result = %lld\n\n", result);
}

// Sine function
void sine() {
    double a, result;
    printf("Enter the angle (in radians): ");
    scanf("%lf", &a);
    result = sin(a);
    printf("Result = %lf\n\n", result);
}

// Log base 10 function
void logBase10() {
    double a, result;
    printf("Enter a positive real number: ");
    scanf("%lf", &a);
    if (a <= 0.0)
        printf("Error: Log undefined for zero or negative values.\n\n");
    else {
        result = log10(a);
        printf("Result = %lf\n\n", result);
    }
}

// Square root function
void squareRoot() {
    double a, result;
    printf("Enter a non-negative number: ");
    scanf("%lf", &a);
    if (a < 0)
        printf("Error: Negative number has no real square root.\n\n");
    else {
        result = sqrt(a);
        printf("Result = %lf\n\n", result);
    }
}

// Permutation (nPr)
void permutation() {
    int n, r, i;
    long long fact_n = 1, fact_diff = 1;
    printf("Enter n and r (n >= r): ");
    scanf("%d %d", &n, &r);
    if (n < r || n < 0 || r < 0) {
        printf("Error: Ensure n >= r and both are non-negative.\n\n");
        return;
    }
    for (i = 1; i <= n; i++) fact_n *= i;
    for (i = 1; i <= (n - r); i++) fact_diff *= i;
    printf("Result = %lld\n\n", fact_n / fact_diff);
}

// Combination (nCr)
void combination() {
    int n, r, i;
    long long fact_n = 1, fact_r = 1, fact_diff = 1;
    printf("Enter n and r (n >= r): ");
    scanf("%d %d", &n, &r);
    if (n < r || n < 0 || r < 0) {
        printf("Error: Ensure n >= r and both are non-negative.\n\n");
        return;
    }
    for (i = 1; i <= n; i++) fact_n *= i;
    for (i = 1; i <= r; i++) fact_r *= i;
    for (i = 1; i <= (n - r); i++) fact_diff *= i;
    printf("Result = %lld\n\n", fact_n / (fact_r * fact_diff));
}

// Cosine function
void cosine() {
    double a, result;
    printf("Enter the angle (in radians): ");
    scanf("%lf", &a);
    result = cos(a);
    printf("Result = %lf\n\n", result);
}

// Main function
int main(void) {
    while (1) {
        switch (menu()) {
            case 1: factorial(); break;
            case 2: sine(); break;
            case 3: logBase10(); break;
            case 4: squareRoot(); break;
            case 5: permutation(); break;
            case 6: combination(); break;
            case 7: cosine(); break;
            case 8:
                printf("Quitting.\n");
                return 0;
            default:
                printf("Bad choice.\n\n");
                break;
        }
    }
}

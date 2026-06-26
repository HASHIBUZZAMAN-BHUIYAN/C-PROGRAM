#include <stdio.h>
//hashib Code
//factorial finding
//factorial Code
long factorial(int n) {
    printf("factorial(%d)\n", n);
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main(void) {
    int x = 0;
    long f;

    printf("Enter an integer: ");
    scanf("%d", &x);

    f = factorial(x);
    printf("%d! is %ld.\n", x, f);

    return 0;
}

#include <stdio.h>
//hashib Code
//sum of n numbers
int main(void) {
    int n, i, sum = 0;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        sum += i;
    }

    printf("Sum from 1 to %d = %d\n", n, sum);
    return 0;
}

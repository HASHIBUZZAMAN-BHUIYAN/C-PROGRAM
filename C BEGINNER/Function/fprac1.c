#include <stdio.h>
//hashib Code
//Large value finding
// Function to return the maximum of two integers
int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int main(void) {
    int x, y, larger;

    // Give input two integers
    printf("Enter two integers: ");
    scanf("%d %d", &x, &y);
    larger = max(x, y);
    printf("The larger value is %d.\n", larger);

    return 0;
}

#include <stdio.h>
//hashib Code
//sum function
// User input
int get_integer() {
    int value;
    printf("Enter an integer: ");
    scanf("%d", &value);
    return value;
}

// adding integers
int add(int x, int y) {
    return x + y;
}

int main(void) {
    int x = get_integer(); // Get first number
    int y = get_integer(); // Get second number

    int sum = add(x, y);   // Compute sum using add function
    printf("The sum of the two numbers is %d.\n", sum);

    return 0;
}

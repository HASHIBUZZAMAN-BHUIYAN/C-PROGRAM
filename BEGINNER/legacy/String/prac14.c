#include <stdio.h>

int main(void)
{
    int i;
    char fruits[3][20];  // Array to hold 3 fruit names, each with a max of 19 characters

    // Taking input for 3 fruits
    for (i = 0; i < 3; i++) {
        printf("Enter the fruit name: ");
        scanf("%s", fruits[i]);  // Read a string into the fruits array
    }

    // Printing the fruit names
    for (i = 0; i < 3; i++) {
        printf("Fruit %d: %s\n", i + 1, fruits[i]);  // Display the fruit names with their index
    }

    return 0;
}

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int c;
    while ((c = getchar()) != EOF)  // Read a character from input
    {
        if (islower(c))  // Check if the character is lowercase
            c = toupper(c);  // Convert to uppercase if lowercase
        putchar(c);  // Output the character (converted or not)
    }
    return 0;
}

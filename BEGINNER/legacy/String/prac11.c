#include <stdio.h>
#include <ctype.h>

int count_word(char *s)
{
    int i, wc = 0, waiting = 1;

    // Examine each character of the string
    for (i = 0; s[i] != '\0'; ++i)
    {
        if (isalpha(s[i]))  // If the character is alphabetic
        {
            if (waiting)  // If we are waiting for a word to start
            {
                wc++;  // Increment the word counter
                waiting = 0;  // We're now processing a word
            }
        }
        else  // If the character is not alphabetic (e.g., space or punctuation)
        {
            waiting = 1;  // We're waiting for the next word to start
        }
    }
    return wc;
}

int main(void)
{
    char str[] = "Hello, this is an example string!";
    printf("Word count: %d\n", count_word(str));  // Output the word count
    return 0;
}

#include <stdio.h>

int main(void)
{
    int i;
    char menu[5][10] = {
        "init",
        "open",
        "close",
        "read",
        "write"
    };

    // Loop through the menu array and print the menu items
    for (i = 0; i < 5; i++) {
        printf("Menu %d: %s\n", i + 1, menu[i]);
    }

    return 0;
}

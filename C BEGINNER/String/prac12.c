#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    int lower_case_count = 0;  // Number of lowercase letters
    int upper_case_count = 0;  // Number of uppercase letters
    int digit_count = 0;       // Number of digits
    char pass[100];
    int len;

    printf("Enter your password: ");
    fgets(pass, sizeof(pass), stdin);  // Read password with spaces safely

    len = strlen(pass);  // Length of the string

    // Remove the newline character added by fgets
    if (pass[len - 1] == '\n') {
        pass[len - 1] = '\0';
        len--;
    }

    // Check if password length is less than 7
    if (len < 7) {
        printf("Not a valid password.\n");
        return 1;
    }

    // Loop through each character in the password
    for (int i = 0; i < len; i++) {
        if (islower(pass[i])) ++lower_case_count;
        if (isupper(pass[i])) ++upper_case_count;
        if (isdigit(pass[i])) ++digit_count;
    }

    // Validate password criteria
    if (lower_case_count > 0 && upper_case_count > 0 && digit_count > 0)
        printf("This is a strong password.\n");
    else
        printf("Not a valid password.\n");

    return 0;
}

/*
 * Day 07 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_palindrome(const char *s) {
    int len = (int)strlen(s);
    for (int i = 0; i < len / 2; i++)
        if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[len-1-i]))
            return 0;
    return 1;
}

void to_title_case(char *s) {
    int new_word = 1;
    for (int i = 0; s[i]; i++) {
        if (isspace((unsigned char)s[i])) new_word = 1;
        else if (new_word) { s[i] = (char)toupper((unsigned char)s[i]); new_word = 0; }
        else               s[i] = (char)tolower((unsigned char)s[i]);
    }
}

int main(void) {
    char s[128];

    /* Ex 1 */
    printf("Enter string to reverse: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';
    int len = (int)strlen(s);
    for (int i = len-1; i >= 0; i--) printf("%c", s[i]);
    printf("\n");

    /* Ex 2 */
    printf("Palindrome test for '%s': %s\n", s, is_palindrome(s) ? "yes" : "no");

    /* Ex 3 */
    int vowels = 0;
    for (int i = 0; s[i]; i++) {
        char c = (char)tolower((unsigned char)s[i]);
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') vowels++;
    }
    printf("Vowels: %d\n", vowels);

    /* Ex 4 */
    char copy[128];
    strcpy(copy, s);
    for (int i = 0; copy[i]; i++) if (copy[i] == ' ') copy[i] = '_';
    printf("Spaces replaced: %s\n", copy);

    /* Ex 5 */
    char tc[128];
    strcpy(tc, "hello world example");
    to_title_case(tc);
    printf("Title case: %s\n", tc);

    return 0;
}

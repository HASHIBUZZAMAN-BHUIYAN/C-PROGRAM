/*
 * Day 07 Mini-Project — Word Counter & Caesar Cipher
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(char *str, int shift) {
    for (int i = 0; str[i]; i++) {
        char c = str[i];
        if (isalpha((unsigned char)c)) {
            char base = islower((unsigned char)c) ? 'a' : 'A';
            str[i] = (char)(base + (c - base + shift) % 26);
        }
    }
}

int count_words(const char *str) {
    int words = 0, in_word = 0;
    for (int i = 0; str[i]; i++) {
        if (isspace((unsigned char)str[i])) in_word = 0;
        else if (!in_word)               { in_word = 1; words++; }
    }
    return words;
}

int main(void) {
    char text[256];
    printf("=== Word Counter & Caesar Cipher ===\n");
    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Words: %d\n", count_words(text));
    printf("Chars: %zu\n", strlen(text));

    char encrypted[256];
    strcpy(encrypted, text);
    caesar_encrypt(encrypted, 3);
    printf("Caesar+3: %s\n", encrypted);

    caesar_encrypt(encrypted, 26 - 3);  /* decrypt */
    printf("Decrypted: %s\n", encrypted);
    return 0;
}

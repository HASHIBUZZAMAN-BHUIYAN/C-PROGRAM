/*
 * Day 07 — Strings in C
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    printf("=== Day 07: Strings ===\n\n");

    /* --- String literals and char arrays --- */
    char greeting[] = "Hello, World!";
    printf("String: %s\n", greeting);
    printf("Length: %zu (not counting null terminator)\n", strlen(greeting));
    printf("Size  : %zu (includes null terminator)\n", sizeof(greeting));

    /* --- String copy and concatenation --- */
    char dest[64];
    strcpy(dest, "C");
    strcat(dest, " programming");
    strcat(dest, " is fun!");
    printf("After strcpy+strcat: %s\n", dest);

    /* --- String comparison --- */
    char s1[] = "apple", s2[] = "banana";
    int cmp = strcmp(s1, s2);
    printf("\nstrcmp(\"%s\", \"%s\") = %d (%s)\n",
           s1, s2, cmp, cmp < 0 ? "s1 < s2" : cmp > 0 ? "s1 > s2" : "equal");

    /* --- Searching in strings --- */
    char sentence[] = "The quick brown fox jumps";
    char *found = strstr(sentence, "fox");
    if (found) printf("Found 'fox' at index %td\n", found - sentence);

    char *ch = strchr(sentence, 'q');
    if (ch) printf("First 'q' at index %td\n", ch - sentence);

    /* --- Character-by-character processing --- */
    char mixed[] = "Hello World 123";
    printf("\nOriginal  : %s\n", mixed);
    for (int i = 0; mixed[i] != '\0'; i++) {
        mixed[i] = (char)toupper((unsigned char)mixed[i]);
    }
    printf("Uppercase : %s\n", mixed);

    /* --- sprintf: format into a buffer --- */
    char buffer[128];
    int age = 25;
    float gpa = 3.75f;
    sprintf(buffer, "Student age=%d GPA=%.2f", age, gpa);
    printf("\nFormatted: %s\n", buffer);

    /* --- Safe input with fgets --- */
    char name[64];
    printf("\nEnter your full name (fgets): ");
    fgets(name, sizeof(name), stdin);
    /* fgets keeps the '\n', strip it */
    name[strcspn(name, "\n")] = '\0';
    printf("Hello, %s! (length=%zu)\n", name, strlen(name));

    return 0;
}

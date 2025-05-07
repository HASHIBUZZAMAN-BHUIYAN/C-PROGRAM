#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_COMMENT_LENGTH 1000

// Define the structure for storing words
typedef struct {
    char negativeWords[10][MAX_WORD_LENGTH]; // Array to store negative words
    char positiveWords[10][MAX_WORD_LENGTH]; // Array to store positive words
    int negativeCount;
    int positiveCount;
} Keywords;

// Function to load keywords from file into the Keywords structure
void loadKeywords(Keywords *keywords) {
    FILE *file = fopen("bad_good_words.txt", "r");
    if (!file) {
        printf("Error opening bad_good_words.txt\n");
        return;
    }

    keywords->negativeCount = 0;
    keywords->positiveCount = 0;

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        if (word[0] == '-') { // Negative words start with '-'
            strcpy(keywords->negativeWords[keywords->negativeCount++], word + 1); // Remove the '-' from the word
        } else { // Positive words
            strcpy(keywords->positiveWords[keywords->positiveCount++], word);
        }
    }

    fclose(file);
}

// Boyer-Moore String Matching Algorithm
int boyerMooreSearch(const char *text, const char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    int badChar[256];
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    // Preprocessing the bad character rule
    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            return shift; // Pattern found
            shift += (shift + m < n) ? m - badChar[(int)text[shift + m]] : 1;
        } else {
            shift += (j - badChar[(int)text[shift + j]] > 1) ? j - badChar[(int)text[shift + j]] : 1;
        }
    }

    return -1; // Pattern not found
}

// Function to filter comments
void filterComments(Keywords *keywords) {
    FILE *file = fopen("fan_response.txt", "r");
    if (!file) {
        printf("Error opening fan_response.txt\n");
        return;
    }

    char comment[MAX_COMMENT_LENGTH];
    while (fgets(comment, MAX_COMMENT_LENGTH, file)) {
        bool isPositive = false, isNegative = false;

        // Check for negative words
        for (int i = 0; i < keywords->negativeCount; i++) {
            if (boyerMooreSearch(comment, keywords->negativeWords[i]) != -1) {
                isNegative = true;
                break;
            }
        }

        // Check for positive words
        for (int i = 0; i < keywords->positiveCount; i++) {
            if (boyerMooreSearch(comment, keywords->positiveWords[i]) != -1) {
                isPositive = true;
                break;
            }
        }

        // Print the comment if it contains no negative words hb inject
        if (isNegative) {
            printf("Filtered out negative comment: %s", comment);
        } else if (isPositive) {
            printf("Positive comment: %s", comment);
        } else {
            printf("Neutral comment: %s", comment);
        }
    }

    fclose(file);
}

// Admin function for filtering comments based on keywords
void filterComment() {
    Keywords keywords;
    loadKeywords(&keywords);
    filterComments(&keywords);
}

int main() {
    filterComment();
    return 0;
}

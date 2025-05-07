#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_EXPRESSIONS 12
#define MAX_PROBLEM_LINES 100

// List of ambiguous expressions (problematic words/phrases)
const char *expressions[MAX_EXPRESSIONS] = {
    "항상", "절대", "모든 사람", "모든 것", "대부분", 
    "상당수", "가끔", "종종", "아마도", "아마", 
    "정확하지는 않지만", "싫지는 않지만", "찐이야", "버려"
};

// Structure to store validation results
typedef struct {
    int lineNumber;
    char line[MAX_LINE_LENGTH];
} ValidationResult;

ValidationResult validationResults[MAX_PROBLEM_LINES];
int resultCount = 0;

// KMP search function to check if a given expression is in a line
int KMPSearch(const char *line, const char *pattern) {
    int m = strlen(pattern);
    int n = strlen(line);
    
    int lps[m];
    int i = 0;
    int j = 0;

    // Preprocessing phase: Compute the LPS array
    lps[0] = 0;
    for (int k = 1; k < m; k++) {
        while (j > 0 && pattern[j] != pattern[k]) {
            j = lps[j - 1];
        }
        if (pattern[j] == pattern[k]) {
            j++;
        }
        lps[k] = j;
    }

    // Searching phase: Use the LPS array to find the pattern
    j = 0;
    for (i = 0; i < n; i++) {
        while (j > 0 && pattern[j] != line[i]) {
            j = lps[j - 1];
        }
        if (pattern[j] == line[i]) {
            j++;
        }
        if (j == m) {
            return 1; // Pattern found
        }
    }
    return 0; // Pattern not found
}

// Brute-force search function (Bonus)
int bruteForceSearch(const char *line, const char *pattern) {
    int m = strlen(pattern);
    int n = strlen(line);

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && line[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return 1; // Pattern found
        }
    }
    return 0; // Pattern not found
}

// Function to validate text and search for problematic expressions
void writingManners(const char *fileName, int useBruteForce) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int lineNumber = 1;

    // Read through each line of the file
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        // Check each expression for a match
        for (int i = 0; i < MAX_EXPRESSIONS; i++) {
            int found = 0;
            if (useBruteForce) {
                found = bruteForceSearch(line, expressions[i]);
            } else {
                found = KMPSearch(line, expressions[i]);
            }

            if (found) {
                // Store the result if an expression is found
                validationResults[resultCount].lineNumber = lineNumber;
                strncpy(validationResults[resultCount].line, line, MAX_LINE_LENGTH);
                resultCount++;
                break; // No need to check further expressions for this line
            }
        }
        lineNumber++;
    }

    fclose(file);
}
//hb inject
// Function to print the validation results
void printValidationResults() {
    if (resultCount == 0) {
        printf("No problematic expressions found.\n");
    } else {
        printf("Problematic expressions found in the following lines:\n");
        for (int i = 0; i < resultCount; i++) {
            printf("Line %d: %s", validationResults[i].lineNumber, validationResults[i].line);
        }
    }
}

int main() {
    int choice;
    char fileName[MAX_LINE_LENGTH];

    printf("Enter the file name to validate: ");
    fgets(fileName, MAX_LINE_LENGTH, stdin);
    fileName[strcspn(fileName, "\n")] = 0; // Remove newline character

    printf("Choose string search method:\n");
    printf("1. KMP Algorithm\n2. Brute Force Algorithm (Bonus)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    // Validate the text using the selected search method
    writingManners(fileName, choice == 2);

    // Print the results
    printValidationResults();

    return 0;
}

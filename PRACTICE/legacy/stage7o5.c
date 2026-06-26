#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50
#define MAX_LINE_LENGTH 200

// Structure for storing words in the word pool
typedef struct WordPool {
    char word[MAX_WORD_LENGTH];
    struct WordPool *next;
} WordPool;

// Structure for storing the frequency of words used in the writing
typedef struct WordFrequency {
    char word[MAX_WORD_LENGTH];
    int frequency;
    struct WordFrequency *next;
} WordFrequency;

// Function prototypes
void doCreativeWriting();
void loadWordPool(const char *filename, WordPool **head);
void printWordPool(WordPool *head);
void selectRandomWords(WordPool *head, int numWords, WordPool **selectedWords);
void addWordToFrequencyList(WordFrequency **head, const char *word);
void printWordFrequencies(WordFrequency *head);
void freeWordPool(WordPool *head);
void freeWordFrequencyList(WordFrequency *head);
int isValidWord(char *word, WordPool *selectedWords);
void saveWritingToFile(char *writing);
void getRandomWordFromPool(WordPool *head, char *word);

int main() {
    // Start the creative writing process
    doCreativeWriting();
    return 0;
}

void doCreativeWriting() {
    WordPool *wordPool = NULL;
    WordPool *selectedWords = NULL;
    WordFrequency *frequencyList = NULL;
    char writing[MAX_LINE_LENGTH * 20]; // To hold all lines of the writing
    int numWords, numLines;
    
    // Load the word pool from the file
    loadWordPool("writing_words.txt", &wordPool);
    
    // Ask the user for the number of words to use (between 10 and 20)
    printf("Enter the number of words to use (10-20): ");
    scanf("%d", &numWords);
    if (numWords < 10 || numWords > 20) {
        printf("Invalid number of words. Please enter a value between 10 and 20.\n");
        return;
    }

    // Ask the user for the maximum word length (between 2 and 7)
    int maxWordLength;
    printf("Enter the maximum word length (2-7): ");
    scanf("%d", &maxWordLength);
    if (maxWordLength < 2 || maxWordLength > 7) {
        printf("Invalid word length. Please enter a value between 2 and 7.\n");
        return;
    }
    
    // Select random words from the word pool
    selectRandomWords(wordPool, numWords, &selectedWords);
    
    // Print the selected words
    printf("\nSelected words for writing:\n");
    printWordPool(selectedWords);
    
    // Write lines of text
    printf("\nStart writing your text. Enter %d lines, each containing the selected words.\n", numWords);
    getchar();  // To consume the leftover newline
    for (int i = 0; i < numWords; i++) {
        printf("Line %d: ", i + 1);
        fgets(writing + i * MAX_LINE_LENGTH, MAX_LINE_LENGTH, stdin);
    }

    // Check if the written lines meet the conditions
    printf("\nChecking if the conditions are met...\n");
    char *wordPtr = writing;
    while (*wordPtr != '\0') {
        // Skip non-alphabetical characters
        if ((*wordPtr < 'a' || *wordPtr > 'z') && (*wordPtr < 'A' || *wordPtr > 'Z')) {
            wordPtr++;
            continue;
        }

        // Start reading the word
        char word[MAX_WORD_LENGTH] = {0};
        int j = 0;
        while ((*wordPtr >= 'a' && *wordPtr <= 'z') || (*wordPtr >= 'A' && *wordPtr <= 'Z')) {
            word[j++] = *wordPtr++;
        }

        // Make sure word is valid
        word[j] = '\0';

        // If it's a valid word, add to the frequency list
        if (isValidWord(word, selectedWords)) {
            addWordToFrequencyList(&frequencyList, word);
        }

        wordPtr++;
    }

    // Check if all selected words have been used at least once
    int valid = 1;
    WordPool *temp = selectedWords;
    while (temp != NULL) {
        int found = 0;
        WordFrequency *freqTemp = frequencyList;
        while (freqTemp != NULL) {
            if (strcmp(temp->word, freqTemp->word) == 0) {
                found = 1;
                break;
            }
            freqTemp = freqTemp->next;
        }
        if (!found) {
            valid = 0;
            break;
        }
        temp = temp->next;
    }

    if (valid) {
        // Save the writing to the file
        saveWritingToFile(writing);
        // Print the word frequencies
        printWordFrequencies(frequencyList);
    } else {
        printf("\nWriting does not meet the required conditions. Please try again.\n");
    }

    // Free the allocated memory
    freeWordPool(wordPool);
    freeWordPool(selectedWords);
    freeWordFrequencyList(frequencyList);
}

void loadWordPool(const char *filename, WordPool **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        WordPool *newNode = (WordPool *)malloc(sizeof(WordPool));
        strcpy(newNode->word, word);
        newNode->next = *head;
        *head = newNode;
    }

    fclose(file);
}

void selectRandomWords(WordPool *head, int numWords, WordPool **selectedWords) {
    WordPool *temp = head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    srand(time(NULL));  // Seed the random number generator

    // Randomly select words from the word pool
    for (int i = 0; i < numWords; i++) {
        int randIndex = rand() % count;
        temp = head;
        for (int j = 0; j < randIndex; j++) {
            temp = temp->next;
        }

        // Add the selected word to the list
        WordPool *newNode = (WordPool *)malloc(sizeof(WordPool));
        strcpy(newNode->word, temp->word);
        newNode->next = *selectedWords;
        *selectedWords = newNode;
    }
}

void addWordToFrequencyList(WordFrequency **head, const char *word) {
    WordFrequency *temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            temp->frequency++;
            return;
        }
        temp = temp->next;
    }

    // If the word is not found, add it
    WordFrequency *newNode = (WordFrequency *)malloc(sizeof(WordFrequency));
    strcpy(newNode->word, word);
    newNode->frequency = 1;
    newNode->next = *head;
    *head = newNode;
}

int isValidWord(char *word, WordPool *selectedWords) {
    WordPool *temp = selectedWords;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
//hb inject
void printWordPool(WordPool *head) {
    WordPool *temp = head;
    while (temp != NULL) {
        printf("%s\n", temp->word);
        temp = temp->next;
    }
}

void printWordFrequencies(WordFrequency *head) {
    WordFrequency *temp = head;
    while (temp != NULL) {
        printf("%s: %d\n", temp->word, temp->frequency);
        temp = temp->next;
    }
}

void saveWritingToFile(char *writing) {
    FILE *file = fopen("camelcase.txt", "w");
    if (file == NULL) {
        printf("Error opening file to save writing.\n");
        return;
    }
    fprintf(file, "%s", writing);
    fclose(file);
}

void freeWordPool(WordPool *head) {
    WordPool *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freeWordFrequencyList(WordFrequency *head) {
    WordFrequency *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

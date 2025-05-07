#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_SENTENCES 10
#define MAX_WORDS_IN_SENTENCE 10
#define MAX_NAME_LENGTH 50
#define MAX_COUNTRY_LENGTH 50
#define MAX_SENTENCE_LENGTH 100

// Structure for storing a Korean sentence and its romanized form
typedef struct {
    char korean_sentence[MAX_SENTENCE_LENGTH];
    char romanized_sentence[MAX_SENTENCE_LENGTH];
    char inputter[MAX_NAME_LENGTH];
} KoreanSentence;

// Structure for storing member information
typedef struct {
    char group_name[MAX_NAME_LENGTH];
    char member_name[MAX_NAME_LENGTH];
    char nationality[MAX_COUNTRY_LENGTH];
} Member;

// Structure for storing evaluation results of the dictation test
typedef struct {
    char member_name[MAX_NAME_LENGTH];
    int score;
    int max_matching_words;
    int min_matching_words;
} EvaluationResult;

// List of members
Member members[MAX_MEMBERS] = {
    {"Milieways", "YJ", "Korean"},
    {"Milieways", "WC", "Korean"},
    {"Milieways", "AR", "Korean"},
    {"Milieways", "JK", "Non-Korean"},
    {"Milieways", "CS", "Non-Korean"}
};

// List of sentences for dictation test
KoreanSentence sentences[MAX_SENTENCES];

// Function to input 5 Korean sentences and their romanized versions
void inputKoreanSentences() {
    char inputter[MAX_NAME_LENGTH];
    printf("Enter the name of the inputter (must be a Korean member): ");
    scanf("%s", inputter);

    // Check if inputter is a Korean member
    int is_korean = 0;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i].member_name, inputter) == 0 && strcmp(members[i].nationality, "Korean") == 0) {
            is_korean = 1;
            break;
        }
    }

    if (!is_korean) {
        printf("Error: Inputter must be a Korean member.\n");
        return;
    }

    // Input 5 Korean sentences and their romanized versions
    printf("Please input 5 Korean sentences and their romanized versions:\n");
    for (int i = 0; i < 5; i++) {
        printf("Sentence %d in Korean: ", i + 1);
        scanf(" %[^\n]", sentences[i].korean_sentence);  // Reading sentence with spaces
        printf("Sentence %d in romanized form: ", i + 1);
        scanf(" %[^\n]", sentences[i].romanized_sentence);
        strcpy(sentences[i].inputter, inputter);
    }
}

// Function to evaluate the word matching ratio for a sentence
int evalWordMatchingRatio(const char* korean, const char* romanized) {
    int match_count = 0;
    char* word_korean = strtok(strdup(korean), " ");
    char* word_romanized = strtok(strdup(romanized), " ");
    
    while (word_korean != NULL && word_romanized != NULL) {
        if (strcmp(word_korean, word_romanized) == 0) {
            match_count++;
        }
        word_korean = strtok(NULL, " ");
        word_romanized = strtok(NULL, " ");
    }
    
    return match_count;
}

// Function to play the dictation game
void playGame(EvaluationResult* result) {
    int total_score = 0;
    int max_matching_words = 0;
    int min_matching_words = MAX_WORDS_IN_SENTENCE;
    
    for (int i = 0; i < 5; i++) {
        printf("Romanized sentence %d: %s\n", i + 1, sentences[i].romanized_sentence);
        char korean_input[MAX_SENTENCE_LENGTH];
        printf("Enter the Korean version: ");
        scanf(" %[^\n]", korean_input);
        
        int matching_words = evalWordMatchingRatio(sentences[i].korean_sentence, korean_input);
        printf("Matching words: %d\n", matching_words);
        total_score += matching_words * 4;  // Each matching word adds 4 points (out of 20)
        
        if (matching_words > max_matching_words) max_matching_words = matching_words;
        if (matching_words < min_matching_words) min_matching_words = matching_words;
    }

    result->score = total_score;
    result->max_matching_words = max_matching_words;
    result->min_matching_words = min_matching_words;
}

// Function to play dictation for each member
void doDictation() {
    // First, check if we need to input new sentences
    if (strlen(sentences[0].korean_sentence) == 0) {
        inputKoreanSentences();
    }

    // Evaluate dictation test for each member
    EvaluationResult results[MAX_MEMBERS];
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i].nationality, "Non-Korean") == 0) {
            printf("Starting dictation for %s...\n", members[i].member_name);
            playGame(&results[i]);
        }
    }

    // Print results
    printf("Dictation Results:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i].nationality, "Non-Korean") == 0) {
            printf("Member: %s, Total Score: %d, Max Matching Words: %d, Min Matching Words: %d\n", 
                   results[i].member_name, results[i].score, results[i].max_matching_words, results[i].min_matching_words);
        }
    }
}

// Function to sort and print dictation results
void printSortedResults(EvaluationResult* results, int count, int sort_by_max) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (sort_by_max ? results[i].max_matching_words < results[j].max_matching_words :
                               results[i].min_matching_words > results[j].min_matching_words) {
                EvaluationResult temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }
        }
    }

    printf("Sorted Dictation Results:\n");
    for (int i = 0; i < count; i++) {
        printf("Member: %s, Total Score: %d, Max Matching Words: %d, Min Matching Words: %d\n", 
               results[i].member_name, results[i].score, results[i].max_matching_words, results[i].min_matching_words);
    }
}

int main() {
    int choice;
    printf("Welcome to the Dictation Test!\n");

    // Main menu loop
    while (1) {
        printf("\n1. Start Dictation Test\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
//hb inject
        switch (choice) {
            case 1:
                doDictation();
                break;
            case 2:
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice. Please choose again.\n");
        }
    }

    return 0;
}

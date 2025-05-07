#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 5
#define MAX_QUIZZES 3
#define MAX_NAME_LENGTH 50

// Define the Hangul character struct
typedef struct {
    char hangul[10];  // Hangul character
    char english[10]; // English alphabet
    char pronunciation[50]; // English pronunciation
} HangulCharacter;

// Define the Learning Result struct
typedef struct {
    char name[MAX_NAME_LENGTH]; // Learner's name
    char challenge_type[3]; // KE (Hangul to English) or EK (English to Hangul)
    int total_score; // Total score
    int attempt_count; // Attempt count
} LearningResult;

// Hangul consonants and vowels
HangulCharacter consonants[] = {
    {"ㄱ", "g", "giyeok"},
    {"ㄴ", "n", "nieun"},
    {"ㄷ", "d", "digeut"},
    {"ㄹ", "r", "rieul"},
    {"ㅁ", "m", "mieum"},
    {"ㅂ", "b", "bieup"},
    {"ㅅ", "s", "siot"},
    {"ㅇ", "ng", "ieung"},
    {"ㅈ", "j", "jieut"},
    {"ㅊ", "ch", "chieut"},
    {"ㅋ", "k", "kieuk"},
    {"ㅌ", "t", "tieut"},
    {"ㅍ", "p", "pieup"},
    {"ㅎ", "h", "hieut"}
};

HangulCharacter vowels[] = {
    {"ㅏ", "a", "a"},
    {"ㅓ", "eo", "eo"},
    {"ㅗ", "o", "o"},
    {"ㅜ", "u", "u"},
    {"ㅡ", "eu", "eu"},
    {"ㅣ", "i", "i"},
    {"ㅐ", "ae", "ae"},
    {"ㅔ", "e", "e"},
    {"ㅑ", "ya", "ya"},
    {"ㅕ", "yeo", "yeo"}
};

// Initialize result storage
LearningResult results[MAX_QUIZZES];

// Function to display the menu
void displayMenu() {
    printf("\n1. Hangul to English\n");
    printf("2. English to Hangul\n");
    printf("3. View Results\n");
    printf("Choose an option (1-3): ");
}

// Function to play the Hangul to English game (KE)
void playKor2EngGame(HangulCharacter *characters, int is_consonant) {
    int score = 0;
    int questions[MAX_QUESTIONS];
    int i, j;
    srand(time(NULL));

    // Select 5 unique random questions
    printf("Choose category:\n");
    printf("1. Consonants\n2. Vowels\nChoose an option: ");
    int category;
    scanf("%d", &category);

    // Select 5 random questions
    for (i = 0; i < MAX_QUESTIONS; i++) {
        do {
            questions[i] = rand() % (category == 1 ? 14 : 10);
        } while (i > 0 && questions[i] == questions[i - 1]);
    }

    // Ask the questions
    for (i = 0; i < MAX_QUESTIONS; i++) {
        int idx = questions[i];
        printf("Question %d: What is the English letter and pronunciation of '%s'? (format: letter, pronunciation)\n", i + 1, characters[idx].hangul);
        char answer[100];
        scanf("%s", answer);

        // Check answer
        if (strcmp(answer, characters[idx].english) == 0 || strcmp(answer, characters[idx].pronunciation) == 0) {
            printf("Correct!\n");
            score += 10;
        } else {
            printf("Incorrect. Correct answer: %s (%s)\n", characters[idx].english, characters[idx].pronunciation);
        }
    }

    printf("Your score: %d\n", score);
}

// Function to play the English to Hangul game (EK)
void playEng2KorGame(HangulCharacter *characters, int is_consonant) {
    int score = 0;
    int questions[MAX_QUESTIONS];
    int i, j;
    srand(time(NULL));

    // Select 5 unique random questions
    printf("Choose category:\n");
    printf("1. Consonants\n2. Vowels\nChoose an option: ");
    int category;
    scanf("%d", &category);

    // Select 5 random questions
    for (i = 0; i < MAX_QUESTIONS; i++) {
        do {
            questions[i] = rand() % (category == 1 ? 14 : 10);
        } while (i > 0 && questions[i] == questions[i - 1]);
    }

    // Ask the questions
    for (i = 0; i < MAX_QUESTIONS; i++) {
        int idx = questions[i];
        printf("Question %d: What is the Hangul character for '%s' (%s)?\n", i + 1, characters[idx].english, characters[idx].pronunciation);
        char answer[100];
        scanf("%s", answer);

        // Check answer
        if (strcmp(answer, characters[idx].hangul) == 0) {
            printf("Correct!\n");
            score += 10;
        } else {
            printf("Incorrect. Correct answer: %s\n", characters[idx].hangul);
        }
    }

    printf("Your score: %d\n", score);
}

// Function to show the results
void showResult(LearningResult *results, int total_quizzes) {
    printf("\nResults:\n");
    for (int i = 0; i < total_quizzes; i++) {
        printf("Name: %s\n", results[i].name);
        printf("Challenge Type: %s\n", results[i].challenge_type);
        printf("Total Score: %d\n", results[i].total_score);
        printf("Attempts: %d\n\n", results[i].attempt_count);
    }
}

// Function to learn Hangul
void learnHangul() {
    char name[MAX_NAME_LENGTH];
    printf("Enter your name: ");
    scanf("%s", name);

    int attempt_count = 0;
    int total_quizzes = 0;

    // Loop for multiple attempts
    while (attempt_count < MAX_QUIZZES) {
        int choice;
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("You chose: Hangul to English (KE)\n");
                playKor2EngGame(consonants, 1); // Play Hangul to English game
                break;

            case 2:
                printf("You chose: English to Hangul (EK)\n");
                playEng2KorGame(consonants, 1); // Play English to Hangul game
                break;

            case 3:
                printf("You chose: View Results\n");
                showResult(results, total_quizzes); // Show results
                break;

            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
//hb inject
        attempt_count++;
        if (attempt_count >= MAX_QUIZZES) break;
    }
}

// Main function
int main() {
    learnHangul(); // Start learning Hangul

    return 0;
}

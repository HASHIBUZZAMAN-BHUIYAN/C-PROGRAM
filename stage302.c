#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 5
#define MAX_TRAINEES 10
#define MAX_NAME_LENGTH 50
#define MAX_WORDS_IN_SENTENCE 10

// Struct to represent an English-Korean sentence set
typedef struct {
    char english[100]; // English sentence
    char korean[100];  // Korean sentence (with at least 6 words)
} EngKorSentence;

// Struct to store learner's nickname and grammar score
typedef struct {
    char nickname[MAX_NAME_LENGTH]; // Learner's nickname
    int grammar_score;              // Learner's grammar score
} GrammarScore;

// Initialize English-Korean sentence pairs
EngKorSentence sentences[] = {
    {"I am a student.", "저는 학생입니다."},
    {"He is reading a book.", "그는 책을 읽고 있습니다."},
    {"She likes coffee.", "그녀는 커피를 좋아합니다."},
    {"We are going to school.", "우리는 학교에 가고 있습니다."},
    {"They are playing soccer.", "그들은 축구를 하고 있습니다."},
    {"I eat lunch every day.", "저는 매일 점심을 먹습니다."},
    {"She can speak English.", "그녀는 영어를 할 수 있습니다."},
    {"He is working hard.", "그는 열심히 일하고 있습니다."},
    {"We are learning Korean.", "우리는 한국어를 배우고 있습니다."},
    {"I am happy today.", "저는 오늘 행복합니다."}
};

// Initialize array to store grammar scores
GrammarScore grammar_scores[MAX_TRAINEES];

// Function to display the menu for learning Korean grammar
void displayMenu() {
    printf("\n1. Compose Korean Sentences\n");
    printf("2. Check Scores\n");
    printf("Choose an option (1-2): ");
}

// Function to shuffle words in the Korean sentence (Selection Sort approach)
void shuffleWords(char *sentence, char words[][20], int word_count) {
    char temp[20];
    int i, j;

    // Split Korean sentence into words
    char *token = strtok(sentence, " ");
    for (i = 0; token != NULL && i < word_count; i++) {
        strcpy(words[i], token);
        token = strtok(NULL, " ");
    }

    // Selection sort to shuffle words
    for (i = 0; i < word_count - 1; i++) {
        for (j = i + 1; j < word_count; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                strcpy(temp, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], temp);
            }
        }
    }
}

// Function to compose Korean sentences
void composeSentences() {
    int score = 0;
    char words[MAX_WORDS_IN_SENTENCE][20];
    char user_answer[100];
    srand(time(NULL));

    // Ask 5 random questions
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        int index = rand() % 10;
        printf("\nQuestion %d: %s\n", i + 1, sentences[index].english);

        // Shuffle Korean words
        shuffleWords(sentences[index].korean, words, 6);

        // Display shuffled words
        printf("Shuffled words: ");
        for (int j = 0; j < 6; j++) {
            printf("%s ", words[j]);
        }
        printf("\n");

        printf("Arrange the words to form the correct Korean sentence: ");
        fgets(user_answer, 100, stdin);
        user_answer[strcspn(user_answer, "\n")] = 0; // Remove trailing newline

        // Check if the answer is correct
        if (strcmp(user_answer, sentences[index].korean) == 0) {
            printf("Correct! +20 points\n");
            score += 20;
        } else {
            printf("Incorrect. The correct sentence is: %s\n", sentences[index].korean);
        }
    }

    printf("\nYour score: %d\n", score);
}

// Function to check and display scores
void printScore(int total_trainees) {
    printf("\nGrammar Scores:\n");

    // Sort results by score using Quick Sort
    quickSort(grammar_scores, 0, total_trainees - 1);

    // Display all learners' scores
    for (int i = 0; i < total_trainees; i++) {
        printf("Nickname: %s, Score: %d\n", grammar_scores[i].nickname, grammar_scores[i].grammar_score);
    }
}

// Quick Sort function to sort grammar scores in descending order
void quickSort(GrammarScore arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Partition function for Quick Sort
int partition(GrammarScore arr[], int low, int high) {
    GrammarScore pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j].grammar_score > pivot.grammar_score) {
            i++;
            GrammarScore temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    GrammarScore temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Function to learn Korean grammar
void learnKoreanGrammar() {
    char nickname[MAX_NAME_LENGTH];
    int attempt_count = 0;
    int total_trainees = 0;

    // Get learner's nickname and validate
    while (attempt_count < 3) {
        printf("Enter your nickname: ");
        scanf("%s", nickname);
        
        // Check if the nickname already exists
        int found = 0;
        for (int i = 0; i < total_trainees; i++) {
            if (strcmp(grammar_scores[i].nickname, nickname) == 0) {
                printf("Nickname already taken. Please choose another nickname.\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            // Add the new trainee
            strcpy(grammar_scores[total_trainees].nickname, nickname);
            grammar_scores[total_trainees].grammar_score = 0;
            total_trainees++;
            break;
        }

        attempt_count++;
    }

    if (attempt_count == 3) {
        printf("Too many attempts. Exiting...\n");
        return;
    }

    // Menu for grammar learning
    int choice;
    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("You chose: Compose Korean Sentences\n");
                composeSentences();
                break;

            case 2:
                printf("You chose: Check Scores\n");
                printScore(total_trainees);
                break;
//hb inject
            default:
                printf("Invalid choice, exiting.\n");
                return;
        }
    }
}

// Main function
int main() {
    learnKoreanGrammar(); // Start the Korean grammar learning process
    return 0;
}

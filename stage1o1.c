// stage1.c version 2.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINING 8
#define MAX_MEMBERS 5
#define FITNESS_CATEGORIES 7
#define MAX_NAME_LEN 50
#define MAX_NICKNAME_LEN 20

// Member structure
typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
} Member;

// Fitness categories
const char *fitnessCategories[] = {
    "1-Mile Running Test (min)",
    "Speed Sprint (sec)",
    "Push-ups (min for 30)",
    "Squats (min for 50)",
    "Arm Strength (min for 50)",
    "Swimming (min for 400m)",
    "Weightlifting (BW multiplier)"
};

// Predefined member data
Member milliways_members[MAX_MEMBERS] = {
    {"Goeun Lee", "goeun"},
    {"Woncheol Kim", "woncheol"},
    {"Youngjin Park", "youngjin"},
    {"Hyekyung Choi", "hyekyung"},
    {"Arthur Song", "arthur"}
};

// Fitness scores: rows = members, cols = test values HB = Hier Database
float health_scores[MAX_MEMBERS][FITNESS_CATEGORIES];

// Training HB menu titles
const char *mainMenu[] = {
    "I. Audition Management",
    "II. Training",
    "III. Debut"
};

const char *trainingMenu[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

// Training Hyper HB status
char trainingStatus[MAX_TRAINING];

// Function declarations
void showMainMenu();
void showTrainingMenu();
void handleTraining();
void handleStage1Menu();
void setHealth();
void getHealth();
int findMemberIndexByNickname(const char *nickname);
void parseFitnessData(const char *input, float values[], int count);
void clearInputBuffer();
char getYesNoInput();
void pressEnterToContinue();

int main() {
    int i;
    for (i = 0; i < MAX_TRAINING; ++i) {
        trainingStatus[i] = 'N';
    }

    while (1) {
        showMainMenu();

        printf("Select a main menu option (1-3), or Q to quit: ");
        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n' || input[0] == '0' || input[0] == 'q' || input[0] == 'Q') {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        switch (input[0]) {
            case '1':
                printf("\n[Audition Management] feature not implemented.\n");
                pressEnterToContinue();
                break;
            case '2':
                handleTraining();
                break;
            case '3':
                printf("\n[Debut] feature not implemented.\n");
                pressEnterToContinue();
                break;
            default:
                printf("Invalid input. Please try again.\n");
                pressEnterToContinue();
        }
    }

    return 0;
}

void showMainMenu() {
    system("clear||cls");
    printf("====== Magrathea System ======\n");
    int i;
    for (i = 0; i < 3; ++i) {
        printf("%d. %s\n", i + 1, mainMenu[i]);
    }
    printf("==============================\n");
}

void showTrainingMenu() {
    printf("\n----- Training Menu -----\n");
    int i;
    for (i = 0; i < MAX_TRAINING; ++i) {
        printf("%d. %s [%c]\n", i + 1, trainingMenu[i], trainingStatus[i]);
    }
    printf("0. Return to Main Menu\n");
    printf("-------------------------\n");
}

void handleTraining() {
    while (1) {
        system("clear||cls");
        showTrainingMenu();
        printf("Select a training stage (1-8), or 0 to return: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        int stage = atoi(input);

        if (stage == 0) {
            break;
        }

        if (stage < 1 || stage > 8) {
            printf("Invalid stage number.\n");
            pressEnterToContinue();
            continue;
        }

        int index = stage - 1;

        if (trainingStatus[index] == 'P') {
            printf("Stage %d already completed. Cannot retake.\n", stage);
            pressEnterToContinue();
            continue;
        }

        if ((stage == 2 && trainingStatus[0] != 'P') ||
            (stage >= 3 && (trainingStatus[0] != 'P' || trainingStatus[1] != 'P'))) {
            printf("You must pass earlier required stages first.\n");
            pressEnterToContinue();
            continue;
        }

        if (stage == 1) {
            handleStage1Menu();
        } else {
            printf("Would you like to enter the evaluation result? (Y/N): ");
            if (getYesNoInput() == 'Y') {
                printf("Did you complete the training and pass the certification? (Y for pass / N for fail): ");
                if (getYesNoInput() == 'Y') {
                    trainingStatus[index] = 'P';
                    printf("Stage %d marked as PASSED.\n", stage);
                } else {
                    trainingStatus[index] = 'F';
                    printf("Stage %d marked as FAILED.\n", stage);
                }
            } else {
                printf("Returning to training menu.\n");
            }
            pressEnterToContinue();
        }
    }
}

void handleStage1Menu() {
    while (1) {
        printf("\n== Physical Strength & Knowledge ==\n");
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("Q. Return to Training Menu\n");
        printf("Select an option: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        switch (input[0]) {
            case 'A':
            case 'a':
                setHealth();
                break;
            case 'B':
            case 'b':
                getHealth();
                break;
            case 'Q':
            case 'q':
                return;
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}

void setHealth() {
    char nickname[MAX_NICKNAME_LEN];
    char input[256];
    float values[FITNESS_CATEGORIES];
    int index;

    printf("Enter member nickname: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = '\0';

    index = findMemberIndexByNickname(nickname);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Enter fitness test values (comma-separated):\n");
    int i;
    for (i = 0; i < FITNESS_CATEGORIES; ++i) {
        printf("%d. %s\n", i + 1, fitnessCategories[i]);
    }

    printf("Input: ");
    fgets(input, sizeof(input), stdin);
    parseFitnessData(input, values, FITNESS_CATEGORIES);

    for (i = 0; i < FITNESS_CATEGORIES; ++i) {
        health_scores[index][i] = values[i];
    }

    printf("Fitness data stored successfully for %s.\n", nickname);
}

void getHealth() {
    char nickname[MAX_NICKNAME_LEN];
    int index, i;

    printf("Enter member nickname to view fitness data: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = '\0';

    index = findMemberIndexByNickname(nickname);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\n--- Fitness Data for %s (%s) ---\n", milliways_members[index].name, milliways_members[index].nickname);
    for (i = 0; i < FITNESS_CATEGORIES; ++i) {
        printf("%s: %.2f\n", fitnessCategories[i], health_scores[index][i]);
    }
    printf("------------------------------------\n");
    pressEnterToContinue();
}

void parseFitnessData(const char *input, float values[], int count) {
    char buffer[256];
    strncpy(buffer, input, sizeof(buffer));
    buffer[strcspn(buffer, "\n")] = '\0';

    char *token = strtok(buffer, ",");
    int i = 0;
    while (token != NULL && i < count) {
        values[i++] = atof(token);
        token = strtok(NULL, ",");
    }

    while (i < count) {
        values[i++] = 0.0f; // Fill missing with zero
    }
}

int findMemberIndexByNickname(const char *nickname) {
    int i;
    for (i = 0; i < MAX_MEMBERS; ++i) {
        if (strcmp(nickname, milliways_members[i].nickname) == 0) {
            return i;
        }
    }
    return -1;
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

char getYesNoInput() {
    char input[10];
    fgets(input, sizeof(input), stdin);
    if (input[0] == 'Y' || input[0] == 'y') {
        return 'Y';
    }
    return 'N';
}

void pressEnterToContinue() {
    printf("Press Enter to continue...");
    getchar();
}

// stage1.c version 1.0

#include <stdio.h>
#include <stdlib.h>

#define MAX_TRAINING 8

// Main and Training Menus as two separate 2D HB arrays
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

// Stores 'P' for passed, 'F' for failed, 'N' for not attempted
char trainingStatus[MAX_TRAINING];

// Function HB declarations
void showMainMenu();
void showTrainingMenu();
void handleTraining();
void clearInputBuffer();
char getYesNoInput();
void pressEnterToContinue();

int main() {
    // Initialize training status to 'N'
    for (int i = 0; i < MAX_TRAINING; ++i) {
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
    for (int i = 0; i < 3; ++i) {
        printf("%d. %s\n", i + 1, mainMenu[i]);
    }
    printf("==============================\n");
}

void showTrainingMenu() {
    printf("\n----- Training Menu -----\n");
    for (int i = 0; i < MAX_TRAINING; ++i) {
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

        // Check if stage already completed
        if (trainingStatus[index] == 'P') {
            printf("Stage %d already completed. Cannot retake.\n", stage);
            pressEnterToContinue();
            continue;
        }

        // Enforce sequential HB logic
        if ((stage == 2 && trainingStatus[0] != 'P') ||
            (stage >= 3 && (trainingStatus[0] != 'P' || trainingStatus[1] != 'P'))) {
            printf("You must pass earlier required stages first.\n");
            pressEnterToContinue();
            continue;
        }

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

void clearInputBuffer() {
    while (getchar() != '\n');
}

char getYesNoInput() {
    char input[10];
    fgets(input, sizeof(input), stdin);
    if (input[0] == 'Y' || input[0] == 'y') {
        return 'Y';
    } else {
        return 'N';
    }
}

void pressEnterToContinue() {
    printf("Press Enter to continue...");
    getchar();
}

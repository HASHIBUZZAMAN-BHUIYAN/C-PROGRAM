//stage1.c version 3.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINING 8
#define MAX_MEMBERS 5
#define FITNESS_CATEGORIES 7
#define MAX_NAME_LEN 50
#define MAX_NICKNAME_LEN 20
#define DAYS_IN_WEEK 6
#define MAX_ROUTINE_STR 100

// Member structure
typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
} Member;

// Member workout routine structure
char member_routine[MAX_MEMBERS][DAYS_IN_WEEK][MAX_ROUTINE_STR];

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

// Days
const char *daysOfWeek[] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

// Exercise types
const char *exercise_types[] = {
    "Cardio: Running, Cycling, Fast Walking",
    "Full-body Strength: Push-ups, Squats",
    "Lower-body Strength: Leg Press, Leg Curl",
    "Upper-body Strength: Pull-ups, Chin-ups",
    "Core Strength: Plank, Crunches"
};

// Predefined member data
Member milliways_members[MAX_MEMBERS] = {
    {"Goeun Lee", "goeun"},
    {"Woncheol Kim", "woncheol"},
    {"Youngjin Park", "youngjin"},
    {"Hyekyung Choi", "hyekyung"},
    {"Arthur Song", "arthur"}
};

// Fitness HB (Hyper Database) scores
float health_scores[MAX_MEMBERS][FITNESS_CATEGORIES];

// Training HB status
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

char trainingStatus[MAX_TRAINING];

// Function declarations
void showMainMenu();
void showTrainingMenu();
void handleTraining();
void handleStage1Menu();
void setHealth();
void getHealth();
void setExerciseRoutine();
void getExerciseRoutine();
void displayMemberList();
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
        printf("C. Set Basic Workout Routine\n");
        printf("D. View Basic Workout Routine\n");
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
            case 'C':
            case 'c':
                setExerciseRoutine();
                break;
            case 'D':
            case 'd':
                getExerciseRoutine();
                break;
            case 'Q':
            case 'q':
                return;
            default:
                printf("Invalid option. Try again.\n");
        }
    }
}

void displayMemberList() {
    int i;
    printf("\n--- Member List ---\n");
    for (i = 0; i < MAX_MEMBERS; ++i) {
        printf("%d. %s (%s)\n", i + 1, milliways_members[i].name, milliways_members[i].nickname);
    }
    printf("-------------------\n");
}

void setExerciseRoutine() {
    int i, j, index, coreUsed = 0;
    char nickname[MAX_NICKNAME_LEN];
    displayMemberList();

    printf("Enter member nickname to set workout routine: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = '\0';

    index = findMemberIndexByNickname(nickname);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Select 2 exercises for each day (1 cardio + 1 strength/core).\nCore exercises allowed only once/week.\n");

    for (i = 0; i < DAYS_IN_WEEK; ++i) {
        printf("\nDay: %s\n", daysOfWeek[i]);
        for (j = 0; j < 5; ++j) {
            printf("%d. %s\n", j + 1, exercise_types[j]);
        }

        int ex1, ex2;
        printf("Enter two exercise numbers separated by space: ");
        scanf("%d %d", &ex1, &ex2);
        clearInputBuffer();

        if ((ex1 == 5 || ex2 == 5)) {
            if (coreUsed) {
                printf("Core exercise already used this week. Skipping core for this day.\n");
                if (ex1 == 5) ex1 = 1;
                if (ex2 == 5) ex2 = 2;
            } else {
                coreUsed = 1;
            }
        }

        snprintf(member_routine[index][i], MAX_ROUTINE_STR, "%s & %s", 
                 exercise_types[ex1 - 1], exercise_types[ex2 - 1]);
    }

    printf("Workout routine stored for %s.\n", nickname);
    pressEnterToContinue();
}

void getExerciseRoutine() {
    char name[MAX_NAME_LEN];
    int i, index = -1;

    displayMemberList();
    printf("Enter member real name to view workout routine: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (i = 0; i < MAX_MEMBERS; ++i) {
        if (strcmp(name, milliways_members[i].name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\nWorkout Routine for %s (%s):\n", 
           milliways_members[index].name, 
           milliways_members[index].nickname);

    for (i = 0; i < DAYS_IN_WEEK; ++i) {
        printf("%s: %s\n", daysOfWeek[i], member_routine[index][i]);
    }

    pressEnterToContinue();
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
        values[i++] = 0.0f;
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

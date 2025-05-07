#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DANCE_STEPS 10
#define MAX_DANCES 6
#define MAX_MEMBERS 5
#define MAX_NAME_LENGTH 100
#define MAX_NICKNAME_LENGTH 50

// Dance structure to hold dance steps and names
typedef struct {
    char korean_name[MAX_NAME_LENGTH];
    char english_name[MAX_NAME_LENGTH];
    char steps[MAX_DANCE_STEPS][MAX_NAME_LENGTH];
    int num_steps;
} Dance;

// Member structure to hold member information
typedef struct {
    char name[MAX_NAME_LENGTH];
    char nickname[MAX_NICKNAME_LENGTH];
    int dance_score;
} Member;

// Global variables
Dance dances[MAX_DANCES]; // Array of dances
Member members[MAX_MEMBERS]; // Array of members

// Function to read dance steps from file
int readDanceSteps() {
    FILE *file = fopen("dance_step.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    for (int i = 0; i < MAX_DANCES; i++) {
        // Read Korean and English names
        fscanf(file, "%s %s", dances[i].korean_name, dances[i].english_name);

        // Read steps for the dance
        fscanf(file, "%d", &dances[i].num_steps);
        for (int j = 0; j < dances[i].num_steps; j++) {
            fscanf(file, "%s", dances[i].steps[j]);
        }
    }

    fclose(file);
    return 0;
}

// Function to shuffle steps randomly
void shuffleSteps(char steps[MAX_DANCE_STEPS][MAX_NAME_LENGTH], int num_steps) {
    srand(time(0)); // Seed for random number generator
    for (int i = 0; i < num_steps; i++) {
        int j = rand() % num_steps;
        char temp[MAX_NAME_LENGTH];
        strcpy(temp, steps[i]);
        strcpy(steps[i], steps[j]);
        strcpy(steps[j], temp);
    }
}

// Function to display steps for 10 seconds
void displayStepsWithTimer(char steps[MAX_DANCE_STEPS][MAX_NAME_LENGTH], int num_steps) {
    for (int i = 0; i < num_steps; i++) {
        printf("%d. %s\n", i + 1, steps[i]);
    }

    printf("\nDisplaying the steps for 10 seconds...\n");
    sleep(10); // Wait for 10 seconds
    system("clear"); // Clears the screen (use "cls" for Windows)
}

// Function to check if the steps are correct and assign score
int evaluateDanceSteps(char correct_steps[MAX_DANCE_STEPS][MAX_NAME_LENGTH], int num_steps,
                       char learner_steps[MAX_DANCE_STEPS][MAX_NAME_LENGTH]) {
    int correct_count = 0;
    int order_match = 1;

    // Check if order matches and steps are correct
    for (int i = 0; i < num_steps; i++) {
        if (strcmp(correct_steps[i], learner_steps[i]) == 0) {
            correct_count++;
        } else {
            order_match = 0;
        }
    }

    // Scoring based on the matching conditions
    if (correct_count == num_steps && order_match == 1) {
        return 100; // Exact match
    }
    if (correct_count == num_steps && order_match == 0) {
        return 50; // Correct steps but wrong order
    }
    if (correct_count > 0) {
        return 20; // At least one correct step
    }
    return 0; // No steps correct
}

// Function to input and validate member's nickname
int validateMemberNickname(char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i].nickname, nickname) == 0) {
            return i; // Valid member, return index
        }
    }
    return -1; // Invalid nickname
}

// Function to handle the learning dance step process
void learnDanceStep() {
    char nickname[MAX_NICKNAME_LENGTH];
    printf("Enter your nickname: ");
    scanf("%s", nickname);

    int member_index = validateMemberNickname(nickname);
    if (member_index == -1) {
        printf("Nickname not found. Try again.\n");
        printf("Enter your nickname: ");
        scanf("%s", nickname);
        member_index = validateMemberNickname(nickname);
        if (member_index == -1) {
            printf("Nickname not found again. Exiting...\n");
            return; // Exit to upper menu
        }
    }

    // Randomly pick a dance
    int dance_index = rand() % MAX_DANCES;
    printf("\nYou have to learn the dance: %s (%s)\n", dances[dance_index].korean_name, dances[dance_index].english_name);

    // Display the correct steps for 10 seconds
    displayStepsWithTimer(dances[dance_index].steps, dances[dance_index].num_steps);

    // Shuffle steps and ask the learner to input the sequence
    shuffleSteps(dances[dance_index].steps, dances[dance_index].num_steps);
    printf("\nEnter the steps in the correct order:\n");

    char learner_steps[MAX_DANCE_STEPS][MAX_NAME_LENGTH];
    for (int i = 0; i < dances[dance_index].num_steps; i++) {
        printf("Step %d: ", i + 1);
        scanf("%s", learner_steps[i]);
    }

    // Evaluate the learner's input
    int score = evaluateDanceSteps(dances[dance_index].steps, dances[dance_index].num_steps, learner_steps);
    members[member_index].dance_score = score;

    // Print results
    printf("\nCorrect answer steps:\n");
    for (int i = 0; i < dances[dance_index].num_steps; i++) {
        printf("%d. %s\n", i + 1, dances[dance_index].steps[i]);
    }
    printf("Your input steps:\n");
    for (int i = 0; i < dances[dance_index].num_steps; i++) {
        printf("%d. %s\n", i + 1, learner_steps[i]);
    }
    printf("Your score: %d\n", score);
}

int main() {
    // Sample members (In real-world case, this data might come from a file)
    strcpy(members[0].name, "John");
    strcpy(members[0].nickname, "Johnny");
    strcpy(members[1].name, "Sara");
    strcpy(members[1].nickname, "Sally");
//hb inject
    // Read dance step file and initialize data
    if (readDanceSteps() != 0) {
        return -1; // Error reading dance steps file
    }

    // Trigger the learning dance step function
    learnDanceStep();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_TRAINEES 10
#define MAX_NAME_LENGTH 50

// Structure to store vocal evaluation data for each trainee
typedef struct {
    char name[MAX_NAME_LENGTH];
    int vocal_range;
    float vocal_stability;
    char feedback[51]; // Feedback (max 50 characters + null terminator)
} Trainee;

// Function prototypes
void evalVocal();
void measure(Trainee *trainee);
float calculateStability(int midi_values[], int num_notes);
void provideFeedback(Trainee *trainee);
void printVocalInfo(Trainee trainees[], int num_trainees);
int compareStability(const void *a, const void *b);  // Comparison function for sorting

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Vocal Evaluation\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                evalVocal();
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

// Function to perform the vocal evaluation
void evalVocal() {
    Trainee trainees[MAX_TRAINEES];
    int num_trainees = 0;
    char cont;

    do {
        printf("\nEnter the trainee's name: ");
        scanf(" %[^\n]", trainees[num_trainees].name); // To allow spaces in name

        measure(&trainees[num_trainees]);

        provideFeedback(&trainees[num_trainees]);

        num_trainees++;

        if (num_trainees >= MAX_TRAINEES) {
            printf("Maximum number of trainees reached.\n");
            break;
        }

        printf("\nDo you want to evaluate another trainee? (y/n): ");
        scanf(" %c", &cont); // Space before %c to capture newline
    } while (cont == 'y' || cont == 'Y');

    printVocalInfo(trainees, num_trainees);
}

// Function to measure the vocal range and generate MIDI values
void measure(Trainee *trainee) {
    int num_notes;
    int highest_note;

    // Input vocal range
    printf("Enter the vocal range (MIDI value between 0 and 127): ");
    scanf("%d", &trainee->vocal_range);

    // Input the number of MIDI values to generate (between 5 and 12)
    do {
        printf("Enter the number of MIDI values (between 5 and 12): ");
        scanf("%d", &num_notes);
    } while (num_notes < 5 || num_notes > 12);

    // Generate random MIDI values within the range
    int midi_values[num_notes];
    srand(trainee->vocal_range);  // Seed the random number generator with the vocal range value
    highest_note = trainee->vocal_range;

    for (int i = 0; i < num_notes; i++) {
        int random_midi;
        do {
            random_midi = rand() % (highest_note + 1);  // Generate values between 0 and highest_note
        } while (i > 0 && random_midi == midi_values[i - 1]);  // Ensure no duplicate MIDI values
        midi_values[i] = random_midi;
    }

    // Calculate the stability of the vocal range
    trainee->vocal_stability = calculateStability(midi_values, num_notes);
}

// Function to calculate vocal stability
float calculateStability(int midi_values[], int num_notes) {
    int total_difference = 0;
    for (int i = 1; i < num_notes; i++) {
        total_difference += abs(midi_values[i] - midi_values[i - 1]);
    }
    return (float) total_difference / (num_notes - 1);
}

// Function to provide feedback based on stability
void provideFeedback(Trainee *trainee) {
    if (trainee->vocal_stability < 5) {
        strncpy(trainee->feedback, "Excellent stability", 51);
    } else if (trainee->vocal_stability < 10) {
        strncpy(trainee->feedback, "Good stability", 51);
    } else {
        strncpy(trainee->feedback, "Needs improvement", 51);
    }
}

// Function to print vocal info, sorted by stability
void printVocalInfo(Trainee trainees[], int num_trainees) {
    // Sort trainees by vocal stability (ascending)
    qsort(trainees, num_trainees, sizeof(Trainee), compareStability);

    printf("\nVocal Evaluation Results (Sorted by Vocal Stability):\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < num_trainees; i++) {
        printf("Name: %s\n", trainees[i].name);
        printf("Vocal Stability: %.2f\n", trainees[i].vocal_stability);
        printf("Feedback: %s\n", trainees[i].feedback);
        printf("-------------------------------------------------------\n");
    }
}
//hb inject
// Comparison function for sorting by stability (ascending order)
int compareStability(const void *a, const void *b) {
    Trainee *traineeA = (Trainee *)a;
    Trainee *traineeB = (Trainee *)b;
    if (traineeA->vocal_stability < traineeB->vocal_stability) {
        return -1;
    } else if (traineeA->vocal_stability > traineeB->vocal_stability) {
        return 1;
    } else {
        return 0;
    }
}

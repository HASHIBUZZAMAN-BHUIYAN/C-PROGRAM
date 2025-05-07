#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ATTEMPTS 3

// Structure to store sound information for the member
typedef struct {
    char name[MAX_NAME_LENGTH];
    char gender; // 'M' for Male, 'F' for Female
    float frequency; // Frequency in Hz
    float amplitude; // Amplitude in dB
    float voice_pulse; // Voice pulse in percentage
    int grbas_values[5]; // GRBAS scale values for voice tone
} VoiceData;

// Function prototypes
void findMyVoice();
void getMyVoiceFromHeaven(VoiceData *member);
float getRandomInRange(float min, float max);
void guessMyFreq(VoiceData *member);
void guessMyAmplitude(VoiceData *member);
void guessMyJitter(VoiceData *member);
void guessMyTone(VoiceData *member);
void printGRBAS(int grbas_values[5]);
void initGRBAS(int grbas_values[5]);

// Main function
int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Find My Voice\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                findMyVoice();
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

// Function to start the "Find My Voice" process
void findMyVoice() {
    VoiceData member;
    printf("\nEnter your nickname: ");
    scanf(" %[^\n]", member.name); // Allow spaces in nickname
    printf("Enter your gender (M for Male, F for Female): ");
    scanf(" %c", &member.gender); // Get gender (M or F)

    // Generate random values for frequency, amplitude, and jitter
    getMyVoiceFromHeaven(&member);

    // Start the up-and-down guessing game for frequency, amplitude, and jitter
    guessMyFreq(&member);
    guessMyAmplitude(&member);
    guessMyJitter(&member);

    // Bonus: Guess voice tone using GRBAS scale values
    guessMyTone(&member);
}

// Function to get random values for frequency, amplitude, and jitter based on gender
void getMyVoiceFromHeaven(VoiceData *member) {
    if (member->gender == 'M') {
        member->frequency = getRandomInRange(85.0, 180.0); // Male frequency range
        member->amplitude = getRandomInRange(2.5, 3.6); // Male amplitude range
        member->voice_pulse = getRandomInRange(0.2, 0.6); // Male jitter range
    } else if (member->gender == 'F') {
        member->frequency = getRandomInRange(165.0, 255.0); // Female frequency range
        member->amplitude = getRandomInRange(3.5, 4.7); // Female amplitude range
        member->voice_pulse = getRandomInRange(0.3, 1.0); // Female jitter range
    }

    printf("\nGenerated voice characteristics for %s:\n", member->name);
    printf("Frequency: %.2f Hz\n", member->frequency);
    printf("Amplitude: %.2f dB\n", member->amplitude);
    printf("Voice Pulse (Jitter): %.2f %%\n", member->voice_pulse);
}

// Function to generate a random value in a given range
float getRandomInRange(float min, float max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

// Function to guess the frequency
void guessMyFreq(VoiceData *member) {
    float guess;
    int attempts = 0;
    printf("\nGuess the frequency (in Hz) between %.2f and %.2f:\n", (member->gender == 'M' ? 85.0 : 165.0), (member->gender == 'M' ? 180.0 : 255.0));
    
    while (attempts < MAX_ATTEMPTS) {
        printf("Attempt %d: Enter your guess: ", attempts + 1);
        scanf("%f", &guess);

        if (guess == member->frequency) {
            printf("Congratulations! You found the correct frequency: %.2f Hz\n", member->frequency);
            return;
        } else if (guess < member->frequency) {
            printf("Try a higher frequency.\n");
        } else {
            printf("Try a lower frequency.\n");
        }
        attempts++;
    }
    printf("Sorry, you didn't find the correct frequency. The correct value was %.2f Hz.\n", member->frequency);
}

// Function to guess the amplitude
void guessMyAmplitude(VoiceData *member) {
    float guess;
    int attempts = 0;
    printf("\nGuess the amplitude (in dB) between %.2f and %.2f:\n", (member->gender == 'M' ? 2.5 : 3.5), (member->gender == 'M' ? 3.6 : 4.7));

    while (attempts < MAX_ATTEMPTS) {
        printf("Attempt %d: Enter your guess: ", attempts + 1);
        scanf("%f", &guess);

        if (guess == member->amplitude) {
            printf("Congratulations! You found the correct amplitude: %.2f dB\n", member->amplitude);
            return;
        } else if (guess < member->amplitude) {
            printf("Try a higher amplitude.\n");
        } else {
            printf("Try a lower amplitude.\n");
        }
        attempts++;
    }
    printf("Sorry, you didn't find the correct amplitude. The correct value was %.2f dB.\n", member->amplitude);
}

// Function to guess the voice pulse (jitter)
void guessMyJitter(VoiceData *member) {
    float guess;
    int attempts = 0;
    printf("\nGuess the voice pulse (Jitter) percentage between %.2f and %.2f:\n", (member->gender == 'M' ? 0.2 : 0.3), (member->gender == 'M' ? 0.6 : 1.0));

    while (attempts < MAX_ATTEMPTS) {
        printf("Attempt %d: Enter your guess: ", attempts + 1);
        scanf("%f", &guess);

        if (guess == member->voice_pulse) {
            printf("Congratulations! You found the correct voice pulse: %.2f %%\n", member->voice_pulse);
            return;
        } else if (guess < member->voice_pulse) {
            printf("Try a higher value.\n");
        } else {
            printf("Try a lower value.\n");
        }
        attempts++;
    }
    printf("Sorry, you didn't find the correct voice pulse. The correct value was %.2f %%.\n", member->voice_pulse);
}

// Function to guess the voice tone using the GRBAS scale
void guessMyTone(VoiceData *member) {
    int grbas_values[5];
    initGRBAS(grbas_values);

    int attempts = 0;
    printf("\nNow, let's guess your voice tone based on the GRBAS scale (0-3 for each value):\n");

    while (attempts < MAX_ATTEMPTS) {
        printf("Attempt %d:\n", attempts + 1);
        printf("Enter Grade (0-3): ");
        scanf("%d", &grbas_values[0]);
        printf("Enter Roughness (0-3): ");
        scanf("%d", &grbas_values[1]);
        printf("Enter Breathiness (0-3): ");
        scanf("%d", &grbas_values[2]);
        printf("Enter Asthenia (0-3): ");
        scanf("%d", &grbas_values[3]);
        printf("Enter Strain (0-3): ");
        scanf("%d", &grbas_values[4]);

        // Check if the guessed values match
        int correct = 1;
        for (int i = 0; i < 5; i++) {
            if (grbas_values[i] != member->grbas_values[i]) {
                correct = 0;
                break;
            }
        }

        if (correct) {
            printf("Congratulations! You guessed the correct voice tone values.\n");
            printGRBAS(grbas_values);
            return;
        } else {
            printf("Try again.\n");
        }
        attempts++;
    }

    printf("Sorry, you didn't guess the correct voice tone values.\n");
}
//hb inject
// Function to initialize GRBAS values for the member (randomly assigned)
void initGRBAS(int grbas_values[5]) {
    for (int i = 0; i < 5; i++) {
        grbas_values[i] = rand() % 4;  // Random values between 0 and 3
    }
}

// Function to print GRBAS scale values
void printGRBAS(int grbas_values[5]) {
    printf("Voice Tone (GRBAS scale):\n");
    printf("Grade: %d, Roughness: %d, Breathiness: %d, Asthenia: %d, Strain: %d\n",
           grbas_values[0], grbas_values[1], grbas_values[2], grbas_values[3], grbas_values[4]);
}

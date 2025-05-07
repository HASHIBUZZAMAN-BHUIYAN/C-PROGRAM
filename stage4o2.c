#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOTE_LENGTH 2
#define MAX_CHORD_SIZE 3

// Enum for note values
typedef enum { A = 0, B, C, D, E, F, G } Note;

// Structure to represent a musical note
typedef struct {
    Note note;
    int octave;
} MusicalNote;

// Structure to represent a chord, which consists of 3 notes
typedef struct {
    MusicalNote notes[MAX_CHORD_SIZE];
} Chord;

// Function prototypes
void learnMusicTheory();
void inputChord(Chord *chord);
int isValidChord(Chord *chord);
void printChord(Chord *chord);
int checkHarmony(Chord *chord);
int noteToIndex(char note);
const char* noteToString(Note note);

// Main function
int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Learn Music Theory\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                learnMusicTheory();
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

// Function to handle the music theory learning process
void learnMusicTheory() {
    Chord chord;
    inputChord(&chord);  // Input the chord
    if (isValidChord(&chord)) {
        printChord(&chord);
        int harmony = checkHarmony(&chord);
        if (harmony) {
            printf("The chord is harmonious.\n");
        } else {
            printf("The chord is not harmonious.\n");
        }
    } else {
        printf("Invalid chord!\n");
    }
}

// Function to input the chord (root, third, fifth)
void inputChord(Chord *chord) {
    char note[MAX_NOTE_LENGTH];
    int octave;
    for (int i = 0; i < MAX_CHORD_SIZE; i++) {
        printf("Enter note %d (A-G): ", i + 1);
        scanf("%s", note);
        printf("Enter octave (1-8): ");
        scanf("%d", &octave);

        chord->notes[i].note = noteToIndex(note[0]);
        chord->notes[i].octave = octave;
    }
}

// Function to check if the chord is valid
int isValidChord(Chord *chord) {
    // Check if all notes are in the same octave
    for (int i = 1; i < MAX_CHORD_SIZE; i++) {
        if (chord->notes[i].octave != chord->notes[0].octave) {
            return 0;  // Invalid if notes are not in the same octave
        }
    }

    // Check for duplicate notes
    for (int i = 0; i < MAX_CHORD_SIZE; i++) {
        for (int j = i + 1; j < MAX_CHORD_SIZE; j++) {
            if (chord->notes[i].note == chord->notes[j].note) {
                return 0;  // Invalid if there are duplicate notes
            }
        }
    }

    return 1;  // Valid chord if no issues found
}

// Function to print the chord notes
void printChord(Chord *chord) {
    printf("\nChord Information:\n");
    for (int i = 0; i < MAX_CHORD_SIZE; i++) {
        printf("Note %d: %s%d\n", i + 1, noteToString(chord->notes[i].note), chord->notes[i].octave);
    }
}

// Function to check the harmony of the chord
int checkHarmony(Chord *chord) {
    // Calculate intervals (in semitones) between the notes (root, third, fifth)
    int intervals[MAX_CHORD_SIZE - 1];
    intervals[0] = (chord->notes[1].note - chord->notes[0].note + 7) % 7;  // Interval between root and third
    intervals[1] = (chord->notes[2].note - chord->notes[0].note + 7) % 7;  // Interval between root and fifth

    // Check if intervals are harmonious
    if ((intervals[0] == 4 && intervals[1] == 7) ||  // Major chord (Root -> 4 semitones -> Third, Root -> 7 semitones -> Fifth)
        (intervals[0] == 3 && intervals[1] == 7)) {  // Minor chord (Root -> 3 semitones -> Third, Root -> 7 semitones -> Fifth)
        return 1;  // Harmonious chord
    }

    return 0;  // Not harmonious chord
}

// Function to convert a note character to its corresponding index (A-G)
int noteToIndex(char note) {
    switch (note) {
        case 'A': return A;
        case 'B': return B;
        case 'C': return C;
        case 'D': return D;
        case 'E': return E;
        case 'F': return F;
        case 'G': return G;
        default: return -1;  // Invalid note
    }
}
//hb inject
// Function to convert note index to string representation
const char* noteToString(Note note) {
    switch (note) {
        case A: return "A";
        case B: return "B";
        case C: return "C";
        case D: return "D";
        case E: return "E";
        case F: return "F";
        case G: return "G";
        default: return "Invalid";
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_FANS 1000
#define SEAT_COUNT 42
#define ROWS 6
#define COLS 7

// Structure to represent a seat
typedef struct Seat {
    int seatNumber;
    char fanID[5];  // String to store fan ID, e.g., "0001"
    struct Seat *next;
} Seat;

// Function to create a new seat node
Seat* createSeat(int seatNumber, const char *fanID) {
    Seat *newSeat = (Seat *)malloc(sizeof(Seat));
    newSeat->seatNumber = seatNumber;
    snprintf(newSeat->fanID, sizeof(newSeat->fanID), "%s", fanID);
    newSeat->next = NULL;
    return newSeat;
}

// Function to add a seat to the linked list
void addSeat(Seat **head, int seatNumber, const char *fanID) {
    Seat *newSeat = createSeat(seatNumber, fanID);
    newSeat->next = *head;
    *head = newSeat;
}

// Function to print the seating arrangement
void printSeating(Seat *head) {
    Seat *current = head;
    int row = 1, col = 1;

    while (current) {
        printf("Seat %2d (%s) ", current->seatNumber, current->fanID);
        col++;
        if (col > COLS) {
            col = 1;
            row++;
            printf("\n");
        }
        current = current->next;
    }
    printf("\n");
}

// Function to randomly select 38 fans from the pool of fans
void randomSelection(int *fanIDs, int totalFans, int *selectedFans, int numSelect) {
    for (int i = 0; i < numSelect; i++) {
        int randIndex = rand() % totalFans;
        selectedFans[i] = fanIDs[randIndex];
        // Mark the selected fan ID as used by setting it to -1
        fanIDs[randIndex] = -1;
    }
}

// Function to open the demo concert and assign seats
void openDemoConcert(int numOrganizers) {
    // Initialize random seed
    srand(time(NULL));

    // Array to represent the pool of fan IDs
    int fanIDs[MAX_FANS];
    for (int i = 0; i < MAX_FANS; i++) {
        fanIDs[i] = i + 1;
    }

    // List to hold the seat assignments
    Seat *seatList = NULL;

    // Assign the 4 organizers to the first 4 seats
    for (int i = 0; i < numOrganizers; i++) {
        char fanID[5];
        snprintf(fanID, sizeof(fanID), "%04d", i + 1);
        addSeat(&seatList, i + 1, fanID);
    }

    // Randomly select 38 fans from the remaining 996 fans
    int selectedFans[38];
    randomSelection(fanIDs + 4, MAX_FANS - 4, selectedFans, 38);

    // Assign the selected fans to the hb remaining 38 seats (5 to 42)
    for (int i = 0; i < 38; i++) {
        char fanID[5];
        snprintf(fanID, sizeof(fanID), "%04d", selectedFans[i]);
        addSeat(&seatList, i + 5, fanID);
    }

    // Print the seating chart
    printf("Seating arrangement (6x7 format):\n");
    printSeating(seatList);
}

// Main function
int main() {
    int numOrganizers;
    printf("Enter the number of organizers (1-10): ");
    scanf("%d", &numOrganizers);

    // Ensure the number of organizers is between 1 and 10
    assert(numOrganizers >= 1 && numOrganizers <= 10);

    openDemoConcert(numOrganizers);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

// Structure to represent fan psychology data in the queue (or stack)
typedef struct FanPsychology {
    int priority;                  // Priority of the psychology
    char description[MAX_LENGTH];  // Description of the psychology
    struct FanPsychology *next;    // Pointer to the next element (for queue/stack)
} FanPsychology;

// Function prototypes
void analyzFanPsychology();
void LoadFanPsychologyData(const char *filename, FanPsychology **head);
void PrintFanPsychology(FanPsychology *head);
void InsertIntoQueue(FanPsychology **head, int priority, const char *description);
void SavePsychologyReport(FanPsychology *head, const char *filename);
void freeFanPsychologyList(FanPsychology *head);
void InsertIntoStack(FanPsychology **head, int priority, const char *description);

// Main function to handle the fan psychology analysis menu
void analyzFanPsychology() {
    FanPsychology *psychologyQueue = NULL;

    // Load fan psychology data from the file
    LoadFanPsychologyData("psychology.txt", &psychologyQueue);

    // Print all available fan psychology data
    PrintFanPsychology(psychologyQueue);

    // Ask for the priority and description for fan psychology data to be added to the queue
    int priority;
    char description[MAX_LENGTH];
    
    printf("Enter priority (1: Highest, 6: Lowest) and description for fan psychology data:\n");
    printf("Priority: ");
    scanf("%d", &priority);
    getchar();  // To consume the newline character after the number input
    printf("Description: ");
    fgets(description, MAX_LENGTH, stdin);
    description[strcspn(description, "\n")] = '\0';  // Remove newline character

    // Insert into queue (or stack for bonus)
    InsertIntoQueue(&psychologyQueue, priority, description);

    // Save the psychology report to a file
    SavePsychologyReport(psychologyQueue, "fan_psychology_report.txt");

    // Print the saved report (for confirmation)
    printf("\nPsychology Report:\n");
    PrintFanPsychology(psychologyQueue);

    // Free the memory allocated for the list
    freeFanPsychologyList(psychologyQueue);
}

// Function to load fan psychology data from a file into the queue
void LoadFanPsychologyData(const char *filename, FanPsychology **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file %s\n", filename);
        return;
    }

    int priority;
    char description[MAX_LENGTH];
    while (fscanf(file, "%d\n", &priority) == 1) {
        fgets(description, MAX_LENGTH, file);
        description[strcspn(description, "\n")] = '\0'; // Remove newline character

        InsertIntoQueue(head, priority, description);
    }

    fclose(file);
}

// Function to insert a new fan psychology data into the queue based on priority
void InsertIntoQueue(FanPsychology **head, int priority, const char *description) {
    FanPsychology *newNode = (FanPsychology *)malloc(sizeof(FanPsychology));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->priority = priority;
    strncpy(newNode->description, description, MAX_LENGTH);
    newNode->next = NULL;

    // If the queue is empty, the new node becomes the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Insert at the correct position based on priority
        FanPsychology *current = *head;
        FanPsychology *prev = NULL;
        
        while (current != NULL && current->priority <= priority) {
            prev = current;
            current = current->next;
        }
        
        if (prev == NULL) {
            // Insert at the beginning
            newNode->next = *head;
            *head = newNode;
        } else {
            // Insert after the previous node
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

// Function to print the fan psychology data in the queue
void PrintFanPsychology(FanPsychology *head) {
    FanPsychology *current = head;
    while (current != NULL) {
        printf("Priority: %d\n", current->priority);
        printf("Description: %s\n", current->description);
        printf("---------------------\n");
        current = current->next;
    }
}

// Function to save the fan psychology report to a file
void SavePsychologyReport(FanPsychology *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file %s\n", filename);
        return;
    }

    FanPsychology *current = head;
    while (current != NULL) {
        fprintf(file, "Priority: %d\n", current->priority);
        fprintf(file, "Description: %s\n", current->description);
        fprintf(file, "---------------------\n");
        current = current->next;
    }

    fclose(file);
}
//hb inject
// Function to free the memory allocated for the fan psychology list
void freeFanPsychologyList(FanPsychology *head) {
    FanPsychology *current = head;
    while (current != NULL) {
        FanPsychology *next = current->next;
        free(current);
        current = next;
    }
}

// Bonus function to insert into the stack (for demonstration purposes)
void InsertIntoStack(FanPsychology **head, int priority, const char *description) {
    FanPsychology *newNode = (FanPsychology *)malloc(sizeof(FanPsychology));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->priority = priority;
    strncpy(newNode->description, description, MAX_LENGTH);
    newNode->next = *head;
    *head = newNode;
}

// Main entry point
int main() {
    analyzFanPsychology();
    return 0;
}

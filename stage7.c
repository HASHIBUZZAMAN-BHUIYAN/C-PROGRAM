#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

// Subject structure to store the name, details, and next subject
typedef struct Subject {
    char name[50];
    char details[MAX_LENGTH];
    struct Subject *next;
} Subject;

// Function prototypes
void learnPerformanceStageTheory();
void LoadContentFile(const char *filename, Subject **head);
void UpdateSubjectInfo(Subject *head, const char *subjectName, const char *details);
void PrintSubjectList(Subject *head);
void insertSubject(Subject **head, const char *subjectName, const char *details);
void removeSubject(Subject **head, const char *subjectName);
void freeSubjectList(Subject *head);

// Main learning theory function (called when menu is selected)
void learnPerformanceStageTheory() {
    Subject *head = NULL;
    
    // Load content from the file
    LoadContentFile("perform_stage.txt", &head);

    // Print the subject list with details
    PrintSubjectList(head);

    // Free the linked list memory
    freeSubjectList(head);
}

// Function to load content from file into linked list
void LoadContentFile(const char *filename, Subject **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file %s\n", filename);
        return;
    }

    char line[MAX_LENGTH];
    const char *subjects[] = {
        "Acting Theory", "Stage Theory", "Script Analysis", "Dialogue Interpretation and Emotional Expression",
        "Character Development", "Storytelling Theory", "Stage Movement and Poses"
    };
    int subjectIndex = 0;

    // Reading the file and updating subject details
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from line if present
        line[strcspn(line, "\n")] = '\0';

        // Update the subject details in the linked list
        if (subjectIndex < 7) {
            UpdateSubjectInfo(*head, subjects[subjectIndex], line);
            subjectIndex++;
        }
    }

    fclose(file);
}

// Function to update a subject's details in the linked list
void UpdateSubjectInfo(Subject *head, const char *subjectName, const char *details) {
    Subject *current = head;
    
    // Find the subject by name
    while (current != NULL) {
        if (strcmp(current->name, subjectName) == 0) {
            // Update the details of the subject
            strncpy(current->details, details, MAX_LENGTH);
            return;
        }
        current = current->next;
    }

    // If subject not found, insert a new subject
    insertSubject(&head, subjectName, details);
}

// Function to insert a new subject into the linked list
void insertSubject(Subject **head, const char *subjectName, const char *details) {
    Subject *newSubject = (Subject *)malloc(sizeof(Subject));
    if (newSubject == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Set subject details
    strncpy(newSubject->name, subjectName, sizeof(newSubject->name));
    strncpy(newSubject->details, details, MAX_LENGTH);
    newSubject->next = NULL;

    // Insert the new subject at the beginning of the list
    if (*head == NULL) {
        *head = newSubject;
    } else {
        newSubject->next = *head;
        *head = newSubject;
    }
}

// Function to remove a subject from the linked list
void removeSubject(Subject **head, const char *subjectName) {
    Subject *current = *head;
    Subject *previous = NULL;

    // Find the subject to remove
    while (current != NULL) {
        if (strcmp(current->name, subjectName) == 0) {
            if (previous == NULL) {
                // Removing the first subject in the list
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Subject '%s' not found!\n", subjectName);
}

// Function to print the subject list
void PrintSubjectList(Subject *head) {
    Subject *current = head;
    
    while (current != NULL) {
        printf("Subject: %s\n", current->name);
        int len = strlen(current->details);
        
        // Print the details of the subject with a line break after a period
        for (int i = 0; i < len; i++) {
            putchar(current->details[i]);
            if (current->details[i] == '.') {
                putchar('\n');
            }
        }
        printf("\n");

        current = current->next;
    }
}
//hb inject
// Function to free the memory allocated for the linked list
void freeSubjectList(Subject *head) {
    Subject *current = head;
    while (current != NULL) {
        Subject *next = current->next;
        free(current);
        current = next;
    }
}

// Main entry point for the program
int main() {
    learnPerformanceStageTheory();
    return 0;
}

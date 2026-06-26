#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 100
#define NUM_CHARACTER_TYPES 8
#define MAX_NAME_LENGTH 50

// Structure to represent character types
typedef struct CharacterType {
    char name[MAX_NAME_LENGTH];
    int percentage;
    struct CharacterType *next;
    struct CharacterType *prev;
} CharacterType;

// Function prototypes
void studyMyCharacter();
void LoadCharacterTypes(const char *filename, CharacterType **head);
void PrintCharacterTypes(CharacterType *head);
void RemoveNegativeCharacterType(CharacterType **head);
void ReplaceNegativeCharacterType(CharacterType **head);
void InsertCharacterTypeInOrder(CharacterType **head, const char *name, int percentage);
void freeCharacterList(CharacterType *head);

// Main function to handle the character analysis menu
void studyMyCharacter() {
    CharacterType *characterList = NULL;
    LoadCharacterTypes("character.txt", &characterList);
    
    // Randomly select 4 character types and assign random percentages
    srand(time(NULL));  // Seed for randomness
    int totalPercentage = 0;
    int percentages[4];
    char *selectedTypes[4];
    
    // Randomly select 4 unique character types
    for (int i = 0; i < 4; i++) {
        int index = rand() % NUM_CHARACTER_TYPES;
        selectedTypes[i] = malloc(MAX_NAME_LENGTH * sizeof(char));
        // Assuming a predefined list of character types from character.txt
        const char *characterNames[NUM_CHARACTER_TYPES] = {
            "Hero", "Villain", "Psychopath", "Sidekick", "Leader", "Follower", "Rebel", "Mystic"
        };
        
        strcpy(selectedTypes[i], characterNames[index]);
        
        // Assign random percentages ensuring total equals 100
        percentages[i] = rand() % (101 - totalPercentage);  // Random percentage
        totalPercentage += percentages[i];
        
        // Insert in the list
        InsertCharacterTypeInOrder(&characterList, selectedTypes[i], percentages[i]);
    }
    
    // Print the final character analysis
    PrintCharacterTypes(characterList);
    
    // Remove negative characters (villain, psychopath)
    RemoveNegativeCharacterType(&characterList);
    printf("After removing negative character types:\n");
    PrintCharacterTypes(characterList);
    
    // Bonus: Replace removed negative character with a positive character
    ReplaceNegativeCharacterType(&characterList);
    printf("After replacing negative character types with positive characters:\n");
    PrintCharacterTypes(characterList);
    
    // Free the dynamically allocated memory
    freeCharacterList(characterList);
}

// Function to load character types from a file
void LoadCharacterTypes(const char *filename, CharacterType **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }
    
    char name[MAX_NAME_LENGTH];
    while (fscanf(file, "%s", name) != EOF) {
        // For now, just print the character names
        printf("Loaded character: %s\n", name);
    }
    
    fclose(file);
}

// Function to print all the character types in the linked list
void PrintCharacterTypes(CharacterType *head) {
    CharacterType *current = head;
    while (current != NULL) {
        printf("Character: %s, Percentage: %d\n", current->name, current->percentage);
        current = current->next;
    }
}

// Function to insert a character type into the list, ordered by percentage
void InsertCharacterTypeInOrder(CharacterType **head, const char *name, int percentage) {
    CharacterType *newNode = (CharacterType *)malloc(sizeof(CharacterType));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    strcpy(newNode->name, name);
    newNode->percentage = percentage;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (*head == NULL) {
        *head = newNode;
    } else {
        CharacterType *current = *head;
        while (current != NULL && current->percentage >= percentage) {
            current = current->next;
        }
        
        if (current == NULL) {
            // Insert at the end
            CharacterType *tail = *head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->prev = tail;
        } else if (current == *head) {
            // Insert at the beginning
            newNode->next = *head;
            (*head)->prev = newNode;
            *head = newNode;
        } else {
            // Insert in the middle
            current->prev->next = newNode;
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev = newNode;
        }
    }
}

// Function to remove negative character types (Villain or Psychopath)
void RemoveNegativeCharacterType(CharacterType **head) {
    CharacterType *current = *head;
    
    while (current != NULL) {
        if (strcmp(current->name, "Villain") == 0 || strcmp(current->name, "Psychopath") == 0) {
            // Remove current node
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *head = current->next;
            }
            
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            
            free(current);
            current = current->next;
        } else {
            current = current->next;
        }
    }
}

// Bonus function to replace negative character types with positive ones
void ReplaceNegativeCharacterType(CharacterType **head) {
    CharacterType *current = *head;
    //hb inject
    while (current != NULL) {
        if (strcmp(current->name, "Villain") == 0 || strcmp(current->name, "Psychopath") == 0) {
            // Replace with a new positive character
            if (strcmp(current->name, "Villain") == 0) {
                strcpy(current->name, "Hero");
            } else {
                strcpy(current->name, "Leader");
            }
            current->percentage = 25;  // Assign a new percentage for the replacement character
        }
        current = current->next;
    }
}

// Function to free the dynamically allocated memory for the character list
void freeCharacterList(CharacterType *head) {
    CharacterType *current = head;
    while (current != NULL) {
        CharacterType *next = current->next;
        free(current);
        current = next;
    }
}

// Main entry point
int main() {
    studyMyCharacter();
    return 0;
}

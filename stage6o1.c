#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CONCEPTS 100
#define MAX_GROUP_NAME_LENGTH 100
#define MAX_CONCEPT_LENGTH 100
#define MAX_DESCRIPTION_LENGTH 200

// Concept data structure to hold the group name, concept, and description
typedef struct {
    char group_name[MAX_GROUP_NAME_LENGTH];
    char concept[MAX_CONCEPT_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} ConceptData;

// Queue structure for matching
typedef struct QueueNode {
    ConceptData data;
    struct QueueNode* next;
} QueueNode;

// Stack structure for matching (bonus)
typedef struct StackNode {
    ConceptData data;
    struct StackNode* next;
} StackNode;

// Concept data and total count
ConceptData concepts[MAX_CONCEPTS];
int totalConcepts = 0;

// Global queues for group and concept
QueueNode* groupQueue = NULL;
QueueNode* conceptQueue = NULL;

// Function to load concept data from a file
void loadConceptData(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    while (fscanf(file, "%99[^\n] %99[^\n] %199[^\n]\n", concepts[totalConcepts].group_name, 
                concepts[totalConcepts].concept, concepts[totalConcepts].description) != EOF) {
        totalConcepts++;
        if (totalConcepts >= MAX_CONCEPTS) break; // Prevent overflow
    }
    fclose(file);
}

// Function to shuffle concepts (Fisher-Yates shuffle)
void shuffleConcepts(ConceptData *data, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        ConceptData temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}

// Function to create a new queue node
QueueNode* createQueueNode(ConceptData data) {
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to enqueue an item
void enqueue(QueueNode **head, ConceptData data) {
    QueueNode *node = createQueueNode(data);
    if (*head == NULL) {
        *head = node;
    } else {
        QueueNode *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

// Function to dequeue an item
ConceptData dequeue(QueueNode **head) {
    if (*head == NULL) {
        printf("Queue is empty!\n");
        exit(1);
    }
    QueueNode *temp = *head;
    ConceptData data = temp->data;
    *head = (*head)->next;
    free(temp);
    return data;
}

// Function to create a new stack node
StackNode* createStackNode(ConceptData data) {
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to push an item onto the stack
void push(StackNode **top, ConceptData data) {
    StackNode *node = createStackNode(data);
    node->next = *top;
    *top = node;
}

// Function to pop an item from the stack
ConceptData pop(StackNode **top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        exit(1);
    }
    StackNode *temp = *top;
    ConceptData data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

// Function to display the concept data
void displayConcepts() {
    printf("\n## Mismatched Group and Concept ##\n");
    printf("Group Queue: Concept Queue\n");
    printf("--------------------\n");

    QueueNode *groupTemp = groupQueue;
    QueueNode *conceptTemp = conceptQueue;

    while (groupTemp != NULL && conceptTemp != NULL) {
        printf("%s: %s\n", groupTemp->data.group_name, conceptTemp->data.concept);
        groupTemp = groupTemp->next;
        conceptTemp = conceptTemp->next;
    }
}

// Function to allow user to match group and concept
void matchConcepts() {
    int correct = 0, incorrect = 0;
    QueueNode *groupTemp = groupQueue;
    QueueNode *conceptTemp = conceptQueue;

    while (groupTemp != NULL && conceptTemp != NULL) {
        char match[MAX_CONCEPT_LENGTH];
        printf("Match the group %s with the concept: ", groupTemp->data.group_name);
        fgets(match, MAX_CONCEPT_LENGTH, stdin);
        match[strcspn(match, "\n")] = 0; // Remove newline

        if (strcmp(match, conceptTemp->data.concept) == 0) {
            printf("Correct!\n");
            correct++;
        } else {
            printf("Incorrect. The correct answer is: %s\n", conceptTemp->data.concept);
            incorrect++;
        }

        groupTemp = groupTemp->next;
        conceptTemp = conceptTemp->next;
    }

    printf("\nTime taken: [Stubbed Timer]\n");
    printf("Correct matches: %d\n", correct);
    printf("Incorrect matches: %d\n", incorrect);
}

// Main function to define the concept research functionality
void defineConcept() {
    char filename[] = "concept.txt";
    loadConceptData(filename);

    int dataSets;
    printf("Enter number of data sets to extract (max %d): ", totalConcepts);
    scanf("%d", &dataSets);
    getchar(); // Consume newline

    if (dataSets > totalConcepts) {
        printf("Warning: Not enough data available. Using maximum available data.\n");
        dataSets = totalConcepts;
    }

    // Randomly shuffle selected concept data
    shuffleConcepts(concepts, totalConcepts);

    // Extract the specified number of data sets and add them to the queues
    for (int i = 0; i < dataSets; i++) {
        enqueue(&groupQueue, concepts[i]);
        enqueue(&conceptQueue, concepts[i]);
    }
//hb inject
    // Shuffle again for mismatching
    shuffleConcepts(concepts, dataSets);

    printf("## Mismatched Group and Concept ##\n");
    displayConcepts();

    // Allow user to match the group and concept
    matchConcepts();
}

// Main menu system to handle queue or stack selection
void menu() {
    int choice;
    while (1) {
        printf("\n[Menu]\n");
        printf("1. Concept Research\n");
        printf("2. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character

        switch (choice) {
            case 1:
                defineConcept();
                break;
            case 2:
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}

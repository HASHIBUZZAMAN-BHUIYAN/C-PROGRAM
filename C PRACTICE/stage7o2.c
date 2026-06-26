#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

// Structure to represent a facial expression node in the doubly linked list
typedef struct Expression {
    char name[MAX_LENGTH];         // Expression name
    char description[MAX_LENGTH];  // Expression description
    struct Expression *next;       // Pointer to next expression
    struct Expression *prev;       // Pointer to previous expression
} Expression;

// Function prototypes
void haveALook();
void LoadExpressionsFromFile(const char *filename, Expression **head);
void PrintExpressions(Expression *head);
void SearchExpression(Expression *head, const char *keyword);
void SwapAdjacentExpressions(Expression *head, int position);
void freeExpressionList(Expression *head);

// Main function to handle the facial expression menu
void haveALook() {
    Expression *expressionList = NULL;

    // Load expressions from the file
    LoadExpressionsFromFile("look.txt", &expressionList);

    // Print all expressions
    PrintExpressions(expressionList);

    // Search for an expression by a keyword
    char keyword[MAX_LENGTH];
    printf("Enter a keyword to search for in expressions: ");
    scanf("%s", keyword);
    SearchExpression(expressionList, keyword);

    // Swap two adjacent expressions and print the result
    int position;
    printf("Enter the position of the expression to swap with the next one: ");
    scanf("%d", &position);
    SwapAdjacentExpressions(expressionList, position);

    // Print all expressions after swapping
    PrintExpressions(expressionList);

    // Free the memory allocated for the list
    freeExpressionList(expressionList);
}

// Function to load expressions from a file into the doubly linked list
void LoadExpressionsFromFile(const char *filename, Expression **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file %s\n", filename);
        return;
    }

    char name[MAX_LENGTH], description[MAX_LENGTH];
    while (fscanf(file, "%[^\n]\n%[^\n]\n", name, description) == 2) {
        Expression *newExpression = (Expression *)malloc(sizeof(Expression));
        if (newExpression == NULL) {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        // Initialize new expression node
        strncpy(newExpression->name, name, MAX_LENGTH);
        strncpy(newExpression->description, description, MAX_LENGTH);
        newExpression->next = NULL;
        newExpression->prev = NULL;

        // Insert into the doubly linked list
        if (*head == NULL) {
            *head = newExpression;
        } else {
            Expression *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newExpression;
            newExpression->prev = current;
        }
    }

    fclose(file);
}

// Function to print all expressions in the list
void PrintExpressions(Expression *head) {
    Expression *current = head;
    while (current != NULL) {
        printf("Expression: %s\n", current->name);
        printf("Description: %s\n", current->description);
        printf("---------------------\n");
        current = current->next;
    }
}

// Function to search for an expression by a keyword in the description
void SearchExpression(Expression *head, const char *keyword) {
    Expression *current = head;
    while (current != NULL) {
        if (strstr(current->description, keyword) != NULL) {
            printf("Found expression with keyword \"%s\":\n", keyword);
            printf("Expression: %s\n", current->name);
            printf("Description: %s\n", current->description);
            printf("---------------------\n");
        }
        current = current->next;
    }
}

// Function to swap two adjacent expressions in the list
void SwapAdjacentExpressions(Expression *head, int position) {
    if (position < 1) {
        printf("Invalid position.\n");
        return;
    }

    Expression *current = head;
    int count = 1;
    while (current != NULL && count < position) {
        current = current->next;
        count++;
    }

    if (current == NULL || current->next == NULL) {
        printf("Cannot swap, invalid position or no adjacent node to swap.\n");
        return;
    }

    // Swap current node with the next node
    Expression *nextNode = current->next;
    Expression *prevNode = current->prev;
    Expression *nextNextNode = nextNode->next;

    // Adjust the pointers for the nodes
    if (prevNode != NULL) {
        prevNode->next = nextNode;
    } else {
        head = nextNode; // head changes if the first node is swapped
    }

    nextNode->prev = prevNode;
    nextNode->next = current;
    current->prev = nextNode;
    current->next = nextNextNode;

    if (nextNextNode != NULL) {
        nextNextNode->prev = current;
    }
//hb inject
    // Print the result of the swap
    printf("Swapped nodes at position %d and %d.\n", position, position + 1);
}

// Function to free the memory allocated for the linked list
void freeExpressionList(Expression *head) {
    Expression *current = head;
    while (current != NULL) {
        Expression *next = current->next;
        free(current);
        current = next;
    }
}

// Main entry point
int main() {
    haveALook();
    return 0;
}

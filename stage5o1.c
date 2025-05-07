#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATTERNS 6
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_NAME_LENGTH 100
#define MAX_SONGS 4
#define MAX_PATTERN_NAME_LENGTH 100
#define MAX_TREE_NODES 20

// Choreography pattern structure
typedef struct {
    char name[MAX_PATTERN_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} ChoreographyPattern;

// Tree node for storing choreography patterns in songs
typedef struct TreeNode {
    ChoreographyPattern pattern;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Global choreography patterns array
ChoreographyPattern patterns[MAX_PATTERNS]; // Choreography patterns

// Sample K-POP song choreography analysis tree
TreeNode* songTrees[MAX_SONGS]; // Stores tree roots for 4 songs

// Function to read the choreography pattern file
int readDancePatterns() {
    FILE *file = fopen("dance_pattern.txt", "r");
    if (file == NULL) {
        printf("Error opening dance pattern file!\n");
        return -1;
    }

    for (int i = 0; i < MAX_PATTERNS; i++) {
        fscanf(file, "%s", patterns[i].name);
        getchar(); // Consume newline after pattern name
        fgets(patterns[i].description, MAX_DESCRIPTION_LENGTH, file);
        patterns[i].description[strcspn(patterns[i].description, "\n")] = 0; // Remove newline at end
    }

    fclose(file);
    return 0;
}

// Function to read the choreography analysis report file and build the tree
int readAnalysisReport() {
    FILE *file = fopen("analyz_dance-pattern.csv", "r");
    if (file == NULL) {
        printf("Error opening analysis report file!\n");
        return -1;
    }

    // Example: Here we are assuming CSV file has the format:
    // song_name, pattern1, pattern2, ..., patternN
    char songName[MAX_NAME_LENGTH];
    char patternName[MAX_PATTERN_NAME_LENGTH];

    for (int i = 0; i < MAX_SONGS; i++) {
        songTrees[i] = NULL; // Initialize each tree to NULL

        // Read song name
        fscanf(file, "%s", songName);
        getchar(); // Consume newline

        // Build tree for each song
        while (fscanf(file, "%s", patternName) != EOF && patternName[0] != ',') {
            // Add each pattern to the song's tree (left-right)
            TreeNode* newNode = malloc(sizeof(TreeNode));
            for (int j = 0; j < MAX_PATTERNS; j++) {
                if (strcmp(patterns[j].name, patternName) == 0) {
                    newNode->pattern = patterns[j];
                    break;
                }
            }
            newNode->left = NULL;
            newNode->right = NULL;

            // Insert into the tree (simple left-right insert for now)
            if (songTrees[i] == NULL) {
                songTrees[i] = newNode;
            } else {
                TreeNode *current = songTrees[i];
                while (current->left != NULL) {
                    current = current->left;
                }
                current->left = newNode;
            }
        }
    }

    fclose(file);
    return 0;
}

// Function to shuffle and select a random description for quiz
int selectRandomPatternDescription(char *selectedDescription) {
    srand(time(NULL));
    int index = rand() % MAX_PATTERNS;
    strcpy(selectedDescription, patterns[index].description);
    return index; // Return the index of the selected pattern
}

// Function to verify user input pattern name
int verifyPatternName(int patternIndex, char *inputName) {
    return strcmp(patterns[patternIndex].name, inputName) == 0;
}

// Function to traverse the song choreography tree and print patterns
void printSongPatterns(TreeNode *root) {
    if (root != NULL) {
        printf("%s: %s\n", root->pattern.name, root->pattern.description);
        printSongPatterns(root->left);
        printSongPatterns(root->right);
    }
}

// Function for learning choreography patterns
void learnDancePattern() {
    int correctAnswers = 0;

    // Generate 4 random problems
    for (int i = 0; i < 4; i++) {
        char description[MAX_DESCRIPTION_LENGTH];
        int correctPatternIndex = selectRandomPatternDescription(description);

        printf("Description: %s\n", description);
        printf("Enter the pattern name: ");
        char userPatternName[MAX_PATTERN_NAME_LENGTH];
        fgets(userPatternName, MAX_PATTERN_NAME_LENGTH, stdin);
        userPatternName[strcspn(userPatternName, "\n")] = 0; // Remove newline

        if (verifyPatternName(correctPatternIndex, userPatternName)) {
            printf("Correct!\n");
            correctAnswers++;
        } else {
            printf("Incorrect. The correct answer was: %s\n", patterns[correctPatternIndex].name);
        }

        // Exit early if fewer than 3 correct answers
        if (correctAnswers < 3) {
            printf("You failed to answer 3 questions correctly. Exiting...\n");
            return;
        }
    }

    // After 3 or more correct answers, proceed to read the analysis report and build the song trees
    if (readAnalysisReport() == 0) {
        // Display song patterns for each song
        printf("Song Choreography Patterns:\n");
        for (int i = 0; i < MAX_SONGS; i++) {
            printf("Song %d:\n", i + 1);
            printSongPatterns(songTrees[i]);
        }

        // Bonus: Handle user interaction with song patterns
        int songSelection;
        printf("Select a song (1-4): ");
        scanf("%d", &songSelection);
        getchar(); // Consume newline

        if (songSelection >= 1 && songSelection <= 4) {
            TreeNode *songTree = songTrees[songSelection - 1];
            TreeNode *current = songTree;
            while (current != NULL) {
                printf("Next pattern: %s\n", current->pattern.name);
                printf("Your answer: ");
                char userPatternName[MAX_PATTERN_NAME_LENGTH];
                fgets(userPatternName, MAX_PATTERN_NAME_LENGTH, stdin);
                userPatternName[strcspn(userPatternName, "\n")] = 0; // Remove newline

                if (verifyPatternName(0, userPatternName)) { // Here you should compare with the current pattern
                    printf("Correct! Proceeding to the next pattern.\n");
                    current = current->left; // Move to the next pattern (left node in this simple tree)
                } else {
                    printf("Incorrect. Exiting...\n");
                    return;
                }
            }

            printf("Congratulations! You've completed the choreography pattern sequence!\n");
        }
    }
}

int main() {
    // Load choreography patterns from file
    if (readDancePatterns() != 0) {
        return -1; // Error loading patterns
    }
//hb inject
    // Run the learnDancePattern function
    learnDancePattern();

    return 0;
}

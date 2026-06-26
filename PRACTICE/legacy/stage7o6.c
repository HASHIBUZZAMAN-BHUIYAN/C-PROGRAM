#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_POSE_NAME_LENGTH 50
#define MAX_POSE_DESC_LENGTH 200
#define MAX_POSES 5

// Pose structure to hold the name and description of each pose
typedef struct Pose {
    char name[MAX_POSE_NAME_LENGTH];
    char description[MAX_POSE_DESC_LENGTH];
    struct Pose *prev;
    struct Pose *next;
} Pose;

// Function prototypes
void takePose();
void loadPosesFromFile(const char *filename, Pose **head, int *totalPoses);
void printPoses(Pose *head);
void addPoseToList(Pose **head, const char *name, const char *description);
void practicePoses(Pose *head, int poseCount);
Pose* selectRandomPose(Pose *head, Pose *selected[], int *selectedCount, int totalPoses);
void freePoseList(Pose *head);

int main() {
    // Call the takePose function when the menu is selected
    takePose();
    return 0;
}

void takePose() {
    Pose *poseList = NULL;
    Pose *selectedPoses[MAX_POSES];
    int totalPoses = 0;
    int poseCount;

    // Load the poses from the file
    loadPosesFromFile("pose.txt", &poseList, &totalPoses);

    // Ask the user for the number of poses to practice (between 3 to 5)
    printf("Enter the number of poses to practice (3-5): ");
    scanf("%d", &poseCount);

    if (poseCount < 3 || poseCount > 5) {
        printf("Invalid input. Please enter a number between 3 and 5.\n");
        return;
    }

    // Select random poses
    int selectedCount = 0;
    while (selectedCount < poseCount) {
        selectRandomPose(poseList, selectedPoses, &selectedCount, totalPoses);
    }

    // Practice the selected poses
    practicePoses(selectedPoses[0], poseCount);

    // Free memory used by the linked list
    freePoseList(poseList);
}

void loadPosesFromFile(const char *filename, Pose **head, int *totalPoses) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char name[MAX_POSE_NAME_LENGTH];
    char description[MAX_POSE_DESC_LENGTH];
    
    while (fscanf(file, "%s", name) != EOF) {
        fgets(description, MAX_POSE_DESC_LENGTH, file);
        // Remove the newline character from description
        description[strcspn(description, "\n")] = 0;

        addPoseToList(head, name, description);
        (*totalPoses)++;
    }

    fclose(file);
}

void addPoseToList(Pose **head, const char *name, const char *description) {
    Pose *newPose = (Pose *)malloc(sizeof(Pose));
    strcpy(newPose->name, name);
    strcpy(newPose->description, description);
    newPose->prev = NULL;
    newPose->next = *head;

    if (*head != NULL) {
        (*head)->prev = newPose;
    }

    *head = newPose;
}

Pose* selectRandomPose(Pose *head, Pose *selected[], int *selectedCount, int totalPoses) {
    Pose *temp = head;
    int index = rand() % totalPoses;

    // Traverse to the selected random index
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    // Check if the pose has already been selected
    for (int i = 0; i < *selectedCount; i++) {
        if (selected[i] == temp) {
            return NULL; // Pose already selected, try again
        }
    }

    // Add the pose to the selected array
    selected[*selectedCount] = temp;
    (*selectedCount)++;

    return temp;
}

void practicePoses(Pose *head, int poseCount) {
    char userInput[4];
    int repeat = 1;//hb inject

    while (repeat) {
        Pose *temp = head;
        for (int i = 0; i < poseCount; i++) {
            printf("\nPose %d: %s\nDescription: %s\n", i + 1, temp->name, temp->description);
            printf("Please perform this pose for 30 seconds.\n");
            printf("Press 'yes' to continue or 'no' to stop: ");
            scanf("%s", userInput);

            // Make case-insensitive comparison
            if (strcasecmp(userInput, "no") == 0) {
                repeat = 0;
                break;
            }

            temp = temp->next;
        }

        // Ask the user if they want to repeat
        if (repeat) {
            printf("\nDo you want to repeat the practice? (yes/no): ");
            scanf("%s", userInput);
            if (strcasecmp(userInput, "no") == 0) {
                repeat = 0;
            }
        }
    }
}

void freePoseList(Pose *head) {
    Pose *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

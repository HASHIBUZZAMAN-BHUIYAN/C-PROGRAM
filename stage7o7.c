#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 100
#define MAX_DESC_LENGTH 500
#define MAX_HINT_LENGTH 50

// WorldView Structure to store album details and the associated world view
typedef struct WorldView {
    char album_name[MAX_NAME_LENGTH];
    char world_view[MAX_DESC_LENGTH];
    struct WorldView *prev;
    struct WorldView *next;
} WorldView;

// Hint Structure to store hint words for each album starting from the second album
typedef struct Hint {
    char first_word[MAX_HINT_LENGTH];
    char second_word[MAX_HINT_LENGTH];
} Hint;

// Function prototypes
void developWorldView();
void loadWorldViews(const char *filename, WorldView **head, int *totalAlbums);
int validateHint(const char *worldView, const char *firstWord, const char *secondWord);
WorldView* createWorldView(const char *albumName, const char *worldView);
void addWorldView(WorldView **head, WorldView *newWorldView);
void printWorldViews(WorldView *head);
void freeWorldViewList(WorldView *head);
void sortWorldViews(WorldView **head, int ascending);

// Main function
int main() {
    developWorldView();
    return 0;
}

void developWorldView() {
    WorldView *worldViewList = NULL;
    Hint albumHints[5] = {
        {"무한", "시공간"},
        {"초공간", "인연"},
        {"코끼리", "스케일"},
        {"은하수", "히치하이킹"},
        {"스타더스트", "스트림"}
    };
    int totalAlbums = 0;
    char albumName[MAX_NAME_LENGTH], worldViewDesc[MAX_DESC_LENGTH];
    int i, validHintCount = 0;

    // Load the first album world view from file
    loadWorldViews("world_view.txt", &worldViewList, &totalAlbums);

    // For each album starting from the second, get the hint words and validate
    for (i = 1; i <= 5; i++) {
        printf("Enter world view for album %d: %s\n", i, albumHints[i-1].first_word);
        printf("World View Description: ");
        getchar();  // to clear the buffer
        fgets(worldViewDesc, MAX_DESC_LENGTH, stdin);
        worldViewDesc[strcspn(worldViewDesc, "\n")] = 0;  // Remove trailing newline
        
        // Validate the hint words
        int tries = 0;
        while (tries < 2) {
            if (validateHint(worldViewDesc, albumHints[i-1].first_word, albumHints[i-1].second_word)) {
                printf("Valid world view!\n");
                WorldView *newWorldView = createWorldView(albumHints[i-1].first_word, worldViewDesc);
                addWorldView(&worldViewList, newWorldView);
                validHintCount++;
                break;
            } else {
                printf("Invalid world view. Please re-enter the world view for album %d: %s\n", i, albumHints[i-1].first_word);
                printf("World View Description: ");
                fgets(worldViewDesc, MAX_DESC_LENGTH, stdin);
                worldViewDesc[strcspn(worldViewDesc, "\n")] = 0;  // Remove trailing newline
            }
            tries++;
        }

        if (tries == 2) {
            printf("Failed to validate after 2 tries. Returning to main menu.\n");
            break;
        }
    }

    if (validHintCount == 5) {
        // Once all albums are added, print all the world views
        printWorldViews(worldViewList);
        
        // Optionally, sort world views (ascending or descending)
        printf("Sort in ascending order? (1 for Yes, 0 for No): ");
        int sortOrder;
        scanf("%d", &sortOrder);
        sortWorldViews(&worldViewList, sortOrder);
        printf("Sorted World Views:\n");
        printWorldViews(worldViewList);
    }

    // Free memory allocated to the linked list
    freeWorldViewList(worldViewList);
}

void loadWorldViews(const char *filename, WorldView **head, int *totalAlbums) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    while (fscanf(file, "%[^\n]\n", (*head)->album_name) != EOF) {
        fgets((*head)->world_view, MAX_DESC_LENGTH, file);
        (*head)->world_view[strcspn((*head)->world_view, "\n")] = 0; // Remove newline
        (*totalAlbums)++;
    }

    fclose(file);
}

int validateHint(const char *worldView, const char *firstWord, const char *secondWord) {
    // Convert world view to lowercase
    char lowerWorldView[MAX_DESC_LENGTH];
    int i;
    for (i = 0; worldView[i]; i++) {
        lowerWorldView[i] = tolower(worldView[i]);
    }
    lowerWorldView[i] = '\0';

    // Convert hints to lowercase and check if they exist in the world view
    char lowerFirstWord[MAX_HINT_LENGTH], lowerSecondWord[MAX_HINT_LENGTH];
    for (i = 0; firstWord[i]; i++) {
        lowerFirstWord[i] = tolower(firstWord[i]);
    }
    lowerFirstWord[i] = '\0';

    for (i = 0; secondWord[i]; i++) {
        lowerSecondWord[i] = tolower(secondWord[i]);
    }
    lowerSecondWord[i] = '\0';

    if (strstr(lowerWorldView, lowerFirstWord) && strstr(lowerWorldView, lowerSecondWord)) {
        return 1;  // Both hint words are present
    }
    return 0;
}

WorldView* createWorldView(const char *albumName, const char *worldView) {
    WorldView *newWorldView = (WorldView *)malloc(sizeof(WorldView));
    strcpy(newWorldView->album_name, albumName);
    strcpy(newWorldView->world_view, worldView);
    newWorldView->prev = NULL;
    newWorldView->next = NULL;
    return newWorldView;
}

void addWorldView(WorldView **head, WorldView *newWorldView) {
    if (*head == NULL) {
        *head = newWorldView;
    } else {
        WorldView *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newWorldView;
        newWorldView->prev = temp;
    }
}

void printWorldViews(WorldView *head) {
    WorldView *temp = head;
    while (temp != NULL) {
        printf("Album: %s\nWorld View: %s\n", temp->album_name, temp->world_view);
        temp = temp->next;
    }
}

void freeWorldViewList(WorldView *head) {
    WorldView *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void sortWorldViews(WorldView **head, int ascending) {
    if (*head == NULL) return;

    WorldView *current, *nextNode;
    char tempName[MAX_NAME_LENGTH], tempView[MAX_DESC_LENGTH];
    
    int swapped;
    do {//hb inject
        swapped = 0;
        current = *head;
        while (current->next != NULL) {
            nextNode = current->next;
            if ((ascending && strcmp(current->album_name, nextNode->album_name) > 0) ||
                (!ascending && strcmp(current->album_name, nextNode->album_name) < 0)) {
                // Swap data
                strcpy(tempName, current->album_name);
                strcpy(tempView, current->world_view);
                strcpy(current->album_name, nextNode->album_name);
                strcpy(current->world_view, nextNode->world_view);
                strcpy(nextNode->album_name, tempName);
                strcpy(nextNode->world_view, tempView);
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

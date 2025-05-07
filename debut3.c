#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_TRAINEES 10
#define MAX_MEDIA 10

// Media names
const char* media[] = {
    "KBS", "MBC", "SBS", "JTBC", "YTN", "한겨례", "오마이뉴스", "BBC", "삼프로TV", "MTN"
};

// Structure to store trainee data
typedef struct {
    char name[50];
    int id;
} Trainee;

// Function to print the ladder structure (before and after)
void printLadder(int trainees_count, int ladder[][MAX_TRAINEES], const Trainee trainees[], const char* media[]) {
    printf("\nLadder Structure:\n");

    // Print Trainee IDs
    for (int i = 0; i < trainees_count; i++) {
        printf("ID: %d (%s)  ", trainees[i].id, trainees[i].name);
    }
    printf("\n");

    // Print the ladder connections
    for (int i = 0; i < trainees_count; i++) {
        printf("Trainee %d (%s): ", trainees[i].id, trainees[i].name);
        for (int j = 0; j < trainees_count; j++) {
            if (ladder[i][j] == 1) {
                printf("-> %d (%s) ", trainees[j].id, trainees[j].name);
            }
        }
        printf("\n");
    }

    // Print media assignments after the ladder
    for (int i = 0; i < trainees_count; i++) {
        printf("Trainee %d (%s) is assigned to media: %s\n", trainees[i].id, trainees[i].name, media[i]);
    }
}

// Function to simulate ladder game and match trainees to media
void interactionMedia() {
    srand(time(NULL));  // Seed the random number generator

    // Get the number of trainees (vertical lines)
    int trainees_count;
    printf("사다리 세로 줄의 수를 입력하세요 (4~6): ");
    scanf("%d", &trainees_count);
    if (trainees_count < 4 || trainees_count > 6) {
        printf("올바른 세로 줄 수를 입력하세요.\n");
        return;
    }

    // Generate trainees (ID & Name)
    Trainee trainees[MAX_TRAINEES];
    for (int i = 0; i < trainees_count; i++) {
        printf("연습생 %d의 닉네임을 입력하세요: ", i + 1);
        snprintf(trainees[i].name, sizeof(trainees[i].name), "Trainee%d", i + 1);
        trainees[i].id = i + 1;
    }

    // Get the number of horizontal lines (connections)
    int horizontal_lines;
    printf("사다리 가로 줄의 수를 입력하세요: ");
    scanf("%d", &horizontal_lines);

    // Ladder setup: Initialize a 2D array for ladder connections (0 = no connection, 1 = connection)
    int ladder[MAX_TRAINEES][MAX_TRAINEES] = { 0 };
    
    // Randomly create horizontal connections (ladder game)
    for (int i = 0; i < horizontal_lines; i++) {
        int start, end;
        printf("가로 줄 %d의 시작 점과 끝 점을 입력하세요 (예: 1 3): ", i + 1);
        scanf("%d %d", &start, &end);
        ladder[start - 1][end - 1] = 1;
        ladder[end - 1][start - 1] = 1;  // hb Ladder is bidirectional
    }

    // Randomly assign media to trainees using the vertical lines
    int media_order[MAX_MEDIA] = { 0 };
    for (int i = 0; i < trainees_count; i++) {
        media_order[i] = i;
    }

    // Shuffle the media array for random assignment
    for (int i = trainees_count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = media_order[i];
        media_order[i] = media_order[j];
        media_order[j] = temp;
    }

    // Print the ladder and media assignments
    printLadder(trainees_count, ladder, trainees, media_order);
}

// Main function
int main() {
    // Running the interactionMedia function for media training
    interactionMedia();
    return 0;
}

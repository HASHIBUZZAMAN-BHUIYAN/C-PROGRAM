#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define CLEAR_COMMAND "cls"
#else
#include <unistd.h>
#define CLEAR_COMMAND "clear"
#endif

#define MAX_LINES 100
#define MAX_LENGTH 256

// Struct to hold song and dance data
typedef struct {
    char lyric[MAX_LENGTH];
    char concept[MAX_LENGTH];
    char expression[MAX_LENGTH];
} SongWithDance;

// Struct to hold user answers
typedef struct {
    char lyric[MAX_LENGTH];
    char user_expression[MAX_LENGTH];
} MyAnswer;

SongWithDance songData[MAX_LINES];
MyAnswer answers[MAX_LINES];
int lineCount = 0;

void LoadFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open error");
        exit(1);
    }
    char buffer[MAX_LENGTH];
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (lineCount >= MAX_LINES) break;
        char *lyric = strtok(buffer, "{");
        char *expression = strtok(NULL, "}");
        char *concept = strtok(NULL, "()\n");
        if (lyric && expression && concept) {
            strncpy(songData[lineCount].lyric, lyric, MAX_LENGTH);
            strncpy(songData[lineCount].expression, expression, MAX_LENGTH);
            strncpy(songData[lineCount].concept, concept, MAX_LENGTH);
            lineCount++;
        }
    }
    fclose(fp);
}
//hb inject
void DisplayHint(int seconds) {
    printf("==== Memorize the following lyrics and choreography ====\n");
    for (int i = 0; i < lineCount; i++) {
        printf("[%d] %s {%s} (%s)\n", i + 1, songData[i].lyric, songData[i].expression, songData[i].concept);
    }
    printf("\nYou have %d seconds...\n", seconds);
    fflush(stdout);
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
    system(CLEAR_COMMAND);
}

void InputDanceSymbol() {
    for (int i = 0; i < lineCount; i++) {
        printf("\nLyric: %s\nYour dance expression: ", songData[i].lyric);
        fgets(answers[i].user_expression, MAX_LENGTH, stdin);
        answers[i].user_expression[strcspn(answers[i].user_expression, "\n")] = '\0';
        strncpy(answers[i].lyric, songData[i].lyric, MAX_LENGTH);
    }
}

void EvalMatchingRatio() {
    int matchCount = 0;
    printf("\n==== Matching Result ====\n");
    for (int i = 0; i < lineCount; i++) {
        if (strcmp(songData[i].expression, answers[i].user_expression) == 0) {
            matchCount++;
        }
    }
    int percentage = (matchCount * 100) / lineCount;
    printf("Your choreography matched %d%% of the lyrics.\n", percentage);
    if (percentage < 100) {
        printf("Mismatched lyrics:\n");
        for (int i = 0; i < lineCount; i++) {
            if (strcmp(songData[i].expression, answers[i].user_expression) != 0) {
                printf("- %s\n", songData[i].lyric);
            }
        }
    }
}

void RememberSongWithDance() {
    int duration;
    printf("Enter display duration in seconds: ");
    scanf("%d", &duration);
    getchar(); // clear newline

    LoadFile("song-with-dance.txt");
    DisplayHint(duration);
    InputDanceSymbol();
    EvalMatchingRatio();
}
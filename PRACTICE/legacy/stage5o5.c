#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DANCE_STYLES 100
#define MAX_LINE 1024

typedef struct {
    char style[100];
    char song[100];
    char description[500];
} DanceStyle;

DanceStyle styles[MAX_DANCE_STYLES];
int styleCount = 0;

// Trim leading/trailing whitespace
void trim(char *str) {
    char *end;
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') str++;
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) end--;
    *(end + 1) = '\0';
}

// Parse HTML file and extract the data for dance styles
void parseDanceStyleHTML(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("파일 열기에 실패했습니다: %s\n", filename);
        return;
    }

    char line[MAX_LINE];
    DanceStyle current;
    memset(&current, 0, sizeof(DanceStyle));

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        // Look for <style> tags for the style name
        if (strstr(line, "<style>") != NULL) {
            sscanf(line, "<style>%99[^\n]</style>", current.style);
        }
        // Look for <song> tags for the song name
        else if (strstr(line, "<song>") != NULL) {
            sscanf(line, "<song>%99[^\n]</song>", current.song);
        }
        // Look for <description> tags for the description
        else if (strstr(line, "<description>") != NULL) {
            sscanf(line, "<description>%499[^\n]</description>", current.description);
            if (styleCount < MAX_DANCE_STYLES) {
                styles[styleCount++] = current;
                memset(&current, 0, sizeof(DanceStyle));
            }
        }
    }

    fclose(file);
}

// Display the dance styles and allow the user to select the correct one
void learnDanceStyle() {
    parseDanceStyleHTML("dance_style.html");
    if (styleCount == 0) {
        printf("안무 스타일이 없습니다.\n");
        return;
    }

    char input[100];
    int correctCount = 0;

    while (1) {
        // Randomly pick a song
        int index = rand() % styleCount;
        printf("\n--- 노래: %s ---\n", styles[index].song);
        printf("이 노래에 맞는 안무 스타일을 입력하세요 (종료: q 또는 quit): ");
        fgets(input, sizeof(input), stdin);
        trim(input);

        if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            printf("안무 스타일 학습을 종료합니다.\n");
            break;
        }

        // Check if the answer matches
        if (strcmp(input, styles[index].style) == 0) {
            correctCount++;
            printf("정답!\n");
        } else {
            printf("틀렸습니다! 정답은: %s\n", styles[index].style);
        }
    }

    printf("총 %d개의 정답을 맞혔습니다.\n", correctCount);
}

// Save the parsed dance styles to a YAML file
void saveToYAML() {
    FILE *file = fopen("dance_style.yaml", "w");
    if (!file) {
        printf("파일 생성에 실패했습니다.\n");
        return;
    }

    fprintf(file, "danceStyles:\n");

    for (int i = 0; i < styleCount; i++) {
        fprintf(file,
                "  - 안무_스타일: %s\n"
                "    노래: %s\n"
                "    설명: %s\n",
                styles[i].style, styles[i].song, styles[i].description);
    }

    fclose(file);
    printf("YAML 파일로 저장되었습니다: dance_style.yaml\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n[댄스 훈련 시스템]\n");
        printf("1. 안무 스타일 학습\n");
        printf("2. YAML로 저장\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        getchar(); // Consume newline after scanf

        switch (choice) {
            case 1:
                learnDanceStyle();
                break;
            case 2:
                saveToYAML();
                break;
            case 3:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }//hb inject

    return 0;
}

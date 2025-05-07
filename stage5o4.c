#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERNS 100
#define MAX_LINE 1024

typedef struct {
    char id[20];
    char name[100];
    char description[500];
} BreathingPattern;

BreathingPattern patterns[MAX_PATTERNS];
int patternCount = 0;

// Trim leading/trailing whitespace and newline characters
void trim(char *str) {
    char *end;
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') str++;
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) end--;
    *(end + 1) = '\0';
}

// Parses JSON manually (assumes formatted line-by-line)
void parseBreathingJSON(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("파일 열기에 실패했습니다: %s\n", filename);
        return;
    }

    char line[MAX_LINE];
    BreathingPattern current;
    memset(&current, 0, sizeof(BreathingPattern));

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (strncmp(line, "\"id\"", 4) == 0) {
            sscanf(line, "\"id\": \"%19[^\"]", current.id);
        } else if (strncmp(line, "\"name\"", 6) == 0) {
            sscanf(line, "\"name\": \"%99[^\"]", current.name);
        } else if (strncmp(line, "\"description\"", 13) == 0) {
            sscanf(line, "\"description\": \"%499[^\"]", current.description);
            if (patternCount < MAX_PATTERNS) {
                patterns[patternCount++] = current;
                memset(&current, 0, sizeof(BreathingPattern));
            }
        }
    }

    fclose(file);
}

void displayPatterns() {
    printf("\n--- 마인드풀니스 호흡 패턴 목록 ---\n");
    for (int i = 0; i < patternCount; i++) {
        printf("ID: %s, 이름: %s\n", patterns[i].id, patterns[i].name);
    }
}

void saveToFavorites(BreathingPattern *pattern) {
    FILE *file = fopen("mymindfulness.json", "a");
    if (!file) {
        printf("즐겨찾기 파일을 생성할 수 없습니다.\n");
        return;
    }

    fprintf(file,
        "{\n"
        "  \"id\": \"%s\",\n"
        "  \"name\": \"%s\",\n"
        "  \"how-to\": \"%s\"\n"
        "}\n",
        pattern->id, pattern->name, pattern->description);

    fclose(file);
    printf("즐겨찾기에 저장되었습니다.\n");
}

void guideMindfulnessBreathing() {
    parseBreathingJSON("mindfulness_breathing.json");
    if (patternCount == 0) {
        printf("호흡 패턴이 없습니다.\n");
        return;
    }

    char input[50];
    while (1) {
        displayPatterns();
        printf("\nID를 입력하세요 (종료: q 또는 quit): ");
        if (!fgets(input, sizeof(input), stdin)) break;
        trim(input);
        if (strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            printf("마인드풀니스 호흡 기능을 종료합니다.\n");
            break;
        }

        int found = 0;
        for (int i = 0; i < patternCount; i++) {
            if (strcmp(patterns[i].id, input) == 0) {
                printf("\n[패턴 이름] %s\n[설명] %s\n", patterns[i].name, patterns[i].description);
                printf("즐겨찾기로 등록하시겠습니까? (y/n): ");
                char choice[10];
                if (fgets(choice, sizeof(choice), stdin)) {
                    trim(choice);
                    if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0) {
                        saveToFavorites(&patterns[i]);
                    }
                }
                found = 1;
                break;
            }
        }
//hb inject
        if (!found) {
            printf("해당 ID를 찾을 수 없습니다. 다시 입력하세요.\n");
        }
    }
}

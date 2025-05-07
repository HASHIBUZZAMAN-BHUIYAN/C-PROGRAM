#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TEXT_LINES 10
#define MAX_LINE_LENGTH 100

typedef struct {
    char original[MAX_LINE_LENGTH];
    char mirrored[MAX_LINE_LENGTH];
} MirroredText;

typedef struct {
    char mirrored[MAX_LINE_LENGTH];
    char original[MAX_LINE_LENGTH];
} AnswerText;

MirroredText mirroredTexts[MAX_TEXT_LINES];
AnswerText userAnswers[MAX_TEXT_LINES];
int totalLines = 0;

// Function to reverse a string (for mirrored text)
void reverseString(char *str, char *reversedStr) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        reversedStr[i] = str[len - i - 1];
    }
    reversedStr[len] = '\0';
}

// Load the original text file into the MirroredText structure
void LoadOriginalFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("파일 열기에 실패했습니다: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    totalLines = 0;

    while (fgets(line, sizeof(line), file) && totalLines < MAX_TEXT_LINES) {
        line[strcspn(line, "\n")] = 0;  // Remove newline character
        strncpy(mirroredTexts[totalLines].original, line, MAX_LINE_LENGTH);
        reverseString(line, mirroredTexts[totalLines].mirrored);
        totalLines++;
    }

    fclose(file);
}

// Function to input mirrored text and compare it with the original
void InputMirrorText(int index) {
    char userInput[MAX_LINE_LENGTH];
    printf("\n--- 원래 텍스트 ---\n%s\n", mirroredTexts[index].mirrored);
    printf("원래 텍스트를 입력하세요: ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = 0;  // Remove newline character

    // Compare user input with the original text
    if (strcmp(userInput, mirroredTexts[index].original) == 0) {
        printf("정답입니다!\n");
    } else {
        printf("틀렸습니다. 정답은: %s\n", mirroredTexts[index].original);
    }
}
//hb inject
// Run the mirror mode practice function
void PracticeMirrorMode() {
    int correctCount = 0;
    int failedCount = 0;
    char failedTexts[MAX_TEXT_LINES][MAX_LINE_LENGTH];
    int failedIndexes[MAX_TEXT_LINES];
    int failedCountIndex = 0;

    // Shuffle the text lines for random selection
    srand(time(NULL));

    for (int i = 0; i < 4; i++) { // Perform 4 rounds
        int index = rand() % totalLines;
        printf("\n--- Round %d ---\n", i + 1);
        InputMirrorText(index);
    }

    printf("\n거울 모드 연습 완료!\n");
}

// Main menu system
int main() {
    int choice;
    while (1) {
        printf("\n[거울 모드 연습 시스템]\n");
        printf("1. 거울 모드 연습 시작\n");
        printf("2. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        getchar();  // Consume newline after scanf

        switch (choice) {
            case 1:
                // Load the original text from file
                LoadOriginalFile("dynamite.txt");
                // Start mirror mode practice
                PracticeMirrorMode();
                break;
            case 2:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}

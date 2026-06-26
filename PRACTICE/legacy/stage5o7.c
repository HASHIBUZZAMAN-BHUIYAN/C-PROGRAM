#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EMOTIONS 10
#define MAX_EXPRESSION_LENGTH 100
#define MAX_BODY_MOVEMENT_LENGTH 200

// Data structure to store emotion data
typedef struct {
    char korean[MAX_EXPRESSION_LENGTH];
    char english[MAX_EXPRESSION_LENGTH];
    char similarKorean[MAX_EXPRESSION_LENGTH];
    char similarEnglish[MAX_EXPRESSION_LENGTH];
    char bodyMovement[MAX_BODY_MOVEMENT_LENGTH];
} Emotion;

Emotion emotions[MAX_EMOTIONS];
int totalEmotions = 0;

// Function to load emotion data from a simulated YAML file (or JSON if needed)
int LoadEmotionYaml(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return 0;
    }

    // Simulating emotion data loading (in place of actual YAML parsing)
    // This is just a placeholder for loading YAML content; it would be replaced by actual YAML parsing logic
    strcpy(emotions[0].korean, "기쁨");
    strcpy(emotions[0].english, "Joy");
    strcpy(emotions[0].similarKorean, "행복");
    strcpy(emotions[0].similarEnglish, "Happiness");
    strcpy(emotions[0].bodyMovement, "밝은 미소와 활기찬 움직임, 눈가 주위의 근육을 이용한 활발한 표정");

    strcpy(emotions[1].korean, "슬픔");
    strcpy(emotions[1].english, "Sadness");
    strcpy(emotions[1].similarKorean, "서러움");
    strcpy(emotions[1].similarEnglish, "Grief");
    strcpy(emotions[1].bodyMovement, "어깨가 처지고 눈빛이 슬프며, 가슴이 움켜쥐어지는 듯한 표정");

    totalEmotions = 2; // This would be based on actual data loaded from YAML

    fclose(file);
    return 1;
}

// Data structure to hold emotion words for practice
typedef struct {
    char korean[MAX_EXPRESSION_LENGTH];
    char english[MAX_EXPRESSION_LENGTH];
} EmotionWord;

EmotionWord emotionWords[MAX_EMOTIONS];
int totalWords = 0;

// Initialize emotion words for practice
void InitializeEmotionWords() {
    for (int i = 0; i < totalEmotions; i++) {
        strcpy(emotionWords[i].korean, emotions[i].korean);
        strcpy(emotionWords[i].english, emotions[i].english);
    }
    totalWords = totalEmotions;
}

// Function for emotion practice
void practiceEmotionWithBody() {
    srand(time(NULL));  // Initialize random seed

    int correctCount = 0;
    while (correctCount < 5) {
        int index = rand() % totalWords;  // Select a random emotion

        printf("\nEmotion in English: %s\n", emotionWords[index].english);
        printf("Enter the corresponding emotion in Korean: ");

        char userInput[MAX_EXPRESSION_LENGTH];
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strcspn(userInput, "\n")] = 0;  // Remove newline from input

        if (strcmp(userInput, emotionWords[index].korean) == 0) {
            printf("Correct! The body movement for this emotion is:\n");
            printf("%s\n", emotions[index].bodyMovement);
            correctCount++;
        } else {
            printf("Incorrect. The correct answer is: %s\n", emotionWords[index].korean);
        }
    }

    printf("\nCongratulations! You completed the emotion practice.\n");

    // If the practice is completed, convert YAML to JSON as a bonus
    convertYamlToJson();
}

// Function to convert emotion data to a JSON file
void convertYamlToJson() {
    FILE *jsonFile = fopen("tasks.json", "w");
    if (jsonFile) {
        // Write opening array bracket
        fprintf(jsonFile, "[\n");

        for (int i = 0; i < totalEmotions; i++) {
            // Writing each emotion object
            fprintf(jsonFile, "  {\n");
            fprintf(jsonFile, "    \"기본 감정\": {\n");
            fprintf(jsonFile, "      \"한국어\": \"%s\",\n", emotions[i].korean);
            fprintf(jsonFile, "      \"영어\": \"%s\"\n", emotions[i].english);
            fprintf(jsonFile, "    },\n");

            fprintf(jsonFile, "    \"유사 감정\": {\n");
            fprintf(jsonFile, "      \"한국어\": \"%s\",\n", emotions[i].similarKorean);
            fprintf(jsonFile, "      \"영어\": \"%s\"\n", emotions[i].similarEnglish);
            fprintf(jsonFile, "    },\n");

            fprintf(jsonFile, "    \"몸 동작\": {\n");
            fprintf(jsonFile, "      \"표현\": \"%s\"\n", emotions[i].bodyMovement);
            fprintf(jsonFile, "    }\n");
            fprintf(jsonFile, "  }");

            if (i < totalEmotions - 1) {
                fprintf(jsonFile, ",\n");
            } else {
                fprintf(jsonFile, "\n");
            }
        }
//hb inject
        // Write closing array bracket
        fprintf(jsonFile, "]\n");

        fclose(jsonFile);
        printf("YAML 데이터가 JSON 파일로 변환되었습니다: tasks.json\n");
    } else {
        printf("JSON 파일 저장에 실패했습니다.\n");
    }
}

// Main function to interact with the user
int main() {
    int choice;
    while (1) {
        printf("\n[감정 표현 연습 시스템]\n");
        printf("1. 감정 표현 연습 시작\n");
        printf("2. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        getchar();  // Consume newline after scanf

        switch (choice) {
            case 1:
                // Load emotion data from YAML file
                if (LoadEmotionYaml("emotion.yaml")) {
                    // Initialize emotion words for practice
                    InitializeEmotionWords();
                    // Start emotion practice
                    practiceEmotionWithBody();
                } else {
                    printf("감정 표현 파일을 불러오지 못했습니다.\n");
                }
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 10
#define MAX_SENTENCE_LENGTH 100
#define MIN_SENTENCE_LENGTH 90
#define NUM_RANDOM_WORDS 5
#define MAX_ATTEMPTS 2
#define MAX_WORD_LENGTH 5

// 단어집 구조체
char wordbook[MAX_WORDS][MAX_WORD_LENGTH + 1];  // 10개의 단어, 최대 5글자
int wordCount = 0;

// 무작위 단어 선택 함수
void selectRandomWords(char result[NUM_RANDOM_WORDS][MAX_WORD_LENGTH + 1]) {
    int selectedIndices[NUM_RANDOM_WORDS] = {0};  // 선택된 단어 인덱스 배열
    int selectedCount = 0;

    while (selectedCount < NUM_RANDOM_WORDS) {
        int index = rand() % wordCount;
        int alreadySelected = 0;

        // 중복된 단어가 있으면 다시 선택
        for (int i = 0; i < selectedCount; i++) {
            if (selectedIndices[i] == index) {
                alreadySelected = 1;
                break;
            }
        }

        if (!alreadySelected) {
            strcpy(result[selectedCount], wordbook[index]);
            selectedIndices[selectedCount] = index;
            selectedCount++;
        }
    }
}

// 문장 길이 검사 및 90~100자 이내로 입력받기
int validateSentenceLength(char *sentence) {
    int length = strlen(sentence);
    return (length >= MIN_SENTENCE_LENGTH && length <= MAX_SENTENCE_LENGTH);
}

// 단어 수 세는 함수
int countWordsInSentence(char *sentence) {
    int count = 0;
    char *token = strtok(sentence, " ");
    
    while (token != NULL) {
        count++;
        token = strtok(NULL, " ");
    }
    
    return count;
}

// 단어 반복 횟수 세는 함수
void countWordOccurrences(char sentence[MAX_SENTENCE_LENGTH], char words[NUM_RANDOM_WORDS][MAX_WORD_LENGTH + 1]) {
    int occurrences[NUM_RANDOM_WORDS] = {0};
    
    // 문장을 단어로 나누어 각 단어가 몇 번 등장하는지 셈
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        for (int i = 0; i < NUM_RANDOM_WORDS; i++) {
            if (strcmp(token, words[i]) == 0) {
                occurrences[i]++;
            }
        }
        token = strtok(NULL, " ");
    }

    // 결과 출력
    printf("\n[반복 횟수]\n");
    for (int i = 0; i < NUM_RANDOM_WORDS; i++) {
        printf("단어 '%s' : %d번 반복\n", words[i], occurrences[i]);
    }
}

// 문장 입력 받기
void writeRandomSentence() {
    char randomWords[NUM_RANDOM_WORDS][MAX_WORD_LENGTH + 1];
    char sentence[MAX_SENTENCE_LENGTH];
    int attempts = 0;
    
    // 5개의 무작위 단어 제시
    selectRandomWords(randomWords);
    
    // 두 번째 시도에서 중복되지 않도록 함수 확장
    while (attempts <= MAX_ATTEMPTS) {
        if (attempts > 0) {
            printf("첫 번째 제시된 단어들과 중복되지 않는 새로운 5개의 단어를 제시합니다.\n");
            selectRandomWords(randomWords);
        }

        // 5개의 단어 출력
        printf("다음 단어들을 사용하여 문장을 작성해주세요:\n");
        for (int i = 0; i < NUM_RANDOM_WORDS; i++) {
            printf("%s ", randomWords[i]);
        }
        printf("\n");

        printf("문장을 작성하세요 (90~100자 이내로 입력): ");
        getchar();  // 버퍼 비우기
        fgets(sentence, sizeof(sentence), stdin);

        // 입력 길이 검사
        if (validateSentenceLength(sentence)) {
            break;
        } else {
            printf("문장 길이가 너무 짧거나 길어요. 다시 시도해주세요.\n");
            attempts++;
        }
    }

    if (attempts > MAX_ATTEMPTS) {
        printf("최대 시도 횟수를 초과했습니다. 종료합니다.\n");
        return;
    }

    // 사용된 단어 수 세기
    int wordCountInSentence = countWordsInSentence(sentence);
    printf("입력한 문장의 단어 수: %d\n", wordCountInSentence);
    printf("입력한 문장의 길이: %ld자\n", strlen(sentence));

    // 단어 반복 횟수 세기
    countWordOccurrences(sentence, randomWords);
}

// 단어집에 단어 입력 함수
void inputWords() {
    printf("단어집에 3~5글자 이내의 단어를 최대 10개까지 입력하세요.\n");
    while (wordCount < MAX_WORDS) {
        char word[MAX_WORD_LENGTH + 1];
        printf("단어 입력 (3~5글자): ");
        scanf("%s", word);

        // 3~5글자 이내 단어 검사
        int len = strlen(word);
        if (len >= 3 && len <= 5) {
            strcpy(wordbook[wordCount], word);
            wordCount++;
        } else {
            printf("단어 길이가 올바르지 않습니다. 다시 시도해주세요.\n");
        }

        // 10개 단어까지 입력 가능
        if (wordCount >= MAX_WORDS) {
            break;
        }
    }
}

int main() {
    srand(time(NULL));  // 난수 초기화

    int menuChoice;
    while (1) {
        printf("\n[훈련 메뉴]\n");
        printf("1. 단어 입력\n");
        printf("2. 창의성 글쓰기 훈련\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1:
                inputWords();
                break;
            case 2:
                writeRandomSentence();
                break;
            case 3:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
        }
    }

    return 0;
}

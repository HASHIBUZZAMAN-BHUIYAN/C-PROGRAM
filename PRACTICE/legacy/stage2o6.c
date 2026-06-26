#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 7
#define MAX_NAME_LEN 30
#define MAX_NICKNAME_LEN 30
#define MAX_DIARY_LEN 41
#define MAX_DIARY_COUNT 100

typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
} Member;

typedef struct {
    char nickname[MAX_NICKNAME_LEN];
    char recentEvent[MAX_DIARY_LEN];
    char mood[MAX_DIARY_LEN];
    char currentEmotion[MAX_DIARY_LEN];
    char strongEmotionSituation[MAX_DIARY_LEN];
    char recentStress[MAX_DIARY_LEN];
    char physicalSymptoms[MAX_DIARY_LEN];
    char emotionHandling[MAX_DIARY_LEN];
} EmotionDiary;

const Member members[MAX_MEMBERS] = {
    {"김영진", "영진"},
    {"이민호", "민호"},
    {"박지훈", "지훈"},
    {"최수빈", "수빈"},
    {"정하늘", "하늘"},
    {"한서준", "서준"},
    {"오유진", "유진"}
};

EmotionDiary diaries[MAX_MEMBERS];
int diaryCount = 0;

const char *questions[7] = {
    "1. 최근에 어떤 일이 있었나요? 그 일에 대한 감정을 어떻게 느꼈나요?",
    "2. 지난 몇 일 동안 기분은 어땠나요?",
    "3. 현재 기분이 어떤가요? 기쁨, 슬픔, 분노, 불안 등 어떤 감정을 느끼고 있나요?",
    "4. 어떤 상황에서 감정을 더 강하게 느끼나요?",
    "5. 감정적인 변화나 스트레스 요인이 최근에 있었나요?",
    "6. 감정을 표현하는 물리적인 증상이 있나요? (예: 눈물, 웃음, 심장이 빠르게 뛰는 소리 등)",
    "7. 감정을 다루는 방식에 대해 어떤 생각이나 전략이 있나요?"
};

int findMemberIndexByNickname(const char *nick) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i].nickname, nick) == 0) {
            return i;
        }
    }
    return -1;
}

void inputNickName(char *nickname) {
    int tryCount = 0;
    while (tryCount < 2) {
        printf("닉네임의 첫 글자와 마지막 글자를 표시한 후 정확한 닉네임을 입력해주세요.\n");
        printf("예시: 영진 => (영진)\n");
        fgets(nickname, MAX_NICKNAME_LEN, stdin);
        nickname[strcspn(nickname, "\n")] = '\0'; // 새 줄 문자 제거
        
        int idx = findMemberIndexByNickname(nickname);
        if (idx != -1) {
            printf("정확한 닉네임: %s\n", members[idx].name);
            return;
        } else {
            printf("잘못된 닉네임입니다. 다시 시도해주세요.\n");
        }
        tryCount++;
    }
    printf("닉네임 입력에 실패했습니다. 프로그램을 종료합니다.\n");
    exit(0);
}

void writeEmotionDiary(int idx) {
    printf("감정 일기 작성을 시작합니다.\n");
    for (int i = 0; i < 7; i++) {
        printf("%s\n", questions[i]);
        printf("답변을 입력하세요 (20~40자): ");
        char response[MAX_DIARY_LEN];
        fgets(response, MAX_DIARY_LEN, stdin);
        response[strcspn(response, "\n")] = '\0'; // 새 줄 문자 제거
        
        if (strlen(response) < 20 || strlen(response) > 40) {
            printf("입력 길이가 잘못되었습니다. 다시 입력해주세요.\n");
            i--; // 현재 질문을 다시 묻게 만듬
            continue;
        }

        if (strcmp(response, "TBD") == 0) {
            strcpy(response, "TBD");
        }

        // 해당 일기 항목에 저장
        if (i == 0) strcpy(diaries[idx].recentEvent, response);
        if (i == 1) strcpy(diaries[idx].mood, response);
        if (i == 2) strcpy(diaries[idx].currentEmotion, response);
        if (i == 3) strcpy(diaries[idx].strongEmotionSituation, response);
        if (i == 4) strcpy(diaries[idx].recentStress, response);
        if (i == 5) strcpy(diaries[idx].physicalSymptoms, response);
        if (i == 6) strcpy(diaries[idx].emotionHandling, response);
    }

    printf("감정 일기가 저장되었습니다.\n");
}

void printEmotionDiary(int idx) {
    printf("감정 일기 출력\n");
    printf("이름: %s\n", members[idx].name);
    if (strcmp(diaries[idx].recentEvent, "TBD") != 0) printf("%s: %s\n", questions[0], diaries[idx].recentEvent);
    if (strcmp(diaries[idx].mood, "TBD") != 0) printf("%s: %s\n", questions[1], diaries[idx].mood);
    if (strcmp(diaries[idx].currentEmotion, "TBD") != 0) printf("%s: %s\n", questions[2], diaries[idx].currentEmotion);
    if (strcmp(diaries[idx].strongEmotionSituation, "TBD") != 0) printf("%s: %s\n", questions[3], diaries[idx].strongEmotionSituation);
    if (strcmp(diaries[idx].recentStress, "TBD") != 0) printf("%s: %s\n", questions[4], diaries[idx].recentStress);
    if (strcmp(diaries[idx].physicalSymptoms, "TBD") != 0) printf("%s: %s\n", questions[5], diaries[idx].physicalSymptoms);
    if (strcmp(diaries[idx].emotionHandling, "TBD") != 0) printf("%s: %s\n", questions[6], diaries[idx].emotionHandling);
}

void logEmotionDiary() {
    char nickname[MAX_NICKNAME_LEN];
    inputNickName(nickname);

    int idx = findMemberIndexByNickname(nickname);
    if (idx == -1) {
        printf("멤버를 찾을 수 없습니다.\n");
        return;
    }

    int choice;
    printf("1. 감정 일기 작성\n2. 감정 일기 출력\n선택: ");
    scanf("%d", &choice);
    getchar();  //hb 엔터 처리

    if (choice == 1) {
        writeEmotionDiary(idx);
    } else if (choice == 2) {
        printEmotionDiary(idx);
    } else {
        printf("잘못된 선택입니다.\n");
    }
}

int main() {
    logEmotionDiary();
    return 0;
}

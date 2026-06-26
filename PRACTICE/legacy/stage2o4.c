#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_MEMBERS 7
#define MAX_NAME_LEN 30
#define MAX_NICKNAME_LEN 30
#define MAX_ANSWER_LEN 51

// 2차원 배열로 된 성찰 질문 (보너스)
const char *questions[3] = {
    "오늘 어떤 성취를 이뤘나?",
    "어떤 어려움을 극복했나?",
    "내일은 어떤 계획을 세울까?"
};

// 멤버 불변 정보 구조체
typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
} Member;

// 멤버 목록
const Member members[MAX_MEMBERS] = {
    {"김영진", "영진"},
    {"이민호", "민호"},
    {"박지훈", "지훈"},
    {"최수빈", "수빈"},
    {"정하늘", "하늘"},
    {"한서준", "서준"},
    {"오유진", "유진"}
};

// 자기 성찰 구조체
typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
    char date[11]; // YYYY-MM-DD
    char answers[3][MAX_ANSWER_LEN];
} DailyReflection;

// 공백 제외 문자열 길이 계산
int effectiveLength(const char *str) {
    int len = 0;
    while (*str) {
        if (!isspace((unsigned char)*str)) len++;
        str++;
    }
    return len;
}

// 현재 날짜를 YYYY-MM-DD 형식으로 반환
void getCurrentDate(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, size, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// 성찰 질문 입력
void inputReflection(DailyReflection *r) {
    getCurrentDate(r->date, sizeof(r->date));
    for (int i = 0; i < 3; i++) {
        while (1) {
            printf("%s\n", questions[i]);
            fgets(r->answers[i], MAX_ANSWER_LEN, stdin);
            r->answers[i][strcspn(r->answers[i], "\n")] = 0;

            int len = strlen(r->answers[i]);
            if (len >= 20 && len <= 50) break;
            else printf("※ 답변은 20자 이상 50자 이내로 입력해주세요.\n");
        }
    }
}

// 성찰 결과 출력
void displayReflection(const DailyReflection *r) {
    int order[3] = {0, 1, 2};
    for (int i = 0; i < 2; i++) { // 길이에 따라 정렬
        for (int j = i + 1; j < 3; j++) {
            if (effectiveLength(r->answers[order[i]]) < effectiveLength(r->answers[order[j]])) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    printf("\n[자기 성찰 결과]\n");
    printf("닉네임: %s\n", r->nickname);
    printf("날짜: %s\n", r->date);
    for (int i = 0; i < 3; i++) {
        int idx = order[i];
        printf("%s\n%s\n\n", questions[idx], r->answers[idx]);
    }

    printf("[2. 자기관리와 팀워크] 메뉴로 돌아갑니다.\n");
}

// 자기 성찰hb 실행
void doSelfReflection() {
    DailyReflection reflection;
    printf("[자기 성찰을 시작합니다]\n");

    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, members[i].name, members[i].nickname);
    }

    int choice;
    while (1) {
        printf("자기 성찰할 멤버 번호를 선택하세요 (1~%d): ", MAX_MEMBERS);
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > MAX_MEMBERS) {
            printf("잘못된 입력입니다.\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            break;
        }
    }

    strcpy(reflection.name, members[choice - 1].name);
    strcpy(reflection.nickname, members[choice - 1].nickname);

    inputReflection(&reflection);
    displayReflection(&reflection);
}

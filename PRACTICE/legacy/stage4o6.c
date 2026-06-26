#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 10
#define MAX_DAYS_IN_WEEK 7
#define MAX_WEEKS_IN_MONTH 4
#define MAX_MONTHS_IN_YEAR 12
#define MAX_TITLE_LENGTH 100

// 체크리스트 항목을 정의하는 구조체
typedef struct {
    int itemId;
    char activity[MAX_TITLE_LENGTH];
    char condition[MAX_TITLE_LENGTH];
    char frequency[MAX_TITLE_LENGTH];
} ChecklistItem;

// 체크리스트 항목 목록
ChecklistItem checklist[MAX_ITEMS] = {
    {1, "아침 복부 호흡 연습", "5 ~ 10분", "매일"},
    {2, "저녁 경구 호흡 연습", "5 ~ 10분", "매일"},
    {3, "가볍고 부드러운 발성 연습", "10~15분", "매일"},
    {4, "음의 높낮이와 음조 연습", "10분", "매일"},
    {5, "발음과 억양 연습", "10분", "매일"},
    {6, "연습 후 목소리에 부담되는 활동 피하기", "긴 시간 대화 또는 통화 / 과도한 고음이나 저음 무대 / 소음 많은 환경에서 대화 / 긴 시간 동안 노래 연습 / 긴 시간 스트레스 상태의 목소리 사용", "매일"},
    {7, "충분히 물 마시기", "8잔", "매일"},
    {8, "적절한 습도 유지하기", "40% ~ 60%", "매일"},
    {9, "목소리 사용 후 적당한 휴식", "30분 이상", "매일"},
    {10, "전문 보컬 튜터와 레슨 또는 상담", "1회", "매주"}
};

// 날짜 계산을 위한 구조체 (주간, 월간 통계를 저장)
typedef struct {
    int completed[MAX_ITEMS];  // 각 항목의 완료 여부 (1: 완료, 0: 미완료)
} DailyChecklist;

// 주간 및 월간 통계를 관리하는 구조체
typedef struct {
    DailyChecklist weekData[MAX_DAYS_IN_WEEK];  // 주간 데이터를 위한 배열 (7일)
    int monthData[MAX_WEEKS_IN_MONTH];  // 월간 데이터를 위한 배열 (4주)
    int totalDays[MAX_ITEMS];  // 각 항목별 완료된 일수
} ChecklistStatistics;

ChecklistStatistics statistics;

// 날짜 기반 통계 초기화
void initStatistics() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        statistics.totalDays[i] = 0;
    }
    for (int week = 0; week < MAX_WEEKS_IN_MONTH; week++) {
        statistics.monthData[week] = 0;
    }
    for (int day = 0; day < MAX_DAYS_IN_WEEK; day++) {
        for (int item = 0; item < MAX_ITEMS; item++) {
            statistics.weekData[day].completed[item] = 0;
        }
    }
}

// 체크리스트 항목을 출력하는 함수
void printChecklist() {
    printf("\n보컬 건강 체크리스트:\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%d. %s\n", checklist[i].itemId, checklist[i].activity);
        printf("   조건: %s\n", checklist[i].condition);
        printf("   주기: %s\n\n", checklist[i].frequency);
    }
}

// 체크리스트 항목을 입력받고 완료 여부 기록
void recordChecklistCompletion() {
    int dayIndex = 0;  // 현재 날짜를 기준으로 인덱스 (예: 월요일 = 0, 일요일 = 6)
    int weekIndex = 0;  // 현재 주차 (1~4주)
    char completion[MAX_TITLE_LENGTH];
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%d. %s 완료 여부 (예/아니오): ", checklist[i].itemId, checklist[i].activity);
        scanf("%s", completion);

        if (strcasecmp(completion, "예") == 0) {
            statistics.weekData[dayIndex].completed[i] = 1;
            statistics.totalDays[i]++;
        }
    }

    // 주간 통계 업데이트
    statistics.monthData[weekIndex] += 1;  // 주차에 완료한 주차 기록 추가
}

// 주간 통계를 출력하는 함수
void printWeeklyStats() {
    printf("\n주간 통계:\n");
    for (int day = 0; day < MAX_DAYS_IN_WEEK; day++) {
        printf("Day %d: ", day + 1);
        for (int item = 0; item < MAX_ITEMS; item++) {
            if (statistics.weekData[day].completed[item]) {
                printf("완료[%d] ", item + 1);
            } else {
                printf("미완료[%d] ", item + 1);
            }
        }
        printf("\n");
    }
}

// 월간 통계를 출력하는 함수
void printMonthlyStats() {
    printf("\n월간 통계:\n");
    for (int week = 0; week < MAX_WEEKS_IN_MONTH; week++) {
        printf("Week %d: %d 항목 완료\n", week + 1, statistics.monthData[week]);
    }
}

// 날짜 계산 (보너스 요구사항)
int calculateDaysInMonth(int month) {
    int daysInMonth;
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            daysInMonth = 28;  // 간단화를 위해 2월을 28일로 계산
            break;
        default:
            daysInMonth = 0;
    }
    return daysInMonth;
}

// 보컬 체크리스트 관리 함수
void checkList4VocalHealth() {
    int option;
    initStatistics();
    while (1) {
        printf("\n1. 체크리스트 항목 입력\n");
        printf("2. 주간 통계 출력\n");
        printf("3. 월간 통계 출력\n");
        printf("4. 종료\n");
        printf("선택하세요: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                recordChecklistCompletion();
                break;
            case 2:
                printWeeklyStats();
                break;
            case 3:
                printMonthlyStats();
                break;
            case 4:
                return;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }//hb inject
}

int main() {
    // 프로그램 시작
    checkList4VocalHealth();
    return 0;
}

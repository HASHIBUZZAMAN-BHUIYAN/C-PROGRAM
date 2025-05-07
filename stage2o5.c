#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MEMBERS 7
#define MAX_NAME_LEN 30
#define MAX_NICKNAME_LEN 30
#define MAX_MEMORY_LEN 71
#define MAX_RECORDS 100

typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
} Member;

typedef struct {
    char name[MAX_NAME_LEN];
    char memory[MAX_MEMORY_LEN];
    char date[9]; // YYYYMMDD
    int wow;
} MemoryRecord;

const Member members[MAX_MEMBERS] = {
    {"김영진", "영진"},
    {"이민호", "민호"},
    {"박지훈", "지훈"},
    {"최수빈", "수빈"},
    {"정하늘", "하늘"},
    {"한서준", "서준"},
    {"오유진", "유진"}
};

MemoryRecord records[MAX_RECORDS];
int recordCount = 0;

const char *wowLabel(int wow) {
    if (wow <= 3) return "Calm";
    else if (wow <= 6) return "Exciting";
    return "Meaningful";
}

void printDateFormatted(const char *yyyymmdd) {
    printf("%c%c%c%c년 %c%c월 %c%c일", 
        yyyymmdd[0], yyyymmdd[1], yyyymmdd[2], yyyymmdd[3],
        yyyymmdd[4], yyyymmdd[5], yyyymmdd[6], yyyymmdd[7]);
}

int getCurrentHour() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_hour;
}

void getCurrentDate(char *dateBuf, int *hourBuf, int useCheat) {
    if (useCheat) {
        char input[11];
        printf("입력할 시간대를 입력하세요 (YYYYMMDDHH): ");
        fgets(input, sizeof(input), stdin);
        for (int i = 0; i < 8; i++) dateBuf[i] = input[i];
        dateBuf[8] = '\0';
        *hourBuf = (input[8] - '0') * 10 + (input[9] - '0');
    } else {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        snprintf(dateBuf, 9, "%04d%02d%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        *hourBuf = tm.tm_hour;
    }
}

int findMemberIndexByNickname(const char *nick) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        int j = 0;
        while (nick[j] && members[i].nickname[j] && nick[j] == members[i].nickname[j]) j++;
        if (nick[j] == '\0' && members[i].nickname[j] == '\0') return i;
    }
    return -1;
}

void displayMemory() {
    char nick[MAX_NICKNAME_LEN];
    printf("멤버 닉네임을 입력하세요: ");
    fgets(nick, sizeof(nick), stdin);
    nick[strcspn(nick, "\n")] = 0;

    int idx = findMemberIndexByNickname(nick);
    if (idx == -1) {
        printf("멤버를 찾을 수 없습니다.\n");
        return;
    }

    printf("이름: %s\n", members[idx].name);
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].name, members[idx].name) == 0) {
            printf("- ");
            printDateFormatted(records[i].date);
            printf(" [%s]\n", wowLabel(records[i].wow));
            printf("  %s\n", records[i].memory);
        }
    }
}
//hbinjectskjfh
void findImpressiveMoment() {
    char nick[MAX_NICKNAME_LEN];
    char wowStr[12];
    int targetWowMin = 0, targetWowMax = 10;

    printf("멤버 닉네임을 입력하세요: ");
    fgets(nick, sizeof(nick), stdin);
    nick[strcspn(nick, "\n")] = 0;

    int idx = findMemberIndexByNickname(nick);
    if (idx == -1) {
        printf("멤버를 찾을 수 없습니다.\n");
        return;
    }

    printf("Wow Effect 입력 (Calm / Exciting / Meaningful): ");
    fgets(wowStr, sizeof(wowStr), stdin);
    wowStr[strcspn(wowStr, "\n")] = 0;

    if (strcmp(wowStr, "Calm") == 0) { targetWowMax = 3; }
    else if (strcmp(wowStr, "Exciting") == 0) { targetWowMin = 4; targetWowMax = 6; }
    else if (strcmp(wowStr, "Meaningful") == 0) { targetWowMin = 7; targetWowMax = 10; }
    else {
        printf("잘못된 입력입니다.\n");
        return;
    }

    printf("[인상 깊은 순간]\n");
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(records[i].name, members[idx].name) == 0 &&
            records[i].wow >= targetWowMin && records[i].wow <= targetWowMax) {
            printDateFormatted(records[i].date);
            printf(" - %s\n", records[i].memory);
        }
    }
}

void createMemory(const char *name, const char *date) {
    if (recordCount >= MAX_RECORDS) {
        printf("더 이상 기록할 수 없습니다.\n");
        return;
    }

    char response[4];
    int tryCount = 0;
    while (tryCount < 2) {
        printf("여정을 기록하시겠습니까? (Y/N): ");
        fgets(response, sizeof(response), stdin);
        if (response[0] == 'y' || response[0] == 'Y') {
            printf("여정을 입력하세요 (30자 이상 70자 이하):\n");
            char mem[MAX_MEMORY_LEN];
            fgets(mem, sizeof(mem), stdin);
            int len = 0; while (mem[len] && mem[len] != '\n') len++;
            if (len < 30 || len > 70) {
                printf("입력 길이가 맞지 않습니다.\n");
                return;
            }
            mem[len] = '\0';

            int wow;
            printf("wow effect (0~10): ");
            scanf("%d", &wow);
            while (getchar() != '\n');

            MemoryRecord *r = &records[recordCount++];
            for (int i = 0; i < MAX_NAME_LEN; i++) r->name[i] = name[i];
            for (int i = 0; i < MAX_MEMORY_LEN; i++) r->memory[i] = mem[i];
            for (int i = 0; i < 9; i++) r->date[i] = date[i];
            r->wow = wow;

            printf("여정이 기록되었습니다.\n");
            return;
        } else if (response[0] == 'n' || response[0] == 'N') {
            printf("1. 기록 출력\n2. 인상 깊은 순간\n3. 상위 메뉴로\n선택: ");
            int sel;
            scanf("%d", &sel);
            while (getchar() != '\n');
            if (sel == 1) displayMemory();
            else if (sel == 2) findImpressiveMoment();
            return;
        } else {
            printf("잘못된 입력입니다.\n");
            tryCount++;
        }
    }
    printf("입력 실패. 상위 메뉴로 돌아갑니다.\n");
}

void buildMemorialPark() {
    printf("[온라인 메모리얼 파크]\n");
    char cheat[4];
    int useCheat = 0;

    printf("치트키를 입력하시겠습니까? (T/t: 사용, 그 외: 현재 시간 사용): ");
    fgets(cheat, sizeof(cheat), stdin);
    if (cheat[0] == 'T' || cheat[0] == 't') useCheat = 1;

    char date[9];
    int hour;
    getCurrentDate(date, &hour, useCheat);

    if (hour < 18 || hour > 22) {
        printf("이 기능은 18시 ~ 22시 사이에만 사용할 수 있습니다.\n");
        return;
    }

    printf("멤버를 선택하세요:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, members[i].name, members[i].nickname);
    }

    int sel;
    printf("번호 선택: ");
    scanf("%d", &sel);
    while (getchar() != '\n');
    if (sel < 1 || sel > MAX_MEMBERS) {
        printf("잘못된 선택입니다.\n");
        return;
    }

    createMemory(members[sel - 1].name, date);
}

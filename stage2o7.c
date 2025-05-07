#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 7
#define MAX_NAME_LEN 30
#define MAX_NICKNAME_LEN 30
#define MAX_SUBMENU_LEN 10
#define MAX_DATA_LEN 100

// Structure for storing member data
typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
} Member;

// Structure for Mentoring data
typedef struct {
    char mentorID[MAX_NICKNAME_LEN];
    char mentorName[MAX_NAME_LEN];
} MentoringData;

// Structure for Trauma data
typedef struct {
    char trauma[MAX_DATA_LEN];
    char consultation[MAX_DATA_LEN];
} TraumaData;

// Structure for Self Reflection data
typedef struct {
    char date[MAX_DATA_LEN];
    char reflectionQuestion[MAX_DATA_LEN];
    char reflectionAnswer[MAX_DATA_LEN];
} SelfReflectionData;

// Structure for Journey Record data
typedef struct {
    char date[MAX_DATA_LEN];
    char content[MAX_DATA_LEN];
    char wowEffect[MAX_DATA_LEN];
} JourneyRecordData;

// Structure for Emotion Diary data
typedef struct {
    char question[MAX_DATA_LEN];
    char answer[MAX_DATA_LEN];
} EmotionDiaryData;

// Structure for storing dashboard data
typedef struct {
    char submenuID[MAX_SUBMENU_LEN]; // Store selected submenu IDs (A, B, D, E, F)
    char memberName[MAX_NAME_LEN];
} Dashboard;

// Predefined member information
Member members[MAX_MEMBERS] = {
    {"김영진", "영진"},
    {"이민호", "민호"},
    {"박지훈", "지훈"},
    {"최수빈", "수빈"},
    {"정하늘", "하늘"},
    {"한서준", "서준"},
    {"오유진", "유진"}
};

// Predefined data for each submenu
MentoringData mentoringData = {"M101", "김영진"};
TraumaData traumaData = {"불안증세", "심리 상담"};
SelfReflectionData selfReflectionData = {"2025년 5월 7일", "오늘의 성찰은 무엇이었나요?", "자기 자신에 대한 깊은 이해가 중요하다."};
JourneyRecordData journeyRecordData = {"2025년 5월 7일", "팀워크의 중요성", "좋은 팀워크는 팀을 강하게 만든다."};
EmotionDiaryData emotionDiaryData = {"현재 감정은 어떠한가요?", "기쁨"};

// Dashboard array to store each member's submenu selection
Dashboard myDashboard[MAX_MEMBERS];

// Function to find member index by nickname
int findMemberIndexByNickname(const char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(members[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to input nickname from the user
void inputNickName(char *nickname) {
    printf("닉네임을 입력하세요: ");
    fgets(nickname, MAX_NICKNAME_LEN, stdin);
    nickname[strcspn(nickname, "\n")] = '\0'; // Remove newline character
}

// Function to select submenus for the dashboard
void selectSubMenu(int idx) {
    char menuID[MAX_SUBMENU_LEN];
    printf("하위 메뉴 목록을 입력하세요 (A, B, D, E, F): ");
    fgets(menuID, MAX_SUBMENU_LEN, stdin);
    menuID[strcspn(menuID, "\n")] = '\0'; // Remove newline character

    // Store the menu IDs in the dashboard structure
    strncpy(myDashboard[idx].submenuID, menuID, MAX_SUBMENU_LEN);
    printf("선택한 메뉴 %s가 대시보드에 저장되었습니다.\n", menuID);
}

// Function to display the dashboard for a selected member
void displayDashboard(int idx) {
    if (strcmp(myDashboard[idx].submenuID, "") == 0) {
        printf("대시보드가 설정되지 않았습니다. 먼저 하위 메뉴를 설정하세요.\n");
        return;
    }

    printf("대시보드 표시: %s\n", members[idx].name);

    // Check selected submenus and display corresponding data
    for (int i = 0; i < strlen(myDashboard[idx].submenuID); i++) {
        char submenuID = myDashboard[idx].submenuID[i];

        switch (submenuID) {
            case 'A':
                printf("멘토링 데이터: 멘토 ID: %s, 멘토 이름: %s\n", mentoringData.mentorID, mentoringData.mentorName);
                break;
            case 'B':
                printf("트라우마 관리: 트라우마: %s, 상담 내용: %s\n", traumaData.trauma, traumaData.consultation);
                break;
            case 'D':
                printf("자기 성찰: 날짜: %s, 성찰 질문: %s, 답변: %s\n", selfReflectionData.date, selfReflectionData.reflectionQuestion, selfReflectionData.reflectionAnswer);
                break;
            case 'E':
                printf("여정 기록: 날짜: %s, 내용: %s, wow 효과: %s\n", journeyRecordData.date, journeyRecordData.content, journeyRecordData.wowEffect);
                break;
            case 'F':
                printf("감정 일기: 질문: %s, 답변: %s\n", emotionDiaryData.question, emotionDiaryData.answer);
                break;
            default:
                printf("알 수 없는 메뉴입니다.\n");
                break;
        }
    }
}

// Main function to show the dashboard menu
void showDashboard() {
    char nickname[MAX_NICKNAME_LEN];
    inputNickName(nickname);

    int idx = findMemberIndexByNickname(nickname);
    if (idx == -1) {
        printf("닉네임에 해당하는 멤버를 찾을 수 없습니다.\n");
        return;
    }

    int choice;
    printf("1. 대시보드 편집\n2. 대시보드 표시\n선택: ");
    scanf("%d", &choice);
    getchar();  // Consume hb the newline left by scanf

    if (choice == 1) {
        selectSubMenu(idx);
    } else if (choice == 2) {
        displayDashboard(idx);
    } else {
        printf("잘못된 선택입니다.\n");
    }
}

int main() {
    showDashboard();
    return 0;
}

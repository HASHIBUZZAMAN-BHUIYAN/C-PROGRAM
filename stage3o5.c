#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_WORDS 5
#define MAX_NAME_LENGTH 50
#define MAX_REGIONS 4

// Enum for Achievement Levels
typedef enum {
    A = 1,
    B,
    C,
    F
} AchievementLevel;

// Structure to store dialect information
typedef struct {
    char dialect[30];  // The dialect word
    char region[30];   // Region where the dialect is used
    char standard_word[30];  // Standard word equivalent
} Dialect;

// Structure for achievement tracking
typedef struct {
    char group_name[MAX_NAME_LENGTH];
    char member_name[MAX_NAME_LENGTH];
    int score;
    AchievementLevel standard_word_achievement;
    AchievementLevel dialect_achievement;
} Achievement;

// List of group members
char group_members[MAX_MEMBERS][MAX_NAME_LENGTH] = {"YJ", "WC", "AR", "JK", "CS"};

// List of dialect words (20 words for 4 regions)
Dialect dialects[MAX_REGIONS * MAX_WORDS] = {
    {"허벅지", "경상도", "허리"}, {"메밀국수", "강원도", "국수"}, {"쌀밥", "전라도", "밥"},
    {"밥상", "전라도", "식탁"}, {"유자", "경상도", "귤"}, {"짬뽕", "강원도", "라면"},
    {"모내기", "경상도", "벼"}, {"포도", "전라도", "과일"}, {"집", "강원도", "가정"},
    {"꽃밭", "경상도", "정원"}, {"걷다", "경상도", "이동하다"}, {"메밀꽃", "강원도", "꽃"},
    {"당기다", "전라도", "끌다"}, {"꽁치", "경상도", "생선"}, {"두부", "강원도", "콩"},
    {"햇볕", "전라도", "햇빛"}, {"포도밭", "경상도", "과수원"}, {"당근", "강원도", "채소"},
    {"소주", "경상도", "술"}, {"오이", "전라도", "채소"}
};

// List to track achievement results
Achievement achievements[MAX_MEMBERS];

// Function to shuffle regions randomly
void shuffleRegions(char regions[MAX_REGIONS][30]) {
    srand(time(NULL));
    for (int i = 0; i < MAX_REGIONS; i++) {
        int j = rand() % MAX_REGIONS;
        char temp[30];
        strcpy(temp, regions[i]);
        strcpy(regions[i], regions[j]);
        strcpy(regions[j], temp);
    }
}

// Function to initialize achievements for each member
void initializeAchievementLevel(Achievement* achievements) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter the name for member %d: ", i + 1);
        strcpy(achievements[i].member_name, group_members[i]);
        strcpy(achievements[i].group_name, "Milieways");
        achievements[i].score = 0;
        achievements[i].standard_word_achievement = F;
        achievements[i].dialect_achievement = F;
    }
}

// Function to display achievement messages
void displayAchievementMessage(AchievementLevel level, const char* type) {
    switch (level) {
        case A:
            printf("당신은 %s 전문가 입니다.\n", type);
            break;
        case B:
            printf("당신의 %s 실력은 훌륭합니다.\n", type);
            break;
        case C:
            printf(" %s에 익숙하네요.\n", type);
            break;
        case F:
            printf("조금 더 공부해서 다시 도전하세요.\n");
            break;
    }
}

// Function for "Standard Word Matching"
void guessStdWord(Achievement* achievement) {
    int correct_count = 0;
    char answer[30];
    char regions[MAX_REGIONS][30] = {"경상도", "강원도", "전라도", "충청도"};

    shuffleRegions(regions);

    printf("표준어 맞추기 시작!\n");
    for (int i = 0; i < MAX_WORDS; i++) {
        printf("사투리: %s (%s 지역)\n", dialects[i].dialect, regions[i % MAX_REGIONS]);
        printf("정답을 입력하세요: ");
        scanf("%s", answer);

        if (strcmp(answer, dialects[i].standard_word) == 0) {
            correct_count++;
        }
    }

    if (correct_count >= 4) {
        achievement->standard_word_achievement = A;
    } else if (correct_count >= 3) {
        achievement->standard_word_achievement = B;
    } else if (correct_count >= 2) {
        achievement->standard_word_achievement = C;
    } else {
        achievement->standard_word_achievement = F;
    }
}

// Function for "Dialect Matching"
void guessDialectWord(Achievement* achievement) {
    int correct_count = 0;
    char answer[30];
    char regions[MAX_REGIONS][30] = {"경상도", "강원도", "전라도", "충청도"};

    shuffleRegions(regions);

    printf("지역 별 사투리 맞추기 시작!\n");
    for (int i = 0; i < MAX_WORDS; i++) {
        printf("표준어: %s\n", dialects[i].standard_word);
        printf("지역을 선택하세요: %s\n", regions[i % MAX_REGIONS]);
        printf("사투리 입력: ");
        scanf("%s", answer);

        if (strcmp(answer, dialects[i].dialect) == 0) {
            correct_count++;
        }
    }

    if (correct_count >= 4) {
        achievement->dialect_achievement = A;
    } else if (correct_count >= 3) {
        achievement->dialect_achievement = B;
    } else if (correct_count >= 2) {
        achievement->dialect_achievement = C;
    } else {
        achievement->dialect_achievement = F;
    }
}

// Function to perform the learning activity
void learnDialect() {
    int choice;
    Achievement selected_achievement;

    initializeAchievementLevel(&selected_achievement);

    printf("학습자 목록:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s\n", i + 1, group_members[i]);
    }

    printf("자신의 이름을 선택하세요 (번호 입력): ");
    scanf("%d", &choice);
    selected_achievement = achievements[choice - 1];

    printf("1. 표준어 맞추기\n");
    printf("2. 지역 별 사투리 맞추기\n");
    printf("선택하세요: ");
    scanf("%d", &choice);
//hb inject
    switch (choice) {
        case 1:
            guessStdWord(&selected_achievement);
            break;
        case 2:
            guessDialectWord(&selected_achievement);
            break;
        default:
            printf("잘못된 선택입니다.\n");
    }

    // Display Achievement Messages
    displayAchievementMessage(selected_achievement.standard_word_achievement, "표준어");
    displayAchievementMessage(selected_achievement.dialect_achievement, "사투리");
}

int main() {
    int choice;

    while (1) {
        printf("\n[II. 훈련 > 3. 언어 및 발음 훈련 > F. 사투리 학습]\n");
        printf("1. 사투리 학습 시작\n");
        printf("2. 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                learnDialect();
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

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 7
#define MAX_NAME_LEN 50
#define MAX_WORKOUTS 10
#define MAX_DAYS 7
#define MAX_TIME_PERIODS 3

// 운동 루틴 데이터 구조체
typedef struct {
    char date[11];         // 날짜 (YYYY-MM-DD)
    char weather[20];      // 날씨
    char timePeriod[20];   // 시간대 (식전, 식후, 공연 직전)
    char workout[50];      // 운동 종류
    int duration;          // 운동 시간 (분)
    int caloriesBurned;    // 소모된 칼로리
} WorkoutRoutine;

WorkoutRoutine workoutRoutines[MAX_WORKOUTS];
int workoutCount = 0;

// 운동 목록
typedef struct {
    int id;
    char name[50];
    int burnCalorie;
} Workout;

// 운동 목록 (for calories burned)
Workout workouts[] = {
    {1, "30분 빠른 걷기 또는 조깅", 200},
    {2, "전신 근력 운동", 250},
    {3, "30분 수영 또는 사이클링", 300},
    {4, "30분 스트레칭 및 요가", 150},
    {5, "30분 무용 또는 에어로빅", 250},
    {6, "테니스, 배드민턴, 댄스", 300},
    {7, "가벼운 산책", 100}
};
int workoutCountList = sizeof(workouts) / sizeof(workouts[0]);

// ==== 운동 루틴 입력 ====
void setMyWorkoutRoutine() {
    if (workoutCount >= MAX_WORKOUTS) {
        printf("❗ 운동 루틴의 최대 입력 개수를 초과했습니다.\n");
        return;
    }

    printf("\n===== 운동 루틴 입력 =====\n");

    // 운동 루틴 입력
    for (int i = workoutCount; i < MAX_WORKOUTS; i++) {
        printf("\n[운동 루틴 %d]\n", i + 1);
        printf("날짜 (YYYY-MM-DD): ");
        scanf("%s", workoutRoutines[i].date);

        printf("날씨: ");
        scanf("%s", workoutRoutines[i].weather);

        printf("시간대 (식전, 식후, 공연 직전): ");
        scanf("%s", workoutRoutines[i].timePeriod);

        printf("운동 종류: ");
        scanf("%s", workoutRoutines[i].workout);

        printf("운동 시간 (분): ");
        scanf("%d", &workoutRoutines[i].duration);

        printf("소모된 칼로리: ");
        scanf("%d", &workoutRoutines[i].caloriesBurned);

        workoutCount++;

        // 입력 완료 후 계속할지 물어보기
        char more;
        printf("계속 입력하시겠습니까? (y/n): ");
        getchar(); // clear buffer
        scanf("%c", &more);
        if (more == 'n' || more == 'N') break;
    }

    // 입력된 운동 루틴 출력
    printf("\n===== 입력된 운동 루틴 =====\n");
    for (int i = 0; i < workoutCount; i++) {
        printf("날짜: %s, 날씨: %s, 시간대: %s, 운동 종류: %s, 운동 시간: %d분, 소모된 칼로리: %d kcal\n",
               workoutRoutines[i].date, workoutRoutines[i].weather,
               workoutRoutines[i].timePeriod, workoutRoutines[i].workout,
               workoutRoutines[i].duration, workoutRoutines[i].caloriesBurned);
    }
}

// ==== 운동 루틴 분석 ====
void statsMyWorkoutRoutine() {
    char date[11];
    char timePeriod[20];

    printf("\n===== 운동 루틴 분석 =====\n");

    // 날짜와 시간대에 따른 운동 데이터 조회
    printf("분석할 날짜 (YYYY-MM-DD): ");
    scanf("%s", date);

    printf("시간대 (식전, 식후, 공연 직전): ");
    scanf("%s", timePeriod);

    printf("\n%s 날짜, %s 시간대의 운동 기록:\n", date, timePeriod);
    int totalCalories = 0;
    for (int i = 0; i < workoutCount; i++) {
        if (strcmp(workoutRoutines[i].date, date) == 0 && strcmp(workoutRoutines[i].timePeriod, timePeriod) == 0) {
            printf(" - 운동 종류: %s, 운동 시간: %d분, 소모된 칼로리: %d kcal\n",
                   workoutRoutines[i].workout, workoutRoutines[i].duration, workoutRoutines[i].caloriesBurned);
            totalCalories += workoutRoutines[i].caloriesBurned;
        }
    }
    printf("총 소모된 칼로리: %d kcal\n", totalCalories);

    // 날짜 별 총 소모 칼로리 계산
    printf("\n날짜별 소모된 칼로리:\n");
    for (int i = 0; i < workoutCount; i++) {
        totalCalories = 0;
        for (int j = 0; j < workoutCount; j++) {
            if (strcmp(workoutRoutines[j].date, workoutRoutines[i].date) == 0) {
                totalCalories += workoutRoutines[j].caloriesBurned;
            }
        }
        printf("날짜: %s, 총 소모 칼로리: %d kcal\n", workoutRoutines[i].date, totalCalories);
    }

    // 가장 많이 수행한 운동 종류
    printf("\n가장 많이 수행한 운동 종류:\n");
    int maxCount = 0;
    char mostPerformedWorkout[50];
    for (int i = 0; i < workoutCount; i++) {
        int count = 0;
        for (int j = 0; j < workoutCount; j++) {
            if (strcmp(workoutRoutines[j].workout, workoutRoutines[i].workout) == 0) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            strcpy(mostPerformedWorkout, workoutRoutines[i].workout);
        }
    }
    printf("가장 많이 수행한 운동 종류: %s\n", mostPerformedWorkout);

    // 가장 오랜 시간 동안 운동을 한 날
    int maxDuration = 0;
    char maxDurationDate[11];
    for (int i = 0; i < workoutCount; i++) {
        int totalDuration = 0;
        for (int j = 0; j < workoutCount; j++) {
            if (strcmp(workoutRoutines[j].date, workoutRoutines[i].date) == 0) {
                totalDuration += workoutRoutines[j].duration;
            }
        }
        if (totalDuration > maxDuration) {
            maxDuration = totalDuration;
            strcpy(maxDurationDate, workoutRoutines[i].date);
        }
    }
    printf("가장 오랜 시간 동안 운동을 한 날: %s (운동 시간: %d분)\n", maxDurationDate, maxDuration);
}

int main() {
    int choice;
    do {
        printf("\n===== 훈련 관리 시스템 =====\n");
        printf("1. [I] 운동 루틴 입력\n");
        printf("2. [J] 운동 루틴 분석\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  // clear hbuffer

        switch (choice) {
            case 1:
                setMyWorkoutRoutine();
                break;
            case 2:
                statsMyWorkoutRoutine();
                break;
            case 0:
                printf("👋 프로그램을 종료합니다.\n");
                break;
            default:
                printf("❗ 잘못된 선택입니다.\n");
        }
    } while (choice != 0);

    return 0;
}

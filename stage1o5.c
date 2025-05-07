#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 7
#define MAX_NAME_LEN 50

typedef struct {
    char food[MAX_NAME_LEN];
    int calorie;
} FoodItem;

typedef struct {
    FoodItem items[MAX_ITEMS];
    int front;
    int rear;
    int size;
} FoodQueue;

// 운동 구조체
typedef struct {
    int id;
    char name[50];
    int burnCalorie;
} Workout;

// 운동 목록
Workout workouts[] = {
    {1, "30분 빠른 걷기 또는 조깅", 200},
    {2, "전신 근력 운동", 250},
    {3, "30분 수영 또는 사이클링", 300},
    {4, "30분 스트레칭 및 요가", 150},
    {5, "30분 무용 또는 에어로빅", 250},
    {6, "테니스, 배드민턴, 댄스", 300},
    {7, "가벼운 산책", 100}
};
int workoutCount = sizeof(workouts) / sizeof(workouts[0]);

// ==== Queue 관련 함수 ====

void initQueue(FoodQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isFull(FoodQueue *q) {
    return q->size == MAX_ITEMS;
}

int isEmpty(FoodQueue *q) {
    return q->size == 0;
}

int enqueue(FoodQueue *q, char food[], int calorie, int *totalCalories) {
    if (isFull(q)) {
        printf("❗ 하루 식단 기록은 최대 7개입니다.\n");
        return 0;
    }
    if (*totalCalories + calorie > 1500) {
        printf("❗ 총 칼로리가 1500을 초과할 수 없습니다. 현재: %d, 추가하려는 칼로리: %d\n", *totalCalories, calorie);
        return 0;
    }
    q->rear = (q->rear + 1) % MAX_ITEMS;
    strcpy(q->items[q->rear].food, food);
    q->items[q->rear].calorie = calorie;
    q->size++;
    *totalCalories += calorie;
    return 1;
}

FoodItem dequeue(FoodQueue *q, int *totalCalories) {
    FoodItem item = q->items[q->front];
    q->front = (q->front + 1) % MAX_ITEMS;
    q->size--;
    *totalCalories -= item.calorie;
    return item;
}

void viewQueue(FoodQueue *q) {
    printf("\n📋 오늘 섭취한 식단 목록 (입력순):\n");
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + i) % MAX_ITEMS;
        printf(" - %s (%d kcal)\n", q->items[idx].food, q->items[idx].calorie);
    }
}

// ==== 기능 1: 식단 기록 ====

int setMyDailyFood(FoodQueue *queue, int *totalCalories) {
    char inputFood[MAX_NAME_LEN];
    int inputCal;
    char more;

    printf("\n🍽️ 오늘의 식단을 입력해주세요 (최대 7개, 총 칼로리 ≤ 1500)\n");
    printf("⚠️ 입력 가능한 칼로리: 100, 150, 200, 250, 300\n");

    do {
        printf("음식 이름: ");
        fgets(inputFood, sizeof(inputFood), stdin);
        inputFood[strcspn(inputFood, "\n")] = '\0';

        printf("칼로리 (100/150/200/250/300): ");
        scanf("%d", &inputCal);
        while (getchar() != '\n'); // clear hbuffer

        if (inputCal != 100 && inputCal != 150 && inputCal != 200 && inputCal != 250 && inputCal != 300) {
            printf("❗ 허용된 칼로리만 입력하세요.\n");
            continue;
        }

        if (!enqueue(queue, inputFood, inputCal, totalCalories)) break;

        printf("✅ 현재 총 칼로리: %d kcal\n", *totalCalories);

        if (isFull(queue) || *totalCalories == 1500) {
            printf("ℹ️ 더 이상 입력할 수 없습니다.\n");
            break;
        }

        printf("➕ 더 입력하시겠습니까? (y/n): ");
        scanf(" %c", &more);
        while (getchar() != '\n');
    } while (more == 'y' || more == 'Y');

    viewQueue(queue);
    printf("✅ 총 섭취 칼로리: %d kcal\n", *totalCalories);
    return *totalCalories;
}

// ==== 기능 2: 칼로리 관리 ====

void mngMyDailyCalorie(FoodQueue *queue, int *totalCalories) {
    int choice;
    if (isEmpty(queue)) {
        printf("❗ 기록된 식단이 없습니다.\n");
        return;
    }

    printf("\n🔥 오늘 어떤 운동을 하셨나요?\n");
    for (int i = 0; i < workoutCount; i++) {
        printf(" %d. %s (%d kcal)\n", workouts[i].id, workouts[i].name, workouts[i].burnCalorie);
    }
    printf("선택 (1-7): ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice < 1 || choice > workoutCount) {
        printf("❗ 잘못된 선택입니다.\n");
        return;
    }

    int burn = workouts[choice - 1].burnCalorie;
    FoodItem frontItem = queue->items[queue->front];

    printf("\n🚴 선택한 운동: %s (소모: %d kcal)\n", workouts[choice - 1].name, burn);
    printf("🥗 식단 기록 앞 항목: %s (%d kcal)\n", frontItem.food, frontItem.calorie);

    if (burn >= frontItem.calorie) {
        FoodItem removed = dequeue(queue, totalCalories);
        printf("✅ \"%s\" 항목이 칼로리 소모로 제거되었습니다.\n", removed.food);
    } else {
        int shortage = frontItem.calorie - burn;
        printf("⚠️ 운동량이 부족합니다. %d kcal 더 소모해야 \"%s\" 항목을 제거할 수 있습니다.\n", shortage, frontItem.food);
    }

    printf("\n📊 남은 식단 기록 및 칼로리:\n");
    viewQueue(queue);
    printf("총 남은 칼로리: %d kcal\n", *totalCalories);
}

int main() {
    FoodQueue foodQueue;
    int totalCalories = 0;
    initQueue(&foodQueue);

    int choice;
    do {
        printf("\n===== 훈련 관리 시스템 =====\n");
        printf("1. [G] 식단 기록\n");
        printf("2. [H] 칼로리 관리\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                setMyDailyFood(&foodQueue, &totalCalories);
                break;
            case 2:
                mngMyDailyCalorie(&foodQueue, &totalCalories);
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

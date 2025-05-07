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
    int top;
} FoodStack;

// Initialize the stack
void initStack(FoodStack *s) {
    s->top = -1;
}

// Check if the stack is full
int isFull(FoodStack *s) {
    return s->top == MAX_ITEMS - 1;
}

// Check if the stack is empty
int isEmpty(FoodStack *s) {
    return s->top == -1;
}

// Push food item onto the stack
int push(FoodStack *s, char food[], int calorie, int *totalCalories) {
    if (isFull(s)) {
        printf("❗ 하루 식단 기록은 최대 7개입니다.\n");
        return 0;
    }
    if (*totalCalories + calorie > 1500) {
        printf("❗ 총 칼로리가 1500을 초과할 수 없습니다. 현재: %d, 추가하려는 칼로리: %d\n", *totalCalories, calorie);
        return 0;
    }
    s->top++;
    strcpy(s->items[s->top].food, food);
    s->items[s->top].calorie = calorie;
    *totalCalories += calorie;
    return 1;
}

// Display the current stack
void viewDailyFood(FoodStack *s) {
    printf("\n📋 오늘 섭취한 식단 목록 (최신순):\n");
    for (int i = s->top; i >= 0; i--) {
        printf(" - %s (%d kcal)\n", s->items[i].food, s->items[i].calorie);
    }
}

// Function to run from the menu
int setMyDailyFood() {
    FoodStack stack;
    initStack(&stack);
    int totalCalories = 0;
    int inputCal;
    char inputFood[MAX_NAME_LEN];
    char more;

    printf("\n🍽️ 오늘의 식단을 입력해주세요 (최대 7개, 총 칼로리 ≤ 1500)\n");
    printf("⚠️ 입력 가능한 칼로리: 100, 150, 200, 250, 300\n");

    do {
        printf("음식 이름: ");
        fgets(inputFood, sizeof(inputFood), stdin);
        inputFood[strcspn(inputFood, "\n")] = '\0'; // remove newline

        printf("칼로리 (100/150/200/250/300): ");
        scanf("%d", &inputCal);
        while (getchar() != '\n'); // clear input buffer

        if (inputCal != 100 && inputCal != 150 && inputCal != 200 && inputCal != 250 && inputCal != 300) {
            printf("❗ 허용된 칼로리만 입력하세요.\n");
            continue;
        }

        if (!push(&stack, inputFood, inputCal, &totalCalories)) {
            break;
        }

        printf("✅ 현재 총 칼로리: %d kcal\n", totalCalories);

        if (isFull(&stack) || totalCalories == 1500) {
            printf("ℹ️ 더 이상 입력할 수 없습니다.\n");
            break;
        }

        printf("➕ 더 입력하시겠습니까? (y/n): ");
        scanf(" %c", &more);
        while (getchar() != '\n'); // clear hb input buffer
    } while (more == 'y' || more == 'Y');

    viewDailyFood(&stack);
    printf("✅ 총 섭취 칼로리: %d kcal\n", totalCalories);
    return totalCalories;
}

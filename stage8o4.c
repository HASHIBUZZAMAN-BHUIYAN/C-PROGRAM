#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HABIT_LENGTH 100
#define REQUIRED_GCC_VERSION 9

// Define linked list nodes for stack and queue
typedef struct Node {
    char habit[MAX_HABIT_LENGTH];
    struct Node *next;
} Node;

// Define stack (bad habits) and queue (good habits)
typedef struct {
    Node *top;
} Stack;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

// Function to create a new node
Node* createNode(const char *habit) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        strncpy(newNode->habit, habit, MAX_HABIT_LENGTH);
        newNode->next = NULL;
    }
    return newNode;
}

// Stack (bad habit) operations
void initStack(Stack *stack) {
    stack->top = NULL;
}

int isStackEmpty(Stack *stack) {
    return stack->top == NULL;
}

void pushStack(Stack *stack, const char *habit) {
    Node *newNode = createNode(habit);
    if (newNode) {
        newNode->next = stack->top;
        stack->top = newNode;
    }
}

void popStack(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("No bad habits to remove.\n");
        return;
    }
    Node *temp = stack->top;
    stack->top = stack->top->next;
    printf("Removed bad habit: %s\n", temp->habit);
    free(temp);
}

void printStack(Stack *stack) {
    Node *current = stack->top;
    while (current) {
        printf("%s\n", current->habit);
        current = current->next;
    }
}

// Queue (good habit) operations
void initQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void enqueueQueue(Queue *queue, const char *habit) {
    Node *newNode = createNode(habit);
    if (newNode) {
        if (isQueueEmpty(queue)) {
            queue->front = queue->rear = newNode;
        } else {
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    }
}

void dequeueQueue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("No good habits to display.\n");
        return;
    }
    Node *temp = queue->front;
    queue->front = queue->front->next;
    printf("Revealed good habit: %s\n", temp->habit);
    free(temp);
}

void printQueue(Queue *queue) {
    Node *current = queue->front;
    while (current) {
        printf("%s\n", current->habit);
        current = current->next;
    }
}

// Function to load habits from file and initialize the stack and queue
void loadHabitsFromFile(Stack *badHabitStack, Queue *goodHabitQueue) {
    FILE *file = fopen("habit.txt", "r");
    if (!file) {
        printf("Error opening habit.txt\n");
        return;
    }

    char habit[MAX_HABIT_LENGTH];
    while (fgets(habit, MAX_HABIT_LENGTH, file)) {
        // Remove newline character
        habit[strcspn(habit, "\n")] = '\0';

        // If the habit starts with "-" it's a bad habit, otherwise it's a good habit
        if (habit[0] == '-') {
            pushStack(badHabitStack, habit + 1); // Remove the '-' for bad habits
        } else {
            enqueueQueue(goodHabitQueue, habit);
        }
    }

    fclose(file);
}

// Function to check GCC version at compile-time (Bonus)
#if __GNUC__ < REQUIRED_GCC_VERSION
    #error "컴파일러 버전이 맞지 않아 더 이상 컴파일을 진행할 수 없습니다."
#endif

// Main function to interact with the user
void promoteGoodHabit() {
    Stack badHabitStack;
    Queue goodHabitQueue;

    initStack(&badHabitStack);
    initQueue(&goodHabitQueue);
    
    loadHabitsFromFile(&badHabitStack, &goodHabitQueue);

    int choice;
    while (1) {
        printf("\n[1] 나쁜 습관 제거\n[2] 좋은 습관 드러내기\n[3] 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);
        getchar(); // Consume newline hb character

        if (choice == 1) {
            // Remove the most recent bad habit
            popStack(&badHabitStack);
            printStack(&badHabitStack);
        } else if (choice == 2) {
            // Display and remove the oldest good habit
            dequeueQueue(&goodHabitQueue);
            printQueue(&goodHabitQueue);
        } else if (choice == 3) {
            break;
        } else {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
        }
    }
}

int main() {
    promoteGoodHabit();
    return 0;
}

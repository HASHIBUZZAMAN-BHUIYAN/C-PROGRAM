#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCESSORY 10
#define MAX_NAME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100

// 액세서리 구조체 정의
typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} Accessory;

// 원형 큐 구조체 정의
typedef struct {
    Accessory* queue[MAX_ACCESSORY];
    int front;
    int rear;
    int size;
    int capacity;
} CircularQueue;

// 원형 큐 초기화 함수
CircularQueue* createQueue(int capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// 큐가 비었는지 확인하는 함수
int isEmpty(CircularQueue* queue) {
    return queue->size == 0;
}

// 큐가 가득 찼는지 확인하는 함수
int isFull(CircularQueue* queue) {
    return queue->size == queue->capacity;
}

// 큐에 액세서리 추가 함수
void enqueue(CircularQueue* queue, Accessory* accessory) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot add more accessories.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->queue[queue->rear] = accessory;
    queue->size++;
}

// 큐에서 액세서리 제거 함수
Accessory* dequeue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot remove any accessories.\n");
        return NULL;
    }
    Accessory* accessory = queue->queue[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return accessory;
}

// 큐 상태 출력 함수
void printQueue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Accessories in the queue:\n");
    int i = queue->front;
    for (int j = 0; j < queue->size; j++) {
        printf("Name: %s, Description: %s\n", queue->queue[i]->name, queue->queue[i]->description);
        i = (i + 1) % queue->capacity;
    }
}

// 액세서리 파일 읽기 함수
void loadAccessories(const char* filename, Accessory* accessories[], int* totalAccessories) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    while (fscanf(file, "%s %99[^\n]\n", accessories[*totalAccessories]->name, accessories[*totalAccessories]->description) != EOF) {
        *totalAccessories += 1;
        if (*totalAccessories >= MAX_ACCESSORY) break; // Prevent overflow
    }
    fclose(file);
}

// 액세서리 선택 및 큐에 추가
void applyAccessory() {
    Accessory* accessories[MAX_ACCESSORY];
    int totalAccessories = 0;

    // 액세서리 로드
    for (int i = 0; i < MAX_ACCESSORY; i++) {
        accessories[i] = (Accessory*)malloc(sizeof(Accessory));
    }
    loadAccessories("accessory.txt", accessories, &totalAccessories);

    if (totalAccessories < 4) {
        printf("Not enough accessories to choose from.\n");
        return;
    }//hb inject

    // 원형 큐 생성
    CircularQueue* queue = createQueue(6);

    // 4~6개의 액세서리를 랜덤으로 선택해서 큐에 넣기
    srand(time(NULL));
    for (int i = 0; i < 6; i++) {
        int randIndex = rand() % totalAccessories;
        enqueue(queue, accessories[randIndex]);
    }

    // 큐 출력
    printQueue(queue);

    // 메모리 해제
    for (int i = 0; i < totalAccessories; i++) {
        free(accessories[i]);
    }
}

// 메뉴 시스템
void menu() {
    int choice;
    while (1) {
        printf("\n[Menu]\n");
        printf("1. Apply Accessory\n");
        printf("2. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                applyAccessory();
                break;
            case 2:
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}

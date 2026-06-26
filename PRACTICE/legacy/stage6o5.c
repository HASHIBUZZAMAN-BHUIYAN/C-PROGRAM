#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MAKEUP_TYPES 10
#define MAX_NAME_LENGTH 50
#define MAX_QUEUE_SIZE 5
#define MAX_LINE_LENGTH 100

// 메이크업 유형 구조체 정의
typedef struct {
    char type[MAX_NAME_LENGTH];  // 메이크업 유형
    char description[MAX_NAME_LENGTH];  // 메이크업 설명
} MakeupType;

// 연습생 구조체 정의
typedef struct {
    int id;  // 연습생 ID
    int arrivalTime;  // 도착 시간
    char makeupType[MAX_NAME_LENGTH];  // 선택된 메이크업 유형
    int duration;  // 소요 시간
    int waitTime;  // 대기 시간
} Trainee;

// 원형 큐 구조체 정의
typedef struct {
    Trainee trainees[MAX_QUEUE_SIZE];
    int front, rear, size;
} CircularQueue;

// 메이크업 유형 파일을 읽어서 메이크업 목록 초기화
void loadMakeupTypes(const char *filename, MakeupType makeupTypes[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    int i = 0;
    while (fscanf(file, "%s %[^\n]\n", makeupTypes[i].type, makeupTypes[i].description) != EOF) {
        i++;
        if (i >= MAX_MAKEUP_TYPES) break;
    }
    fclose(file);
}

// 원형 큐 초기화
void initQueue(CircularQueue *queue) {
    queue->front = queue->rear = -1;
    queue->size = 0;
}

// 큐가 비었는지 확인
int isEmpty(CircularQueue *queue) {
    return queue->size == 0;
}

// 큐가 가득 찼는지 확인
int isFull(CircularQueue *queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

// 큐에 연습생 추가
void enqueue(CircularQueue *queue, Trainee trainee) {
    if (isFull(queue)) {
        printf("Queue is full, cannot add more trainees.\n");
        return;
    }
    if (queue->rear == -1) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    }
    queue->trainees[queue->rear] = trainee;
    queue->size++;
}

// 큐에서 연습생 제거
Trainee dequeue(CircularQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty, no trainees to process.\n");
        Trainee emptyTrainee = {0};
        return emptyTrainee;
    }
    Trainee trainee = queue->trainees[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    }
    queue->size--;
    return trainee;
}

// 난수 생성 함수 (0~10 사이)
int generateRandomNumber() {
    return rand() % 11;
}

// 메이크업 테스트 함수
void testMakeUp(CircularQueue *queue, MakeupType makeupTypes[], int makeupCount) {
    int currentTime = 0;
    int totalWaitTime = 0;
    int maleWaitTime = 0, femaleWaitTime = 0;
    int maleCount = 0, femaleCount = 0;
    
    while (currentTime <= 60) {  // 60분간 운영
        if (generateRandomNumber() < 3) {  // 3보다 작은 값이 나오면 연습생 추가
            Trainee trainee;
            trainee.id = currentTime + 1;
            trainee.arrivalTime = currentTime;
            trainee.waitTime = currentTime;
            strcpy(trainee.makeupType, makeupTypes[rand() % makeupCount].type);
            trainee.duration = rand() % 4 + 3;  // 소요 시간: 3~6분

            if (trainee.id % 2 == 0) {  // 여성 연습생
                femaleCount++;
                femaleWaitTime += trainee.waitTime;
            } else {  // 남성 연습생
                maleCount++;
                maleWaitTime += trainee.waitTime;
            }

            // 연습생 큐에 추가
            enqueue(queue, trainee);
            printf("Trainee %d entered at time %d. Makeup: %s, Duration: %d minutes\n",
                trainee.id, trainee.arrivalTime, trainee.makeupType, trainee.duration);
        }

        // 큐에서 연습생 처리 (소요 시간만큼 진행)
        if (!isEmpty(queue)) {
            Trainee trainee = dequeue(queue);
            currentTime += trainee.duration;  // 메이크업 테스트 소요 시간 추가
            trainee.waitTime = currentTime - trainee.arrivalTime;  // 대기 시간 계산
            printf("Trainee %d completed makeup at time %d. Waited for %d minutes.\n",
                trainee.id, currentTime, trainee.waitTime);
            totalWaitTime += trainee.waitTime;
        }

        currentTime++;
    }

    // 결과 출력
    printf("\n--- Makeup Test Summary ---\n");
    printf("Total wait time: %d minutes\n", totalWaitTime);
    if (maleCount > 0) {
        printf("Average male wait time: %.2f minutes\n", (float)maleWaitTime / maleCount);
    }
    if (femaleCount > 0) {
        printf("Average female wait time: %.2f minutes\n", (float)femaleWaitTime / femaleCount);
    }
    printf("Total trainees processed: %d\n", maleCount + femaleCount);
}

// 메뉴 함수
void menu() {
    MakeupType makeupTypes[MAX_MAKEUP_TYPES];
    int makeupCount = 0;
    CircularQueue queue;

    // 메이크업 유형 파일에서 데이터 로드
    loadMakeupTypes("makeup.txt", makeupTypes);
    makeupCount = MAX_MAKEUP_TYPES;  // 10개의 메이크업 유형
//hb inject
    // 큐 초기화
    initQueue(&queue);

    int choice;
    while (1) {
        printf("\n[Menu]\n");
        printf("1. Start Makeup Test\n");
        printf("2. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                testMakeUp(&queue, makeupTypes, makeupCount);
                break;
            case 2:
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    srand(time(NULL));  // 난수 시드 설정
    menu();
    return 0;
}

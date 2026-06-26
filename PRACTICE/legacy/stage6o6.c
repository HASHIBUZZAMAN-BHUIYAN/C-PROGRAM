#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUCKETS 100
#define MAX_NAME_LENGTH 100
#define MAX_QUEUE_SIZE 10
#define MAX_LINE_LENGTH 200

// 버킷 구조체 정의
typedef struct {
    int id;                // 버킷 ID
    char content[MAX_NAME_LENGTH];  // 버킷 내용
} Bucket;

// 원형 큐 구조체 정의
typedef struct {
    Bucket buckets[MAX_QUEUE_SIZE];
    int front, rear, size;
} CircularQueue;

// 동적 배열을 위한 버킷 리스트 구조체
typedef struct {
    Bucket *buckets;
    int size;
    int capacity;
} BucketList;

// 버킷 리스트를 초기화하는 함수
void initBucketList(BucketList *list) {
    list->size = 0;
    list->capacity = 10;
    list->buckets = (Bucket *)malloc(list->capacity * sizeof(Bucket));
    if (!list->buckets) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

// 버킷 리스트 크기를 늘리는 함수
void resizeBucketList(BucketList *list) {
    list->capacity *= 2;
    list->buckets = (Bucket *)realloc(list->buckets, list->capacity * sizeof(Bucket));
    if (!list->buckets) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

// 버킷을 리스트에 추가하는 함수
void addBucket(BucketList *list, int id, const char *content) {
    if (list->size == list->capacity) {
        resizeBucketList(list);
    }
    list->buckets[list->size].id = id;
    strncpy(list->buckets[list->size].content, content, MAX_NAME_LENGTH);
    list->size++;
}

// 버킷 리스트 파일에서 버킷들을 읽어오는 함수
void loadBucketListFromFile(const char *filename, BucketList *list) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open the file %s\n", filename);
        return;
    }

    int id;
    char content[MAX_NAME_LENGTH];
    while (fscanf(file, "%d,%[^\n]\n", &id, content) != EOF) {
        addBucket(list, id, content);
    }

    fclose(file);
}

// 원형 큐 초기화 함수
void initQueue(CircularQueue *queue) {
    queue->front = queue->rear = -1;
    queue->size = 0;
}

// 큐가 비었는지 확인하는 함수
int isQueueEmpty(CircularQueue *queue) {
    return queue->size == 0;
}

// 큐가 가득 찼는지 확인하는 함수
int isQueueFull(CircularQueue *queue) {
    return queue->size == MAX_QUEUE_SIZE;
}

// 큐에 항목 추가 함수
void enqueue(CircularQueue *queue, Bucket bucket) {
    if (isQueueFull(queue)) {
        printf("Queue is full, cannot add more completed buckets.\n");
        return;
    }
    if (queue->rear == -1) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    }
    queue->buckets[queue->rear] = bucket;
    queue->size++;
}

// 큐에서 항목 제거 함수
Bucket dequeue(CircularQueue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty, no completed bucket to process.\n");
        Bucket emptyBucket = {0};
        return emptyBucket;
    }
    Bucket bucket = queue->buckets[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    }
    queue->size--;
    return bucket;
}

// 버킷 리스트 출력 함수
void printBucketList(BucketList *list) {
    printf("\n--- Bucket List ---\n");
    for (int i = 0; i < list->size; i++) {
        printf("ID: %d, Content: %s\n", list->buckets[i].id, list->buckets[i].content);
    }
}

// 완료된 버킷 처리 함수
void markBucketAsCompleted(BucketList *list, CircularQueue *queue, int id) {
    int index = -1;
    for (int i = 0; i < list->size; i++) {
        if (list->buckets[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Bucket with ID %d not found!\n", id);
        return;
    }

    // 완료된 버킷을 큐에 추가
    enqueue(queue, list->buckets[index]);

    // 완료된 버킷을 리스트에서 제거
    for (int i = index; i < list->size - 1; i++) {
        list->buckets[i] = list->buckets[i + 1];
    }
    list->size--;
}

// 버킷 검색 함수 (선형 탐색)
void searchBucket(BucketList *list, const char *query) {
    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (strstr(list->buckets[i].content, query) != NULL || list->buckets[i].id == atoi(query)) {
            printf("Found Bucket - ID: %d, Content: %s\n", list->buckets[i].id, list->buckets[i].content);
            found = 1;
        }
    }
    if (!found) {
        printf("No bucket found with the query '%s'.\n", query);
    }
}

// 메인 기능 함수
void makeBucketList() {
    BucketList bucketList;
    CircularQueue completedQueue;
    initBucketList(&bucketList);
    initQueue(&completedQueue);

    // 버킷 리스트 파일에서 데이터 읽기
    loadBucketListFromFile("bucket_list.csv", &bucketList);

    int choice;//hb inject
    while (1) {
        printf("\n[Menu]\n");
        printf("1. Print Bucket List\n");
        printf("2. Mark Bucket as Completed\n");
        printf("3. Print Completed Buckets\n");
        printf("4. Search Bucket\n");
        printf("5. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printBucketList(&bucketList);
                break;
            case 2:
                {
                    int id;
                    printf("Enter Bucket ID to mark as completed: ");
                    scanf("%d", &id);
                    markBucketAsCompleted(&bucketList, &completedQueue, id);
                }
                break;
            case 3:
                printf("\n--- Completed Buckets ---\n");
                while (!isQueueEmpty(&completedQueue)) {
                    Bucket bucket = dequeue(&completedQueue);
                    printf("ID: %d, Content: %s\n", bucket.id, bucket.content);
                }
                break;
            case 4:
                {
                    char query[MAX_NAME_LENGTH];
                    printf("Enter Bucket ID or content to search: ");
                    scanf(" %[^\n]", query);
                    searchBucket(&bucketList, query);
                }
                break;
            case 5:
                free(bucketList.buckets);
                return;
            default:
                printf("Invalid option, try again.\n");
        }
    }
}

int main() {
    makeBucketList();
    return 0;
}

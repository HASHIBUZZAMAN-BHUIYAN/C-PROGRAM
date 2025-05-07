#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_QUEUE_SIZE 10

// ---------- Circular Queue ----------
typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front, rear;
    int size;
} CircularQueue;

void initQueue(CircularQueue* q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int isFull(CircularQueue* q) {
    return q->size == MAX_QUEUE_SIZE;
}

int isEmpty(CircularQueue* q) {
    return q->size == 0;
}

void enqueue(CircularQueue* q, int item) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue %d\n", item);
        return;
    }
    q->data[q->rear] = item;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->size++;
}

int dequeue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }
    int item = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return item;
}

void printQueue(CircularQueue* q) {
    printf("Queue: ");
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + i) % MAX_QUEUE_SIZE;
        printf("%d ", q->data[idx]);
    }
    printf("\n");
}

// ---------- Linked List ----------
typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* createNode(int val) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int val) {
    Node* newNode = createNode(val);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
}

void printList(Node* head) {
    printf("Delivered Messages (Linked List): ");
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int countValidPairs(Node* head) {
    int count = 0;
    Node* curr = head;
    while (curr && curr->next) {
        int sum = curr->value + curr->next->value;
        if (sum >= 24 && sum <= 42) count++;
        curr = curr->next;
    }
    return count;
}

// ---------- Main hb Logic ----------
void bufferMsgSpeed() {
    int msgCount;
    CircularQueue queue;
    Node* deliveredMsgs = NULL;

    initQueue(&queue);
    srand((unsigned int)time(NULL));

    printf("Enter number of messages to process: ");
    scanf("%d", &msgCount);
    assert(msgCount > 0);

    for (int i = 0; i < msgCount; i++) {
        int randMsg = rand() % 100 + 1;

        printf("Generated Message: %d\n", randMsg);

        if (randMsg % 5 == 0) {
            printf("Received good message. ");
            enqueue(&queue, randMsg);
            printQueue(&queue);
        }

        if (randMsg % 10 == 0) {
            printf("Message %d is being delivered.\n", randMsg);
            int delivered = dequeue(&queue);
            if (delivered != -1) {
                appendNode(&deliveredMsgs, delivered);
                printQueue(&queue);
            }
        }
    }

    printList(deliveredMsgs);
    int pairs = countValidPairs(deliveredMsgs);
    printf("Valid adjacent value pairs (sum in 24~42): %d\n", pairs);
}

// ---------- Menu and Main ----------
void showMenu() {
    int choice;
    do {
        printf("\n--- 팬 소통 메뉴 ---\n");
        printf("1. 팬 메시지 버퍼\n");
        printf("0. 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bufferMsgSpeed();
                break;
            case 0:
                printf("종료합니다.\n");
                break;
            default:
                printf("잘못된 선택입니다.\n");
        }
    } while (choice != 0);
}

int main() {
    showMenu();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FASHION 100
#define MAX_NAME_LENGTH 50
#define MAX_FASHION_STYLE_LENGTH 100
#define MAX_MEMBERS 50

// 1. 최악의 패션 스타일을 저장하는 구조체
typedef struct {
    char gender[10];  // 'Male' or 'Female'
    char fashion_style[MAX_FASHION_STYLE_LENGTH];
    char reason[MAX_FASHION_STYLE_LENGTH];
} FashionStyle;

// 2. 덱(Deque) 자료 구조
typedef struct DequeNode {
    FashionStyle data;
    struct DequeNode* next;
    struct DequeNode* prev;
} DequeNode;

typedef struct {
    DequeNode* front;
    DequeNode* rear;
    int size;
    int capacity;
} Deque;

// 3. 밀리웨이즈 멤버 구조체
typedef struct {
    char nickname[MAX_NAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
} Member;

// 전역 변수
FashionStyle worstFashionStyles[MAX_FASHION];
int totalWorstFashionStyles = 0;
Member milliwaysMembers[MAX_MEMBERS];
int totalMembers = 0;

// 덱 초기화
Deque* createDeque(int capacity) {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = deque->rear = NULL;
    deque->size = 0;
    deque->capacity = capacity;
    return deque;
}

// 덱에 항목 추가 (앞 또는 뒤)
void addToDeque(Deque* deque, FashionStyle style, int atFront) {
    if (deque->size == deque->capacity) {
        printf("Deque is full.\n");
        return;
    }
    DequeNode* newNode = (DequeNode*)malloc(sizeof(DequeNode));
    newNode->data = style;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (atFront) {
        // 덱 앞에 추가
        if (deque->front == NULL) {
            deque->front = deque->rear = newNode;
        } else {
            newNode->next = deque->front;
            deque->front->prev = newNode;
            deque->front = newNode;
        }
    } else {
        // 덱 뒤에 추가
        if (deque->rear == NULL) {
            deque->front = deque->rear = newNode;
        } else {
            newNode->prev = deque->rear;
            deque->rear->next = newNode;
            deque->rear = newNode;
        }
    }
    deque->size++;
}

// 덱에서 항목 제거
FashionStyle removeFromDeque(Deque* deque) {
    if (deque->size == 0) {
        printf("Deque is empty.\n");
        exit(1);
    }
    DequeNode* temp = deque->front;
    FashionStyle style = temp->data;
    deque->front = deque->front->next;
    if (deque->front != NULL) {
        deque->front->prev = NULL;
    }
    free(temp);
    deque->size--;
    return style;
}

// 덱 출력
void printDeque(Deque* deque) {
    DequeNode* temp = deque->front;
    while (temp != NULL) {
        printf("Fashion Style: %s\n", temp->data.fashion_style);
        temp = temp->next;
    }
}

// 4. 최악의 패션 스타일 데이터를 로드하는 함수
void loadWorstFashionStyles(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    while (fscanf(file, "%s %99[^\n] %99[^\n]\n", worstFashionStyles[totalWorstFashionStyles].gender,
        worstFashionStyles[totalWorstFashionStyles].fashion_style, worstFashionStyles[totalWorstFashionStyles].reason) != EOF) {
        totalWorstFashionStyles++;
        if (totalWorstFashionStyles >= MAX_FASHION) break; // Prevent overflow
    }
    fclose(file);
}

// 5. 밀리웨이즈 멤버 데이터를 로드하는 함수
void loadMembers(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    while (fscanf(file, "%49s %49s %49s\n", milliwaysMembers[totalMembers].nickname,
        milliwaysMembers[totalMembers].first_name, milliwaysMembers[totalMembers].last_name) != EOF) {
        totalMembers++;
        if (totalMembers >= MAX_MEMBERS) break;
    }
    fclose(file);
}

// 6. 사용자 입력을 처리하여 덱에 패션 스타일 추가
void understandFashion() {
    char nickname[MAX_NAME_LENGTH];
    printf("Enter nickname of member: ");
    scanf("%s", nickname);

    // 사용자 닉네임이 유효한지 확인
    int memberIndex = -1;
    for (int i = 0; i < totalMembers; i++) {
        if (strcmp(milliwaysMembers[i].nickname, nickname) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Invalid nickname. Exiting.\n");
        return;
    }//hb inject

    // 성별에 맞는 최악의 패션 스타일 목록 가져오기
    char gender[10];
    strcpy(gender, milliwaysMembers[memberIndex].first_name);
    Deque* deque = createDeque(10); // 덱의 크기 설정 (예: 10)

    // 성별에 맞는 패션 스타일 필터링
    for (int i = 0; i < totalWorstFashionStyles; i++) {
        if (strcmp(worstFashionStyles[i].gender, gender) == 0) {
            int atFront;
            printf("Fashion Style: %s\n", worstFashionStyles[i].fashion_style);
            printf("Add to front (1) or back (0): ");
            scanf("%d", &atFront);

            // 덱에 추가
            addToDeque(deque, worstFashionStyles[i], atFront);
        }
    }

    // 덱 출력
    printf("\nDeque content:\n");
    printDeque(deque);
    printf("Congratulations! The deque has been filled.\n");
}

// 7. 메뉴 및 프로그램 실행
void menu() {
    int choice;
    while (1) {
        printf("\n[Menu]\n");
        printf("1. Understand Fashion\n");
        printf("2. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                understandFashion();
                break;
            case 2:
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

int main() {
    // 파일 로드
    loadWorstFashionStyles("fashion.txt");
    loadMembers("milliways_member.csv");

    // 메뉴 실행
    menu();

    return 0;
}

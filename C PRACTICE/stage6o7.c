#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AIRPORTS 10
#define MAX_PATH_LENGTH 100
#define MAX_TICKETS 100

// 티켓 정보 구조체 정의
typedef struct {
    char from[4];  // 출발지 공항 (3자리)
    char to[4];    // 도착지 공항 (3자리)
} Ticket;

// 여행 경로를 저장할 동적 배열 리스트 구조체
typedef struct {
    char **path;   // 공항 경로를 저장
    int size;      // 경로 길이
    int capacity;  // 동적 배열 크기
} TravelPath;

// 동적 배열 리스트 초기화
void initTravelPath(TravelPath *tp) {
    tp->size = 0;
    tp->capacity = 10;
    tp->path = (char **)malloc(tp->capacity * sizeof(char *));
    if (!tp->path) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

// 동적 배열 리스트 크기 변경
void resizeTravelPath(TravelPath *tp) {
    tp->capacity *= 2;
    tp->path = (char **)realloc(tp->path, tp->capacity * sizeof(char *));
    if (!tp->path) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

// 동적 배열 리스트에 경로 추가
void addPath(TravelPath *tp, const char *airport) {
    if (tp->size == tp->capacity) {
        resizeTravelPath(tp);
    }
    tp->path[tp->size] = (char *)malloc(4 * sizeof(char));  // 3자 공항 코드 + null terminator
    strncpy(tp->path[tp->size], airport, 4);
    tp->size++;
}

// 동적 배열 리스트 메모리 해제
void freeTravelPath(TravelPath *tp) {
    for (int i = 0; i < tp->size; i++) {
        free(tp->path[i]);
    }
    free(tp->path);
}

// 티켓 파일 읽어오는 함수
int loadTickets(const char *filename, Ticket **tickets) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open the file %s\n", filename);
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %s\n", (*tickets)[count].from, (*tickets)[count].to) != EOF) {
        count++;
        if (count >= MAX_TICKETS) break;
    }

    fclose(file);
    return count;
}

// 경로를 찾는 함수 (DFS)
int compareTickets(const void *a, const void *b) {
    return strcmp(((Ticket *)a)->to, ((Ticket *)b)->to);
}

int dfs(Ticket *tickets, int ticketCount, TravelPath *tp, char *currentAirport, int *usedTickets) {
    // 여행 경로에 공항 추가
    addPath(tp, currentAirport);

    // 모든 항공권을 사용했으면 경로를 완성한 것
    if (tp->size == ticketCount + 1) {
        return 1;
    }

    // 현재 공항에서 떠나는 티켓을 모두 찾아서 DFS 진행
    for (int i = 0; i < ticketCount; i++) {
        if (!usedTickets[i] && strcmp(tickets[i].from, currentAirport) == 0) {
            // 티켓 사용 마킹//hb inject
            usedTickets[i] = 1;
            // DFS 호출
            if (dfs(tickets, ticketCount, tp, tickets[i].to, usedTickets)) {
                return 1;
            }
            // 백트래킹
            usedTickets[i] = 0;
        }
    }

    // 경로가 완성되지 않으면 돌아가야 하므로 경로에서 마지막 공항을 제거
    tp->size--;
    return 0;
}

// 여행 경로 출력 함수
void printTravelPath(TravelPath *tp) {
    for (int i = 0; i < tp->size; i++) {
        printf("%s ", tp->path[i]);
    }
    printf("\n");
}

// 계획된 해외 훈련 경로를 찾는 함수
void planOverseasTraining() {
    Ticket tickets[MAX_TICKETS];
    TravelPath tp;
    int usedTickets[MAX_TICKETS] = {0}; // 티켓 사용 여부 체크
    int ticketCount;

    // 동적 배열 리스트 초기화
    initTravelPath(&tp);

    // 티켓 파일 로딩
    ticketCount = loadTickets("tickets.txt", &tickets);
    if (ticketCount == 0) {
        printf("No tickets to process.\n");
        return;
    }

    // 티켓을 알파벳 순으로 정렬
    qsort(tickets, ticketCount, sizeof(Ticket), compareTickets);

    // ICN에서 시작
    dfs(tickets, ticketCount, &tp, "ICN", usedTickets);

    // 경로 출력
    printTravelPath(&tp);

    // 메모리 해제
    freeTravelPath(&tp);
}

int main() {
    planOverseasTraining();
    return 0;
}

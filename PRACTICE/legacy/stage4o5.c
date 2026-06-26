#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MASKS 10
#define MAX_GAME_ROUNDS 5
#define MAX_TITLE_LENGTH 100

// 복면과 노래 매칭을 위한 자료 구조
typedef struct {
    int maskId;
    char maskName[MAX_TITLE_LENGTH];
    char songTitle[MAX_TITLE_LENGTH];
} MaskSongPair;

// 게임의 복면과 노래 매칭 기초 데이터
MaskSongPair maskSongPairs[MAX_MASKS] = {
    {1, "곰발바닥", "이 밤의 끝을 잡고"},
    {2, "주윤발", "단발머리"},
    {3, "달마시안", "나의 옛날 이야기"},
    {4, "천둥 호랑이", "Love Affair"},
    {5, "개구리 왕자", "지친 하루"},
    {6, "거북이", "그녀를 사랑해줘요"},
    {7, "코끼리", "첫 인상"},
    {8, "뱀파이어", "지금은 알 수 없어"},
    {9, "햄스터", "내 얘길 들어봐"},
    {10, "돌고래", "못다 핀 꽃 한 송이"}
};

// 게임 점수 계산 함수
void calculateScore(int correctAnswers, int timeTaken) {
    int score = correctAnswers * 10;

    if (timeTaken <= 30) {
        score += 5;  // 보너스 5점
    } else if (timeTaken <= 60) {
        score += 0;  // 1분 이내 -> 추가 점수 없음
    } else {
        score -= 5;  // 1분 초과 -> -5점
    }

    printf("최종 점수: %d\n", score);
}

// 게임 스플래시 화면 출력
void printGameInstructions() {
    printf("\n복면 무대 연습 준비 게임\n");
    printf("게임 제목: 복면 노래 매칭\n");
    printf("게임 방법: \n");
    printf("1. 무작위로 선택된 복면과 그에 맞는 노래 제목을 맞추는 게임입니다.\n");
    printf("2. 복면의 이름은 16진수 코드로 변환되어 표시됩니다.\n");
    printf("3. 5개의 복면과 노래 매칭에 대해 답을 입력하십시오.\n");
    printf("4. 노래 제목을 입력할 때 공백은 무시됩니다.\n");
    printf("5. 총점을 계산하고, 제한 시간 내에 해결할 경우 추가 점수가 주어집니다.\n");
    printf("\n게임 시작!\n");
}

// 16진수로 복면 ID 출력
void printMask(int maskId) {
    printf("복면 코드: 0x%X\n", maskId);
}

// 시간 계산 함수 (초 단위로 경과 시간 계산)
int getElapsedTime(time_t startTime) {
    time_t endTime = time(NULL);
    return (int)(endTime - startTime);
}

// 복면과 노래 매칭 게임
void prepareMaskedStage() {
    int correctAnswers = 0;
    time_t startTime, endTime;

    // 게임 시작 시간 기록
    startTime = time(NULL);

    printGameInstructions();

    // 5개의 무작위 복면과 노래 매칭
    for (int i = 0; i < MAX_GAME_ROUNDS; i++) {
        int randomIndex = rand() % MAX_MASKS;  // 0부터 9까지 랜덤 인덱스

        int maskId = maskSongPairs[randomIndex].maskId;
        char correctSong[MAX_TITLE_LENGTH];
        strcpy(correctSong, maskSongPairs[randomIndex].songTitle);

        // 복면 ID를 16진수 코드로 변환하여 출력
        printMask(maskId);

        // 사용자로부터 노래 제목 입력 받기
        char userSong[MAX_TITLE_LENGTH];
        printf("매칭된 노래 제목을 입력하세요 (공백은 무시): ");
        scanf(" %[^\n]", userSong);

        // 공백 제거
        for (int j = 0; userSong[j]; j++) {
            if (userSong[j] == ' ') {
                for (int k = j; userSong[k]; k++) {
                    userSong[k] = userSong[k + 1];
                }
                j--;  // 공백을 제거한 뒤, j를 하나 감소시켜서 잘못된 인덱스를 방지
            }
        }

        // 노래 제목을 공백을 제거한 형태로 비교
        if (strcasecmp(userSong, correctSong) == 0) {
            correctAnswers++;
            printf("정답! 10점을 얻었습니다.\n");
        } else {
            printf("오답! 정답은 '%s' 입니다.\n", correctSong);
        }

        // 제한 시간 내에 문제를 해결한 경우 점수 계산
        int elapsedTime = getElapsedTime(startTime);
        if (elapsedTime >= 60) {
            break; // 1분이 지나면 게임 종료
        }
    }

    // 경과 시간 계산
    int elapsedTime = getElapsedTime(startTime);
    calculateScore(correctAnswers, elapsedTime);
}//hb inject

int main() {
    srand(time(NULL));  // 난수 초기화

    // 게임 시작
    prepareMaskedStage();

    return 0;
}

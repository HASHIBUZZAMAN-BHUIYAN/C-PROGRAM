#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TUTORS 10
#define MAX_TRAINEES 5

// 보컬 튜터 정보 구조체
typedef struct {
    char nickname[50];
    char skill[200];
} VocalTutor;

// 밀리웨이즈 연습생 구조체
typedef struct {
    char name[50];
    VocalTutor *assignedTutor;
} Trainee;

// 보컬 튜터 풀 초기화
VocalTutor tutors[MAX_TUTORS] = {
    {"아리아", "넓은 음역대와 강렬한 음성으로 다양한 음악 장르 소화"},
    {"레트로", "다양한 시대의 음악 스타일을 자유자재로 소화하며 현대적이고 고전적인 조합 제시"},
    {"매직", "음악을 통해 감정과 상상을 자아내는 마법적인 능력 소유"},
    {"심포니", "다양한 악기와 보컬을 조화롭게 결합하여 실제 오케스트라를 연주하는 듯한 효과 창출"},
    {"사이렌", "미스테리한 노래로 청중을 미지의 세계로 초대하며 감성적인 여행을 하는 느낌 제공"},
    {"룬", "음악을 통해 상상의 세계를 창조하고 듣는 이들에게 특별한 감동을 전하는 능력"},
    {"퓨처", "음악 트렌드를 미리 예측하여 학생들에게 미래 지향적이고 혁신적인 가이던스 제공"},
    {"매시브", "강력하고 힘찬 보이스로 학생들을 격려하며 힘을 실어주는 능력"},
    {"에코", "음악을 통해 감정과 메시지를 반영하여 듣는 이들에게 다양한 의미를 전달하는 능력"},
    {"에코", "음악을 통해 감정과 메시지를 반영하여 듣는 이들에게 다양한 의미를 전달하는 능력"} // 에코 튜터 추가
};

// 밀리웨이즈 연습생들
Trainee trainees[MAX_TRAINEES] = {
    {"소진", NULL},
    {"정민", NULL},
    {"태훈", NULL},
    {"민재", NULL},
    {"유나", NULL}
};

// 함수 선언
void adminVocalTuition();
void assignTutor(Trainee *trainee, VocalTutor *tutors, int numTutors);
void printTraineesAndTutors();
void removeTutorFromTrainee(Trainee *trainee);
int playRockPaperScissors();
void swapTutors(Trainee *trainee1, Trainee *trainee2);

// 관리자 보컬 튜터링 함수
void adminVocalTuition() {
    int choice;

    while (1) {
        printf("\n[II. 훈련 > 4. 보컬 훈련 > E. 보컬 튜터링]\n");
        printf("1. 보컬 튜터 할당 및 연습생 정보 출력\n");
        printf("2. 가위-바위-보 게임을 통한 튜터 교환\n");
        printf("3. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // 보컬 튜터 할당 및 연습생 출력
                for (int i = 0; i < MAX_TRAINEES; i++) {
                    if (trainees[i].assignedTutor == NULL) {
                        // 튜터가 할당되지 않은 경우
                        assignTutor(&trainees[i], tutors, MAX_TUTORS);
                    }
                }
                printTraineesAndTutors();
                break;
            case 2:
                // 가위-바위-보 게임을 통한 튜터 교환
                printf("가위-바위-보 게임을 진행합니다.\n");
                int winner = playRockPaperScissors();

                if (winner != -1) {
                    // 승리한 경우 튜터 교환
                    printf("게임 승리! 튜터를 교환합니다.\n");
                    int trainee1, trainee2;
                    printf("교환할 연습생 번호를 입력하세요 (0-%d): ", MAX_TRAINEES - 1);
                    scanf("%d", &trainee1);
                    printf("교환할 연습생 번호를 입력하세요 (0-%d): ", MAX_TRAINEES - 1);
                    scanf("%d", &trainee2);

                    swapTutors(&trainees[trainee1], &trainees[trainee2]);
                    printTraineesAndTutors();
                } else {
                    printf("게임에서 졌습니다. 튜터 교환이 실패했습니다.\n");
                }
                break;
            case 3:
                printf("프로그램을 종료합니다.\n");
                return;
            default:
                printf("잘못된 입력입니다. 다시 선택해주세요.\n");
        }
    }
}

// 연습생에 보컬 튜터 할당
void assignTutor(Trainee *trainee, VocalTutor *tutors, int numTutors) {
    // 무작위로 튜터 할당
    int tutorIndex = rand() % numTutors;
    trainee->assignedTutor = &tutors[tutorIndex];
}

// 연습생과 튜터 정보 출력
void printTraineesAndTutors() {
    printf("\n연습생과 할당된 보컬 튜터 목록:\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (trainees[i].assignedTutor != NULL) {
            printf("연습생: %s, 튜터: %s, 스킬: %s\n",
                trainees[i].name, trainees[i].assignedTutor->nickname, trainees[i].assignedTutor->skill);
        } else {
            printf("연습생: %s, 튜터: 없음\n", trainees[i].name);
        }
    }
}

// 연습생에서 튜터 제거
void removeTutorFromTrainee(Trainee *trainee) {
    trainee->assignedTutor = NULL;
}

// 가위-바위-보 게임을 위한 함수
int playRockPaperScissors() {
    int playerChoice, opponentChoice;
    printf("가위(1), 바위(2), 보(3)를 선택하세요: ");
    scanf("%d", &playerChoice);

    // 상대방의 선택 무작위
    opponentChoice = rand() % 3 + 1;

    printf("상대방은 %d 선택\n", opponentChoice);

    // 게임 결과
    if (playerChoice == opponentChoice) {
        printf("비겼습니다! 다시 시도하세요.\n");
        return -1;  // 비긴 경우
    }

    if ((playerChoice == 1 && opponentChoice == 3) ||
        (playerChoice == 2 && opponentChoice == 1) ||
        (playerChoice == 3 && opponentChoice == 2)) {
        printf("이겼습니다!\n");
        return 1;  // 플레이어가 이긴 경우
    } else {
        printf("졌습니다!\n");
        return 0;  // 플레이어가 진 경우
    }
}

// 두 연습생의 튜터 교환 함수
void swapTutors(Trainee *trainee1, Trainee *trainee2) {
    VocalTutor *temp = trainee1->assignedTutor;
    trainee1->assignedTutor = trainee2->assignedTutor;
    trainee2->assignedTutor = temp;
}
    //hb inject
int main() {
    srand(time(NULL));  // 난수 생성기 초기화

    // 관리자 보컬 튜터링 기능 실행
    adminVocalTuition();

    return 0;
}

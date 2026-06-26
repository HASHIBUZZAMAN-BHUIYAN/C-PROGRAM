#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_WORDS 10
#define MAX_NAME_LENGTH 50

// Structure for word card with definition and difficulty
typedef struct {
    char word[30];
    char definition[100];
    int difficulty; // 1 = low, 2 = medium, 3 = high
} WordCard;

// Structure for tracking the player's challenge progress
typedef struct {
    char name[MAX_NAME_LENGTH];
    int difficulty_level; // 1 = low, 2 = medium, 3 = high
    int score;
    int pass_status; // 1 = pass, 0 = fail
    char pass_date[9]; // Format: YYYYMMDD
} ChallengeResult;

// List of players' names (Milieways members)
char members[MAX_MEMBERS][MAX_NAME_LENGTH] = {"YJ", "WC", "AR", "JK", "CS"};

// Word cards (30 sets, divided into 3 levels)
WordCard word_cards[MAX_WORDS * 3] = {
    {"사과", "Fruit that is often red or green", 1}, {"책", "Object for reading", 1}, {"가방", "A container for carrying things", 1},
    {"강", "A body of flowing water", 1}, {"꽃", "A part of a plant that is colorful", 1},
    {"컴퓨터", "An electronic device for computing", 2}, {"프로그래밍", "Writing code to create software", 2}, {"인터넷", "Global system of interconnected computers", 2},
    {"인공지능", "Technology that mimics human intelligence", 2}, {"언어", "A system of communication through speech or writing", 2},
    {"우주", "The cosmos beyond Earth", 3}, {"기후변화", "Long-term changes in global weather patterns", 3}, {"블록체인", "A decentralized digital ledger", 3},
    {"암호화", "The process of encoding information", 3}, {"로봇", "A machine that can carry out tasks automatically", 3},
    {"무역", "The exchange of goods and services between countries", 1}, {"정치", "The process of governing and making decisions", 1}, {"경제", "System for producing and distributing goods", 1},
    {"환경", "The surroundings in which organisms live", 2}, {"사회", "The structure of human relationships and institutions", 2},
    {"신경망", "A system of algorithms designed to mimic human brain structure", 3}, {"가상현실", "Computer-generated simulation of a real or imagined environment", 3}, {"기계학습", "A method of data analysis that automates analytical model building", 3},
    {"동물", "Living organisms that can move and usually consume organic matter", 1}, {"고양이", "Small domesticated mammal", 1}, {"강아지", "Domestic carnivorous mammal", 1},
    {"로봇공학", "Study and creation of robots", 2}, {"지구", "Our home planet", 2}, {"우주여행", "The act of traveling beyond Earth into space", 2},
    {"기후", "Weather conditions over a long period", 3}, {"에너지", "Capacity to do work or produce heat", 3}, {"정신건강", "Mental state of an individual", 3}
};

// Array to hold challenge results
ChallengeResult results[MAX_MEMBERS];

// Function to shuffle words based on difficulty
void shuffleWordsByDifficulty(WordCard* word_list, int count, int difficulty) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        if (word_list[i].difficulty == difficulty) {
            int j = rand() % count;
            WordCard temp = word_list[i];
            word_list[i] = word_list[j];
            word_list[j] = temp;
        }
    }
}

// Function to select a random member
void selectMember(char* selected_member) {
    int index = rand() % MAX_MEMBERS;
    strcpy(selected_member, members[index]);
}

// Function to start the dictionary game
void doDictionaryGame() {
    int choice;
    
    // Select a random member
    char selected_member[MAX_NAME_LENGTH];
    selectMember(selected_member);
    printf("선택된 게이머: %s\n", selected_member);

    // Display the challenge menu
    printf("1. 최고 난이도 시험 도전\n");
    printf("2. 난이도 단계 별로 도전\n");
    printf("선택하세요: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            challengeHighLevel(selected_member);
            break;
        case 2:
            challengeStepByStep(selected_member);
            break;
        default:
            printf("잘못된 선택입니다.\n");
    }
}

// Function to handle the challenge at the highest level (level 3)
void challengeHighLevel(char* player_name) {
    int correct_answers = 0;
    char answer[50];

    printf("최고 난이도 시험 도전 시작!\n");

    // Select 5 random words from high difficulty
    shuffleWordsByDifficulty(word_cards, MAX_WORDS * 3, 3);
    for (int i = 0; i < 5; i++) {
        printf("문제 %d: %s\n", i + 1, word_cards[i].definition);
        printf("정답을 입력하세요: ");
        scanf("%s", answer);

        if (strcmp(answer, word_cards[i].word) == 0) {
            correct_answers++;
        }
    }

    // If all answers are correct, mark the player as passed and update the date
    if (correct_answers == 5) {
        printf("축하합니다! 최고 난이도 시험에 합격하셨습니다.\n");
        strcpy(results[0].name, player_name); // Assuming player is the first member for simplicity
        results[0].pass_status = 1;
        strcpy(results[0].pass_date, "20230507"); // Example date
    } else {
        printf("모든 문제에 정답을 내지 못했습니다. 다시 도전해야 합니다.\n");
    }
}

// Function to handle the step-by-step challenge
void challengeStepByStep(char* player_name) {
    int correct_answers = 0;
    char answer[50];
    int difficulty = 1;

    printf("난이도 단계 별로 도전 시작!\n");

    // Loop through the difficulty levels
    for (difficulty = 1; difficulty <= 3; difficulty++) {
        int questions_answered = 0;

        // Shuffle words for the current difficulty
        shuffleWordsByDifficulty(word_cards, MAX_WORDS * 3, difficulty);

        // Ask 3 questions
        for (int i = 0; i < 3; i++) {
            printf("문제 %d: %s\n", i + 1, word_cards[i].definition);
            printf("정답을 입력하세요: ");
            scanf("%s", answer);

            if (strcmp(answer, word_cards[i].word) == 0) {
                questions_answered++;
            }
        }

        // If player answers 2 or more questions correctly, pass the level
        if (questions_answered >= 2) {
            printf("난이도 %d 합격!\n", difficulty);
            results[0].difficulty_level = difficulty; // Assuming player is the first member for simplicity
        } else {
            printf("난이도 %d 실패. 다시 도전해야 합니다.\n", difficulty);
            break;
        }
    }

    if (results[0].difficulty_level == 3) {
        printf("축하합니다! 모든 난이도를 합격하셨습니다.\n");
        strcpy(results[0].pass_status, "Pass");
        strcpy(results[0].pass_date, "20230507"); //hb Example date
    }
}

int main() {
    int choice;
    
    while (1) {
        printf("\n[II. 훈련 > 3. 언어 및 발음 훈련 > E. 딕셔너리 게임]\n");
        printf("1. 딕셔너리 게임 시작\n");
        printf("2. 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                doDictionaryGame();
                break;
            case 2:
                printf("게임 종료\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
    
    return 0;
}

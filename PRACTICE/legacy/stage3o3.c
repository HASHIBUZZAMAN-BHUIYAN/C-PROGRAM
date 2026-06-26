#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 100
#define MAX_NAME_LENGTH 50
#define GAME_DURATION 60 // Game duration in seconds
#define GAME_WORDS 42   // Number of words used in the game

// Structure for the score details
typedef struct {
    char challenger_name[MAX_NAME_LENGTH]; // Challenger's name
    int challenger_score;                  // Number of words the challenger successfully connected
    int challenger_time;                   // Time taken by the challenger
    char target_name[MAX_NAME_LENGTH];     // Target's name
    int target_score;                      // Number of words the target successfully connected
    int target_time;                       // Time taken by the target
} GameScore;

// List of words for the game (100 words)
char words[MAX_WORDS][5] = {
    "사과", "사슴", "말", "불", "불꽃", "꽃", "눈", "눈물", "눈꽃", "구름",
    "하늘", "바람", "나무", "소리", "시간", "바다", "동물", "계절", "일", "하루",
    "강", "별", "빛", "꿈", "기억", "하트", "체리", "가방", "열쇠", "달",
    "밤", "머리", "사랑", "아이", "물", "모래", "강아지", "고양이", "펜", "가게",
    "길", "배", "화장", "기차", "시간", "친구", "바위", "도시", "소리", "책",
    "종이", "나비", "물고기", "앵무새", "대나무", "학교", "연필", "핸드폰", "버스",
    "비행기", "장미", "수정", "점", "대문", "머리카락", "강철", "책상", "자전거", "탑",
    "종", "하늘", "샘", "빛", "문", "아이디어", "예술", "별빛", "태양", "소파",
    "위", "그림", "향기", "설탕", "기억", "꽃밭", "연기", "국기", "비", "해",
    "계단", "편지", "우산", "자동차", "토끼", "공원", "침대", "바닥", "벽", "사람"
};

// Structure to hold the game score
GameScore score;

// Function to display the menu for starting the game
void displayMenu() {
    printf("\n1. Start Word Relay Game\n");
    printf("2. Exit\n");
    printf("Choose an option: ");
}

// Function to shuffle the words randomly
void shuffleWords(char words[][5], int count) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int j = rand() % count;
        char temp[5];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
}

// Function to prompt for names and check if they're valid
int promptForNames(char *challenger, char *target) {
    printf("Enter Challenger's Name: ");
    scanf("%s", challenger);
    printf("Enter Target's Name: ");
    scanf("%s", target);

    // Validation could be added here for Milieways members if necessary
    return 1; // Always return 1 to continue for now
}

// Function to play the game, with challenger and target names
void playGame(char *challenger, char *target) {
    char usedWords[GAME_WORDS][5];
    int usedCount = 0;
    int scoreChallenger = 0, scoreTarget = 0;
    time_t startTime, endTime;
    
    printf("Game started! Press Enter to begin...\n");
    getchar(); // To wait for the user to press enter to start the game
    startTime = time(NULL);

    shuffleWords(words, GAME_WORDS); // Shuffle the words
    
    // Challenger's turn
    printf("\nChallenger's turn (60 seconds)!\n");
    for (int i = 0; i < GAME_WORDS; i++) {
        printf("Word: %s\n", words[i]);
        char answer[5];
        printf("Enter the next word: ");
        scanf("%s", answer);

        // Simulate the word relay logic (You can add actual word comparison logic here)
        scoreChallenger++;
    }
    
    endTime = time(NULL);
    int challengerTime = (int)(endTime - startTime); // Time taken for the challenger
    
    // Target's turn
    printf("\nTarget's turn (60 seconds)!\n");
    startTime = time(NULL);
    for (int i = 0; i < GAME_WORDS; i++) {
        printf("Word: %s\n", words[i]);
        char answer[5];
        printf("Enter the next word: ");
        scanf("%s", answer);
        
        // Simulate the word relay logic (You can add actual word comparison logic here)
        scoreTarget++;
    }
    
    endTime = time(NULL);
    int targetTime = (int)(endTime - startTime); // Time taken for the target
    
    // Store the results in the score structure
    strcpy(score.challenger_name, challenger);
    score.challenger_score = scoreChallenger;
    score.challenger_time = challengerTime;
    strcpy(score.target_name, target);
    score.target_score = scoreTarget;
    score.target_time = targetTime;

    evalGame();
}

// Function to evaluate the game result and update the score structure
void evalGame() {
    printf("\nGame Over!\n");

    // Determine the winner based on score and time
    if (score.challenger_score > score.target_score) {
        printf("Challenger wins!\n");
    } else if (score.target_score > score.challenger_score) {
        printf("Target wins!\n");
    } else {
        if (score.challenger_time < score.target_time) {
            printf("Challenger wins due to faster time!\n");
        } else if (score.challenger_time > score.target_time) {
            printf("Target wins due to faster time!\n");
        } else {
            printf("It's a tie!\n");
        }
    }
    
    displayWinner();
}

// Function to display the winner's score
void displayWinner() {
    printf("\n--- Game Results ---\n");
    printf("Challenger: %s, Score: %d, Time: %d seconds\n", score.challenger_name, score.challenger_score, score.challenger_time);
    printf("Target: %s, Score: %d, Time: %d seconds\n", score.target_name, score.target_score, score.target_time);
}

// Function to starthb the Word Relay game
void doWordRelay() {
    char challenger[MAX_NAME_LENGTH], target[MAX_NAME_LENGTH];
    
    if (promptForNames(challenger, target)) {
        playGame(challenger, target);
    } else {
        printf("Invalid player names.\n");
    }
}

int main() {
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                doWordRelay();
                break;
            case 2:
                printf("Exiting game...\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    
    return 0;
}

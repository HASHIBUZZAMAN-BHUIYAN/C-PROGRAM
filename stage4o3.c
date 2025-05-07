#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SONGS 10
#define MAX_HINT_LENGTH 4

// 노래 정보 구조체
typedef struct {
    char title[50];
    char genre[30];
    char artist[50];
} Song;

// 노래 정보 초기화
Song songs[MAX_SONGS] = {
    {"Call Me Baby", "댄스 팝", "EXO"},
    {"Through the Night", "발라드", "IU"},
    {"Mic Drop", "힙합", "BTS"},
    {"Eyes, Nose, Lips", "R&B", "Taeyang"},
    {"Shoot Me", "록(Rock)", "Day6"},
    {"Electric Shock", "일렉트로니카", "f(x)"},
    {"Love Tonight", "트로트", "홍진영"},
    {"Island", "레게", "WINNER"},
    {"Dumb Litty", "퓨전", "KARD"},
    {"I'm Sorry", "밴드", "CNBLUE"}
};

// 장르 정보
const char *genres[MAX_SONGS] = {
    "댄스 팝", "발라드", "힙합", "R&B", "록(Rock)", "일렉트로니카", 
    "트로트", "레게", "퓨전", "밴드"
};

// 함수 선언
void learnSongGenre();
void giveHint(char *hint, const char *artist);
int matchSongGenre(char *userInput, Song *song);
void shuffleSongs(Song *songs, int n);
void shuffleGenres(char genres[][30], int n);

int main() {
    srand(time(NULL));  // 랜덤 함수 초기화

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Learn Song Genre\n");
        printf("2. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                learnSongGenre();
                break;
            case 2:
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice. Please choose again.\n");
        }
    }

    return 0;
}

// 장르 학습 함수
void learnSongGenre() {
    int songIndex = rand() % MAX_SONGS;  // 무작위로 노래 선택
    Song selectedSong = songs[songIndex];
    char userGenre[30];
    char hint[MAX_HINT_LENGTH + 1];
    int attempts = 0;

    printf("\nSong Title: %s\n", selectedSong.title);

    while (attempts < 2) {
        printf("Guess the genre: ");
        scanf(" %[^\n]", userGenre);  // 사용자 입력 받기

        if (matchSongGenre(userGenre, &selectedSong)) {
            printf("Congratulations! You guessed the correct genre.\n");
            return;
        } else {
            printf("Wrong guess.\n");

            // 1번째 시도 후 힌트를 제공
            if (attempts == 0) {
                giveHint(hint, selectedSong.artist);
                printf("Hint: Artist - %s\n", hint);
            }
            attempts++;
        }
    }

    printf("Sorry! The correct genre was: %s\n", selectedSong.genre);
}

// 장르가 맞는지 확인하는 함수
int matchSongGenre(char *userInput, Song *song) {
    return strcasecmp(userInput, song->genre) == 0;  // 대소문자 구분 없이 비교
}

// 힌트를 제공하는 함수
void giveHint(char *hint, const char *artist) {
    int len = strlen(artist);
    if (len <= 3) {
        strncpy(hint, artist, 1);  // 3자 이하일 경우 1자 제공
    } else if (len <= 5) {
        strncpy(hint, artist, 2);  // 4-5자일 경우 2자 제공
    } else {
        strncpy(hint, artist, 3);  // 그 이상일 경우 3자 제공
    }
    hint[3] = '\0';  // 문자열 종료
}

// 노래와 장르를 무작위로 섞는 함수
void shuffleSongs(Song *songs, int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        Song temp = songs[i];
        songs[i] = songs[j];
        songs[j] = temp;
    }
}

// 장르를 무작위로 섞는 함수
void shuffleGenres(char genres[][30], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        char temp[30];
        strcpy(temp, genres[i]);
        strcpy(genres[i], genres[j]);
        strcpy(genres[j], temp);
    }
}

// 보너스: 노래와 장르를 매칭시키는 게임
void matchSongsToGenres() {
    shuffleSongs(songs, MAX_SONGS);  // 노래 섞기
    char shuffledGenres[MAX_SONGS][30];
    for (int i = 0; i < MAX_SONGS; i++) {
        strcpy(shuffledGenres[i], genres[i]);
    }
    shuffleGenres(shuffledGenres, MAX_SONGS);  // 장르 섞기

    printf("\nMatch the songs to their genres:\n");
    for (int i = 0; i < MAX_SONGS; i++) {
        printf("Song: %s\n", songs[i].title);
        printf("Possible genres: ");
        for (int j = 0; j < MAX_SONGS; j++) {
            printf("%s ", shuffledGenres[j]);
        }//hb inject
        printf("\nGuess the genre: ");
        char userGenre[30];
        scanf(" %[^\n]", userGenre);

        if (matchSongGenre(userGenre, &songs[i])) {
            printf("Correct!\n");
        } else {
            printf("Wrong! The correct genre was: %s\n", songs[i].genre);
        }
    }
}

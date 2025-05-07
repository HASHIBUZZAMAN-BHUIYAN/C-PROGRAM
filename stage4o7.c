#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LYRICS 100
#define MAX_PARTS 7
#define MAX_MEMBERS 10
#define MAX_NAME_LENGTH 100

// 노래 가사 구조체
typedef struct {
    char *lyrics[MAX_LYRICS];
    int total_lines;
} SongLyrics;

// 노래 분석 구조체 (파트)
typedef struct {
    char part_name[MAX_NAME_LENGTH];
    int start_index;  // 파트의 시작 인덱스
    int end_index;    // 파트의 끝 인덱스
} SongPart;

// 팀 구성원 구조체
typedef struct {
    char name[MAX_NAME_LENGTH];
    int assigned_part[MAX_PARTS];  // 각 연습생이 담당하는 파트의 인덱스
} Member;

// 노래 분석 구조체
typedef struct {
    SongPart parts[MAX_PARTS];  // 7개의 파트 (Intro, Verse 1, Pre-Chorus, Chorus, Verse 2, Bridge, Final Chorus)
    int total_parts;
} SongAnalysis;

// 샘플 노래 가사 (BTS - 봄날)
SongLyrics songLyrics = {
    .lyrics = {
        "그리움에 겨워",
        "너의 이름을 부르면",
        "가슴이 아파오고",
        "아직 너를 사랑해",
        "우리 함께한 시간",
        "그리움 속에",
        "내게 돌아와",
        "봄날은 가고",
        "너와 나의 사랑은",
        "다시 피어나길",
        "너는 내게 올 거야",
        "따스한 햇살 속에",
        "함께 웃을 거야",
        "봄날을 기다려",
        "너와 나의 마음이",
        "어디에 있든",
        "다시 만날 거야"
    },
    .total_lines = 17
};

// 노래 가사 출력 함수
void printLyrics(SongLyrics *song) {
    for (int i = 0; i < song->total_lines; i++) {
        printf("%d: %s\n", i + 1, song->lyrics[i]);
    }
}

// 노래 분석 초기화 함수
void analyzSong(SongLyrics *song, SongAnalysis *analysis) {
    // 각 파트를 설정하는 예시
    strcpy(analysis->parts[0].part_name, "Intro");
    analysis->parts[0].start_index = 0;
    analysis->parts[0].end_index = 1;

    strcpy(analysis->parts[1].part_name, "Verse 1");
    analysis->parts[1].start_index = 2;
    analysis->parts[1].end_index = 5;

    strcpy(analysis->parts[2].part_name, "Pre-Chorus");
    analysis->parts[2].start_index = 6;
    analysis->parts[2].end_index = 7;

    strcpy(analysis->parts[3].part_name, "Chorus");
    analysis->parts[3].start_index = 8;
    analysis->parts[3].end_index = 9;

    strcpy(analysis->parts[4].part_name, "Verse 2");
    analysis->parts[4].start_index = 10;
    analysis->parts[4].end_index = 12;

    strcpy(analysis->parts[5].part_name, "Bridge");
    analysis->parts[5].start_index = 13;
    analysis->parts[5].end_index = 14;

    strcpy(analysis->parts[6].part_name, "Final Chorus");
    analysis->parts[6].start_index = 15;
    analysis->parts[6].end_index = 16;

    analysis->total_parts = 7;
}

// 노래 분석 결과 출력 함수
void printAnalyzedSong(SongAnalysis *analysis, SongLyrics *song) {
    for (int i = 0; i < analysis->total_parts; i++) {
        printf("\n--- %s ---\n", analysis->parts[i].part_name);
        for (int j = analysis->parts[i].start_index; j <= analysis->parts[i].end_index; j++) {
            printf("%d: %s\n", j + 1, song->lyrics[j]);
        }
    }
}

// 파트 할당 함수
void assignSongPart(Member *members, int member_count, SongAnalysis *analysis, SongLyrics *song) {
    for (int i = 0; i < member_count; i++) {
        printf("\n%s의 담당 파트를 입력하세요:\n", members[i].name);
        for (int j = 0; j < analysis->total_parts; j++) {
            printf("%d. %s: %d - %d\n", j + 1, analysis->parts[j].part_name,
                   analysis->parts[j].start_index + 1, analysis->parts[j].end_index + 1);
        }
        printf("담당할 파트 번호를 선택하세요: ");
        int part_choice;
        scanf("%d", &part_choice);
        part_choice--;  // 배열은 0부터 시작하므로 1을 빼야 함
        if (part_choice >= 0 && part_choice < analysis->total_parts) {
            members[i].assigned_part[i] = part_choice;
        }
    }
}

// 파트별 가사 출력 함수
void printPartLyrics(Member *members, int member_count, SongAnalysis *analysis, SongLyrics *song) {
    for (int i = 0; i < member_count; i++) {
        printf("\n%s의 담당 파트:\n", members[i].name);
        for (int j = 0; j < analysis->total_parts; j++) {
            if (members[i].assigned_part[j] == j) {
                printf("--- %s ---\n", analysis->parts[j].part_name);
                for (int k = analysis->parts[j].start_index; k <= analysis->parts[j].end_index; k++) {
                    printf("%d: %s\n", k + 1, song->lyrics[k]);
                }
            }
        }
    }
}

// 팀 노래 분석 메뉴
void understandSongs() {
    SongAnalysis analysis;
    analyzSong(&songLyrics, &analysis);

    printf("\n노래 가사 출력:\n");
    printLyrics(&songLyrics);

    printf("\n노래 분석 결과 출력:\n");
    printAnalyzedSong(&analysis, &songLyrics);

    int member_count;
    printf("\n연습생 수를 입력하세요: ");
    scanf("%d", &member_count);

    Member members[MAX_MEMBERS];
    for (int i = 0; i < member_count; i++) {
        printf("\n연습생 이름을 입력하세요: ");
        scanf("%s", members[i].name);
    }
//hb inject
    assignSongPart(members, member_count, &analysis, &songLyrics);

    printf("\n파트별 가사 출력:\n");
    printPartLyrics(members, member_count, &analysis, &songLyrics);
}

int main() {
    understandSongs();
    return 0;
}

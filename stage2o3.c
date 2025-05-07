#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SONGS 7
#define MAX_TITLE_LEN 100
#define MAX_LYRIC_LEN 200
#define MAX_MEMBERS 7
#define MAX_NAME_LEN 50
#define MAX_NICKNAME_LEN 50

// 밀리웨이즈 멤버 정보
const char *members[MAX_MEMBERS][2] = {
    {"김영진", "영진"},
    {"이민호", "민호"},
    {"박지훈", "지훈"},
    {"최수빈", "수빈"},
    {"정하늘", "하늘"},
    {"한서준", "서준"},
    {"오유진", "유진"}
};

// 초성 리스트
const char *chosung_list[19] = {
    "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ",
    "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
    "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"
};

// 노래 정보 구조체
typedef struct {
    char title[MAX_TITLE_LEN];
    char initials[MAX_TITLE_LEN];
    char lyric[MAX_LYRIC_LEN];
} KpopSong;

// 노래 목록
KpopSong songs[MAX_SONGS];
int song_count = 0;

// 초성 추출 함수
void extractConsonant(const char *input, char *output) {
    int i = 0, j = 0;
    while (input[i]) {
        unsigned char c1 = input[i];
        if (c1 >= 0xE0) { // UTF-8 3바이트 문자
            unsigned char c2 = input[i + 1];
            unsigned char c3 = input[i + 2];
            unsigned int unicode = ((c1 & 0x0F) << 12) |
                                   ((c2 & 0x3F) << 6) |
                                   (c3 & 0x3F);
            if (unicode >= 0xAC00 && unicode <= 0xD7A3) {
                int cho = (unicode - 0xAC00) / (21 * 28);
                strcat(output, chosung_list[cho]);
            }
            i += 3;
        } else {
            i++;
        }
    }
}

// 노래 입력 함수
void inputKpopSongInitials() {
    printf("K-POP 노래 제목과 가사를 최대 %d개까지 입력하세요.\n", MAX_SONGS);
    for (int i = 0; i < MAX_SONGS; i++) {
        printf("\n[%d번째 노래]\n", i + 1);
        printf("노래 제목: ");
        fgets(songs[i].title, MAX_TITLE_LEN, stdin);
        songs[i].title[strcspn(songs[i].title, "\n")] = 0;

        printf("가사의 일부: ");
        fgets(songs[i].lyric, MAX_LYRIC_LEN, stdin);
        songs[i].lyric[strcspn(songs[i].lyric, "\n")] = 0;

        songs[i].initials[0] = '\0';
        extractConsonant(songs[i].title, songs[i].initials);

        song_count++;
        if (song_count >= MAX_SONGS) break;
    }
}

// 노래 제목 확인 hb함수
int checkKpopSongTitle(const char *input, const char *initials) {
    char input_initials[MAX_TITLE_LEN] = "";
    extractConsonant(input, input_initials);
    return strcmp(input_initials, initials) == 0;
}

// 블랙 나이트 선택 함수
int getBlackKnight(int exclude) {
    int idx;
    do {
        idx = rand() % MAX_MEMBERS;
    } while (idx == exclude);
    return idx;
}

// 미션 수행 함수
void completeMission() {
    if (song_count == 0) {
        printf("노래 목록이 비어 있습니다. 먼저 노래를 입력하세요.\n");
        return;
    }

    int completed[MAX_MEMBERS] = {0};
    int remaining = MAX_MEMBERS;
    srand((unsigned int)time(NULL));

    while (remaining > 0) {
        int member_idx;
        do {
            member_idx = rand() % MAX_MEMBERS;
        } while (completed[member_idx]);

        int song_idx = rand() % song_count;
        printf("\n[%s(%s)님에게 주어진 초성: %s]\n",
               members[member_idx][0],
               members[member_idx][1],
               songs[song_idx].initials);

        int success = 0;
        for (int attempt = 1; attempt <= 2; attempt++) {
            char answer[MAX_TITLE_LEN];
            printf("노래 제목 입력 (시도 %d): ", attempt);
            fgets(answer, MAX_TITLE_LEN, stdin);
            answer[strcspn(answer, "\n")] = 0;

            if (checkKpopSongTitle(answer, songs[song_idx].initials)) {
                printf("%s님, 미션을 성공적으로 완료했습니다!\n", members[member_idx][0]);
                completed[member_idx] = 1;
                remaining--;
                success = 1;
                break;
            } else {
                printf("틀렸습니다.\n");
            }
        }

        if (!success) {
            printf("%s님이 미션을 실패했습니다. 블랙 나이트를 호출합니다.\n", members[member_idx][0]);
            int knight_idx = getBlackKnight(member_idx);
            printf("블랙 나이트: %s(%s)\n", members[knight_idx][0], members[knight_idx][1]);

            char answer[MAX_TITLE_LEN];
            printf("노래 제목 입력: ");
            fgets(answer, MAX_TITLE_LEN, stdin);
            answer[strcspn(answer, "\n")] = 0;

            if (checkKpopSongTitle(answer, songs[song_idx].initials)) {
                printf("%s님이 미션을 성공적으로 완료했습니다!\n", members[knight_idx][0]);
                completed[member_idx] = 1;
                remaining--;
            } else {
                printf("밀리웨이즈는 팀워크를 더 발전시켜서 다시 도전하세요!\n");
                return;
            }
        }
    }

    printf("밀리웨이즈의 팀워크는 훌륭합니다!\n");
}

// 메인 함수
int main() {
    inputKpopSongInitials();
    completeMission();
    return 0;
}

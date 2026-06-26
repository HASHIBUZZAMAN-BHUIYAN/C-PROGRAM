#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for usleep

#define MAX_MSG_LEN 43         // 42 + nullhb
#define DISPLAY_WIDTH 18
#define MAX_SETS 5

char messages[MAX_SETS][2][MAX_MSG_LEN];

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void inputMessages() {
    for (int s = 0; s < MAX_SETS; ++s) {
        for (int l = 0; l < 2; ++l) {
            while (1) {
                printf("Set %d Line %d (24~42 chars): ", s + 1, l + 1);
                fgets(messages[s][l], MAX_MSG_LEN, stdin);
                size_t len = strlen(messages[s][l]);
                if (messages[s][l][len - 1] == '\n')
                    messages[s][l][len - 1] = '\0';
                len = strlen(messages[s][l]);
                if (len >= 24 && len <= 42) break;
                printf("Length was %zu. Try again.\n", len);
            }
        }
    }
}

void scrollOneSet(const char *line1, const char *line2) {
    int len1 = strlen(line1);
    int len2 = strlen(line2);
    int totalFrames = 24;

    int maxPos1 = len1 + DISPLAY_WIDTH;
    int maxPos2 = len2 + DISPLAY_WIDTH;

    for (int t = 0; t < totalFrames; ++t) {
        clearScreen();

        int pos1 = t % maxPos1;
        int pos2 = (t * 2) % maxPos2;

        char display1[DISPLAY_WIDTH + 1] = {0};
        char display2[DISPLAY_WIDTH + 1] = {0};

        for (int i = 0; i < DISPLAY_WIDTH; ++i) {
            int idx1 = pos1 + i;
            display1[i] = (idx1 < len1) ? line1[idx1] : ' ';

            int idx2 = pos2 + i;
            display2[i] = (idx2 < len2) ? line2[idx2] : ' ';
        }

        printf("┌──────────────────┐\n");
        printf("│%-18s│\n", display1);
        printf("│%-18s│\n", display2);
        printf("└──────────────────┘\n");

        usleep(1000000); // 1 second
    }
}

void showMyAdMsg() {
    inputMessages();
    for (int i = 0; i < MAX_SETS; ++i) {
        scrollOneSet(messages[i][0], messages[i][1]);
    }
}

int main() {
    printf("💡 K-POP 홍보 메시지 광고판\n");
    showMyAdMsg();
    printf("🎉 모든 메시지를 출력했습니다!\n");
    return 0;
}
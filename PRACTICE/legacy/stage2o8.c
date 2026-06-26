#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 4
#define MAX_NAME_LEN 30
#define MAX_NICKNAME_LEN 30
#define MAX_GIFT_LEN 100

// Structure for storing member data
typedef struct {
    char name[MAX_NAME_LEN];
    char nickname[MAX_NICKNAME_LEN];
} Member;

// Base64 Encoding function
const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void encode_base64(const unsigned char *input, unsigned char *output, int len) {
    int i, j;
    unsigned char temp[3];
    unsigned char enc[4];
    
    for (i = 0, j = 0; len > 0; len -= 3, input += 3) {
        temp[0] = input[0];
        temp[1] = (len > 1) ? input[1] : 0;
        temp[2] = (len > 2) ? input[2] : 0;

        enc[0] = (temp[0] >> 2) & 0x3F;
        enc[1] = ((temp[0] & 0x03) << 4) | ((temp[1] >> 4) & 0x0F);
        enc[2] = ((temp[1] & 0x0F) << 2) | ((temp[2] >> 6) & 0x03);
        enc[3] = temp[2] & 0x3F;

        for (i = 0; i < 4; i++) {
            output[j++] = base64_table[enc[i]];
        }
    }
    output[j] = '\0';  // Null terminate the string
}

// Base64 Decoding function
int decode_base64(const unsigned char *input, unsigned char *output) {
    int len = strlen(input);
    int i, j = 0;
    unsigned char temp[4];
    int value = 0;
    
    for (i = 0; i < len; i++) {
        char c = input[i];
        if (c == '=')
            break;
        if (c >= 'A' && c <= 'Z') value = c - 'A';
        else if (c >= 'a' && c <= 'z') value = c - 'a' + 26;
        else if (c >= '0' && c <= '9') value = c - '0' + 52;
        else if (c == '+') value = 62;
        else if (c == '/') value = 63;
        
        temp[j] = value;
        
        if (++j == 4) {
            output[0] = (temp[0] << 2) | (temp[1] >> 4);
            output[1] = (temp[1] << 4) | (temp[2] >> 2);
            output[2] = (temp[2] << 6) | temp[3];
            j = 0;
        }
    }

    if (j > 0) {
        if (j == 3) {
            output[0] = (temp[0] << 2) | (temp[1] >> 4);
            output[1] = (temp[1] << 4) | (temp[2] >> 2);
        } else if (j == 2) {
            output[0] = (temp[0] << 2) | (temp[1] >> 4);
        }
    }
    return 0;
}

// Function to play the Manito game
void playManito() {
    Member members[MAX_MEMBERS] = {
        {"김영진", "영진"},
        {"이민호", "민호"},
        {"박지훈", "지훈"},
        {"최수빈", "수빈"}
    };

    char name[MAX_NAME_LEN], nickname[MAX_NICKNAME_LEN], gift[MAX_GIFT_LEN];
    char encodedInfo[MAX_GIFT_LEN];
    unsigned char decodedInfo[MAX_GIFT_LEN];
    int selectedIdx = -1;

    // Step 1: Get the Manito player and their gift
    printf("마니또 역할을 할 멤버의 이름을 입력하세요: ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline character

    printf("마니또 역할을 할 멤버의 닉네임을 입력하세요: ");
    fgets(nickname, MAX_NICKNAME_LEN, stdin);
    nickname[strcspn(nickname, "\n")] = '\0';  // Remove newline character

    printf("선물을 입력하세요: ");
    fgets(gift, MAX_GIFT_LEN, stdin);
    gift[strcspn(gift, "\n")] = '\0';  // Remove newline character

    // Step 2: Encode the gift and name using Base64
    char giftInfo[MAX_NAME_LEN + MAX_GIFT_LEN];
    snprintf(giftInfo, sizeof(giftInfo), "%s:%s", name, gift);
    encode_base64((unsigned char*)giftInfo, (unsigned char*)encodedInfo, strlen(giftInfo));

    // Step 3: Randomly select a recipient for the gift
    srand(time(NULL));
    int recipientIdx;
    do {
        recipientIdx = rand() % MAX_MEMBERS;
    } while (strcmp(members[recipientIdx].nickname, nickname) == 0);

    printf("마니또 역할을 할 멤버에게 선물을 보내세요: %s\n", members[recipientIdx].nickname);

    // Step 4: Get the recipient's nickname and compare
    char recipientNickname[MAX_NICKNAME_LEN];
    while (1) {
        printf("선물을 받을 멤버의 닉네임을 입력하세요: ");
        fgets(recipientNickname, MAX_NICKNAME_LEN, stdin);
        recipientNickname[strcspn(recipientNickname, "\n")] = '\0';  // Remove newline character

        if (strcmp(members[recipientIdx].nickname, recipientNickname) == 0) {
            printf("성공적으로 선물을 보냈습니다.\n");
            break;
        } else {
            printf("잘못된 닉네임입니다. 다시 시도해주세요.\n");
        }
    }

    // Step 5: The recipient decodes the message
    printf("받은 정보를 입력하세요: ");
    char receivedInfo[MAX_GIFT_LEN];
    fgets(receivedInfo, MAX_GIFT_LEN, stdin);
    receivedInfo[strcspn(receivedInfo, "\n")] = '\0';  // Remove hb newline character

    // Decode the Base64 message
    decode_base64((unsigned char*)receivedInfo, decodedInfo);

    // Print the decoded gift info
    printf("디코딩된 정보: %s\n", decodedInfo);
}

int main() {
    playManito();
    return 0;
}

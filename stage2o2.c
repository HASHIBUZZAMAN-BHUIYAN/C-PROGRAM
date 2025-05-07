// stage2.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_NAME 50
#define MAX_MSG 300
#define KEYWORD "specter"

// Arthur's Easter Egg Struct
typedef struct {
    char keyword[10];
    char message[MAX_MSG];
} ArthurTrauma;

// Function to convert char to binary string (8-bit)
void charToBinary(char c, char *output) {
    for (int i = 7; i >= 0; i--) {
        output[7 - i] = ((c >> i) & 1) + '0';
    }
    output[8] = '\0';
}

// Function to reverse a string in-place
void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

// Function to check if user's character inputs match reversed binary of keyword
int isRightChar(char reversed_bin[][9], char *input_word) {
    for (int i = 0; i < 7; i++) {
        char expected_char = 0;
        for (int j = 0; j < 8; j++) {
            expected_char = (expected_char << 1) | (reversed_bin[i][j] - '0');
        }
        if (input_word[i] != expected_char) return 0;
    }
    return 1;
}

// Function to check if input matches the keyword
int isEasterEgg(char *input) {
    return strcmp(input, KEYWORD) == 0;
}

// Function to shuffle keyword (Bonus)
void shuffleKeyword(char *input, char *output) {
    int len = strlen(input);
    int oddIdx = 0, evenIdx = 0;
    char odd[10], even[10];

    for (int i = 0; i < len; i++) {
        if (i % 2) odd[oddIdx++] = input[i];
        else even[evenIdx++] = input[i];
    }

    memcpy(output, odd, oddIdx);
    memcpy(output + oddIdx, even, evenIdx);
    output[oddIdx + evenIdx] = '\0';
}

// Main Easter Egg trigger function
void find_easter_egg() {
    ArthurTrauma arthur = {
        .keyword = "specter",
        .message = "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
    };

    printf("<<Arthur's Easter Egg>>\n");

    // Convert to binary and reverse
    char reversed_bin[7][9];
    for (int i = 0; i < 7; i++) {
        char bin[9];
        charToBinary(arthur.keyword[i], bin);
        reverseString(bin);
        strcpy(reversed_bin[i], bin);
        printf("Reversed Binary for letter %d: %s\n", i + 1, bin);
    }

    printf("Enter the 7 characters matching these binary codes: ");
    char user_input[10];
    scanf("%s", user_input);

    if (!isRightChar(reversed_bin, user_input)) {
        printf("Incorrect characters. Try again.\n");
        return;
    }

    printf("Enter the full keyword: ");
    char keyword_input[20];
    scanf("%s", keyword_input);

    if (isEasterEgg(keyword_input)) {
        printf("##Easter Egg Discovered!$$\n%s\n", arthur.message);
    } else {
        printf("Wrong keyword. Returning to menu...\n");
    }
}

// Dummy menu system
void menuSystem() {
    char choice[20];
    while (1) {
        printf("\n[II. Training > 2. Self-Management and Teamwork]\n");
        printf("Enter member name (or 'exit' to quit): ");
        scanf("%s", choice);

        if (strcasecmp(choice, "Arthur") == 0) {
            find_easter_egg();
        } else if (strcasecmp(choice, "exit") == 0) {
            break;
        } else {
            printf("Normal member processing...\n");
        }
    }
}
//hb inject
int main() {
    menuSystem();
    return 0;
}

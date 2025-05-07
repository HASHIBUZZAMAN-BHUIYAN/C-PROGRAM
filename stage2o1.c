#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMBERS 20
#define MAX_RESPONSES 5
#define MAX_RESPONSE_LEN 100
#define MAX_TRAUMA_LEN 200

typedef struct {
    char nickname[50];
    int age;
    char trauma[MAX_TRAUMA_LEN];
} Trauma;

typedef struct {
    int id;
    char content[150];
} CounselingQuestion;

typedef struct {
    char nickname[50];
    int question_id;
    char question[150];
    char response[MAX_RESPONSE_LEN + 1];
} CounselingResponse;

const char *memberNames[MAX_MEMBERS] = {
    "Arthur", "Lancelot", "Guinevere", "Merlin",
    "Morgana", "Percival", "Tristan", "Galahad",
    "Elaine", "Isolde", "Kay", "Bors",
    "Gareth", "Geraint", "Bedivere", "Uther",
    "Leodegrance", "Palamedes", "Yvain", "Pellinore"
};

int memberAges[MAX_MEMBERS] = {
    22, 24, 21, 25, 23, 22, 21, 24,
    20, 22, 23, 25, 24, 21, 22, 23,
    21, 24, 22, 20
};

const CounselingQuestion questions[5] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

Trauma traumaList[MAX_MEMBERS];
int traumaCount = 0;

CounselingResponse responseList[MAX_MEMBERS * MAX_RESPONSES];
int responseCount = 0;

int findMemberIndex(const char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(nickname, memberNames[i]) == 0) return i;
    }
    return -1;
}

void inputTrauma() {
    char nickname[50];
    char traumaText[MAX_TRAUMA_LEN];
    while (1) {
        printf("Enter nickname (or 'exit' to return): ");
        scanf("%s", nickname);
        if (strcasecmp(nickname, "exit") == 0) break;

        int index = findMemberIndex(nickname);
        index != -1
            ? (printf("Enter trauma description: "), getchar(), fgets(traumaText, MAX_TRAUMA_LEN, stdin),
               traumaText[strcspn(traumaText, "\n")] = '\0',
               strncpy(traumaList[traumaCount].nickname, nickname, 50),
               traumaList[traumaCount].age = memberAges[index],
               strncpy(traumaList[traumaCount].trauma, traumaText, MAX_TRAUMA_LEN),
               traumaCount++, printf("Trauma recorded.\n"))
            : printf("Nickname not found. Try again.\n");
    }
}

int hasTrauma(const char *nickname) {
    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) return 1;
    }
    return 0;
}

void listTraumaMembers() {
    printf("Members with trauma:\n");
    for (int i = 0; i < traumaCount; i++) {
        printf("- %s\n", traumaList[i].nickname);
    }
}

int isAnswered(const char *nickname, int question_id) {
    for (int i = 0; i < responseCount; i++) {
        if (strcmp(responseList[i].nickname, nickname) == 0 &&
            responseList[i].question_id == question_id) {
            return 1;
        }
    }
    return 0;
}

void startCounseling() {
    char nickname[50];
    listTraumaMembers();
    printf("Enter nickname to begin counseling: ");
    scanf("%s", nickname);

    if (!hasTrauma(nickname)) {
        printf("No trauma record found for %s.\n", nickname);
        return;
    }

    int selected[3] = {-1, -1, -1};
    int count = 0;
    while (count < 3) {
        int r = rand() % 5;
        int duplicate = 0;
        for (int j = 0; j < count; j++) {
            if (selected[j] == r) duplicate = 1;
        }
        if (!duplicate) selected[count++] = r;
    }
//hb inject
    for (int i = 0; i < 3; i++) {
        int qid = questions[selected[i]].id;
        if (isAnswered(nickname, qid)) continue;

        char response[MAX_RESPONSE_LEN + 2];
        do {
            printf("Q%d: %s\n", qid, questions[selected[i]].content);
            printf("Your answer (max 100 chars): ");
            getchar();
            fgets(response, MAX_RESPONSE_LEN + 2, stdin);
            response[strcspn(response, "\n")] = '\0';
        } while (strlen(response) == 0 || strlen(response) > MAX_RESPONSE_LEN);

        strncpy(responseList[responseCount].nickname, nickname, 50);
        responseList[responseCount].question_id = qid;
        strncpy(responseList[responseCount].question, questions[selected[i]].content, 150);
        strncpy(responseList[responseCount].response, response, MAX_RESPONSE_LEN);
        responseCount++;
    }

    printf("Counseling complete for %s.\n", nickname);
}

void viewCounselingResults() {
    char nickname[50];
    printf("Enter nickname to view counseling result: ");
    scanf("%s", nickname);

    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            printf("\nNickname: %s\n", traumaList[i].nickname);
            printf("Trauma: %s\n", traumaList[i].trauma);
            printf("Responses:\n");
            for (int j = 0; j < responseCount; j++) {
                if (strcmp(responseList[j].nickname, nickname) == 0) {
                    printf("- Q: %s\n  A: %s\n", responseList[j].question, responseList[j].response);
                }
            }
            return;
        }
    }
    printf("No counseling record found for %s.\n", nickname);
}

void overcomeTrauma() {
    char choice;
    do {
        printf("\n[Trauma Management Menu]\n");
        printf("A. Input Trauma\n");
        printf("B. Start Counseling Session\n");
        printf("C. View Counseling Results\n");
        printf("Q. Quit to Main Menu\n");
        printf("Select an option: ");
        scanf(" %c", &choice);
        choice = toupper(choice);

        switch (choice) {
            case 'A': inputTrauma(); break;
            case 'B': startCounseling(); break;
            case 'C': viewCounselingResults(); break;
            case 'Q': printf("Returning to main menu...\n"); break;
            default: printf("Invalid option.\n"); break;
        }
    } while (choice != 'Q');
}

int main() {
    srand((unsigned int)time(NULL));
    char mainChoice;
    do {
        printf("\n[Millieway Stage2 Menu]\n");
        printf("1. Trauma Management\n");
        printf("Q. Quit\n");
        printf("Select an option: ");
        scanf(" %c", &mainChoice);
        mainChoice = toupper(mainChoice);

        switch (mainChoice) {
            case '1': overcomeTrauma(); break;
            case 'Q': printf("Exiting program.\n"); break;
            default: printf("Invalid input. Try again.\n"); break;
        }
    } while (mainChoice != 'Q');

    return 0;
}

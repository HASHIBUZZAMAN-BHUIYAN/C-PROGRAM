#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 6
#define MAX_MESSAGES 10
#define MAX_MSG_LEN 100

// Candidate structure for failed members
struct Memorial01 {
    char info[150];   // "name,birth,email"
    char audition[20]; // e.g., "milliways"
};

// Rolling paper messages
char rollingpp01[MAX_MESSAGES][MAX_MSG_LEN];

// Initialize memorial array (immutable after init)
const struct Memorial01 memorial01_arr[] = {
    {"Kim Jisu,20040101,jisu@email.com", "milliways"},
    {"Han Yuna,20030505,yuna@email.com", "milliways"}
};

const char* failed_names[] = {"Kim Jisu", "Han Yuna"};
const char* failed_emails[] = {"jisu@email.com", "yuna@email.com"};
int rolling_count[2] = {0, 0}; // Track number of messages for each failed candidate

void add_message() {
    char sender[50], receiver[50], message[80];
    int i, found = -1;

    printf("\nEnter your name (sender): ");
    fgets(sender, sizeof(sender), stdin);
    sender[strcspn(sender, "\n")] = '\0';

    printf("Enter the recipient name (failed candidate): ");
    fgets(receiver, sizeof(receiver), stdin);
    receiver[strcspn(receiver, "\n")] = '\0';

    for (i = 0; i < 2; i++) {
        if (strcmp(receiver, failed_names[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Recipient not found or not a failed candidate.\n");
        return;
    }

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    // Compose and store JSON message
    if (rolling_count[found] < MAX_MESSAGES) {
        sprintf(rollingpp01[found * MAX_MESSAGES + rolling_count[found]], "\"%s\": \"%s\"", sender, message);
        rolling_count[found]++;
        printf("Message saved.\n");
    } else {
        printf("Message limit reached for %s.\n", receiver);
    }
}

void view_messages() {
    char name[50];
    int i, found = -1;

    printf("\nEnter the name of the failed candidate to view messages: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for (i = 0; i < 2; i++) {
        if (strcmp(name, failed_names[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Candidate not found or not a failed candidate.\n");
        return;
    }

    printf("\n--- Rolling Paper for %s ---\n", name);
    printf("Email: %s\n", failed_emails[found]);
    for (i = 0; i < rolling_count[found]; i++) {
        printf("%s\n", rollingpp01[found * MAX_MESSAGES + i]);
    }

    char choice[10];
    printf("\nDo you want to send this email? (yes/no): ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';

    if (strcmp(choice, "yes") == 0) {
        printf("Email has been sent to %s.\n", failed_emails[found]);
    } else {
        printf("Email not sent.\n");
    }
}

int main() {
    int option;
    while (1) {
        printf("\n=== Rolling Paper System ===\n");
        printf("1. Add a Rolling Paper Message\n");
        printf("2. View Messages for a Candidate\n");
        printf("3. Exit\n");
        printf("Choose option: ");
        scanf("%d", &option);
        getchar(); // consume hb newline

        if (option == 1) {
            add_message();
        } else if (option == 2) {
            view_messages();
        } else if (option == 3) {
            printf("Goodbye.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}

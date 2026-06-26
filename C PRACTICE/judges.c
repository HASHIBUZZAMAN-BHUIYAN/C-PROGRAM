#include <stdio.h>
#include <stdlib.h>

#define MAX_JUDGES 100
#define MAX_LENGTH 512

char *judges_array[MAX_JUDGES];

void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void remove_newline(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int main() {
    char project[100];
    int total_judges = 0;
    int selected_members = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project, sizeof(project), stdin);
    remove_newline(project);

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    clear_input_buffer();

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    clear_input_buffer();

    if (total_judges <= 0 || total_judges > MAX_JUDGES) {
        printf("Invalid number of judges.\n");
        return 1;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    for (int i = 0; i < total_judges; i++) {
        char name[100], gender[20], affiliation[100], title[100];
        char expertise[100], email[100], phone[30];
        int valid = 0;

        while (!valid) {
            printf("Judge %d:\n", i + 1);

            printf("  Name: ");
            fgets(name, sizeof(name), stdin);
            remove_newline(name);

            printf("  Gender: ");
            fgets(gender, sizeof(gender), stdin);
            remove_newline(gender);

            printf("  Affiliation: ");
            fgets(affiliation, sizeof(affiliation), stdin);
            remove_newline(affiliation);

            printf("  Title: ");
            fgets(title, sizeof(title), stdin);
            remove_newline(title);

            printf("  Expertise: ");
            fgets(expertise, sizeof(expertise), stdin);
            remove_newline(expertise);

            printf("  Email: ");
            fgets(email, sizeof(email), stdin);
            remove_newline(email);

            printf("  Phone: ");
            fgets(phone, sizeof(phone), stdin);
            remove_newline(phone);

            if (name[0] == '\0' || gender[0] == '\0' || affiliation[0] == '\0' ||
                title[0] == '\0' || expertise[0] == '\0' || email[0] == '\0' || phone[0] == '\0') {
                printf("The input items are incorrect. Please enter them again.\n");
            } else {
                valid = 1;
            }
        }

        judges_array[i] = (char *)malloc(MAX_LENGTH);
        if (judges_array[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        snprintf(judges_array[i], MAX_LENGTH, "%s|%s|%s|%s|%s|%s|%s",
                 name, gender, affiliation, title, expertise, email, phone);
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char choice;
    printf("[%s] Should we check the judge information? (Y/N): ", project);
    scanf(" %c", &choice);

    if (choice == 'Y' || choice == 'y') {
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            char name[100], gender[20], affiliation[100], title[100];
            char expertise[100], email[100], phone[30];

            int parsed = sscanf(judges_array[i], "%99[^|]|%19[^|]|%99[^|]|%99[^|]|%99[^|]|%99[^|]|%29[^|]",
                                name, gender, affiliation, title, expertise, email, phone);

            if (parsed != 7) {
                printf("[Judge %d] The input items are incorrect. Please enter them again.\n", i + 1);
                continue;
            }

            printf("[Judge %d]\n", i + 1);
            printf("Name: %s\n", name);
            printf("Gender: %s\n", gender);
            printf("Affiliation: %s\n", affiliation);
            printf("Title: %s\n", title);
            printf("Expertise: %s\n", expertise);
            printf("Email: %s\n", email);
            printf("Phone: %s\n", phone);
            printf("-----------------------------------\n");
        }
    } else if (choice == 'N' || choice == 'n') {
        printf("Program terminated.\n");
    } else {
        printf("Invalid choice. Program terminated.\n");
    }

    for (int i = 0; i < total_judges; i++) {
        free(judges_array[i]);
    }

    return 0;
}

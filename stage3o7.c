#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 5
#define MAX_NAME_LENGTH 50
#define MAX_TEAM_NAME_LENGTH 50

// Structure for storing team performance data
typedef struct {
    char team_name[MAX_TEAM_NAME_LENGTH];
    int team_avg_score;  // Average score of the team
    int team_min_score;  // Minimum score among members
    int team_duration;   // Total time spent on the course
    char result[10];     // Pass or Fail based on criteria
} TeamPerformance;

// Structure for storing member information
typedef struct {
    char member_name[MAX_NAME_LENGTH];
    int score;
    int duration;  // Time each member took to finish their tasks
} Member;

// Function prototypes
void inputBaseLine(int* avg_score, int* min_score, int* duration, int min_time, int max_time);
void evalTeamPerformance(TeamPerformance* team, Member members[], int num_members);
void learnHangul();
void learnKoreanGrammar();
void printTeamResult(TeamPerformance* team);

int main() {
    int choice;
    printf("Welcome to the Korean Learning Program!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Learn Hangul\n");
        printf("2. Learn Korean Grammar\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                learnHangul();
                break;
            case 2:
                learnKoreanGrammar();
                break;
            case 3:
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice. Please choose again.\n");
        }
    }

    return 0;
}

// Function to input team baseline values
void inputBaseLine(int* avg_score, int* min_score, int* duration, int min_time, int max_time) {
    printf("Enter the team average score (between 0 and 300): ");
    scanf("%d", avg_score);
    if (*avg_score < 0 || *avg_score > 300) {
        printf("Invalid score. It must be between 0 and 300.\n");
        return;
    }

    printf("Enter the team minimum score (between 0 and 300): ");
    scanf("%d", min_score);
    if (*min_score < 0 || *min_score > 300) {
        printf("Invalid score. It must be between 0 and 300.\n");
        return;
    }

    printf("Enter the team total duration (in minutes) (between %d and %d): ", min_time * MAX_MEMBERS, max_time * MAX_MEMBERS);
    scanf("%d", duration);
    if (*duration < min_time * MAX_MEMBERS || *duration > max_time * MAX_MEMBERS) {
        printf("Invalid duration. It must be between %d and %d minutes.\n", min_time * MAX_MEMBERS, max_time * MAX_MEMBERS);
        return;
    }
}

// Function to evaluate team performance
void evalTeamPerformance(TeamPerformance* team, Member members[], int num_members) {
    int total_score = 0;
    int min_score = members[0].score;
    int total_duration = 0;
    
    for (int i = 0; i < num_members; i++) {
        total_score += members[i].score;
        if (members[i].score < min_score) {
            min_score = members[i].score;
        }
        total_duration += members[i].duration;
    }

    team->team_avg_score = total_score / num_members;
    team->team_min_score = min_score;
    team->team_duration = total_duration;

    // Check if the team passes or fails
    if (team->team_avg_score >= 100 && team->team_min_score >= 60 && team->team_duration <= 120) {
        strcpy(team->result, "Pass");
    } else {
        strcpy(team->result, "Fail");
    }
}

// Function to learn Hangul
void learnHangul() {
    TeamPerformance team;
    Member members[MAX_MEMBERS];
    char team_name[MAX_TEAM_NAME_LENGTH];
    int avg_score, min_score, duration;

    printf("Enter the team name: ");
    scanf(" %[^\n]", team_name);
    strcpy(team.team_name, team_name);

    inputBaseLine(&avg_score, &min_score, &duration, 10, 30);

    printf("Enter the member scores and durations:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter member %d name: ", i + 1);
        scanf(" %[^\n]", members[i].member_name);
        printf("Enter score for %s (out of 100): ", members[i].member_name);
        scanf("%d", &members[i].score);
        printf("Enter duration (minutes) for %s: ", members[i].member_name);
        scanf("%d", &members[i].duration);
    }

    evalTeamPerformance(&team, members, MAX_MEMBERS);
    printTeamResult(&team);
}

// Function to learn Korean Grammar
void learnKoreanGrammar() {
    TeamPerformance team;
    Member members[MAX_MEMBERS];
    char team_name[MAX_TEAM_NAME_LENGTH];
    int avg_score, min_score, duration;

    printf("Enter the team name: ");
    scanf(" %[^\n]", team_name);
    strcpy(team.team_name, team_name);

    inputBaseLine(&avg_score, &min_score, &duration, 10, 20);

    printf("Enter the member scores and durations:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter member %d name: ", i + 1);
        scanf(" %[^\n]", members[i].member_name);
        printf("Enter score for %s (out of 100): ", members[i].member_name);
        scanf("%d", &members[i].score);
        printf("Enter duration (minutes) for %s: ", members[i].member_name);
        scanf("%d", &members[i].duration);
    }
//hb inject
    evalTeamPerformance(&team, members, MAX_MEMBERS);
    printTeamResult(&team);
}

// Function to print the team result
void printTeamResult(TeamPerformance* team) {
    printf("\nTeam: %s\n", team->team_name);
    printf("Average Score: %d\n", team->team_avg_score);
    printf("Minimum Score: %d\n", team->team_min_score);
    printf("Total Duration: %d minutes\n", team->team_duration);
    printf("Final Result: %s\n", team->result);
}

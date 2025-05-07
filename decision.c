#include <stdio.h>
#include <math.h>

#define MAX_MEMBERS 10
#define CATEGORY_COUNT 9

// Enum for categories
enum Category {
    PHYSICAL,
    KNOWLEDGE,
    SELF_MGMT,
    TEAMWORK,
    KOREAN,
    VOCAL,
    DANCE,
    VISUAL,
    ACTING
};

// Array of category names (1D array of strings)
const char category_names[CATEGORY_COUNT][20] = {
    "Physical Strength", "Knowledge", "Self-Management", "Teamwork",
    "Korean Language", "Vocal", "Dance", "Visual", "Acting"
};

int main() {
    int num_members;
    int min_score, pass_score;
    int scores[MAX_MEMBERS][CATEGORY_COUNT];
    int i, j;
    int category_totals[CATEGORY_COUNT] = {0};

    printf("Enter number of team members (1-10): ");
    scanf("%d", &num_members);
    if (num_members < 1 || num_members > MAX_MEMBERS) {
        printf("Invalid number of members.\n");
        return 1;
    }

    printf("Enter team average passing score (1–100): ");
    scanf("%d", &pass_score);

    printf("Enter minimum individual score (1–100): ");
    scanf("%d", &min_score);

    // Input scores
    for (i = 0; i < num_members; i++) {
        printf("\nEnter scores for Member %d (0–11 per category):\n", i + 1);
        for (j = 0; j < CATEGORY_COUNT; j++) {
            int score;
            printf("  %s: ", category_names[j]);
            scanf("%d", &score);

            if (score < min_score) {
                printf("\nMinimum required score is %d.\n", min_score);
                printf("All team members must retake %s.\n", category_names[j]);
                return 0;
            }

            if (score < 0 || score > 11) {
                printf("Invalid score! Must be 0–11.\n");
                return 1;
            }

            scores[i][j] = score;
            category_totals[j] += score;
        }
    }

    // Calculate averageh bscore (truncated)
    int total_score = 0;
    for (j = 0; j < CATEGORY_COUNT; j++) {
        total_score += category_totals[j];
    }

    int team_avg_score = total_score / (num_members * CATEGORY_COUNT);
    printf("\nTruncated team average score: %d\n", team_avg_score);

    if (team_avg_score < pass_score) {
        printf("Team failed to meet the average passing score.\n");
        return 0;
    }

    // Decision using switch
    printf("\n--- Milliways Debut Status ---\n");
    switch (team_avg_score) {
        case 95: case 96: case 97: case 98: case 99: case 100:
            printf("Congratulations! Your stage debut is confirmed!\n");
            break;

        case 90: case 91: case 92: case 93: case 94:
            printf("The Debut Certification Team will hold a final evaluation meeting to make a decision.\n");
            break;

        default:
            if (team_avg_score >= 80 && team_avg_score < 90) {
                // Calculate 3 lowest scoring categories
                int min1 = 0, min2 = 1, min3 = 2;
                for (j = 0; j < CATEGORY_COUNT; j++) {
                    int avg = category_totals[j] / num_members;
                    int a = category_totals[min1] / num_members;
                    int b = category_totals[min2] / num_members;
                    int c = category_totals[min3] / num_members;

                    if (avg < a || (min1 == min2 || min1 == min3)) min1 = j;
                    else if (avg < b || min2 == min1 || min2 == min3) min2 = j;
                    else if (avg < c || min3 == min1 || min3 == min2) min3 = j;
                }

                // Ensure unique lowest scores
                if (min1 == min2 || min1 == min3 || min2 == min3) {
                    int category_avg[CATEGORY_COUNT];
                    for (j = 0; j < CATEGORY_COUNT; j++)
                        category_avg[j] = category_totals[j] / num_members;

                    // Bubble sort categories by average score
                    for (i = 0; i < CATEGORY_COUNT - 1; i++) {
                        for (j = i + 1; j < CATEGORY_COUNT; j++) {
                            if (category_avg[i] > category_avg[j]) {
                                int temp = category_avg[i];
                                category_avg[i] = category_avg[j];
                                category_avg[j] = temp;

                                char tmpname[20];
                                strcpy(tmpname, category_names[i]);
                                strcpy((char*)category_names[i], category_names[j]);
                                strcpy((char*)category_names[j], tmpname);
                            }
                        }
                    }

                    printf("Retake the three lowest-scoring categories (%s, %s, %s) after 30 days.\n",
                           category_names[0], category_names[1], category_names[2]);
                } else {
                    printf("Retake the three lowest-scoring categories (%s, %s, %s) after 30 days.\n",
                           category_names[min1], category_names[min2], category_names[min3]);
                }
            } else {
                printf("The team must significantly improve before re-evaluation.\n");
            }
            break;
    }

    return 0;
}

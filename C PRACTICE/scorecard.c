#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 6
#define NUM_CATEGORIES 5
#define MAX_JUDGES 10

// Candidate data
char *candidate_names[NUM_CANDIDATES] = {
    "Jiyeon Park",
    "Ethan Smith",
    "Helena Silva",
    "Liam Wilson",
    "Sora Lee",
    "Noah Brown"
};
int candidate_ids[NUM_CANDIDATES];

// Each candidate has one scoring_sheet per judge: [ID, Music, Dance, Vocal, Visual, Expression, Total]
int scoring_sheets[MAX_JUDGES][NUM_CANDIDATES][7];
int total_judges = 0;

// Generate unique 6-digit IDs
void generate_unique_ids(unsigned int seed) {
    int i, j, duplicate;
    srand(seed);
    for (i = 0; i < NUM_CANDIDATES; i++) {
        do {
            duplicate = 0;
            candidate_ids[i] = 100000 + rand() % 900000;
            for (j = 0; j < i; j++) {
                if (candidate_ids[i] == candidate_ids[j]) {
                    duplicate = 1;
                    break;
                }
            }
        } while (duplicate);
    }
}

// Get candidate index by ID
int get_candidate_index_by_id(int id) {
    int i;
    for (i = 0; i < NUM_CANDIDATES; i++) {
        if (candidate_ids[i] == id) return i;
    }
    return -1;
}

// Get validated score input
int get_valid_score(const char *category) {
    int score;
    do {
        printf("%s (10-100): ", category);
        scanf("%d", &score);
        if (score < 10 || score > 100) {
            printf("Invalid input. Please enter a score between 10 and 100.\n");
        }
    } while (score < 10 || score > 100);
    return score;
}

// Clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Input scores
void enter_scores(int judge_index) {
    char judge_name[100], expertise[100];
    printf("####################################\n");
    printf("#     Audition Evaluation Entry    #\n");
    printf("####################################\n");
    printf("> Judge Name: ");
    fgets(judge_name, sizeof(judge_name), stdin);
    printf("> Expertise: ");
    fgets(expertise, sizeof(expertise), stdin);
    printf("++++++++++++++++++++++++++++++++++++\n");

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("Candidate: %s\n", candidate_names[i]);
        scoring_sheets[judge_index][i][0] = candidate_ids[i];
        int total = 0;
        total += scoring_sheets[judge_index][i][1] = get_valid_score("Music Proficiency");
        total += scoring_sheets[judge_index][i][2] = get_valid_score("Dance");
        total += scoring_sheets[judge_index][i][3] = get_valid_score("Vocal");
        total += scoring_sheets[judge_index][i][4] = get_valid_score("Visual");
        total += scoring_sheets[judge_index][i][5] = get_valid_score("Expression");
        scoring_sheets[judge_index][i][6] = total;
        printf("------------------------------------\n");
    }
    clear_input_buffer();
}

// Review and modify scores
void review_and_confirm(int judge_index) {
    char choice;
    do {
        printf("++++++++++++++++++++++++++++++++++++\n");
        printf("Submission completed.\nPlease review your input!\n");
        printf("------------------------------------\n");
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            printf("%s: %d\n", candidate_names[i], scoring_sheets[judge_index][i][6]);
        }

        printf("Would you like to submit? (Y/N): ");
        scanf(" %c", &choice);
        clear_input_buffer();

        if (choice == 'N' || choice == 'n') {
            printf("Here are the candidates and their IDs:\n");
            for (int i = 0; i < NUM_CANDIDATES; i++) {
                printf("%s - ID: %d\n", candidate_names[i], candidate_ids[i]);
            }

            while (1) {
                int id;
                printf("Enter candidate ID to modify (or -1 to finish): ");
                scanf("%d", &id);
                clear_input_buffer();
                if (id == -1) break;
                int index = get_candidate_index_by_id(id);
                if (index == -1) {
                    printf("Invalid ID. Try again.\n");
                } else {
                    int total = 0;
                    printf("Modifying scores for %s:\n", candidate_names[index]);
                    total += scoring_sheets[judge_index][index][1] = get_valid_score("Music Proficiency");
                    total += scoring_sheets[judge_index][index][2] = get_valid_score("Dance");
                    total += scoring_sheets[judge_index][index][3] = get_valid_score("Vocal");
                    total += scoring_sheets[judge_index][index][4] = get_valid_score("Visual");
                    total += scoring_sheets[judge_index][index][5] = get_valid_score("Expression");
                    scoring_sheets[judge_index][index][6] = total;
                }
            }
        }
    } while (choice != 'Y' && choice != 'y');

    printf("***Final submission completed.***\n");
}

// Compile final selection
void compile_final_results() {
    int totals[NUM_CANDIDATES] = {0};
    int indices[NUM_CANDIDATES];
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        for (int j = 0; j < total_judges; j++) {
            totals[i] += scoring_sheets[j][i][6];
        }
        indices[i] = i;
    }

    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            if (totals[indices[j]] > totals[indices[i]]) {
                int tmp = indices[i];
                indices[i] = indices[j];
                indices[j] = tmp;
            }
        }
    }

    printf("=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[indices[i]]);
    }
    printf(">\n");
}

int main() {
    unsigned int seed;
    printf("Enter a seed number for ID generation: ");
    scanf("%u", &seed);
    clear_input_buffer();
    generate_unique_ids(seed);

    printf("How many judges are entering scores? (max %d): ", MAX_JUDGES);
    scanf("%d", &total_judges);
    clear_input_buffer();
    if (total_judges > MAX_JUDGES) total_judges = MAX_JUDGES;

    for (int i = 0; i < total_judges; i++) {
        enter_scores(i);
        review_and_confirm(i);
    }

    compile_final_results();
    return 0;
}

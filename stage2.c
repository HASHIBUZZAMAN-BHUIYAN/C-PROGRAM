#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 20
#define MAX_MENTORS 8
#define NAME_LEN 50

typedef struct {
    int ascii_sum;
    int ability;
    char nickname[NAME_LEN];
} Trainee;

typedef struct {
    int id; // 1 to 8
    char name[NAME_LEN];
    int mentee_index; // indexhb in trainee list
} Mentor;

Trainee trainees[MAX_TRAINEES];
Mentor mentors[MAX_MENTORS];
int trainee_count = 0;
int mentor_count = 0;

// Function to calculate ASCII sum of nickname
int parseIntMember(const char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

// Function to get random ability between 100 and 1000
int getRandomAbility() {
    return 100 + rand() % 901;
}

// Function to initialize trainee list
void initTrainees(const char *names[], int count) {
    trainee_count = count;
    for (int i = 0; i < count; i++) {
        strncpy(trainees[i].nickname, names[i], NAME_LEN);
        trainees[i].ascii_sum = parseIntMember(names[i]);
        trainees[i].ability = getRandomAbility();
    }
}

// Function to input mentor data
void inputMentors(const char *names[], int count) {
    mentor_count = count > MAX_MENTORS ? MAX_MENTORS : count;
    for (int i = 0; i < mentor_count; i++) {
        mentors[i].id = i + 1;
        strncpy(mentors[i].name, names[i], NAME_LEN);
        mentors[i].mentee_index = -1;
    }
}

// Function to match mentors to trainees 1:1 using modulo
void matchMentoring() {
    int used_trainees[MAX_TRAINEES] = {0};
    int assigned = 0;

    for (int i = 0; i < mentor_count && assigned < trainee_count; i++) {
        for (int j = 0; j < trainee_count; j++) {
            if (!used_trainees[j] && (j % MAX_MENTORS) == (mentors[i].id - 1)) {
                mentors[i].mentee_index = j;
                used_trainees[j] = 1;
                assigned++;
                break;
            }
        }
    }

    // Fallback: randomly assign remaining mentors
    for (int i = 0; i < mentor_count; i++) {
        if (mentors[i].mentee_index == -1) {
            for (int j = 0; j < trainee_count; j++) {
                if (!used_trainees[j]) {
                    mentors[i].mentee_index = j;
                    used_trainees[j] = 1;
                    break;
                }
            }
        }
    }
}

// Function to print trainee and mentor pairs
void printMatches() {
    printf("Trainee Index | ASCII Sum | Ability | Mentor ID | Mentor Name\n");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < mentor_count; i++) {
        int idx = mentors[i].mentee_index;
        if (idx != -1) {
            printf("%13d | %10d | %7d | %9d | %s\n",
                   idx,
                   trainees[idx].ascii_sum,
                   trainees[idx].ability,
                   mentors[i].id,
                   mentors[i].name);
        }
    }
}

// Example usage
int main() {
    srand((unsigned int)time(NULL));

    // Sample data (replace with Millieway’s member info)
    const char *trainee_names[MAX_TRAINEES] = {
        "Arthur", "Lancelot", "Guinevere", "Merlin",
        "Morgana", "Percival", "Tristan", "Galahad",
        "Elaine", "Isolde", "Kay", "Bors",
        "Gareth", "Geraint", "Bedivere", "Uther",
        "Leodegrance", "Palamedes", "Yvain", "Pellinore"
    };

    const char *mentor_names[MAX_MENTORS] = {
        "MentorA", "MentorB", "MentorC", "MentorD",
        "MentorE", "MentorF", "MentorG", "MentorH"
    };

    initTrainees(trainee_names, 20);
    inputMentors(mentor_names, 8);
    matchMentoring();
    printMatches();

    return 0;
}

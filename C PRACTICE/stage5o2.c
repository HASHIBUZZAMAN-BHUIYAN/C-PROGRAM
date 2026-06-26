#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MEMBERS 100
#define MAX_NAME_LENGTH 100
#define MAX_GROUP_NAME_LENGTH 100

// Immutable Tempo and Rhythm Data Structure
typedef struct {
    int bpm;           // Beats per minute
    char rhythm[10];   // Time signature
} TempoRhythm;

// Practice Record Structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    char date[20];
    int target_beats;
    double duration;   // seconds
} PracticeRecord;

// Member Information
char memberList[MAX_MEMBERS][MAX_NAME_LENGTH];
int memberCount = 0;

// Group Information
typedef struct {
    char groupName[MAX_GROUP_NAME_LENGTH];
    char members[MAX_MEMBERS][MAX_NAME_LENGTH];
    int memberCount;
} TraineeGroup;

TraineeGroup traineeGroups[MAX_MEMBERS];
int groupCount = 0;

TempoRhythm tempoRhythms[] = {
    {60, "2/4"}, {60, "3/4"}, {60, "4/4"}, {60, "6/8"},
    {80, "2/4"}, {80, "3/4"}, {80, "4/4"}, {80, "6/8"},
    {120, "2/4"}, {120, "3/4"}, {120, "4/4"}, {120, "6/8"}
};
int tempoCount = 12;

void loadTrainees(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening trainee file");
        exit(1);
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,]", memberList[memberCount++]);
    }
    fclose(file);
}

void loadGroups(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening group file");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",\n");
        if (!token) continue;

        strcpy(traineeGroups[groupCount].groupName, token);
        int count = 0;
        while ((token = strtok(NULL, ",\n")) != NULL) {
            strcpy(traineeGroups[groupCount].members[count++], token);
        }
        traineeGroups[groupCount].memberCount = count;
        groupCount++;
    }
    fclose(file);
}

int validateMember(const char *name) {
    for (int i = 0; i < memberCount; ++i) {
        if (strcmp(name, memberList[i]) == 0) return 1;
    }
    return 0;
}

void inputTrainee(char *name) {
    int attempts = 3;
    while (attempts--) {
        printf("Enter your trainee name: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = 0;
        if (validateMember(name)) return;
        printf("Invalid name. Attempts left: %d\n", attempts);
    }
    printf("Too many failed attempts. Returning to menu.\n");
    exit(0);
}

void writeFile(PracticeRecord *record) {
    FILE *file = fopen("beat_test_result.txt", "a");
    if (!file) {
        perror("Error writing result file");
        return;
    }
    fprintf(file, "%s,%s,%d,%.2f\n",
        record->name, record->date, record->target_beats, record->duration);
    fclose(file);
}

void printResult(int target, double duration) {
    double expected = (double)target;
    double diff = duration - expected;
    printf("\nTarget beats: %d\n", target);
    printf("Your counted time: %.2f seconds\n", duration);
    printf("Difference: %.2f seconds (%s)\n",
           fabs(diff), diff < 0 ? "early" : "late");
}

void testBeat(PracticeRecord *record) {
    srand(time(NULL));
    int index = rand() % tempoCount;
    TempoRhythm tr = tempoRhythms[index];

    double beat_interval = 60.0 / tr.bpm;
    int beats = 60.0 / beat_interval; // For 60 seconds duration

    record->target_beats = beats;
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[20];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%y%m%d%H", timeinfo);
    strcpy(record->date, buffer);

    printf("\nTempo: %d BPM, Rhythm: %s\n", tr.bpm, tr.rhythm);
    printf("Target beats in 60s: %d\n", beats);
    printf("Press Enter to start counting...\n");
    getchar();

    clock_t start = clock();
    printf("Counting... Press Enter when done.\n");
    getchar();
    clock_t end = clock();
    record->duration = (double)(end - start) / CLOCKS_PER_SEC;

    printResult(beats, record->duration);
    writeFile(record);
}

void improveSenseOfBeat() {
    char name[MAX_NAME_LENGTH];
    inputTrainee(name);

    PracticeRecord record;
    strcpy(record.name, name);

    int testCount = 0;
    while (testCount < 3) {
        printf("\nTest #%d\n", testCount + 1);
        testBeat(&record);
        testCount++;
    }
}

// BONUS: Select trainee by group
void selectFromGroup() {
    printf("Available groups:\n");
    for (int i = 0; i < groupCount; ++i) {
        printf("%d. %s\n", i + 1, traineeGroups[i].groupName);
    }
    int choice;
    printf("Select group: ");
    scanf("%d", &choice); getchar();

    if (choice < 1 || choice > groupCount) {
        printf("Invalid choice.\n");
        return;
    }

    TraineeGroup group = traineeGroups[choice - 1];
    printf("Members in %s:\n", group.groupName);
    for (int i = 0; i < group.memberCount; ++i) {
        printf("%d. %s\n", i + 1, group.members[i]);
    }
    int mchoice;
    printf("Select member: ");
    scanf("%d", &mchoice); getchar();

    if (mchoice < 1 || mchoice > group.memberCount) {
        printf("Invalid member choice.\n");
        return;
    }

    PracticeRecord record;
    strcpy(record.name, group.members[mchoice - 1]);

    int testCount = 0;
    while (testCount < 3) {
        printf("\nTest #%d\n", testCount + 1);
        testBeat(&record);
        testCount++;
    }
}//hb inject

int main() {
    loadTrainees("trainee.csv");
    loadGroups("newtrainees.csv");

    printf("1. Improve Beat Sense (Single Trainee)\n");
    printf("2. Improve Beat Sense (By Group)\n");
    int option;
    printf("Select option: ");
    scanf("%d", &option); getchar();

    if (option == 1) improveSenseOfBeat();
    else if (option == 2) selectFromGroup();
    else printf("Invalid selection.\n");

    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 10
#define MAX_DAYS 7

typedef struct {
    int weight; // in kg
    int height; // in cm
    char condition[100];
} PhysicalCondition;

typedef struct {
    char routine[100];
} WorkoutRoutine;

typedef struct {
    char diet[100];
} DietPlan;

typedef struct {
    char name[50];
    PhysicalCondition physical[MAX_DAYS];
    WorkoutRoutine workout[MAX_DAYS];
    DietPlan diet[MAX_DAYS];
} Member;

Member members[MAX_MEMBERS];
int memberCount = 0;

const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// Function declarations
void addMember();
void enterPhysicalCondition();
void viewPhysicalCondition();
void setWorkoutRoutine();
void viewWorkoutRoutine();
void setDietPlan();
void viewDietPlan();
int selectMember();
int selectDay();

int main() {
    int choice;
    while (1) {
        printf("\n--- Millieway's Health Management System ---\n");
        printf("1. Add Member\n");
        printf("2. Enter Physical Condition\n");
        printf("3. View Physical Condition\n");
        printf("4. Set Workout Routine\n");
        printf("5. View Workout Routine\n");
        printf("6. Set Diet Plan\n");
        printf("7. View Diet Plan\n");
        printf("0. Exit\n");
        printf("Select a menu option: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addMember(); break;
            case 2: enterPhysicalCondition(); break;
            case 3: viewPhysicalCondition(); break;
            case 4: setWorkoutRoutine(); break;
            case 5: viewWorkoutRoutine(); break;
            case 6: setDietPlan(); break;
            case 7: viewDietPlan(); break;
            case 0: return 0;
            default: printf("Invalid option. Try again.\n");
        }
    }
    return 0;
}

void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Member limit reached.\n");
        return;
    }
    printf("Enter member name: ");
    fgets(members[memberCount].name, sizeof(members[memberCount].name), stdin);
    members[memberCount].name[strcspn(members[memberCount].name, "\n")] = 0; // remove newline
    printf("Member '%s' added.\n", members[memberCount].name);
    memberCount++;
}

int selectMember() {
    if (memberCount == 0) {
        printf("No members available.\n");
        return -1;
    }
    for (int i = 0; i < memberCount; i++) {
        printf("%d. %s\n", i + 1, members[i].name);
    }
    printf("Select member (1-%d): ", memberCount);
    int index;
    scanf("%d", &index);
    getchar();
    if (index < 1 || index > memberCount) {
        printf("Invalid selection.\n");
        return -1;
    }
    return index - 1;
}

int selectDay() {
    for (int i = 0; i < MAX_DAYS; i++) {
        printf("%d. %s\n", i + 1, days[i]);
    }
    printf("Select day (1-7): ");
    int day;
    scanf("%d", &day);
    getchar();
    if (day < 1 || day > MAX_DAYS) {
        printf("Invalid day.\n");
        return -1;
    }
    return day - 1;
}

void enterPhysicalCondition() {
    int idx = selectMember();
    if (idx == -1) return;
    int day = selectDay();
    if (day == -1) return;

    printf("Enter weight (kg): ");
    scanf("%d", &members[idx].physical[day].weight);
    printf("Enter height (cm): ");
    scanf("%d", &members[idx].physical[day].height);
    getchar();
    printf("Enter condition description: ");
    fgets(members[idx].physical[day].condition, sizeof(members[idx].physical[day].condition), stdin);
    members[idx].physical[day].condition[strcspn(members[idx].physical[day].condition, "\n")] = 0;

    printf("Physical condition for %s on %s saved.\n", members[idx].name, days[day]);
}

void viewPhysicalCondition() {
    int idx = selectMember();
    if (idx == -1) return;
    int day = selectDay();
    if (day == -1) return;

    PhysicalCondition *pc = &members[idx].physical[day];
    printf("\n--- %s's Physical Condition on %s ---\n", members[idx].name, days[day]);
    printf("Weight: %d kg\n", pc->weight);
    printf("Height: %d cm\n", pc->height);
    printf("Condition: %s\n", pc->condition);
}

void setWorkoutRoutine() {
    int idx = selectMember();
    if (idx == -1) return;
    int day = selectDay();
    if (day == -1) return;

    printf("Enter workout routine: ");
    fgets(members[idx].workout[day].routine, sizeof(members[idx].workout[day].routine), stdin);
    members[idx].workout[day].routine[strcspn(members[idx].workout[day].routine, "\n")] = 0;

    printf("Workout routine for %s on %s saved.\n", members[idx].name, days[day]);
}

void viewWorkoutRoutine() {
    int idx = selectMember();
    if (idx == -1) return;
    int day = selectDay();
    if (day == -1) return;

    printf("\n--- %s's Workout on %s ---\n", members[idx].name, days[day]);
    printf("Routine: %s\n", members[idx].workout[day].routine);
}

void setDietPlan() {
    int idx = selectMember();
    if (idx == -1) return;
    int day = selectDay();
    if (day == -1) return;

    printf("Enter diet plan: ");
    fgets(members[idx].diet[day].diet, sizeof(members[idx].diet[day].diet), stdin);
    members[idx].diet[day].diet[strcspn(members[idx].diet[day].diet, "\n")] = 0;

    printf("Diet plan for %s on %s saved.\n", members[idx].name, days[day]);
}

void viewDietPlan() {
    int idx = selectMember();
    if (idx == -1) return;
    int day = selectDay();
    if (day == -1) return;

    printf("\n--- %s's Diet on %s ---\n", members[idx].name, days[day]);
    printf("Diet: %s\n", members[idx].diet[day].diet);
}

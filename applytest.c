#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_EXAMS 9

// Simulate current date for testing (e.g., 20250507 = May 7, 2025)
#define CURRENT_DATE 20250507

// Categories
const char categories01_arr[MAX_EXAMS][20] = {
    "Physical Strength", "Knowledge", "Self-Management", "Teamwork",
    "Korean Language", "Vocal", "Dance", "Visual", "Acting"
};

// Exam schedule info
int exam_dates01_arr[MAX_EXAMS]; // YYYYMMDD per category
int scheduled01_arr[MAX_EXAMS];  // 1 if scheduled

int training_start_date01 = 0;

// Utility: Convert YYYYMMDD to days since epoch (simplified)
int date_to_days(int yyyymmdd) {
    int y = yyyymmdd / 10000;
    int m = (yyyymmdd / 100) % 100;
    int d = yyyymmdd % 100;
    return y * 365 + m * 30 + d;
}

int date_diff_days(int d1, int d2) {
    return date_to_days(d2) - date_to_days(d1);
}

// Check exam eligibility logic
int is_eligible(int index) {
    if (index == 0 || index == 1) return 1; // Physical Strength or Knowledge
    if (index == 2 || index == 3) {
        if (scheduled01_arr[0] && scheduled01_arr[1]) return 1;
        return 0;
    }
    if (index >= 4) {
        if (scheduled01_arr[2] && scheduled01_arr[3]) return 1;
        return 0;
    }
    return 0;
}

// Schedule exam
void schedule_exam() {
    int index, exam_date;
    printf("\nAvailable Training Categories:\n");
    for (int i = 0; i < MAX_EXAMS; i++) {
        printf("%d. %s\n", i + 1, categories01_arr[i]);
    }
    printf("Select a category to schedule (1–9): ");
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > 9) {
        printf("Invalid category.\n");
        return;
    }
    index--;

    if (!is_eligible(index)) {
        printf("You are not eligible to take this exam yet.\n");
        return;
    }

    printf("Enter exam date (YYYYMMDD): ");
    scanf("%d", &exam_date);
    getchar();

    int diff = date_diff_days(training_start_date01, exam_date);
    if (diff < 30 || diff > 100) {
        printf("Exam must be taken 30–100 days after training start date.\n");
        return;
    }

    exam_dates01_arr[index] = exam_date;
    scheduled01_arr[index] = 1;

    printf("Exam scheduled for %s on %d.\n", categories01_arr[index], exam_date);
}

// Show reminders if any exam is within 10 days
void check_reminders() {
    printf("\n--- Exam Reminders ---\n");
    int reminder_shown = 0;
    for (int i = 0; i < MAX_EXAMS; i++) {
        if (scheduled01_arr[i]) {
            int diff = date_diff_days(CURRENT_DATE, exam_dates01_arr[i]);
            if (diff >= 0 && diff <= 10) {
                printf("Reminder: %s exam on %d is coming soon (in %d days).\n",
                       categories01_arr[i], exam_dates01_arr[i], diff);
                reminder_shown = 1;
            }
        }
    }
    if (!reminder_shown) {
        printf("No upcoming exams within the next 10 days.\n");
    }
}

// Assign test venue if today is exam day
void assign_exam_venue() {
    printf("\n--- Today's Exams (%d) ---\n", CURRENT_DATE);
    int exam_today = 0;

    for (int i = 0; i < MAX_EXAMS; i++) {
        if (scheduled01_arr[i] && exam_dates01_arr[i] == CURRENT_DATE) {
            int room = (CURRENT_DATE * (i + 3)) % 10 + 1; // deterministic random
            printf("%s exam is today. Assigned to Room %d.\n", categories01_arr[i], room);
            exam_today = 1;
        }
    }

    if (!exam_today) {
        printf("No exams scheduled for today.\n");
    }
}

// Entry point
int main() {
    int option;

    printf("Enter training start date (YYYYMMDD): ");
    scanf("%d", &training_start_date01);
    getchar();

    while (1) {
        printf("\n=== Certification Exam System ===\n");
        printf("1. Schedule Exam\n");
        printf("2. Check Reminders\n");
        printf("3. Assign Venue for Today's Exams\n");
        printf("4. Exit\n");
        printf("Select option: ");
        scanf("%d", &option);
        getchar();

        if (option == 1) schedule_exam();
        else if (option == 2) check_reminders();
        else if (option == 3) assign_exam_venue();
        else if (option == 4) break;
        else printf("Invalid option.\n");
    }

    return 0;
}

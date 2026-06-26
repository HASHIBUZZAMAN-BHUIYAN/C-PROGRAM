/*
 * Day 12 Mini-Project — Simple CSV Student Database
 * Compile: gcc mini_project.c -o mini_project.exe
 * Creates: students.csv
 */
#include <stdio.h>
#include <string.h>

#define MAX 20
typedef struct { char name[64]; int age; float gpa; } Student;

void save_csv(const char *filename, const Student *arr, int n) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror("save"); return; }
    fprintf(f, "name,age,gpa\n");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s,%d,%.2f\n", arr[i].name, arr[i].age, arr[i].gpa);
    fclose(f);
}

int load_csv(const char *filename, Student *arr, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    char line[128];
    fgets(line, sizeof(line), f);  /* skip header */
    int n = 0;
    while (n < max && fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        sscanf(line, "%63[^,],%d,%f", arr[n].name, &arr[n].age, &arr[n].gpa);
        n++;
    }
    fclose(f);
    return n;
}

int main(void) {
    Student students[MAX];
    int count = 0;

    printf("=== CSV Student Database ===\n");
    printf("Enter students (blank name to stop):\n");
    while (count < MAX) {
        printf("Name: "); fgets(students[count].name, 64, stdin);
        students[count].name[strcspn(students[count].name, "\n")] = '\0';
        if (!students[count].name[0]) break;
        printf("Age : "); scanf("%d",  &students[count].age);
        printf("GPA : "); scanf("%f",  &students[count].gpa);
        getchar();  /* consume newline */
        count++;
    }

    save_csv("students.csv", students, count);
    printf("Saved to students.csv\n");

    /* Reload and print */
    Student loaded[MAX];
    int n = load_csv("students.csv", loaded, MAX);
    printf("\nLoaded from CSV:\n");
    for (int i = 0; i < n; i++)
        printf("  %-20s  age=%d  gpa=%.2f\n", loaded[i].name, loaded[i].age, loaded[i].gpa);

    remove("students.csv");
    return 0;
}

/*
 * Day 14 Capstone — Student Record Manager
 * Demonstrates: structs, dynamic arrays, file I/O, pointers, strings, loops
 *
 * Compile: gcc lesson.c -o capstone.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE    "students_db.csv"
#define INITIAL_CAP 8

typedef struct {
    int   id;
    char  name[64];
    int   age;
    float gpa;
} Student;

typedef struct {
    Student *data;
    int      size;
    int      capacity;
} DB;

/* --- DB lifecycle --- */
DB* db_create(void) {
    DB *db = malloc(sizeof(DB));
    db->data     = malloc(INITIAL_CAP * sizeof(Student));
    db->size     = 0;
    db->capacity = INITIAL_CAP;
    return db;
}

void db_free(DB *db) {
    free(db->data);
    free(db);
}

int db_add(DB *db, Student s) {
    if (db->size == db->capacity) {
        db->capacity *= 2;
        Student *bigger = realloc(db->data, db->capacity * sizeof(Student));
        if (!bigger) return 0;
        db->data = bigger;
    }
    db->data[db->size++] = s;
    return 1;
}

/* --- File I/O --- */
void db_save(const DB *db) {
    FILE *f = fopen(DB_FILE, "w");
    if (!f) { perror("save"); return; }
    fprintf(f, "id,name,age,gpa\n");
    for (int i = 0; i < db->size; i++) {
        Student *s = &db->data[i];
        fprintf(f, "%d,%s,%d,%.2f\n", s->id, s->name, s->age, s->gpa);
    }
    fclose(f);
    printf("Saved %d record(s) to %s\n", db->size, DB_FILE);
}

void db_load(DB *db) {
    FILE *f = fopen(DB_FILE, "r");
    if (!f) return;   /* no file yet is OK */
    char line[128];
    fgets(line, sizeof(line), f);   /* skip header */
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        Student s;
        if (sscanf(line, "%d,%63[^,],%d,%f", &s.id, s.name, &s.age, &s.gpa) == 4)
            db_add(db, s);
    }
    fclose(f);
    printf("Loaded %d record(s) from %s\n", db->size, DB_FILE);
}

/* --- Operations --- */
void db_list(const DB *db) {
    if (db->size == 0) { printf("  (no records)\n"); return; }
    printf("  %-5s  %-22s  %-5s  %s\n", "ID", "Name", "Age", "GPA");
    printf("  %-5s  %-22s  %-5s  %s\n", "-----", "----------------------", "-----", "----");
    for (int i = 0; i < db->size; i++) {
        Student *s = &db->data[i];
        printf("  %-5d  %-22s  %-5d  %.2f\n", s->id, s->name, s->age, s->gpa);
    }
}

Student *db_find_id(DB *db, int id) {
    for (int i = 0; i < db->size; i++)
        if (db->data[i].id == id) return &db->data[i];
    return NULL;
}

Student *db_find_name(DB *db, const char *query) {
    for (int i = 0; i < db->size; i++)
        if (strstr(db->data[i].name, query)) return &db->data[i];
    return NULL;
}

int db_delete(DB *db, int id) {
    for (int i = 0; i < db->size; i++) {
        if (db->data[i].id == id) {
            memmove(&db->data[i], &db->data[i+1],
                    (db->size - i - 1) * sizeof(Student));
            db->size--;
            return 1;
        }
    }
    return 0;
}

int gpa_cmp(const void *a, const void *b) {
    float diff = ((Student*)b)->gpa - ((Student*)a)->gpa;  /* descending */
    return (diff > 0) - (diff < 0);
}

void db_sort_by_gpa(DB *db) {
    qsort(db->data, db->size, sizeof(Student), gpa_cmp);
}

/* --- UI helpers --- */
static void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    DB *db = db_create();
    db_load(db);   /* load from file if it exists */

    int next_id = 1;
    for (int i = 0; i < db->size; i++)
        if (db->data[i].id >= next_id) next_id = db->data[i].id + 1;

    printf("\n========================================\n");
    printf("  Student Record Manager\n");
    printf("========================================\n");

    int running = 1;
    while (running) {
        printf("\n[1] Add  [2] List  [3] Search  [4] Delete  [5] Sort by GPA  [6] Save & Quit\n> ");
        int choice;
        if (scanf("%d", &choice) != 1) { clear_input(); continue; }
        clear_input();

        switch (choice) {
        case 1: {
            Student s;
            s.id = next_id++;
            printf("Name: "); fgets(s.name, 64, stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Age : "); scanf("%d",  &s.age); clear_input();
            printf("GPA : "); scanf("%f",  &s.gpa); clear_input();
            db_add(db, s);
            printf("Added ID=%d\n", s.id);
            break;
        }
        case 2:
            db_list(db);
            break;
        case 3: {
            printf("Search by (1) ID  (2) Name: ");
            int mode; scanf("%d", &mode); clear_input();
            if (mode == 1) {
                int id; printf("ID: "); scanf("%d", &id); clear_input();
                Student *s = db_find_id(db, id);
                if (s) printf("Found: %-22s age=%d gpa=%.2f\n", s->name, s->age, s->gpa);
                else   printf("Not found.\n");
            } else {
                char q[64]; printf("Name fragment: "); fgets(q, 64, stdin);
                q[strcspn(q, "\n")] = '\0';
                Student *s = db_find_name(db, q);
                if (s) printf("Found: ID=%d  %-22s age=%d gpa=%.2f\n", s->id, s->name, s->age, s->gpa);
                else   printf("Not found.\n");
            }
            break;
        }
        case 4: {
            int id; printf("Delete ID: "); scanf("%d", &id); clear_input();
            printf(db_delete(db, id) ? "Deleted.\n" : "ID not found.\n");
            break;
        }
        case 5:
            db_sort_by_gpa(db);
            printf("Sorted by GPA (highest first):\n");
            db_list(db);
            break;
        case 6:
            db_save(db);
            running = 0;
            break;
        default:
            printf("Invalid choice.\n");
        }
    }

    db_free(db);
    printf("Goodbye!\n");
    return 0;
}

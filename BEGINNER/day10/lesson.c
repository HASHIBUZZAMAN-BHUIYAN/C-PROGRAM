/*
 * Day 10 — Structs and Unions
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* --- Struct definitions --- */
typedef struct {
    double x, y;
} Point;

typedef struct {
    char  name[64];
    int   id;
    float gpa;
} Student;

/* --- Functions using structs --- */
double distance(Point a, Point b) {  /* pass by value: gets copies */
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

void student_print(const Student *s) {   /* pass by pointer: more efficient */
    printf("  ID:%d  %-20s  GPA:%.2f\n", s->id, s->name, s->gpa);
}

void student_raise_gpa(Student *s, float delta) {
    s->gpa += delta;
    if (s->gpa > 4.0f) s->gpa = 4.0f;
}

int main(void) {
    printf("=== Day 10: Structs & Unions ===\n\n");

    /* --- Basic struct usage --- */
    Point p1 = {0.0, 0.0};
    Point p2 = {3.0, 4.0};
    printf("p1=(%.1f,%.1f)  p2=(%.1f,%.1f)\n", p1.x, p1.y, p2.x, p2.y);
    printf("Distance: %.2f\n", distance(p1, p2));

    /* --- Modifying via pointer --- */
    Point *pp = &p1;
    pp->x = 1.0;   /* arrow operator for pointer-to-struct */
    pp->y = 1.0;
    printf("p1 moved to (%.1f,%.1f)\n", p1.x, p1.y);

    /* --- Array of structs --- */
    printf("\n--- Student Roster ---\n");
    Student students[3] = {
        {"Alice Smith",  1001, 3.8f},
        {"Bob Johnson",  1002, 3.2f},
        {"Carol White",  1003, 3.6f}
    };

    for (int i = 0; i < 3; i++) student_print(&students[i]);

    student_raise_gpa(&students[1], 0.5f);
    printf("\nAfter Bob's GPA raise:\n");
    student_print(&students[1]);

    /* --- Nested struct --- */
    typedef struct {
        char street[64];
        char city[32];
        int  zip;
    } Address;

    typedef struct {
        char    name[64];
        int     age;
        Address addr;
    } Person;

    Person person = {"Dave", 30, {"123 Main St", "Springfield", 62701}};
    printf("\nPerson: %s, age %d\n", person.name, person.age);
    printf("Address: %s, %s %d\n",
           person.addr.street, person.addr.city, person.addr.zip);

    /* --- Union --- */
    printf("\n--- Union ---\n");
    union Data {
        int   i;
        float f;
        char  c;
    };
    union Data d;
    d.i = 65;
    printf("As int  : %d\n", d.i);
    printf("As char : %c  (union: all members share same memory)\n", d.c);
    d.f = 3.14f;
    printf("As float: %.2f  (overwrote the int)\n", d.f);
    printf("Size of union: %zu  (= largest member)\n", sizeof(d));

    return 0;
}

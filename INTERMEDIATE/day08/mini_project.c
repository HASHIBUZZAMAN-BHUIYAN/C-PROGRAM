/*
 * Int Day 08 Mini-Project — Arena Allocator (bump pointer)
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define ARENA_SIZE (4 * 1024)  /* 4 KB arena */

typedef struct {
    uint8_t buf[ARENA_SIZE];
    size_t  used;
} Arena;

void arena_init(Arena *a) { a->used = 0; }

void* arena_alloc(Arena *a, size_t size) {
    /* Align to 8 bytes */
    size_t aligned = (size + 7) & ~(size_t)7;
    if (a->used + aligned > ARENA_SIZE) return NULL;
    void *ptr = a->buf + a->used;
    a->used += aligned;
    return ptr;
}

void arena_reset(Arena *a) { a->used = 0; }

typedef struct { char name[32]; int age; float score; } Person;

int main(void) {
    Arena arena; arena_init(&arena);
    printf("=== Arena Allocator ===\n");
    printf("Arena size: %d bytes\n", ARENA_SIZE);

    Person *p1 = arena_alloc(&arena, sizeof(Person));
    Person *p2 = arena_alloc(&arena, sizeof(Person));
    Person *p3 = arena_alloc(&arena, sizeof(Person));

    if (p1) { strcpy(p1->name,"Alice"); p1->age=25; p1->score=95.5f; }
    if (p2) { strcpy(p2->name,"Bob");   p2->age=30; p2->score=88.0f; }
    if (p3) { strcpy(p3->name,"Carol"); p3->age=28; p3->score=92.3f; }

    printf("Used: %zu / %d bytes\n", arena.used, ARENA_SIZE);
    if(p1) printf("  %-10s age=%d score=%.1f\n", p1->name, p1->age, p1->score);
    if(p2) printf("  %-10s age=%d score=%.1f\n", p2->name, p2->age, p2->score);
    if(p3) printf("  %-10s age=%d score=%.1f\n", p3->name, p3->age, p3->score);

    /* Allocate a string in the arena */
    char *msg = arena_alloc(&arena, 64);
    if (msg) { strcpy(msg, "Arena-allocated string!"); printf("String: %s\n", msg); }

    arena_reset(&arena);
    printf("After reset: used=%zu\n", arena.used);
    return 0;
}

/*
 * Day 11 Mini-Project — Dynamic Integer Stack
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int  *data;
    int   size;
    int   capacity;
} Stack;

Stack* stack_create(int cap) {
    Stack *s = malloc(sizeof(Stack));
    if (!s) return NULL;
    s->data = malloc(cap * sizeof(int));
    if (!s->data) { free(s); return NULL; }
    s->size = 0;
    s->capacity = cap;
    return s;
}

int stack_push(Stack *s, int val) {
    if (s->size == s->capacity) {
        int new_cap = s->capacity * 2;
        int *bigger = realloc(s->data, new_cap * sizeof(int));
        if (!bigger) return 0;
        s->data = bigger;
        s->capacity = new_cap;
    }
    s->data[s->size++] = val;
    return 1;
}

int stack_pop(Stack *s, int *out) {
    if (s->size == 0) return 0;
    *out = s->data[--s->size];
    return 1;
}

void stack_free(Stack *s) {
    free(s->data);
    free(s);
}

int main(void) {
    Stack *s = stack_create(4);
    printf("=== Dynamic Stack ===\n");
    for (int i = 1; i <= 10; i++) {
        stack_push(s, i * 5);
        printf("Pushed %d  (size=%d cap=%d)\n", i*5, s->size, s->capacity);
    }
    printf("\nPopping:\n");
    int val;
    while (stack_pop(s, &val)) printf("  %d\n", val);
    stack_free(s);
    return 0;
}

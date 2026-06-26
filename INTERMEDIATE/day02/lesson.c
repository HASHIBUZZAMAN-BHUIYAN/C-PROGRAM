/*
 * Intermediate Day 02 — Stacks & Queues
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ======= Array-based Stack ======= */
#define STACK_MAX 64
typedef struct { int data[STACK_MAX]; int top; } AStack;
void   as_init(AStack *s)       { s->top = -1; }
int    as_empty(AStack *s)      { return s->top < 0; }
int    as_push(AStack *s, int v){ if (s->top >= STACK_MAX-1) return 0; s->data[++s->top]=v; return 1; }
int    as_pop(AStack *s, int *v){ if (as_empty(s)) return 0; *v=s->data[s->top--]; return 1; }
int    as_peek(AStack *s)       { return s->data[s->top]; }

/* ======= Linked-list-based Queue ======= */
typedef struct QNode { int data; struct QNode *next; } QNode;
typedef struct { QNode *front, *back; int size; } LQueue;
void   lq_init(LQueue *q)    { q->front=q->back=NULL; q->size=0; }
void   lq_enqueue(LQueue *q, int v) {
    QNode *n = malloc(sizeof(QNode)); n->data=v; n->next=NULL;
    if (q->back) q->back->next=n; else q->front=n;
    q->back=n; q->size++;
}
int    lq_dequeue(LQueue *q, int *v) {
    if (!q->front) return 0;
    *v = q->front->data; QNode *t=q->front; q->front=q->front->next;
    if (!q->front) q->back=NULL;
    free(t); q->size--; return 1;
}
void   lq_free(LQueue *q) { int v; while(lq_dequeue(q,&v)); }

/* ======= Application: Balanced Bracket Checker ======= */
int is_balanced(const char *expr) {
    AStack s; as_init(&s);
    for (int i=0; expr[i]; i++) {
        char c = expr[i];
        if (c=='('||c=='['||c=='{') { as_push(&s,(int)c); }
        else if (c==')'||c==']'||c=='}') {
            if (as_empty(&s)) return 0;
            int top; as_pop(&s,&top);
            if ((c==')'&&top!='(')||(c==']'&&top!='[')||(c=='}'&&top!='{')) return 0;
        }
    }
    return as_empty(&s);
}

int main(void) {
    printf("=== Intermediate Day 02: Stacks & Queues ===\n\n");

    /* --- Array Stack --- */
    printf("--- Array Stack (LIFO) ---\n");
    AStack st; as_init(&st);
    for (int i=1; i<=5; i++) { as_push(&st, i*10); printf("Pushed %d\n", i*10); }
    printf("Peek: %d\n", as_peek(&st));
    int v;
    while (as_pop(&st, &v)) printf("Popped: %d\n", v);

    /* --- Linked Queue --- */
    printf("\n--- Linked-List Queue (FIFO) ---\n");
    LQueue q; lq_init(&q);
    for (int i=1; i<=5; i++) { lq_enqueue(&q, i*5); printf("Enqueued %d\n", i*5); }
    printf("Size: %d\n", q.size);
    while (lq_dequeue(&q, &v)) printf("Dequeued: %d\n", v);
    lq_free(&q);

    /* --- Bracket Checker --- */
    printf("\n--- Balanced Bracket Checker ---\n");
    const char *tests[] = {"({[]})", "([)]", "{[]}", "((())", "a*(b+c)/[d-{e}]"};
    for (int i=0; i<5; i++)
        printf("  %-25s  %s\n", tests[i], is_balanced(tests[i]) ? "BALANCED" : "UNBALANCED");

    return 0;
}


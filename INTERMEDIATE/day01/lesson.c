/*
 * Intermediate Day 01 — Linked Lists (Singly + Doubly)
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>

/* ============================
 * SINGLY LINKED LIST
 * ============================ */
typedef struct SNode {
    int          data;
    struct SNode *next;
} SNode;

SNode* slist_new(int val) {
    SNode *n = malloc(sizeof(SNode));
    n->data = val; n->next = NULL;
    return n;
}

void slist_push_front(SNode **head, int val) {
    SNode *n = slist_new(val);
    n->next = *head;
    *head = n;
}

void slist_push_back(SNode **head, int val) {
    SNode *n = slist_new(val);
    if (!*head) { *head = n; return; }
    SNode *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

void slist_print(const SNode *head) {
    const SNode *cur = head;
    while (cur) { printf("%d", cur->data); if (cur->next) printf(" -> "); cur = cur->next; }
    printf(" -> NULL\n");
}

int slist_delete(SNode **head, int val) {
    if (!*head) return 0;
    if ((*head)->data == val) {
        SNode *tmp = *head; *head = (*head)->next; free(tmp); return 1;
    }
    SNode *cur = *head;
    while (cur->next && cur->next->data != val) cur = cur->next;
    if (!cur->next) return 0;
    SNode *tmp = cur->next; cur->next = tmp->next; free(tmp); return 1;
}

void slist_free(SNode *head) {
    while (head) { SNode *tmp = head; head = head->next; free(tmp); }
}

int slist_length(const SNode *head) {
    int n = 0; while (head) { n++; head = head->next; } return n;
}

void slist_reverse(SNode **head) {
    SNode *prev = NULL, *cur = *head, *next = NULL;
    while (cur) { next = cur->next; cur->next = prev; prev = cur; cur = next; }
    *head = prev;
}

/* ============================
 * DOUBLY LINKED LIST
 * ============================ */
typedef struct DNode {
    int          data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
    int    size;
} DList;

DList* dlist_create(void) {
    DList *l = calloc(1, sizeof(DList));
    return l;
}

void dlist_push_back(DList *l, int val) {
    DNode *n = malloc(sizeof(DNode));
    n->data = val; n->next = NULL; n->prev = l->tail;
    if (l->tail) l->tail->next = n;
    else         l->head = n;
    l->tail = n;
    l->size++;
}

void dlist_print_forward(const DList *l) {
    DNode *cur = l->head;
    while (cur) { printf("%d", cur->data); if (cur->next) printf(" <-> "); cur = cur->next; }
    printf("\n");
}

void dlist_print_backward(const DList *l) {
    DNode *cur = l->tail;
    while (cur) { printf("%d", cur->data); if (cur->prev) printf(" <-> "); cur = cur->prev; }
    printf("\n");
}

void dlist_free(DList *l) {
    DNode *cur = l->head;
    while (cur) { DNode *tmp = cur->next; free(cur); cur = tmp; }
    free(l);
}

int main(void) {
    printf("=== Intermediate Day 01: Linked Lists ===\n\n");

    /* --- Singly Linked List --- */
    printf("--- Singly Linked List ---\n");
    SNode *head = NULL;
    for (int i = 1; i <= 5; i++) slist_push_back(&head, i * 10);
    slist_print(head);
    printf("Length: %d\n", slist_length(head));

    slist_push_front(&head, 5);
    printf("After push_front(5): ");
    slist_print(head);

    slist_delete(&head, 30);
    printf("After delete(30): ");
    slist_print(head);

    slist_reverse(&head);
    printf("After reverse: ");
    slist_print(head);
    slist_free(head);

    /* --- Doubly Linked List --- */
    printf("\n--- Doubly Linked List ---\n");
    DList *dl = dlist_create();
    for (int i = 1; i <= 6; i++) dlist_push_back(dl, i);
    printf("Forward : "); dlist_print_forward(dl);
    printf("Backward: "); dlist_print_backward(dl);
    printf("Size: %d\n", dl->size);
    dlist_free(dl);

    return 0;
}

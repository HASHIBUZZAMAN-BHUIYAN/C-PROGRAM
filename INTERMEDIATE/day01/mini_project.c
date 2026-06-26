/*
 * Intermediate Day 01 Mini-Project — Sorted Insert & Merge Sorted Lists
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct Node { int data; struct Node *next; } Node;

Node* new_node(int v) { Node *n = malloc(sizeof(Node)); n->data=v; n->next=NULL; return n; }

void sorted_insert(Node **head, int val) {
    Node *n = new_node(val);
    if (!*head || (*head)->data >= val) { n->next = *head; *head = n; return; }
    Node *cur = *head;
    while (cur->next && cur->next->data < val) cur = cur->next;
    n->next = cur->next; cur->next = n;
}

Node* merge_sorted(Node *a, Node *b) {
    Node dummy = {0, NULL}; Node *tail = &dummy;
    while (a && b) {
        if (a->data <= b->data) { tail->next = a; a = a->next; }
        else                    { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

void print_list(Node *h) { while(h){printf("%d%s",h->data,h->next?" -> ":"");h=h->next;} printf("\n"); }
void free_list(Node *h) { while(h){Node*t=h;h=h->next;free(t);} }

int main(void) {
    Node *a = NULL, *b = NULL;
    int vals_a[] = {1,3,5,7,9};
    int vals_b[] = {2,4,6,8,10};
    for (int i = 0; i < 5; i++) { sorted_insert(&a, vals_a[i]); sorted_insert(&b, vals_b[i]); }
    printf("List A: "); print_list(a);
    printf("List B: "); print_list(b);
    Node *merged = merge_sorted(a, b);
    printf("Merged: "); print_list(merged);
    free_list(merged);
    return 0;
}

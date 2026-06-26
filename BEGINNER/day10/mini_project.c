/*
 * Day 10 Mini-Project — Contact Book
 * Compile: gcc mini_project.c -o mini_project.exe -lm
 */
#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 10

typedef struct {
    char name[64];
    char phone[20];
    char email[64];
} Contact;

void print_contact(int idx, const Contact *c) {
    printf("[%d] %-20s  %s  <%s>\n", idx + 1, c->name, c->phone, c->email);
}

int find_by_name(const Contact *book, int count, const char *name) {
    for (int i = 0; i < count; i++)
        if (strstr(book[i].name, name)) return i;
    return -1;
}

int main(void) {
    Contact book[MAX_CONTACTS];
    int count = 0;

    printf("=== Contact Book ===\n");
    printf("Add contacts (max %d). Leave name blank to stop.\n\n", MAX_CONTACTS);

    while (count < MAX_CONTACTS) {
        printf("Name  : "); fgets(book[count].name, 64, stdin);
        book[count].name[strcspn(book[count].name, "\n")] = '\0';
        if (book[count].name[0] == '\0') break;
        printf("Phone : "); fgets(book[count].phone, 20, stdin);
        book[count].phone[strcspn(book[count].phone, "\n")] = '\0';
        printf("Email : "); fgets(book[count].email, 64, stdin);
        book[count].email[strcspn(book[count].email, "\n")] = '\0';
        count++;
        printf("\n");
    }

    printf("\n--- All Contacts (%d) ---\n", count);
    for (int i = 0; i < count; i++) print_contact(i, &book[i]);

    if (count > 0) {
        char query[64];
        printf("\nSearch by name: ");
        fgets(query, sizeof(query), stdin);
        query[strcspn(query, "\n")] = '\0';
        int idx = find_by_name(book, count, query);
        if (idx >= 0) { printf("Found: "); print_contact(idx, &book[idx]); }
        else           printf("Not found.\n");
    }
    return 0;
}

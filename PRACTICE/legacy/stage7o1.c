#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

// Structure to represent a book
typedef struct Book {
    int order;              // Reading order
    char title[MAX_LENGTH]; // Book title
    char author[MAX_LENGTH];// Author name
    struct Book *next;      // Pointer to next book in the list
} Book;

// Function prototypes
void doReadingList();
void LoadBookListFile(const char *filename, Book **head);
void InsertBook(Book **head, int order, const char *title, const char *author);
void PrintBookList(Book *head);
void ChangeReadingOrder(Book *head, int oldOrder, int newOrder);
void RemoveBook(Book **head, int order);
void MoveToReadList(Book **toReadHead, Book **readHead, int order);
void freeBookList(Book *head);

// Main function to handle the reading list menu
void doReadingList() {
    Book *readingList = NULL;
    Book *readList = NULL;

    // Load the book list from the file
    LoadBookListFile("book_list.txt", &readingList);

    // Print the current reading list
    PrintBookList(readingList);

    // Example operations:
    // Insert a new book (example)
    InsertBook(&readingList, 3, "The Great Gatsby", "F. Scott Fitzgerald");
    PrintBookList(readingList);

    // Change reading order (example)
    ChangeReadingOrder(readingList, 3, 2);
    PrintBookList(readingList);

    // Remove a book by its order
    RemoveBook(&readingList, 2);
    PrintBookList(readingList);

    // Move a book to the read list
    MoveToReadList(&readingList, &readList, 1);
    PrintBookList(readingList);
    PrintBookList(readList);

    // Free the memory allocated for the lists
    freeBookList(readingList);
    freeBookList(readList);
}

// Function to load the book list from the file
void LoadBookListFile(const char *filename, Book **head) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file %s\n", filename);
        return;
    }

    char line[MAX_LENGTH];
    int order = 1;
    while (fgets(line, sizeof(line), file)) {
        char title[MAX_LENGTH], author[MAX_LENGTH];
        sscanf(line, "%[^,], %[^\n]", title, author);
        
        InsertBook(head, order++, title, author);
    }

    fclose(file);
}

// Function to insert a book into the list at a specific order
void InsertBook(Book **head, int order, const char *title, const char *author) {
    Book *newBook = (Book *)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newBook->order = order;
    strncpy(newBook->title, title, MAX_LENGTH);
    strncpy(newBook->author, author, MAX_LENGTH);
    newBook->next = NULL;

    if (*head == NULL || (*head)->order > order) {
        newBook->next = *head;
        *head = newBook;
    } else {
        Book *current = *head;
        while (current->next != NULL && current->next->order < order) {
            current = current->next;
        }
        newBook->next = current->next;
        current->next = newBook;
    }
}

// Function to print the book list
void PrintBookList(Book *head) {
    Book *current = head;
    while (current != NULL) {
        printf("Order: %d\n", current->order);
        printf("Title: %s\n", current->title);
        printf("Author: %s\n", current->author);
        printf("---------------------\n");
        current = current->next;
    }
}

// Function to change the reading order of two books
void ChangeReadingOrder(Book *head, int oldOrder, int newOrder) {
    Book *current = head;
    Book *prev = NULL;
    Book *bookToMove = NULL;
    while (current != NULL) {
        if (current->order == oldOrder) {
            bookToMove = current;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (bookToMove == NULL) {
        printf("No book found with order %d\n", oldOrder);
        return;
    }

    // Remove the book from the list
    if (prev == NULL) {
        head = bookToMove->next;
    } else {
        prev->next = bookToMove->next;
    }

    // Insert it at the new order
    InsertBook(&head, newOrder, bookToMove->title, bookToMove->author);
    free(bookToMove);
}

// Function to remove a book from the list by its order
void RemoveBook(Book **head, int order) {
    Book *current = *head;
    Book *prev = NULL;

    while (current != NULL && current->order != order) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("No book found with order %d\n", order);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

// Function to move a book from the reading list to the read list
void MoveToReadList(Book **toReadHead, Book **readHead, int order) {
    Book *current = *toReadHead;
    Book *prev = NULL;

    // Find the book by order
    while (current != NULL && current->order != order) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("No book found with order %d\n", order);
        return;
    }
//hb inject
    // Remove the book from the reading list
    if (prev == NULL) {
        *toReadHead = current->next;
    } else {
        prev->next = current->next;
    }

    // Add the book to the read list
    current->next = *readHead;
    *readHead = current;
}

// Function to free the memory of the linked list
void freeBookList(Book *head) {
    Book *current = head;
    while (current != NULL) {
        Book *next = current->next;
        free(current);
        current = next;
    }
}

// Main entry point
int main() {
    doReadingList();
    return 0;
}

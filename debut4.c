#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PERFORMANCES 100
#define MAX_TITLE_LEN 100
#define MAX_SONGS 50
#define MAX_COUNTRY_LEN 50
#define MAX_REGION_LEN 50
#define MAX_DATE_LEN 20

// Performance types
#define CONCERT 1
#define INTERNATIONAL 2
#define DOMESTIC 3

// Structure to store song information
typedef struct Song {
    char title[MAX_TITLE_LEN];
    struct Song* next;
} Song;

// Structure to store performance schedule
typedef struct Performance {
    char country[MAX_COUNTRY_LEN];
    char region[MAX_REGION_LEN];
    char date[MAX_DATE_LEN];
    char performance_name[MAX_TITLE_LEN];
    Song* song_list;  // Linked list of songs
    int performance_type;
    struct Performance* next;  // Linked list of performances
} Performance;

// Global list of performance schedules
Performance* performance_list = NULL;

// Function to add a song to the song list
void addSong(Song** song_list, const char* song_title) {
    Song* new_song = (Song*)malloc(sizeof(Song));
    strncpy(new_song->title, song_title, MAX_TITLE_LEN);
    new_song->next = *song_list;
    *song_list = new_song;
}

// Function to print the song list
void printSongList(Song* song_list) {
    Song* current = song_list;
    while (current) {
        printf("%s\n", current->title);
        current = current->next;
    }
}

// Function to create a new performance schedule
Performance* createPerformance(const char* country, const char* region, const char* date, const char* performance_name, int performance_type) {
    Performance* new_performance = (Performance*)malloc(sizeof(Performance));
    strncpy(new_performance->country, country, MAX_COUNTRY_LEN);
    strncpy(new_performance->region, region, MAX_REGION_LEN);
    strncpy(new_performance->date, date, MAX_DATE_LEN);
    strncpy(new_performance->performance_name, performance_name, MAX_TITLE_LEN);
    new_performance->performance_type = performance_type;
    new_performance->song_list = NULL;
    new_performance->next = NULL;
    return new_performance;
}

// Function to add a performance to the performance list
void addPerformance(Performance** list, Performance* performance) {
    performance->next = *list;
    *list = performance;
}

// Function to add songs to a performance
void addSongsToPerformance(Performance* performance) {
    int num_songs;
    printf("How many songs are in this performance? ");
    scanf("%d", &num_songs);
    getchar();  // to clear the newline character from the input buffer

    for (int i = 0; i < num_songs; i++) {
        char song_title[MAX_TITLE_LEN];
        printf("Enter song title: ");
        fgets(song_title, MAX_TITLE_LEN, stdin);
        song_title[strcspn(song_title, "\n")] = 0; // Remove newline character
        addSong(&performance->song_list, song_title);
    }
}

// Function to print performance details
void printPerformance(Performance* performance) {
    printf("\nPerformance Name: %s\n", performance->performance_name);
    printf("Country: %s, Region: %s\n", performance->country, performance->region);
    printf("Date: %s\n", performance->date);
    printf("Songs:\n");
    printSongList(performance->song_list);
}

// Function to print all performances
void printAllPerformances() {
    Performance* current = performance_list;
    while (current) {
        printPerformance(current);
        current = current->next;
    }
}

// Function to search for a performance by date or name
Performance* searchPerformance(const char* search_term) {
    Performance* current = performance_list;
    while (current) {
        if (strstr(current->date, search_term) || strstr(current->performance_name, search_term)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to delete a performance by date
void deletePerformance(const char* date) {
    Performance* current = performance_list;
    Performance* prev = NULL;
    while (current) {
        if (strcmp(current->date, date) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                performance_list = current->next;
            }
            free(current);
            printf("Performance on %s has been deleted.\n", date);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("No performance found on %s.\n", date);
}

// Function to update a performance
void updatePerformance(const char* date) {
    Performance* performance = searchPerformance(date);
    if (performance) {
        char new_performance_name[MAX_TITLE_LEN];
        printf("Enter new performance name: ");
        fgets(new_performance_name, MAX_TITLE_LEN, stdin);
        new_performance_name[strcspn(new_performance_name, "\n")] = 0;
        strncpy(performance->performance_name, new_performance_name, MAX_TITLE_LEN);
        printf("Performance updated!\n");
    } else {
        printf("No performance found on %s.\n", date);
    }
}

// Function to load performances from a file
void loadPerformances(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    while (!feof(file)) {
        char country[MAX_COUNTRY_LEN], region[MAX_REGION_LEN], date[MAX_DATE_LEN], performance_name[MAX_TITLE_LEN];
        int performance_type;

        if (fscanf(file, "%s %s %s %s %d\n", country, region, date, performance_name, &performance_type) == 5) {
            Performance* performance = createPerformance(country, region, date, performance_name, performance_type);
            addPerformance(&performance_list, performance);
            addSongsToPerformance(performance);
        }
    }

    fclose(file);
}

// Function to save performances to a file
void savePerformances(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    Performance* current = performance_list;
    while (current) {
        fprintf(file, "%s %s %s %s %d\n", current->country, current->region, current->date, current->performance_name, current->performance_type);
        Song* song = current->song_list;
        while (song) {
            fprintf(file, "%s\n", song->title);
            song = song->next;
        }
        current = current->next;
    }

    fclose(file);
}

// Menu function
void planSchedule() {
    int choice;
    while (1) {
        printf("\nSchedule Management\n");
        printf("1. Add Performance\n");
        printf("2. Search Performance\n");
        printf("3. Update Performance\n");
        printf("4. Delete Performance\n");
        printf("5. Print All Performances\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To clear newline

        if (choice == 1) {
            // Add Performance
            char country[MAX_COUNTRY_LEN], region[MAX_REGION_LEN], date[MAX_DATE_LEN], performance_name[MAX_TITLE_LEN];
            int performance_type;

            printf("Enter country: ");
            fgets(country, MAX_COUNTRY_LEN, stdin);
            country[strcspn(country, "\n")] = 0;

            printf("Enter region: ");
            fgets(region, MAX_REGION_LEN, stdin);
            region[strcspn(region, "\n")] = 0;

            printf("Enter date (yyyy-mm-dd): ");
            fgets(date, MAX_DATE_LEN, stdin);
            date[strcspn(date, "\n")] = 0;

            printf("Enter performance name: ");
            fgets(performance_name, MAX_TITLE_LEN, stdin);
            performance_name[strcspn(performance_name, "\n")] = 0;

            printf("Enter performance type (1 for concert, 2 for international, 3 for domestic): ");
            scanf("%d", &performance_type);
            getchar();  // To clear hb newline

            Performance* new_performance = createPerformance(country, region, date, performance_name, performance_type);
            addPerformance(&performance_list, new_performance);
            addSongsToPerformance(new_performance);
        } else if (choice == 2) {
            // Search Performance
            char search_term[MAX_TITLE_LEN];
            printf("Enter search term (date or performance name): ");
            fgets(search_term, MAX_TITLE_LEN, stdin);
            search_term[strcspn(search_term, "\n")] = 0;

            Performance* performance = searchPerformance(search_term);
            if (performance) {
                printPerformance(performance);
            } else {
                printf("No performance found.\n");
            }
        } else if (choice == 3) {
            // Update Performance
            char date[MAX_DATE_LEN];
            printf("Enter date of the performance to update: ");
            fgets(date, MAX_DATE_LEN, stdin);
            date[strcspn(date, "\n")] = 0;
            updatePerformance(date);
        } else if (choice == 4) {
            // Delete Performance
            char date[MAX_DATE_LEN];
            printf("Enter date of the performance to delete: ");
            fgets(date, MAX_DATE_LEN, stdin);
            date[strcspn(date, "\n")] = 0;
            deletePerformance(date);
        } else if (choice == 5) {
            // Print All Performances
            printAllPerformances();
        } else if (choice == 6) {
            // Save and Exit
            savePerformances("performances.txt");
            break;
        } else {
            printf("Invalid choice, try again.\n");
        }
    }
}

// Main function
int main() {
    loadPerformances("performances.txt");
    planSchedule();
    return 0;
}

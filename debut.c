#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_DESC 200
#define MAX_COMPOSERS 3

typedef struct Song {
    char title[MAX_TITLE];
    char description[MAX_DESC];
    int priority;
    struct Song* next;
} Song;

typedef struct Composer {
    char name[50];
    Song* allSongs;        // All songs proposed
    Song* selectedSongs;   // Selected 3 songs for debut album
    int songCount;
} Composer;

Composer composers[MAX_COMPOSERS] = {
    {"Alice", NULL, NULL, 0},
    {"Bob", NULL, NULL, 0},
    {"Charlie", NULL, NULL, 0}
};

// Create a new song node
Song* createSong(const char* title, const char* desc, int priority) {
    Song* s = (Song*)malloc(sizeof(Song));
    strcpy(s->title, title);
    strcpy(s->description, desc);
    s->priority = priority;
    s->next = NULL;
    return s;
}

// Add a song to a composer's list (prepend)
void addSongToComposer(Composer* comp, Song* song) {
    song->next = comp->allSongs;
    comp->allSongs = song;
    comp->songCount++;
}

// Load songs from music.txt
void loadSongsFromFile() {
    FILE* file = fopen("music.txt", "r");
    if (!file) {
        perror("Error opening music.txt");
        exit(1);
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char name[50], title[MAX_TITLE], desc[MAX_DESC];
        int priority;

        if (sscanf(line, "%[^,],%[^,],%[^,],%d", name, title, desc, &priority) == 4) {
            for (int i = 0; i < MAX_COMPOSERS; i++) {
                if (strcmp(composers[i].name, name) == 0) {
                    Song* song = createSong(title, desc, priority);
                    addSongToComposer(&composers[i], song);
                    break;
                }
            }
        }
    }

    fclose(file);
}

// Select up to 3 songs per composer (max 2 consecutively)
Song* selectSongs(Composer* comp, int limit) {
    Song *selected = NULL, *tail = NULL;
    Song* curr = comp->allSongs;
    int count = 0;
    int consecutive = 0;
    char lastTitle[MAX_TITLE] = "";

    while (curr && count < limit) {
        if (strcmp(curr->title, lastTitle) == 0) {
            if (++consecutive > 2) {
                curr = curr->next;
                continue;
            }
        } else {
            consecutive = 1;
        }

        Song* copy = createSong(curr->title, curr->description, count + 1);
        if (!selected)
            selected = tail = copy;
        else {
            tail->next = copy;
            tail = copy;
        }

        strcpy(lastTitle, curr->title);
        count++;
        curr = curr->next;
    }

    return selected;
}

// Merge two sorted lists by priority
Song* mergeSorted(Song* a, Song* b) {
    if (!a) return b;
    if (!b) return a;

    Song* result = NULL;

    if (a->priority < b->priority) {
        result = a;
        result->next = mergeSorted(a->next, b);
    } else {
        result = b;
        result->next = mergeSorted(a, b->next);
    }

    return result;
}

// Merge 3 sorted song lists
Song* mergeThree(Song* a, Song* b, Song* c) {
    return mergeSorted(mergeSorted(a, b), c);
}

// Print the final debut album
void printAlbum(Song* head) {
    int idx = 1;
    printf("\n=== Debut Album Tracklist ===\n");
    while (head) {
        printf("%d. %s - %s\n", idx++, head->title, head->description);
        head = head->next;
    }
}

// Main function that ties everything together
int main() {
    loadSongsFromFile();

    // Step 1: Select 3 songs per composer
    for (int i = 0; i < MAX_COMPOSERS; i++) {
        composers[i].selectedSongs = selectSongs(&composers[i], 3);
    }

    // Step 2: Merge all selected songs into one debut album (sorted)
    Song* debutAlbum = mergeThree(
        composers[0].selectedSongs,
        composers[1].selectedSongs,
        composers[2].selectedSongs
    );
/*text of music
Alice,Starlight,Upbeat cosmic vibe,5
Alice,Galaxy Whisper,Ballad with synth,3
Alice,Light Years,A bright pop tune,7
Bob,Orbit Dance,Funky dance beat,4
Bob,Meteor Shower,Dramatic chorus,6
Bob,Gravity Call,Deep bass drop,2
Charlie,Supernova,Explosive rock theme,1
Charlie,Comet Trail,Soft acoustic ballad,5
Charlie,Lunar Echo,Retro synthwave,8

*/
    // Step 3: Print final album
    printAlbum(debutAlbum);

    return 0;
}

/*
 * Intermediate Day 10 Capstone — CLI Task Manager
 * Hash table + doubly linked list + file persistence
 * Compile: gcc lesson.c -o capstone.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_SIZE    64
#define DB_FILE    "tasks.csv"

/* ======================== TASK ======================== */
typedef enum { PENDING=0, IN_PROGRESS=1, DONE=2 } Status;
const char *status_str[] = {"PENDING","IN_PROGRESS","DONE"};

typedef struct Task {
    int    id;
    char   name[128];
    int    priority;  /* 1(low)..5(high) */
    Status status;
    struct Task *prev, *next;   /* for doubly linked list */
} Task;

/* ======================== DATA STORE ======================== */
typedef struct HEntry { Task *task; struct HEntry *chain; } HEntry;
typedef struct {
    HEntry   *buckets[HT_SIZE];
    Task     *head, *tail;   /* ordered list */
    int       count, next_id;
} Store;

Store* store_create(void) { return calloc(1, sizeof(Store)); }

static unsigned int hf(int id) { return (unsigned int)id % HT_SIZE; }

void store_add(Store *s, Task *t) {
    /* Hash table */
    unsigned int idx = hf(t->id);
    HEntry *e = malloc(sizeof(HEntry)); e->task = t;
    e->chain = s->buckets[idx]; s->buckets[idx] = e;
    /* Append to list */
    t->prev = s->tail; t->next = NULL;
    if (s->tail) s->tail->next = t; else s->head = t;
    s->tail = t;
    s->count++;
    if (t->id >= s->next_id) s->next_id = t->id + 1;
}

Task* store_find(Store *s, int id) {
    for (HEntry *e = s->buckets[hf(id)]; e; e = e->chain)
        if (e->task->id == id) return e->task;
    return NULL;
}

int store_delete(Store *s, int id) {
    unsigned int idx = hf(id);
    HEntry *prev_e = NULL, *e = s->buckets[idx];
    while (e && e->task->id != id) { prev_e = e; e = e->chain; }
    if (!e) return 0;
    if (prev_e) prev_e->chain = e->chain; else s->buckets[idx] = e->chain;
    free(e);
    Task *t = store_find(s, id); /* can't use pointer after chain removal */
    /* Walk list to find it */
    for (Task *cur = s->head; cur; cur = cur->next) {
        if (cur->id == id) {
            if (cur->prev) cur->prev->next = cur->next; else s->head = cur->next;
            if (cur->next) cur->next->prev = cur->prev; else s->tail = cur->prev;
            free(cur); s->count--; return 1;
        }
    }
    (void)t;
    return 0;
}

/* ======================== FILE I/O ======================== */
void store_save(Store *s) {
    FILE *f = fopen(DB_FILE, "w"); if (!f) return;
    fprintf(f, "id,name,priority,status\n");
    for (Task *t = s->head; t; t = t->next)
        fprintf(f, "%d,%s,%d,%d\n", t->id, t->name, t->priority, (int)t->status);
    fclose(f);
    printf("Saved %d tasks.\n", s->count);
}

void store_load(Store *s) {
    FILE *f = fopen(DB_FILE, "r"); if (!f) return;
    char line[256]; fgets(line, sizeof(line), f);
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        Task *t = calloc(1, sizeof(Task));
        if (sscanf(line, "%d,%127[^,],%d,%d", &t->id, t->name, &t->priority, (int*)&t->status) == 4)
            store_add(s, t);
        else free(t);
    }
    fclose(f);
    printf("Loaded %d tasks.\n", s->count);
}

/* ======================== UI ======================== */
void print_task(const Task *t) {
    printf("  [%3d] P%d %-40s %s\n", t->id, t->priority, t->name, status_str[t->status]);
}

void list_tasks(const Store *s) {
    if (!s->count) { printf("  (no tasks)\n"); return; }
    printf("  %-5s P  %-40s %s\n", "ID", "Name", "Status");
    printf("  %-5s -- %-40s ------\n", "-----", "----------------------------------------");
    for (Task *t = s->head; t; t = t->next) print_task(t);
}

static void flush(void) { int c; while((c=getchar())!='\n'&&c!=EOF){} }

int main(void) {
    Store *s = store_create();
    s->next_id = 1;
    store_load(s);

    printf("========================================\n");
    printf("  Intermediate Capstone: Task Manager\n");
    printf("========================================\n");

    int running = 1;
    while (running) {
        printf("\n[1]Add [2]List [3]Search [4]Status [5]Delete [6]Save&Quit\n> ");
        int ch; if(scanf("%d",&ch)!=1){flush();continue;} flush();

        switch (ch) {
        case 1: {
            Task *t = calloc(1, sizeof(Task));
            t->id = s->next_id;
            printf("Name    : "); fgets(t->name, 128, stdin); t->name[strcspn(t->name,"\n")]='\0';
            printf("Priority (1-5): "); scanf("%d",&t->priority); flush();
            if(t->priority<1)t->priority=1;
            if(t->priority>5)t->priority=5;
            t->status = PENDING;
            store_add(s, t);
            printf("Added ID=%d\n", t->id);
            break;
        }
        case 2: list_tasks(s); break;
        case 3: {
            printf("Search ID: "); int id; scanf("%d",&id); flush();
            Task *t = store_find(s,id);
            if(t) print_task(t); else printf("Not found.\n");
            break;
        }
        case 4: {
            printf("Task ID: "); int id; scanf("%d",&id); flush();
            Task *t = store_find(s,id);
            if(!t){printf("Not found.\n");break;}
            printf("Status: 0=PENDING 1=IN_PROGRESS 2=DONE: ");
            int st; scanf("%d",&st); flush();
            if(st>=0&&st<=2) t->status=(Status)st;
            break;
        }
        case 5: {
            printf("Delete ID: "); int id; scanf("%d",&id); flush();
            printf(store_delete(s,id)?"Deleted.\n":"Not found.\n");
            break;
        }
        case 6: store_save(s); running=0; break;
        default: printf("Invalid.\n");
        }
    }
    printf("Goodbye!\n");
    return 0;
}


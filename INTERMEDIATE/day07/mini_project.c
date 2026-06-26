/*
 * Int Day 07 Mini-Project — Bitmask-based todo/task list
 * Up to 32 tasks stored in a single uint32_t
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_TASKS 16
char tasks[MAX_TASKS][64];
int  task_count = 0;
uint32_t done_mask = 0;

void add_task(const char *t)   { if(task_count<MAX_TASKS){strncpy(tasks[task_count++],t,63);} }
void mark_done(int i)          { if(i<task_count) done_mask|=(1u<<i); }
void mark_undone(int i)        { if(i<task_count) done_mask&=~(1u<<i); }
int  is_done(int i)            { return (done_mask>>i)&1; }
void print_tasks(void) {
    for(int i=0;i<task_count;i++) printf("  [%s] %d: %s\n", is_done(i)?"X":" ", i+1, tasks[i]);
}

int main(void) {
    add_task("Write lesson.c"); add_task("Compile code"); add_task("Run tests");
    add_task("Write README");  add_task("Push to git");

    printf("=== Bitmask Task List ===\n");
    print_tasks();

    mark_done(0); mark_done(1); mark_done(3);
    printf("\nAfter completing tasks 1,2,4:\n");
    print_tasks();
    printf("Done mask: 0x%08X  (%d/%d done)\n", done_mask, __builtin_popcount(done_mask), task_count);

    mark_undone(1);
    printf("\nAfter unchecking task 2:\n");
    print_tasks();
    return 0;
}

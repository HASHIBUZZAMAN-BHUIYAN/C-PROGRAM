/*
 * Cooperative Real-Time Task Scheduler Simulation
 * Models: a simplified version of how an RTOS (FreeRTOS-style) schedules periodic tasks.
 *
 * Compile: gcc realtime_scheduler_sim.c -o realtime_scheduler_sim.exe
 */
#include <stdio.h>
#include <string.h>

#define MAX_TASKS    8
#define SIM_TICKS  100   /* simulate 100 ms */

typedef void (*TaskFn)(int tick);

typedef struct {
    const char *name;
    int         period_ms;
    int         exec_time_ms;
    TaskFn      fn;
    int         last_run;
    int         run_count;
    long        total_exec_ms;
} Task;

/* Task implementations */
void task_sensors(int t)   { (void)t; }
void task_control(int t)   { (void)t; }
void task_comms(int t)     { (void)t; }
void task_logging(int t)   { (void)t; }

Task tasks[] = {
    {"SensorRead",   10, 2, task_sensors, -1, 0, 0},
    {"ControlLoop",  20, 5, task_control, -1, 0, 0},
    {"Communications",50, 3, task_comms,  -1, 0, 0},
    {"DataLogger",  100, 8, task_logging, -1, 0, 0},
};
int ntasks = 4;

int main(void) {
    printf("=== Real-Time Scheduler Simulation ===\n");
    printf("Simulating %d ms of cooperative scheduling\n\n", SIM_TICKS);
    printf("%-6s  %-20s  %s\n", "Tick", "Task", "Timeline");
    printf("%-6s  %-20s  %s\n", "------", "--------------------", "--------");

    char timeline[SIM_TICKS+1];
    memset(timeline, '.', SIM_TICKS);
    timeline[SIM_TICKS] = '\0';

    /* Run each task separately to show its timeline */
    for (int ti = 0; ti < ntasks; ti++) {
        Task *t = &tasks[ti];
        char tl[SIM_TICKS+1];
        memset(tl, '.', SIM_TICKS);
        tl[SIM_TICKS] = '\0';

        for (int tick = 0; tick < SIM_TICKS; tick++) {
            if ((tick % t->period_ms) == 0) {
                t->fn(tick);
                t->run_count++;
                t->last_run = tick;
                t->total_exec_ms += t->exec_time_ms;
                /* Mark execution window in timeline */
                for (int e = tick; e < tick + t->exec_time_ms && e < SIM_TICKS; e++)
                    tl[e] = '#';
            }
        }
        printf("%-25s [%s]\n", t->name, tl);
    }

    printf("\n--- Task Summary ---\n");
    printf("%-20s  %6s  %8s  %10s  %s\n", "Task","Period","Runs","Total exec","CPU%");
    for (int ti = 0; ti < ntasks; ti++) {
        Task *t = &tasks[ti];
        double cpu = (double)t->total_exec_ms / SIM_TICKS * 100.0;
        printf("%-20s  %5dms  %8d  %8ldms  %.1f%%\n",
               t->name, t->period_ms, t->run_count, t->total_exec_ms, cpu);
    }
    return 0;
}

/*
 * Simplified Cooperative RTOS-Style Task Scheduler
 *
 * MODELS:    FreeRTOS-style cooperative multitasking on a microcontroller.
 *            In a real RTOS, tasks are functions that run until they yield.
 * SIMULATED: Tasks are called in round-robin order on each simulated tick.
 * REAL HW:   Replace sim_tick_advance() with a real hardware timer ISR and
 *            use vTaskDelay() / portYIELD() for FreeRTOS.
 *
 * Compile: gcc simple_rtos_scheduler.c -o simple_rtos_scheduler.exe
 */
#include <stdio.h>
#include <string.h>

#define MAX_TASKS    8
#define TICK_MS      1
#define SIM_TICKS  200

typedef enum { TASK_READY, TASK_BLOCKED, TASK_SUSPENDED } TaskState;

typedef struct {
    const char *name;
    int         period_ms;
    int         priority;       /* higher = more important */
    TaskState   state;
    long        next_run_ms;
    long        total_runs;
    void      (*run)(int tick_ms);
} RTOSTask;

/* ---- Simulated task bodies ---- */
static long sensor_val = 0;
static long control_out = 0;

void task_read_sensors(int t)   { sensor_val = t * 3 % 256; }
void task_run_controller(int t) { control_out = sensor_val * 2; (void)t; }
void task_send_telemetry(int t) { (void)t; /* would send over UART */ }
void task_heartbeat_led(int t)  { (void)t; /* would toggle LED */ }

static RTOSTask tasks[MAX_TASKS];
static int      ntasks = 0;

void rtos_add_task(const char *name, int period, int priority, void(*fn)(int)) {
    tasks[ntasks++] = (RTOSTask){name, period, priority, TASK_READY, 0, 0, fn};
}

/* Priority-based scheduler: run the highest-priority ready task at each tick */
void rtos_tick(long now_ms) {
    int best = -1;
    for (int i = 0; i < ntasks; i++) {
        if (tasks[i].state != TASK_READY) continue;
        if (now_ms < tasks[i].next_run_ms) continue;
        if (best < 0 || tasks[i].priority > tasks[best].priority) best = i;
    }
    if (best >= 0) {
        RTOSTask *t = &tasks[best];
        printf("  t=%-4ld  [P%d] %-20s (run #%ld)\n",
               now_ms, t->priority, t->name, t->total_runs + 1);
        t->run((int)now_ms);
        t->next_run_ms = now_ms + t->period_ms;
        t->total_runs++;
    }
}

int main(void) {
    printf("=== Cooperative RTOS Scheduler Simulation ===\n");
    printf("Simulating %d ticks of %d ms each = %d ms total\n\n",
           SIM_TICKS, TICK_MS, SIM_TICKS * TICK_MS);

    rtos_add_task("ReadSensors",    10, 4, task_read_sensors);
    rtos_add_task("RunController",  20, 5, task_run_controller);
    rtos_add_task("SendTelemetry",  50, 2, task_send_telemetry);
    rtos_add_task("HeartbeatLED",  100, 1, task_heartbeat_led);

    printf("%-8s  %-5s %-22s %s\n", "Time(ms)", "Pri", "Task", "Run#");
    printf("%-8s  %-5s %-22s %s\n", "--------", "---", "----", "----");

    for (int tick = 0; tick < SIM_TICKS; tick++) {
        rtos_tick((long)tick * TICK_MS);
    }

    printf("\n--- Summary ---\n");
    for (int i = 0; i < ntasks; i++)
        printf("  %-22s  period=%3dms  runs=%ld\n",
               tasks[i].name, tasks[i].period_ms, tasks[i].total_runs);
    return 0;
}

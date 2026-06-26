/*
 * Interrupt-Driven Pattern Simulation
 *
 * MODELS:    A hardware timer interrupt firing every 10 ms on a microcontroller.
 *            An ISR (Interrupt Service Routine) updates a counter/flag.
 *            The main loop reads the flag and acts on it.
 * SIMULATED: No real interrupts — a software flag is set on each simulated tick.
 * REAL HW:   Replace the software flag with a real ISR attached to a timer vector
 *            (e.g. ISR(TIMER1_OVF_vect) on AVR, or HAL_TIM_PeriodElapsedCallback
 *            on STM32).
 *
 * WHY THIS MATTERS:  Polling wastes CPU; interrupts let the MCU do other work
 *                    and only react when something actually happens.
 *
 * Compile: gcc interrupt_simulation.c -o interrupt_simulation.exe
 */
#include <stdio.h>

#define TIMER_PERIOD_MS   10   /* ISR fires every 10 ms */
#define SIM_TOTAL_MS     200

/* Simulated ISR state */
static volatile int  timer_flag  = 0;  /* set by ISR, cleared by main */
static volatile long tick_count  = 0;

/* ---- Simulated ISR (called when timer fires) ---- */
void timer_isr(void) {
    tick_count++;
    timer_flag = 1;   /* signal main loop */
}

/* ---- Simulated polling approach (for comparison) ---- */
void polling_demo(int total_ms) {
    printf("\n--- POLLING approach (%d ms) ---\n", total_ms);
    int last_checked = 0;
    for (int t = 0; t < total_ms; t++) {
        /* Main loop "busy-waits" checking the timer every ms */
        last_checked = t;
        if (t % TIMER_PERIOD_MS == 0 && t > 0) {
            printf("  t=%3d ms: handled (polled every ms — CPU busy the whole time)\n", t);
        }
    }
    printf("Polling checked timer %d times.\n", last_checked);
}

/* ---- Simulated interrupt-driven approach ---- */
void interrupt_demo(int total_ms) {
    printf("\n--- INTERRUPT-DRIVEN approach (%d ms) ---\n", total_ms);
    tick_count = 0;
    int work_done = 0;

    for (int t = 0; t < total_ms; t++) {
        /* Simulate timer interrupt firing */
        if (t % TIMER_PERIOD_MS == 0 && t > 0) {
            timer_isr();   /* "hardware" calls our ISR */
        }

        /* Main loop only acts when ISR has set the flag */
        if (timer_flag) {
            timer_flag = 0;   /* acknowledge / clear */
            work_done++;
            printf("  t=%3d ms: ISR fired (tick=%ld), main handled it\n", t, tick_count);
        } else {
            /* Main loop free to do other work */
        }
    }
    printf("ISR fired %ld times; main handled %d events.\n", tick_count, work_done);
}

int main(void) {
    printf("=== Interrupt Simulation ===\n");
    printf("Timer period: %d ms\nSimulation: %d ms\n", TIMER_PERIOD_MS, SIM_TOTAL_MS);

    polling_demo(SIM_TOTAL_MS);
    interrupt_demo(SIM_TOTAL_MS);

    printf("\nKey insight: interrupt-driven frees the CPU between events.\n");
    printf("On real hardware the ISR runs from a hardware vector, not a function call.\n");
    return 0;
}

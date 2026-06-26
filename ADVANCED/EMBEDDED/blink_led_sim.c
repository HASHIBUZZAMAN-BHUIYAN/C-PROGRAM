/*
 * Blink LED Simulation
 *
 * MODELS:    Arduino Uno blinking the built-in LED on pin 13
 * SIMULATED: GPIO layer prints state changes instead of writing AVR registers
 * REAL HW:   Replace #include "gpio_simulated.h" with <avr/io.h> and use:
 *              DDRB  |= (1<<5);        // pin 13 = PB5
 *              PORTB ^= (1<<5);        // toggle
 *              _delay_ms(500);
 *
 * Compile: gcc blink_led_sim.c -o blink_led_sim.exe
 */
#include <stdio.h>
#include "gpio_simulated.h"

#define LED_PIN    13
#define BLINK_MS  500
#define ITERATIONS 10   /* number of blink cycles to simulate */

int main(void) {
    printf("=== Blink LED Simulation (Arduino Uno style) ===\n");
    printf("LED on pin %d, period=%dms\n\n", LED_PIN, BLINK_MS * 2);

    gpio_init();
    gpio_set_mode(LED_PIN, GPIO_OUTPUT);

    for (int i = 0; i < ITERATIONS; i++) {
        printf("--- Cycle %d (t=%lums) ---\n", i+1, millis());
        gpio_write(LED_PIN, GPIO_HIGH);
        delay_ms(BLINK_MS);
        sim_tick_advance(BLINK_MS);

        gpio_write(LED_PIN, GPIO_LOW);
        delay_ms(BLINK_MS);
        sim_tick_advance(BLINK_MS);
    }

    printf("\nSimulation complete: %d blink cycles, %lu ms simulated time.\n",
           ITERATIONS, millis());
    return 0;
}

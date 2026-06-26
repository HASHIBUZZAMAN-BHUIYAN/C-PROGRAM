/*
 * gpio_simulated.h
 * Simulated GPIO layer for embedded C programs running on a PC.
 *
 * WHAT THIS MODELS:   Arduino Uno / AVR-style digital GPIO
 * SIMULATED HERE:     All register writes are replaced with printf() calls
 * FOR REAL HARDWARE:  Replace gpio_write/gpio_read with direct AVR register
 *                     access or Arduino digitalWrite()/digitalRead() calls.
 *
 * No external dependencies — drop this header into any C project.
 */
#ifndef GPIO_SIMULATED_H
#define GPIO_SIMULATED_H

#include <stdio.h>
#include <time.h>

/* ---- Pin modes ---- */
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

/* ---- Pin values ---- */
#define GPIO_LOW  0
#define GPIO_HIGH 1

/* ---- Simulated pin state ---- */
typedef struct {
    int  mode;
    int  value;
    char name[16];
} SimPin;

static SimPin _sim_pins[64];   /* support pins 0-63 */

static inline void gpio_init(void) {
    for (int i = 0; i < 64; i++) {
        _sim_pins[i].mode  = GPIO_INPUT;
        _sim_pins[i].value = GPIO_LOW;
        snprintf(_sim_pins[i].name, 16, "P%d", i);
    }
}

static inline void gpio_set_mode(int pin, int mode) {
    _sim_pins[pin].mode = mode;
    printf("[GPIO] Pin %d (%s) set to %s\n",
           pin, _sim_pins[pin].name,
           mode == GPIO_OUTPUT ? "OUTPUT" : "INPUT");
}

static inline void gpio_write(int pin, int value) {
    _sim_pins[pin].value = value;
    printf("[GPIO] Pin %d (%s): %s\n",
           pin, _sim_pins[pin].name,
           value == GPIO_HIGH ? "HIGH" : "LOW");
}

static inline int gpio_read(int pin) {
    return _sim_pins[pin].value;
}

/* Simulated delay (prints message, no real blocking) */
static inline void delay_ms(int ms) {
    printf("[DELAY] %d ms\n", ms);
}

/* Simulated time counter (tick count) */
static unsigned long _sim_tick = 0;
static inline unsigned long millis(void) { return _sim_tick; }
static inline void sim_tick_advance(unsigned long ms) { _sim_tick += ms; }

#endif /* GPIO_SIMULATED_H */

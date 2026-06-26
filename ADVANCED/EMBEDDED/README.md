# ADVANCED/EMBEDDED — Embedded-Systems C (Simulated Hardware)

All programs use real embedded coding patterns with a simulated hardware layer
(`gpio_simulated.h`) so they compile and run correctly on any PC.

| File | Models | Simulated |
|------|--------|-----------|
| `blink_led_sim.c` | Arduino Uno LED blink | gpio_write() prints state |
| `button_debounce_sim.c` | MCU button debounce algorithm | noisy signal generated in software |
| `simple_rtos_scheduler.c` | FreeRTOS cooperative task scheduler | timer tick simulated in loop |
| `uart_protocol_sim.c` | Framed UART protocol with checksum | byte buffer instead of USART |
| `interrupt_simulation.c` | Hardware timer interrupt + ISR pattern | software flag replaces HW vector |

**To adapt for real hardware:** replace `#include "gpio_simulated.h"` with the target MCU's
HAL (Arduino `digitalWrite`, STM32 HAL, AVR `<avr/io.h>`, etc.).

## Build all
```
.\build.bat
```

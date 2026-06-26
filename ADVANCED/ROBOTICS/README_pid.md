# PID Controller

Implements a discrete PID controller driving a simulated first-order plant.

## What it demonstrates
- Proportional, integral, and derivative terms in code
- Anti-windup via output clamping
- Plant model (time constant tau) responding to control signal

## Build & Run
```
gcc pid_controller.c -o pid_controller.exe -lm
pid_controller.exe
```
Produces `pid_output.csv` — import into any plotting tool to visualize the step response.

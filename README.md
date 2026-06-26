# C-PROGRAM — Complete C Learning Repository

A structured, hands-on C programming curriculum from absolute basics to robotics,
embedded systems, and real graphical games. Every project compiles and runs on Windows
with the included GCC toolchain.

---

## Table of Contents

- [Quick Start](#quick-start)
- [Toolchain Setup](#toolchain-setup)
- [BEGINNER Track (14 Days)](#beginner-track-14-days)
- [INTERMEDIATE Track (10 Days)](#intermediate-track-10-days)
- [ADVANCED / ROBOTICS](#advanced--robotics)
- [ADVANCED / EMBEDDED](#advanced--embedded)
- [ADVANCED / GAMES](#advanced--games)
- [PRACTICE](#practice)
- [Directory Structure](#directory-structure)

---

## Quick Start

### 1. Verify your compiler
```bat
gcc --version
```
If not found, see [TOOLCHAIN_SETUP.md](TOOLCHAIN_SETUP.md).

### 2. Run Beginner Day 1
```bat
cd BEGINNER\day01
build.bat
lesson.exe
```

### 3. Run a Robotics example (A* Pathfinding)
```bat
cd ADVANCED\ROBOTICS
gcc pathfinding_grid_c.c -o pathfinding_grid_c.exe
pathfinding_grid_c.exe
```

### 4. Run a game (Snake — terminal, no dependencies)
```bat
cd ADVANCED\GAMES
gcc snake_terminal.c -o snake_terminal.exe
snake_terminal.exe
```

### 5. Run an SDL2 game (Pong — real windowed graphics)
```bat
cd ADVANCED\GAMES
build.bat
pong_sdl2.exe
```

---

## Toolchain Setup

- **Compiler**: GCC 16.1.0 via [WinLibs](https://winlibs.com/) (MinGW-w64, UCRT)
- **SDL2**: v2.32.8 — located in `SDL2/` folder, DLL pre-copied to `ADVANCED/GAMES/`
- **Full details**: [TOOLCHAIN_SETUP.md](TOOLCHAIN_SETUP.md) and [SDL2_SETUP.md](SDL2_SETUP.md)

---

## BEGINNER Track (14 Days)

| Day | Topic | Key Concepts |
|-----|-------|-------------|
| [day01](BEGINNER/day01/) | C Basics | printf, scanf, variables, data types |
| [day02](BEGINNER/day02/) | Operators | Arithmetic, relational, logical, casting, const |
| [day03](BEGINNER/day03/) | Conditionals | if/else, switch, ternary |
| [day04](BEGINNER/day04/) | Loops | for, while, do-while, break, continue |
| [day05](BEGINNER/day05/) | Functions | Declarations, parameters, return values, recursion |
| [day06](BEGINNER/day06/) | Arrays | 1D, 2D arrays, passing to functions |
| [day07](BEGINNER/day07/) | Strings | char arrays, string.h, fgets, ctype.h |
| [day08](BEGINNER/day08/) | Pointers I | Basics, pointer arithmetic, arrays |
| [day09](BEGINNER/day09/) | Pointers II | Double pointers, function pointers |
| [day10](BEGINNER/day10/) | Structs & Unions | typedef, nested structs, unions |
| [day11](BEGINNER/day11/) | Dynamic Memory | malloc, calloc, realloc, free |
| [day12](BEGINNER/day12/) | File I/O | fopen, fprintf, fread, fwrite, fseek |
| [day13](BEGINNER/day13/) | Preprocessor | #define, multi-file programs, header guards |
| [day14](BEGINNER/day14/) | **Capstone** | Student Record Manager (structs + file I/O + dynamic arrays) |

Each day folder contains: `lesson.c`, `exercises.c`, `solutions.c`, `mini_project.c`, `build.bat`, `README.md`.

---

## INTERMEDIATE Track (10 Days)

| Day | Topic | Key Concepts |
|-----|-------|-------------|
| [day01](INTERMEDIATE/day01/) | Linked Lists | Singly + doubly linked, sorted insert, merge |
| [day02](INTERMEDIATE/day02/) | Stacks & Queues | Array stack, linked queue, RPN calculator, bracket checker |
| [day03](INTERMEDIATE/day03/) | Binary Trees | BST insert/delete/search, traversals, word frequency |
| [day04](INTERMEDIATE/day04/) | Sorting | Bubble, insertion, quicksort, mergesort, performance timing |
| [day05](INTERMEDIATE/day05/) | Searching | Linear, binary, hash tables (chaining) |
| [day06](INTERMEDIATE/day06/) | Recursion | Fibonacci (memoized), Hanoi, N-Queens, maze solver |
| [day07](INTERMEDIATE/day07/) | Bit Manipulation | Bit ops, flags, bitmask task list |
| [day08](INTERMEDIATE/day08/) | Memory & Allocators | Pool allocator, arena allocator, stack frames |
| [day09](INTERMEDIATE/day09/) | Multi-threading | Windows threads, mutex, producer-consumer |
| [day10](INTERMEDIATE/day10/) | **Capstone** | CLI Task Manager (hash table + linked list + file persistence) |

---

## ADVANCED / ROBOTICS

Real robotics algorithms in C — no hardware needed, all simulate correctly on your PC.

| File | Description |
|------|-------------|
| [pid_controller.c](ADVANCED/ROBOTICS/pid_controller.c) | PID control loop, step-response, outputs CSV |
| [kinematics_2d_arm.c](ADVANCED/ROBOTICS/kinematics_2d_arm.c) | Forward + inverse kinematics, 2-DOF arm |
| [pathfinding_grid_c.c](ADVANCED/ROBOTICS/pathfinding_grid_c.c) | A* on a grid, ASCII path display |
| [sensor_fusion_simple.c](ADVANCED/ROBOTICS/sensor_fusion_simple.c) | Complementary filter, two noisy sensors |
| [realtime_scheduler_sim.c](ADVANCED/ROBOTICS/realtime_scheduler_sim.c) | Cooperative RTOS-style task scheduler |

```bat
cd ADVANCED\ROBOTICS && build.bat
```

---

## ADVANCED / EMBEDDED

Real embedded C patterns — simulated hardware layer so everything runs on your laptop.

| File | Models |
|------|--------|
| [blink_led_sim.c](ADVANCED/EMBEDDED/blink_led_sim.c) | Arduino Uno LED blink |
| [button_debounce_sim.c](ADVANCED/EMBEDDED/button_debounce_sim.c) | Software debounce algorithm |
| [simple_rtos_scheduler.c](ADVANCED/EMBEDDED/simple_rtos_scheduler.c) | FreeRTOS-style cooperative scheduler |
| [uart_protocol_sim.c](ADVANCED/EMBEDDED/uart_protocol_sim.c) | Framed UART protocol + checksum validation |
| [interrupt_simulation.c](ADVANCED/EMBEDDED/interrupt_simulation.c) | Timer interrupt pattern vs polling |

Hardware layer: [gpio_simulated.h](ADVANCED/EMBEDDED/gpio_simulated.h) — replace with real MCU HAL for actual hardware.

```bat
cd ADVANCED\EMBEDDED && build.bat
```

---

## ADVANCED / GAMES

### Terminal Games (zero extra dependencies)

| Game | Build | Controls |
|------|-------|----------|
| [snake_terminal.c](ADVANCED/GAMES/snake_terminal.c) | `gcc snake_terminal.c -o snake_terminal.exe` | WASD / arrows |
| [tetris_terminal.c](ADVANCED/GAMES/tetris_terminal.c) | `gcc tetris_terminal.c -o tetris_terminal.exe` | W/A/D/S/Space |

### SDL2 Games (real windowed graphics — SDL2.dll pre-copied)

| Game | Description | Controls |
|------|-------------|----------|
| [pong_sdl2.c](ADVANCED/GAMES/pong_sdl2.c) | Classic Pong, AI opponent, 7-point win | W/S or Up/Down |
| [breakout_sdl2.c](ADVANCED/GAMES/breakout_sdl2.c) | Breakout, 6 colored brick rows, 3 lives | A/D or arrows, R=restart |
| [platformer_sdl2.c](ADVANCED/GAMES/platformer_sdl2.c) | 2D platformer, gravity, jump, reach the gold goal | A/D, Space/W=jump |

```bat
cd ADVANCED\GAMES && build.bat
```

> **SDL2 note**: `SDL2.dll` is already in `ADVANCED/GAMES/`. For new projects, copy it from
> `SDL2/SDL2-2.32.8/x86_64-w64-mingw32/bin/SDL2.dll`. See [SDL2_SETUP.md](SDL2_SETUP.md).

---

## PRACTICE

`PRACTICE/legacy/` — original practice files preserved from before the restructure.
Use this folder for any free-form extra practice work.

---

## Directory Structure

```
C-PROGRAM/
+-- BEGINNER/           day01..day14  (C fundamentals)
+-- INTERMEDIATE/       day01..day10  (data structures, algorithms)
+-- ADVANCED/
¦   +-- ROBOTICS/       5 robotics simulations
¦   +-- EMBEDDED/       5 embedded-systems projects (simulated HW)
¦   +-- GAMES/          2 terminal + 3 SDL2 games
+-- PRACTICE/
¦   +-- legacy/         original practice files
+-- SDL2/               SDL2 development libraries
+-- TOOLCHAIN_SETUP.md
+-- SDL2_SETUP.md
+-- README.md
+-- LICENSE
```

# Day 13 — Preprocessor & Multi-File Programs

## Objectives
- Use `#define` for constants and function-like macros
- Use `#include` for system and user headers
- Split a program across multiple .c files
- Write a proper .h header file
- Understand basic Makefile concepts
- Use conditional compilation `#ifdef`/`#ifndef`

## Concepts Covered
- `#define PI 3.14159`
- `#define SQ(x) ((x)*(x))` — macro with argument
- `#include "myheader.h"` vs `#include <stdio.h>`
- Header guards: `#ifndef MYHEADER_H ... #endif`
- `extern` declarations
- Separate compilation: `gcc a.c b.c -o prog`

## Time Estimate
~2.5 hours

## How to Build & Run
```
.\build.bat
lesson.exe
multi_file_demo.exe
```

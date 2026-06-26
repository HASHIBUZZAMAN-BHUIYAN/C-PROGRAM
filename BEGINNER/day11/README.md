# Day 11 — Dynamic Memory: malloc/calloc/realloc/free

## Objectives
- Allocate memory at runtime with malloc and calloc
- Resize allocations with realloc
- Always free allocated memory and avoid leaks
- Understand the heap vs the stack
- Detect and reason about common memory errors

## Concepts Covered
- `int *arr = malloc(n * sizeof(int));`
- `calloc(n, size)` — also zeroes memory
- `realloc(ptr, new_size)` — resize
- `free(ptr)` — release memory
- Always check malloc return for NULL
- Valgrind-style thinking: every malloc needs a free

## Time Estimate
~2 hours

## How to Build & Run
```
.\build.bat
lesson.exe
```

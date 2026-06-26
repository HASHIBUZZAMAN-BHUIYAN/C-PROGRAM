# Day 08 — Pointers I: Basics, Pointer Arithmetic, Pointers & Arrays

## Objectives
- Declare pointers and understand the address-of (&) and dereference (*) operators
- Understand the relationship between pointers and arrays
- Use pointer arithmetic to traverse arrays
- Pass pointers to functions to modify values (pass-by-pointer)

## Concepts Covered
- `int *p = &x;`  — pointer declaration
- `*p` — dereference (read/write the value at the address)
- `p++` — pointer arithmetic (moves by sizeof(type) bytes)
- Arrays decay to pointers: `arr` == `&arr[0]`
- `void swap(int *a, int *b)` — pass-by-pointer

## Time Estimate
~2.5 hours

## How to Build & Run
```
.\build.bat
lesson.exe
```

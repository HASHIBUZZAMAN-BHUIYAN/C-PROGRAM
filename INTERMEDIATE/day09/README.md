# Intermediate Day 09 — Multi-threading Basics

## Platform Note
Uses Windows threads (`windows.h` HANDLE/CreateThread) since this is a Windows machine.
The concepts (thread creation, mutexes, producer-consumer) are identical to pthreads.

## Objectives
- Create and join threads with CreateThread / WaitForSingleObject
- Synchronize with a mutex (CRITICAL_SECTION)
- Implement a producer-consumer queue with a fixed buffer
- Understand race conditions

## Time Estimate
~3 hours

## How to Build & Run
```
.\build.bat
lesson.exe
```

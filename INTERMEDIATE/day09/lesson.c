/*
 * Intermediate Day 09 — Multi-threading (Windows threads)
 * Compile: gcc lesson.c -o lesson.exe
 * Note: Uses Windows HANDLE/CreateThread/CRITICAL_SECTION
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* ======= Shared counter with a race condition demo then fix ======= */
static long counter_unsafe = 0;
static long counter_safe   = 0;
static CRITICAL_SECTION cs;

DWORD WINAPI increment_unsafe(LPVOID arg) {
    int n = *(int*)arg;
    for (int i = 0; i < n; i++) counter_unsafe++;  /* RACE CONDITION! */
    return 0;
}

DWORD WINAPI increment_safe(LPVOID arg) {
    int n = *(int*)arg;
    for (int i = 0; i < n; i++) {
        EnterCriticalSection(&cs);
        counter_safe++;
        LeaveCriticalSection(&cs);
    }
    return 0;
}

/* ======= Producer-Consumer ======= */
#define BUF_SIZE 8
static int  buf[BUF_SIZE];
static int  buf_head = 0, buf_tail = 0, buf_count = 0;
static CRITICAL_SECTION buf_cs;
static HANDLE sem_slots;   /* counts empty slots */
static HANDLE sem_items;   /* counts filled items */

DWORD WINAPI producer(LPVOID arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        WaitForSingleObject(sem_slots, INFINITE);   /* wait for empty slot */
        EnterCriticalSection(&buf_cs);
        int item = id * 100 + i;
        buf[buf_tail] = item;
        buf_tail = (buf_tail + 1) % BUF_SIZE;
        buf_count++;
        printf("  Producer %d put %d  (buf=%d)\n", id, item, buf_count);
        LeaveCriticalSection(&buf_cs);
        ReleaseSemaphore(sem_items, 1, NULL);        /* signal new item */
        Sleep(10);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 5; i++) {
        WaitForSingleObject(sem_items, INFINITE);    /* wait for item */
        EnterCriticalSection(&buf_cs);
        int item = buf[buf_head];
        buf_head = (buf_head + 1) % BUF_SIZE;
        buf_count--;
        printf("  Consumer %d got %d  (buf=%d)\n", id, item, buf_count);
        LeaveCriticalSection(&buf_cs);
        ReleaseSemaphore(sem_slots, 1, NULL);        /* signal empty slot */
        Sleep(15);
    }
    return 0;
}

int main(void) {
    printf("=== Intermediate Day 09: Multi-threading ===\n\n");

    /* --- Race condition demo --- */
    printf("--- Race Condition Demo ---\n");
    InitializeCriticalSection(&cs);

    HANDLE t1, t2;
    int iters = 100000;
    t1 = CreateThread(NULL, 0, increment_unsafe, &iters, 0, NULL);
    t2 = CreateThread(NULL, 0, increment_unsafe, &iters, 0, NULL);
    WaitForSingleObject(t1, INFINITE); WaitForSingleObject(t2, INFINITE);
    CloseHandle(t1); CloseHandle(t2);
    printf("Unsafe (2 threads * %d): expected=%d  got=%ld\n",
           iters, 2*iters, counter_unsafe);

    t1 = CreateThread(NULL, 0, increment_safe, &iters, 0, NULL);
    t2 = CreateThread(NULL, 0, increment_safe, &iters, 0, NULL);
    WaitForSingleObject(t1, INFINITE); WaitForSingleObject(t2, INFINITE);
    CloseHandle(t1); CloseHandle(t2);
    printf("Safe   (mutex-guarded):  expected=%d  got=%ld\n", 2*iters, counter_safe);
    DeleteCriticalSection(&cs);

    /* --- Producer-Consumer --- */
    printf("\n--- Producer-Consumer (1 producer, 1 consumer) ---\n");
    InitializeCriticalSection(&buf_cs);
    sem_slots = CreateSemaphore(NULL, BUF_SIZE, BUF_SIZE, NULL);
    sem_items = CreateSemaphore(NULL, 0,        BUF_SIZE, NULL);

    int prod_id=1, cons_id=1;
    HANDLE prod = CreateThread(NULL,0,producer,&prod_id,0,NULL);
    HANDLE cons = CreateThread(NULL,0,consumer,&cons_id,0,NULL);
    WaitForSingleObject(prod, INFINITE);
    WaitForSingleObject(cons, INFINITE);
    CloseHandle(prod); CloseHandle(cons);
    CloseHandle(sem_slots); CloseHandle(sem_items);
    DeleteCriticalSection(&buf_cs);

    printf("Producer-consumer finished cleanly.\n");
    return 0;
}

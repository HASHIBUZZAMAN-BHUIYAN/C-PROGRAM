/*
 * Intermediate Day 08 — Memory & Custom Pool Allocator
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* =====================================================
 * MEMORY POOL ALLOCATOR
 * Fixed-size blocks, no fragmentation, O(1) alloc/free
 * ===================================================== */
#define POOL_BLOCK_SIZE  32
#define POOL_BLOCK_COUNT 16

typedef struct PoolBlock {
    struct PoolBlock *next;
} PoolBlock;

typedef struct {
    uint8_t    memory[POOL_BLOCK_SIZE * POOL_BLOCK_COUNT];
    PoolBlock *free_list;
    int        blocks_used;
} MemPool;

void pool_init(MemPool *pool) {
    pool->free_list  = NULL;
    pool->blocks_used = 0;
    /* Link all blocks into free list */
    for (int i = POOL_BLOCK_COUNT - 1; i >= 0; i--) {
        PoolBlock *blk = (PoolBlock*)(pool->memory + i * POOL_BLOCK_SIZE);
        blk->next = pool->free_list;
        pool->free_list = blk;
    }
}

void* pool_alloc(MemPool *pool) {
    if (!pool->free_list) return NULL;  /* pool exhausted */
    PoolBlock *blk  = pool->free_list;
    pool->free_list = blk->next;
    pool->blocks_used++;
    memset(blk, 0, POOL_BLOCK_SIZE);
    return blk;
}

void pool_free(MemPool *pool, void *ptr) {
    PoolBlock *blk  = (PoolBlock*)ptr;
    blk->next = pool->free_list;
    pool->free_list = blk;
    pool->blocks_used--;
}

void pool_print_status(const MemPool *pool) {
    printf("Pool: %d/%d blocks used\n", pool->blocks_used, POOL_BLOCK_COUNT);
}

/* =====================================================
 * Stack frame visualization
 * ===================================================== */
void stack_demo_c(int depth) {
    int local = depth * 100;
    printf("  depth=%d  &local=%p  value=%d\n", depth, (void*)&local, local);
    if (depth > 0) stack_demo_c(depth - 1);
}

int main(void) {
    printf("=== Intermediate Day 08: Memory & Pool Allocator ===\n\n");

    /* Stack frame addresses */
    printf("--- Stack Frame Visualization ---\n");
    printf("  (local variables are on the stack; addresses decrease as calls go deeper)\n");
    stack_demo_c(4);

    /* Heap vs stack */
    int  stack_var = 42;
    int *heap_var  = malloc(sizeof(int));
    *heap_var = 99;
    printf("\n--- Stack vs Heap ---\n");
    printf("  stack_var address: %p  value: %d\n", (void*)&stack_var, stack_var);
    printf("  heap_var  address: %p  value: %d\n", (void*)heap_var,  *heap_var);
    free(heap_var);

    /* Memory pool */
    printf("\n--- Memory Pool Allocator ---\n");
    printf("  Block size: %d bytes  Blocks: %d  Total: %d bytes\n",
           POOL_BLOCK_SIZE, POOL_BLOCK_COUNT, POOL_BLOCK_SIZE*POOL_BLOCK_COUNT);

    MemPool pool;
    pool_init(&pool);
    pool_print_status(&pool);

    /* Allocate several blocks */
    void *ptrs[6];
    for (int i = 0; i < 6; i++) {
        ptrs[i] = pool_alloc(&pool);
        snprintf((char*)ptrs[i], POOL_BLOCK_SIZE, "Block %d data", i);
        printf("  Allocated block %d at %p: \"%s\"\n", i, ptrs[i], (char*)ptrs[i]);
    }
    pool_print_status(&pool);

    /* Free some */
    pool_free(&pool, ptrs[1]);
    pool_free(&pool, ptrs[3]);
    pool_print_status(&pool);

    /* Re-alloc (reuses freed blocks) */
    void *reused = pool_alloc(&pool);
    printf("  Reused block at: %p\n", reused);
    pool_print_status(&pool);

    /* Free remaining */
    pool_free(&pool, ptrs[0]);
    pool_free(&pool, ptrs[2]);
    pool_free(&pool, ptrs[4]);
    pool_free(&pool, ptrs[5]);
    pool_free(&pool, reused);
    pool_print_status(&pool);

    printf("\nMemory alignment: sizeof(int)=%zu  sizeof(double)=%zu  sizeof(void*)=%zu\n",
           sizeof(int), sizeof(double), sizeof(void*));

    return 0;
}

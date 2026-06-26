/*
 * Day 09 — Pointers II: double pointers & function pointers
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>

/* --- Function pointer demo functions --- */
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

/* A function that accepts another function as a parameter */
void apply_and_print(int x, int y, int (*op)(int, int), const char *name) {
    printf("%s(%d, %d) = %d\n", name, x, y, op(x, y));
}

int main(void) {
    printf("=== Day 09: Pointers II ===\n\n");

    /* --- Pointer to pointer --- */
    int  x   = 42;
    int *p   = &x;    /* pointer to int */
    int **pp = &p;    /* pointer to pointer to int */

    printf("x    = %d\n", x);
    printf("*p   = %d\n", *p);
    printf("**pp = %d\n", **pp);
    printf("Addresses: x=%p  p=%p  pp=%p\n",
           (void*)&x, (void*)p, (void*)pp);

    /* Modify via double pointer */
    **pp = 99;
    printf("After **pp=99: x=%d\n", x);

    /* --- Double pointer in function (out-parameter pattern) --- */
    printf("\n--- Double pointer as out-parameter ---\n");

    /* Common pattern: function that sets a pointer */
    int data = 7;
    int *result = NULL;

    /* Inline demonstration: set result to point at data */
    int **out = &result;
    *out = &data;
    printf("result now points to data=%d\n", *result);

    /* --- const with pointers --- */
    printf("\n--- const pointer variations ---\n");
    int val = 10;
    const int *ptr_to_const = &val;  /* can't change *ptr_to_const */
    int * const const_ptr   = &val;  /* can't change const_ptr itself */
    printf("ptr_to_const=%d  const_ptr=%d\n", *ptr_to_const, *const_ptr);
    /* *ptr_to_const = 20;  -- compile error */
    *const_ptr = 20;                 /* this IS allowed: val changes */
    printf("After *const_ptr=20: val=%d\n", val);

    /* --- Function pointers --- */
    printf("\n--- Function Pointers ---\n");
    int (*fp)(int, int);   /* declare a function pointer */

    fp = add;
    printf("fp = add:  fp(3, 4) = %d\n", fp(3, 4));

    fp = sub;
    printf("fp = sub:  fp(10, 3) = %d\n", fp(10, 3));

    fp = mul;
    printf("fp = mul:  fp(6, 7) = %d\n", fp(6, 7));

    /* Passing function pointer to another function */
    apply_and_print(8, 5, add, "add");
    apply_and_print(8, 5, sub, "sub");
    apply_and_print(8, 5, mul, "mul");

    /* --- Function pointer array (dispatch table) --- */
    printf("\n--- Dispatch Table ---\n");
    int (*ops[3])(int, int) = {add, sub, mul};
    const char *names[] = {"add", "sub", "mul"};
    int a = 12, b = 4;
    for (int i = 0; i < 3; i++) {
        printf("%s(%d, %d) = %d\n", names[i], a, b, ops[i](a, b));
    }

    return 0;
}

/*
 * Day 13 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>

#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : (x) > (hi) ? (hi) : (x))
#define SWAP(type, a, b) do { type _t = (a); (a) = (b); (b) = _t; } while(0)

#ifdef SPECIAL
  #define EASTER_EGG() printf("*** Easter egg found! Compile with -DSPECIAL ***\n")
#else
  #define EASTER_EGG()
#endif

int main(void) {
    /* Ex 1 */
    printf("CLAMP(5, 1, 10) = %d\n", CLAMP(5, 1, 10));
    printf("CLAMP(-3, 0, 10) = %d\n", CLAMP(-3, 0, 10));
    printf("CLAMP(15, 0, 10) = %d\n", CLAMP(15, 0, 10));

    /* Ex 3 */
    EASTER_EGG();

    /* Ex 4 */
    printf("File: %s  Line: %d\n", __FILE__, __LINE__);
    printf("Date: %s  Time: %s\n", __DATE__, __TIME__);

    /* Ex 5 */
    int a = 10, b = 20;
    SWAP(int, a, b);
    printf("After SWAP: a=%d b=%d\n", a, b);

    float x = 1.5f, y = 2.5f;
    SWAP(float, x, y);
    printf("After SWAP: x=%.1f y=%.1f\n", x, y);

    return 0;
}

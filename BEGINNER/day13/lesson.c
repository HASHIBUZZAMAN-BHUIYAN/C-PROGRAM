/*
 * Day 13 — Preprocessor & Multi-File Programs
 * Uses mathutils.h / mathutils.c
 * Compile: gcc lesson.c mathutils.c -o lesson.exe
 */
#include <stdio.h>
#include "mathutils.h"

/* Conditional compilation */
#define DEBUG_MODE 1

#ifdef DEBUG_MODE
  #define DPRINT(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
  #define DPRINT(fmt, ...)   /* nothing */
#endif

/* Stringify macro */
#define STRINGIFY(x) #x
#define TOSTRING(x)  STRINGIFY(x)

int main(void) {
    printf("=== Day 13: Preprocessor & Multi-File ===\n\n");

    /* --- #define constants --- */
    printf("PI      = %.10f\n", PI);
    printf("E       = %.10f\n", E);
    printf("GRAVITY = %.2f\n",  GRAVITY);

    /* --- Function-like macros --- */
    printf("\nSQ(5)       = %d\n", SQ(5));
    printf("CUBE(3)     = %d\n", CUBE(3));
    printf("MAX(7, 12)  = %d\n", MAX(7, 12));
    printf("ABS(-42)    = %d\n", ABS(-42));

    /* --- Functions from mathutils.c --- */
    double r = 5.0;
    printf("\ncircle_area(%.1f)   = %.4f\n", r, circle_area(r));
    printf("sphere_volume(%.1f) = %.4f\n", r, sphere_volume(r));
    printf("gcd(48, 18)        = %d\n", gcd(48, 18));
    printf("lcm(4, 6)          = %ld\n", lcm(4, 6));

    /* --- Debug printing (only compiled in DEBUG_MODE) --- */
    DPRINT("r = %.1f, area = %.4f", r, circle_area(r));

    /* --- Predefined macros --- */
    printf("\nBuilt from file : %s\n", __FILE__);
    printf("At line         : %d\n", __LINE__);
    printf("Compiled        : %s %s\n", __DATE__, __TIME__);

    /* --- Stringification --- */
    printf("\nPI stringified: " TOSTRING(PI) "\n");

    return 0;
}

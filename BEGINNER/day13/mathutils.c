/*
 * mathutils.c — implementation file for mathutils.h
 * Compile with: gcc mathutils.c lesson.c -o lesson.exe
 */
#include "mathutils.h"

double circle_area(double r)     { return PI * r * r; }
double sphere_volume(double r)   { return (4.0/3.0) * PI * r * r * r; }

int gcd(int a, int b) {
    while (b != 0) { int t = b; b = a % b; a = t; }
    return a;
}

long lcm(long a, long b) {
    return (a / gcd((int)a, (int)b)) * b;
}

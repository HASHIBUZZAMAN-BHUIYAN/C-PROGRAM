#ifndef MATHUTILS_H
#define MATHUTILS_H

/* Constants */
#define PI      3.14159265358979
#define E       2.71828182845905
#define GRAVITY 9.81

/* Macros */
#define SQ(x)     ((x) * (x))
#define CUBE(x)   ((x) * (x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x)    ((x) >= 0 ? (x) : -(x))

/* Function prototypes */
double circle_area(double radius);
double sphere_volume(double radius);
int    gcd(int a, int b);
long   lcm(long a, long b);

#endif /* MATHUTILS_H */

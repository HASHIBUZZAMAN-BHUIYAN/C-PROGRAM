/*
 * Day 02 — Operators, Expressions, Type Casting, const
 * Compile: gcc lesson.c -o lesson.exe
 */
#include <stdio.h>

int main(void) {
    printf("=== Day 02: Operators & Expressions ===\n\n");

    /* --- Arithmetic operators --- */
    int a = 17, b = 5;
    printf("a=%d  b=%d\n", a, b);
    printf("a+b=%d  a-b=%d  a*b=%d  a/b=%d  a%%b=%d\n",
           a+b, a-b, a*b, a/b, a%b);

    /* --- Increment / decrement --- */
    int x = 10;
    printf("\nBefore: x=%d\n", x);
    int old_x = x++; printf("x++ (post): returned %d, x is now %d\n", old_x, x);
    int new_x = ++x; printf("++x (pre) : returned %d, x is now %d\n", new_x, x);

    /* --- Compound assignment --- */
    int n = 100;
    n += 5;   printf("n+=5  -> %d\n", n);
    n -= 20;  printf("n-=20 -> %d\n", n);
    n *= 2;   printf("n*=2  -> %d\n", n);
    n /= 3;   printf("n/=3  -> %d\n", n);
    n %= 7;   printf("n%%=7  -> %d\n", n);

    /* --- Relational operators (result: 0=false, 1=true) --- */
    printf("\nRelational (a=%d, b=%d):\n", a, b);
    printf("a==b:%d  a!=b:%d  a>b:%d  a<b:%d  a>=b:%d  a<=b:%d\n",
           a==b, a!=b, a>b, a<b, a>=b, a<=b);

    /* --- Logical operators --- */
    int p = 1, q = 0;
    printf("\nLogical (p=%d, q=%d):\n", p, q);
    printf("p&&q=%d  p||q=%d  !p=%d\n", p&&q, p||q, !p);

    /* --- Type casting --- */
    int   i  = 7;
    float f  = 2.5f;
    printf("\nType casting:\n");
    printf("7 / 2   = %d  (integer division)\n", 7 / 2);
    printf("7 / 2.0 = %.1f (float division)\n", 7 / 2.0);
    printf("(float)i / 2 = %.1f\n", (float)i / 2);
    printf("(int)f = %d\n", (int)f);   /* truncates, does not round */

    /* --- const: value cannot change after initialisation --- */
    const double PI = 3.14159265;
    double radius = 5.0;
    printf("\nCircle radius=%.1f: area=%.4f  circumference=%.4f\n",
           radius, PI * radius * radius, 2 * PI * radius);
    /* PI = 3.0;  <-- would cause a compile error */

    return 0;
}

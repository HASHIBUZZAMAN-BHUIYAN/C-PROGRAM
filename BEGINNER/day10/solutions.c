/*
 * Day 10 — Solutions
 * Compile: gcc solutions.c -o solutions.exe -lm
 */
#include <stdio.h>
#include <math.h>

typedef struct { double width, height; } Rectangle;
typedef struct { double x, y; } Point;
typedef struct { int h, m, s; } Time;
typedef struct { char item[32]; int qty; float price; } Item;

double rect_area(Rectangle r) { return r.width * r.height; }
double rect_perim(Rectangle r) { return 2 * (r.width + r.height); }
double dist_origin(Point p) { return sqrt(p.x*p.x + p.y*p.y); }

Time add_time(Time a, Time b) {
    Time r;
    r.s = a.s + b.s;
    r.m = a.m + b.m + r.s / 60;
    r.s %= 60;
    r.h = a.h + b.h + r.m / 60;
    r.m %= 60;
    r.h %= 24;
    return r;
}

int main(void) {
    /* Ex 1 */
    Rectangle rec = {5.0, 3.0};
    printf("Area=%.1f  Perimeter=%.1f\n", rect_area(rec), rect_perim(rec));

    /* Ex 2 */
    Point pts[5] = {{1,2},{3,4},{0,5},{-2,1},{6,0}};
    int maxIdx = 0;
    for (int i = 1; i < 5; i++) if (dist_origin(pts[i]) > dist_origin(pts[maxIdx])) maxIdx = i;
    printf("Furthest: (%.1f, %.1f) dist=%.2f\n", pts[maxIdx].x, pts[maxIdx].y, dist_origin(pts[maxIdx]));

    /* Ex 3 */
    Time t1 = {1, 50, 45}, t2 = {0, 15, 30};
    Time t3 = add_time(t1, t2);
    printf("Time sum: %02d:%02d:%02d\n", t3.h, t3.m, t3.s);

    /* Ex 4 */
    union Multi { int i; double d; char c[8]; };
    union Multi u;
    printf("Union size: %zu\n", sizeof(u));
    u.i = 42; printf("int: %d\n", u.i);
    u.d = 3.14; printf("double: %.2f\n", u.d);

    /* Ex 5 */
    Item inv[] = {{"Widget",10,2.5f},{"Gadget",5,15.0f},{"Doohickey",20,1.0f},
                  {"Thingamajig",3,30.0f},{"Whatchamacallit",8,5.0f}};
    float total = 0;
    for (int i = 0; i < 5; i++) total += inv[i].qty * inv[i].price;
    printf("Total inventory value: $%.2f\n", total);

    return 0;
}

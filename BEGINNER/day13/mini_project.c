/*
 * Day 13 Mini-Project — Multi-file geometry calculator
 * Uses mathutils.h / mathutils.c
 * Compile: gcc mini_project.c mathutils.c -o mini_project.exe -lm
 */
#include <stdio.h>
#include <math.h>
#include "mathutils.h"

int main(void) {
    printf("=== Geometry Calculator ===\n");
    printf("Shape: 1=circle  2=sphere  3=cylinder  4=cone\n> ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        double r; printf("Radius: "); scanf("%lf", &r);
        printf("Area        : %.4f\n", circle_area(r));
        printf("Circumference: %.4f\n", 2 * PI * r);
        break;
    }
    case 2: {
        double r; printf("Radius: "); scanf("%lf", &r);
        printf("Volume      : %.4f\n", sphere_volume(r));
        printf("Surface area: %.4f\n", 4 * PI * r * r);
        break;
    }
    case 3: {
        double r, h; printf("Radius: "); scanf("%lf", &r); printf("Height: "); scanf("%lf", &h);
        printf("Volume      : %.4f\n", PI * r * r * h);
        printf("Surface area: %.4f\n", 2 * PI * r * (r + h));
        break;
    }
    case 4: {
        double r, h; printf("Radius: "); scanf("%lf", &r); printf("Height: "); scanf("%lf", &h);
        double slant = sqrt(r*r + h*h);
        printf("Volume      : %.4f\n", (PI * r * r * h) / 3.0);
        printf("Surface area: %.4f\n", PI * r * (r + slant));
        break;
    }
    default: printf("Invalid\n");
    }
    return 0;
}

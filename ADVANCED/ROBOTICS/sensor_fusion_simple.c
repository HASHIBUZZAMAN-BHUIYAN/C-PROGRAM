/*
 * Sensor Fusion — Complementary Filter
 * Models: two noisy sensors measuring the same quantity (e.g. gyro + accelerometer).
 * A complementary filter blends them: fused = alpha*fast_sensor + (1-alpha)*slow_sensor
 *
 * Compile: gcc sensor_fusion_simple.c -o sensor_fusion_simple.exe -lm
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Pseudo-random noise (deterministic for reproducibility) */
static unsigned int rng_state = 12345;
double rand_noise(double amplitude) {
    rng_state = rng_state * 1664525u + 1013904223u;
    return amplitude * ((double)(int)rng_state / 2147483648.0);
}

int main(void) {
    printf("=== Sensor Fusion: Complementary Filter ===\n");
    printf("True signal: sine wave  |  Sensor1: low noise  |  Sensor2: high noise\n\n");
    printf("%-6s %-10s %-12s %-12s %-12s\n", "t(s)", "True", "Sensor1", "Sensor2", "Fused");
    printf("%-6s %-10s %-12s %-12s %-12s\n", "------", "----------", "------------", "------------", "------------");

    double alpha  = 0.8;   /* weight for sensor1 (lower noise) */
    double fused  = 0.0;
    double dt     = 0.1;
    int    steps  = 60;

    for (int i = 0; i <= steps; i++) {
        double t    = i * dt;
        double true_val  = 10.0 * sin(2.0 * 3.14159 * 0.2 * t);  /* 0.2 Hz sine */
        double s1   = true_val + rand_noise(0.5);   /* low noise */
        double s2   = true_val + rand_noise(3.0);   /* high noise */
        fused = alpha * s1 + (1.0 - alpha) * s2;

        if (i % 5 == 0)
            printf("%-6.1f %-10.3f %-12.3f %-12.3f %-12.3f\n",
                   t, true_val, s1, s2, fused);
    }

    printf("\nalpha=%.1f means %.0f%% weight on low-noise Sensor1\n", alpha, alpha*100);
    printf("Fused signal tracks true signal better than Sensor2 alone.\n");
    return 0;
}

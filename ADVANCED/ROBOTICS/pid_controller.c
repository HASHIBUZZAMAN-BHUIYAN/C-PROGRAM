/*
 * PID Controller Simulation
 * Models: a simulated motor (or any first-order system) being controlled to a setpoint.
 * Outputs a time-series of system response to stdout AND writes pid_output.csv.
 *
 * Compile: gcc pid_controller.c -o pid_controller.exe -lm
 * Run:     pid_controller.exe
 *
 * To plot: load pid_output.csv in Excel, Python (matplotlib), or any graphing tool.
 * Columns: time_s, setpoint, measured, error, control_output
 */
#include <stdio.h>
#include <math.h>

/* PID state */
typedef struct {
    double kp, ki, kd;
    double integral;
    double prev_error;
    double output_min, output_max;
} PID;

void pid_init(PID *pid, double kp, double ki, double kd, double lo, double hi) {
    pid->kp = kp; pid->ki = ki; pid->kd = kd;
    pid->integral = 0; pid->prev_error = 0;
    pid->output_min = lo; pid->output_max = hi;
}

double pid_update(PID *pid, double setpoint, double measured, double dt) {
    double error = setpoint - measured;
    pid->integral += error * dt;
    double derivative = (error - pid->prev_error) / dt;
    pid->prev_error = error;

    double output = pid->kp * error + pid->ki * pid->integral + pid->kd * derivative;

    /* Clamp output */
    if (output > pid->output_max) output = pid->output_max;
    if (output < pid->output_min) output = pid->output_min;
    return output;
}

/* Simple first-order plant model: output changes toward input with time constant tau */
double plant_update(double current, double input, double tau, double dt) {
    return current + (input - current) * (dt / tau);
}

int main(void) {
    printf("=== PID Controller Simulation ===\n");
    printf("Setpoint: 100.0 (target speed)\n");
    printf("Plant: first-order, tau=0.5s\n\n");

    PID pid;
    pid_init(&pid,
        2.0,    /* Kp: proportional gain */
        0.8,    /* Ki: integral gain     */
        0.1,    /* Kd: derivative gain   */
        -200.0, /* output min            */
        200.0   /* output max            */
    );

    double setpoint  = 100.0;
    double measured  = 0.0;
    double tau       = 0.5;    /* plant time constant (seconds) */
    double dt        = 0.05;   /* simulation step (50 ms) */
    double sim_time  = 5.0;    /* total simulation time  */
    int    steps     = (int)(sim_time / dt);

    FILE *csv = fopen("pid_output.csv", "w");
    fprintf(csv, "time_s,setpoint,measured,error,control_output\n");

    printf("%-8s %-10s %-10s %-10s %-10s\n", "Time(s)", "Setpoint", "Measured", "Error", "Output");
    printf("%-8s %-10s %-10s %-10s %-10s\n", "-------", "--------", "--------", "-----", "------");

    for (int i = 0; i <= steps; i++) {
        double t = i * dt;
        double control = pid_update(&pid, setpoint, measured, dt);
        measured = plant_update(measured, control, tau, dt);

        double error = setpoint - measured;
        if (i % 5 == 0)  /* print every 5th step */
            printf("%-8.2f %-10.2f %-10.2f %-10.2f %-10.2f\n",
                   t, setpoint, measured, error, control);
        fprintf(csv, "%.3f,%.3f,%.3f,%.3f,%.3f\n", t, setpoint, measured, error, control);
    }

    fclose(csv);
    printf("\nWrote pid_output.csv (plot columns: time_s vs measured)\n");
    printf("Steady-state error: %.4f\n", setpoint - measured);
    return 0;
}

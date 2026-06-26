/*
 * Day 12 — Solutions
 * Compile: gcc solutions.c -o solutions.exe
 */
#include <stdio.h>
#include <string.h>
#include <time.h>

void log_message(const char *msg) {
    FILE *f = fopen("log.txt", "a");
    if (!f) return;
    time_t t = time(NULL);
    char *ts = ctime(&t);
    ts[strcspn(ts, "\n")] = '\0';
    fprintf(f, "[%s] %s\n", ts, msg);
    fclose(f);
}

int main(void) {
    /* Ex 1 */
    FILE *f = fopen("ex1.txt", "w");
    fprintf(f, "Hello, file!\n");
    for (int i = 0; i < 5; i++) fprintf(f, "User line %d\n", i+1);
    fclose(f);
    f = fopen("ex1.txt", "r"); fseek(f, 0, SEEK_END); printf("Chars: %ld\n", ftell(f)); fclose(f);

    /* Ex 2 */
    f = fopen("ex1.txt", "r");
    char line[128]; int ln = 1;
    while (fgets(line, sizeof(line), f)) printf("%3d: %s", ln++, line);
    fclose(f);

    /* Ex 3 */
    double vals[10];
    for (int i = 0; i < 10; i++) vals[i] = (i+1) * 1.1;
    f = fopen("vals.bin", "wb"); fwrite(vals, sizeof(double), 10, f); fclose(f);
    double back[10] = {0};
    f = fopen("vals.bin", "rb"); fread(back, sizeof(double), 10, f); fclose(f);
    int ok = 1;
    for (int i = 0; i < 10; i++) if (vals[i] != back[i]) ok = 0;
    printf("Binary round-trip: %s\n", ok ? "OK" : "FAILED");

    /* Ex 4 */
    f = fopen("ex1.txt", "r"); fseek(f, -20, SEEK_END);
    char tail[21] = {0}; fread(tail, 1, 20, f); fclose(f);
    printf("Last 20 chars: [%s]\n", tail);

    /* Ex 5 */
    log_message("Application started");
    log_message("Test event");
    printf("Logged to log.txt\n");

    remove("ex1.txt"); remove("vals.bin"); remove("log.txt");
    return 0;
}

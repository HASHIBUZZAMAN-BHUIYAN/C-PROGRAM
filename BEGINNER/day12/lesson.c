/*
 * Day 12 — File I/O
 * Compile: gcc lesson.c -o lesson.exe
 * Creates: test.txt, numbers.bin
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("=== Day 12: File I/O ===\n\n");

    /* --- Write a text file --- */
    FILE *f = fopen("test.txt", "w");
    if (!f) { perror("fopen write"); return 1; }

    fprintf(f, "Line 1: Hello, file!\n");
    fprintf(f, "Line 2: C file I/O demo\n");
    fprintf(f, "Score: %d  GPA: %.2f\n", 95, 3.8);
    fclose(f);
    printf("Written test.txt\n");

    /* --- Read back the text file --- */
    f = fopen("test.txt", "r");
    if (!f) { perror("fopen read"); return 1; }

    printf("\nContents of test.txt:\n");
    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
        printf("  %s", line);
    }
    fclose(f);

    /* --- Append to the file --- */
    f = fopen("test.txt", "a");
    fprintf(f, "Line 3: Appended!\n");
    fclose(f);
    printf("\nAppended a line.\n");

    /* --- fscanf: read formatted data --- */
    f = fopen("test.txt", "r");
    int lines = 0;
    while (!feof(f)) {
        if (fgets(line, sizeof(line), f)) lines++;
    }
    fclose(f);
    printf("Total lines: %d\n", lines);

    /* --- Binary file I/O --- */
    printf("\n--- Binary File ---\n");
    int data[] = {10, 20, 30, 40, 50};
    int n = 5;

    FILE *bf = fopen("numbers.bin", "wb");
    if (!bf) { perror("bin fopen"); return 1; }
    fwrite(data, sizeof(int), n, bf);
    fclose(bf);
    printf("Wrote %d ints to numbers.bin\n", n);

    /* Read binary file back */
    bf = fopen("numbers.bin", "rb");
    int read_data[5] = {0};
    size_t count = fread(read_data, sizeof(int), 5, bf);
    fclose(bf);

    printf("Read back %zu ints: ", count);
    for (int i = 0; i < (int)count; i++) printf("%d ", read_data[i]);
    printf("\n");

    /* --- fseek / ftell --- */
    f = fopen("test.txt", "r");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    printf("\nFile size of test.txt: %ld bytes\n", size);
    fseek(f, 0, SEEK_SET);   /* back to start */
    fclose(f);

    /* Cleanup */
    remove("test.txt");
    remove("numbers.bin");
    printf("Cleaned up temporary files.\n");

    return 0;
}

#include <stdio.h>
//hashib
int writeFile(void)
{
    FILE *fp = fopen("sample.txt", "w");
    if (fp == NULL) {
        perror("file opening Failed");
        return 1;
    } else {
        printf("file opening Success\n");
    }

    // 1. save character
    fputc('a', fp);
    fputc('b', fp);
    fputc('c', fp);
    fputc('\n', fp);

    // 2. save string
    fputs("hello", fp);
    fputs(" world\n", fp);

    // 3. save number
    fprintf(fp, "%d %d %d %.2f", 1, 2, 3, 3.14);

    fclose(fp);
    return 0;
}

int readFile(void)
{
    FILE *fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        perror("Fail to open");
        return 1;
    }

    // 1. read 4 characters
    char ch1 = fgetc(fp);
    char ch2 = fgetc(fp);
    char ch3 = fgetc(fp);
    char ch4 = fgetc(fp);

    // 2. read string
    char str1[20], str2[20];
    fscanf(fp, "%s %s", str1, str2);

    // 3. read numbers
    int n1, n2, n3;
    float f;
    fscanf(fp, "%d %d %d %f", &n1, &n2, &n3, &f);

    // print
    printf("\n== readFile ==\n");
    printf("Characters: %c %c %c %c\n", ch1, ch2, ch3, ch4);
    printf("String: %s %s\n", str1, str2);
    printf("Integers: %d %d %d\n", n1, n2, n3);
    printf("Float: %.2f\n", f);

    fclose(fp);
    return 0;
}

int readFileByOne(void)
{
    FILE *fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        perror("file opening Failed");
        return 1;
    } else {
        printf("file opening Success\n");
    }

    printf("\n== readFileByOne ==\n");
    int c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }

    fclose(fp);
    return 0;
}

int readFileByLine(void)
{
    FILE *fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        perror("file opening Failed");
        return 1;
    } else {
        printf("file opening Success\n");
    }

    printf("\n== readFileByLine ==\n");
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}

int main(void)
{
    writeFile();
    readFile();
    readFileByOne();
    readFileByLine();
    return 0;
}

/*
 * Int Day 02 Mini-Project — RPN Calculator using a Stack
 * Compile: gcc mini_project.c -o mini_project.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_MAX 64
typedef struct { double data[STACK_MAX]; int top; } DStack;
void   ds_init(DStack *s)         { s->top = -1; }
int    ds_empty(DStack *s)        { return s->top < 0; }
void   ds_push(DStack *s, double v){ s->data[++s->top] = v; }
double ds_pop(DStack *s)          { return s->data[s->top--]; }

int main(void) {
    DStack s; ds_init(&s);
    char line[256];
    printf("=== RPN Calculator ===\n");
    printf("Enter RPN expression (e.g. '3 4 + 2 *'): ");
    fgets(line, sizeof(line), stdin);

    char *tok = strtok(line, " \t\n");
    while (tok) {
        if (isdigit((unsigned char)tok[0]) || (tok[0]=='-' && isdigit((unsigned char)tok[1]))) {
            ds_push(&s, atof(tok));
        } else {
            double b = ds_pop(&s), a = ds_pop(&s);
            if      (tok[0]=='+') ds_push(&s, a+b);
            else if (tok[0]=='-') ds_push(&s, a-b);
            else if (tok[0]=='*') ds_push(&s, a*b);
            else if (tok[0]=='/') { if(b==0){printf("Div by zero\n");return 1;} ds_push(&s,a/b); }
            else { printf("Unknown op: %s\n", tok); return 1; }
        }
        tok = strtok(NULL, " \t\n");
    }
    if (!ds_empty(&s)) printf("Result: %.6g\n", ds_pop(&s));
    return 0;
}

/*
 * Snake — Terminal Game (Windows Console)
 * Controls: WASD or arrow keys. Q to quit.
 * Uses Windows Console API for raw input + rendering.
 *
 * Compile: gcc snake_terminal.c -o snake_terminal.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDTH   40
#define HEIGHT  20
#define MAX_LEN (WIDTH * HEIGHT)

/* ANSI color codes (Windows 10+ supports them) */
#define CLR_RESET  "\x1b[0m"
#define CLR_GREEN  "\x1b[32m"
#define CLR_RED    "\x1b[31m"
#define CLR_YELLOW "\x1b[33m"
#define CLR_CYAN   "\x1b[36m"
#define CLR_WHITE  "\x1b[37m"

typedef struct { int x, y; } Point;

/* Game state */
static Point  snake[MAX_LEN];
static int    snake_len;
static Point  food;
static int    dir_x, dir_y;
static int    score;
static int    running;

void move_cursor(int x, int y) { printf("\x1b[%d;%dH", y+1, x+1); }
void clear_screen(void)        { printf("\x1b[2J\x1b[H"); }
void hide_cursor(void)         { printf("\x1b[?25l"); }
void show_cursor(void)         { printf("\x1b[?25h"); }

void spawn_food(void) {
    int ok;
    do {
        ok = 1;
        food.x = rand() % (WIDTH  - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
        for (int i = 0; i < snake_len; i++)
            if (snake[i].x == food.x && snake[i].y == food.y) { ok = 0; break; }
    } while (!ok);
}

void init_game(void) {
    snake_len = 3;
    for (int i = 0; i < snake_len; i++) { snake[i].x = WIDTH/2 - i; snake[i].y = HEIGHT/2; }
    dir_x = 1; dir_y = 0;
    score = 0; running = 1;
    srand((unsigned)time(NULL));
    spawn_food();
}

void draw(void) {
    move_cursor(0, 0);
    /* Top border */
    printf(CLR_WHITE);
    for (int x = 0; x < WIDTH; x++) printf("#");
    printf("\n");

    /* Game rows */
    for (int y = 1; y < HEIGHT - 1; y++) {
        printf("#");
        for (int x = 1; x < WIDTH - 1; x++) {
            int is_head = (snake[0].x == x && snake[0].y == y);
            int is_body = 0;
            for (int i = 1; i < snake_len; i++)
                if (snake[i].x == x && snake[i].y == y) { is_body = 1; break; }
            int is_food = (food.x == x && food.y == y);

            if      (is_head) printf(CLR_GREEN  "O" CLR_RESET);
            else if (is_body) printf(CLR_GREEN  "o" CLR_RESET);
            else if (is_food) printf(CLR_RED    "*" CLR_RESET);
            else              printf(" ");
        }
        printf("#\n");
    }
    /* Bottom border */
    for (int x = 0; x < WIDTH; x++) printf("#");
    printf(CLR_YELLOW "\nScore: %d   WASD=move  Q=quit" CLR_RESET "     \n", score);
}

void update(void) {
    /* Read input (non-blocking) */
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 0 || ch == 0xE0) ch = _getch();  /* arrow key prefix */
        switch (ch) {
            case 'w': case 'W': case 72: if (dir_y != 1)  { dir_x=0; dir_y=-1; } break;
            case 's': case 'S': case 80: if (dir_y != -1) { dir_x=0; dir_y= 1; } break;
            case 'a': case 'A': case 75: if (dir_x != 1)  { dir_x=-1;dir_y= 0; } break;
            case 'd': case 'D': case 77: if (dir_x != -1) { dir_x= 1;dir_y= 0; } break;
            case 'q': case 'Q': running = 0; return;
        }
    }

    /* Move snake */
    Point new_head = { snake[0].x + dir_x, snake[0].y + dir_y };

    /* Wall collision */
    if (new_head.x <= 0 || new_head.x >= WIDTH-1 || new_head.y <= 0 || new_head.y >= HEIGHT-1) {
        running = 0; return;
    }

    /* Self collision */
    for (int i = 0; i < snake_len - 1; i++)
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) { running = 0; return; }

    /* Shift body */
    for (int i = snake_len - 1; i > 0; i--) snake[i] = snake[i-1];
    snake[0] = new_head;

    /* Food eaten */
    if (new_head.x == food.x && new_head.y == food.y) {
        score += 10;
        if (snake_len < MAX_LEN - 1) snake_len++;
        spawn_food();
    }
}

int main(void) {
    /* Enable ANSI escape codes on Windows */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  mode;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    clear_screen();
    hide_cursor();
    init_game();

    while (running) {
        draw();
        update();
        Sleep(120);   /* ~8 FPS */
    }

    show_cursor();
    clear_screen();
    printf(CLR_RED "GAME OVER" CLR_RESET " — Final score: %d\n", score);
    return 0;
}

/*
 * Tetris — Terminal Game (Windows Console)
 * Controls: A/D = move, W = rotate, S = soft drop, Space = hard drop, Q = quit.
 *
 * Compile: gcc tetris_terminal.c -o tetris_terminal.exe
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define BOARD_W  10
#define BOARD_H  20
#define PREVIEW_X (BOARD_W + 4)

/* ANSI colors */
#define CLR_RESET  "\x1b[0m"
#define CLR_CYAN   "\x1b[36m"
#define CLR_BLUE   "\x1b[34m"
#define CLR_ORANGE "\x1b[33m"
#define CLR_YELLOW "\x1b[93m"
#define CLR_GREEN  "\x1b[32m"
#define CLR_PURPLE "\x1b[35m"
#define CLR_RED    "\x1b[31m"
#define CLR_WHITE  "\x1b[37m"

/* Tetromino definitions: 4 rotations * 4 blocks each */
static const int PIECES[7][4][4][2] = {
    /* I */ {{{0,1},{1,1},{2,1},{3,1}},{{2,0},{2,1},{2,2},{2,3}},{{0,2},{1,2},{2,2},{3,2}},{{1,0},{1,1},{1,2},{1,3}}},
    /* O */ {{{1,0},{2,0},{1,1},{2,1}},{{1,0},{2,0},{1,1},{2,1}},{{1,0},{2,0},{1,1},{2,1}},{{1,0},{2,0},{1,1},{2,1}}},
    /* T */ {{{1,0},{0,1},{1,1},{2,1}},{{1,0},{1,1},{2,1},{1,2}},{{0,1},{1,1},{2,1},{1,2}},{{1,0},{0,1},{1,1},{1,2}}},
    /* S */ {{{1,0},{2,0},{0,1},{1,1}},{{1,0},{1,1},{2,1},{2,2}},{{1,1},{2,1},{0,2},{1,2}},{{0,0},{0,1},{1,1},{1,2}}},
    /* Z */ {{{0,0},{1,0},{1,1},{2,1}},{{2,0},{1,1},{2,1},{1,2}},{{0,1},{1,1},{1,2},{2,2}},{{1,0},{0,1},{1,1},{0,2}}},
    /* L */ {{{2,0},{0,1},{1,1},{2,1}},{{1,0},{1,1},{1,2},{2,2}},{{0,1},{1,1},{2,1},{0,2}},{{0,0},{1,0},{1,1},{1,2}}},
    /* J */ {{{0,0},{0,1},{1,1},{2,1}},{{1,0},{2,0},{1,1},{1,2}},{{0,1},{1,1},{2,1},{2,2}},{{1,0},{1,1},{0,2},{1,2}}},
};
static const char *COLORS[] = {CLR_CYAN,CLR_YELLOW,CLR_PURPLE,CLR_GREEN,CLR_RED,CLR_ORANGE,CLR_BLUE};

typedef struct { int x, y, type, rot; } Piece;

static int  board[BOARD_H][BOARD_W];   /* 0=empty, 1-7=block color */
static int  board_colors[BOARD_H][BOARD_W];
static Piece cur, next_p;
static int  score, lines, level, running, game_over;
static long drop_interval;

void move_cursor(int x, int y) { printf("\x1b[%d;%dH", y+1, x*2+1); }
void clear_screen(void)        { printf("\x1b[2J"); }
void hide_cursor(void)         { printf("\x1b[?25l"); }
void show_cursor(void)         { printf("\x1b[?25h"); }

int new_piece_type(void) { return rand() % 7; }

void spawn_piece(Piece *p, int type) {
    p->type = type; p->rot = 0;
    p->x = BOARD_W/2 - 2; p->y = 0;
}

int collides(const Piece *p, int dx, int dy, int dr) {
    int rot = (p->rot + dr + 4) % 4;
    for (int i = 0; i < 4; i++) {
        int nx = p->x + PIECES[p->type][rot][i][0] + dx;
        int ny = p->y + PIECES[p->type][rot][i][1] + dy;
        if (nx < 0 || nx >= BOARD_W || ny >= BOARD_H) return 1;
        if (ny < 0) continue;
        if (board[ny][nx]) return 1;
    }
    return 0;
}

void lock_piece(const Piece *p) {
    for (int i = 0; i < 4; i++) {
        int nx = p->x + PIECES[p->type][p->rot][i][0];
        int ny = p->y + PIECES[p->type][p->rot][i][1];
        if (ny >= 0 && ny < BOARD_H) {
            board[ny][nx] = 1;
            board_colors[ny][nx] = p->type + 1;
        }
    }
}

int clear_lines(void) {
    int cleared = 0;
    for (int r = BOARD_H - 1; r >= 0; r--) {
        int full = 1;
        for (int c = 0; c < BOARD_W; c++) if (!board[r][c]) { full = 0; break; }
        if (full) {
            for (int rr = r; rr > 0; rr--) {
                memcpy(board[rr], board[rr-1], sizeof(board[0]));
                memcpy(board_colors[rr], board_colors[rr-1], sizeof(board_colors[0]));
            }
            memset(board[0], 0, sizeof(board[0]));
            memset(board_colors[0], 0, sizeof(board_colors[0]));
            cleared++; r++;  /* recheck this row */
        }
    }
    return cleared;
}

void draw_board(void) {
    /* Border */
    for (int y = 0; y < BOARD_H; y++) {
        move_cursor(-1, y);
        printf(CLR_WHITE "|" CLR_RESET);
        for (int x = 0; x < BOARD_W; x++) {
            /* Check active piece */
            int is_cur = 0;
            for (int i = 0; i < 4; i++) {
                int px = cur.x + PIECES[cur.type][cur.rot][i][0];
                int py = cur.y + PIECES[cur.type][cur.rot][i][1];
                if (px == x && py == y) { is_cur = 1; break; }
            }
            if (is_cur) printf("%s[]" CLR_RESET, COLORS[cur.type]);
            else if (board[y][x]) printf("%s[]" CLR_RESET, COLORS[board_colors[y][x]-1]);
            else printf("  ");
        }
        printf(CLR_WHITE "|" CLR_RESET);
    }
    /* Bottom */
    move_cursor(-1, BOARD_H);
    printf(CLR_WHITE);
    for (int x = 0; x < BOARD_W + 2; x++) printf("--");
    printf(CLR_RESET);

    /* Info panel */
    move_cursor(PREVIEW_X, 1);  printf("TETRIS");
    move_cursor(PREVIEW_X, 3);  printf("Score: %d   ", score);
    move_cursor(PREVIEW_X, 4);  printf("Lines: %d   ", lines);
    move_cursor(PREVIEW_X, 5);  printf("Level: %d   ", level);
    move_cursor(PREVIEW_X, 7);  printf("Next:");
    /* Draw next piece preview */
    for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) {
        move_cursor(PREVIEW_X + c, 8 + r);
        printf("  ");
    }
    for (int i = 0; i < 4; i++) {
        int px = PIECES[next_p.type][0][i][0];
        int py = PIECES[next_p.type][0][i][1];
        move_cursor(PREVIEW_X + px, 8 + py);
        printf("%s[]" CLR_RESET, COLORS[next_p.type]);
    }
    move_cursor(PREVIEW_X, 13); printf("W=rotate");
    move_cursor(PREVIEW_X, 14); printf("A/D=move");
    move_cursor(PREVIEW_X, 15); printf("S=down  ");
    move_cursor(PREVIEW_X, 16); printf("SPC=drop");
    move_cursor(PREVIEW_X, 17); printf("Q=quit  ");
}

void handle_input(void) {
    if (!_kbhit()) return;
    int ch = _getch();
    if (ch == 0 || ch == 0xE0) ch = _getch();
    switch (ch) {
        case 'a': case 'A': case 75: if (!collides(&cur,-1,0,0)) cur.x--; break;
        case 'd': case 'D': case 77: if (!collides(&cur, 1,0,0)) cur.x++; break;
        case 'w': case 'W': case 72: if (!collides(&cur, 0,0,1)) cur.rot=(cur.rot+1)%4; break;
        case 's': case 'S': case 80: if (!collides(&cur, 0,1,0)) cur.y++; break;
        case ' ': while (!collides(&cur,0,1,0)) cur.y++; break;
        case 'q': case 'Q': running = 0; break;
    }
}

int main(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode; GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    srand((unsigned)time(NULL));
    clear_screen(); hide_cursor();

    memset(board, 0, sizeof(board));
    memset(board_colors, 0, sizeof(board_colors));
    score = lines = 0; level = 1; running = 1; game_over = 0;
    drop_interval = 500;

    spawn_piece(&cur,    new_piece_type());
    spawn_piece(&next_p, new_piece_type());

    LARGE_INTEGER freq, last_drop, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&last_drop);

    while (running) {
        handle_input();

        QueryPerformanceCounter(&now);
        long elapsed_ms = (long)((now.QuadPart - last_drop.QuadPart) * 1000 / freq.QuadPart);

        if (elapsed_ms >= drop_interval) {
            if (!collides(&cur, 0, 1, 0)) {
                cur.y++;
            } else {
                lock_piece(&cur);
                int cl = clear_lines();
                if (cl) {
                    static const int pts[] = {0,100,300,500,800};
                    score += pts[cl] * level;
                    lines += cl;
                    level = lines / 10 + 1;
                    drop_interval = 500 - (level - 1) * 40;
                    if (drop_interval < 80) drop_interval = 80;
                }
                cur = next_p;
                spawn_piece(&next_p, new_piece_type());
                if (collides(&cur, 0, 0, 0)) { game_over = 1; running = 0; }
            }
            QueryPerformanceCounter(&last_drop);
        }

        draw_board();
        Sleep(16);  /* ~60 FPS render */
    }

    show_cursor();
    clear_screen();
    if (game_over) printf(CLR_RED "GAME OVER" CLR_RESET);
    printf(" — Score: %d  Lines: %d  Level: %d\n", score, lines, level);
    return 0;
}

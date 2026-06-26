/*
 * Breakout — SDL2 Graphical Game
 * Paddle: Left/Right arrow keys. Q or Esc to quit.
 * Clear all bricks to win. Lose when ball falls below paddle.
 *
 * Compile: see build.bat  |  SDL2.dll must be in the same folder.
 */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define W          800
#define H          600
#define PADDLE_W   120
#define PADDLE_H    12
#define BALL_R       8
#define BRICK_COLS  10
#define BRICK_ROWS   6
#define BRICK_W     72
#define BRICK_H     24
#define BRICK_PAD    4
#define BRICK_OFF_X 16
#define BRICK_OFF_Y 60

typedef struct { float x, y, vx, vy; int active; } Ball;
typedef struct { float x; } Paddle;
typedef struct { int alive; Uint8 r, g, b; } Brick;

static Brick bricks[BRICK_ROWS][BRICK_COLS];
static Ball  ball;
static Paddle pad;
static int   score, lives, won, lost;

static Uint8 ROW_COLORS[BRICK_ROWS][3] = {
    {255,50,50},{255,150,50},{255,220,50},{50,220,50},{50,150,255},{180,50,255}
};

static void init_bricks(void) {
    for (int r=0;r<BRICK_ROWS;r++) for(int c=0;c<BRICK_COLS;c++) {
        bricks[r][c].alive=1;
        bricks[r][c].r=ROW_COLORS[r][0];
        bricks[r][c].g=ROW_COLORS[r][1];
        bricks[r][c].b=ROW_COLORS[r][2];
    }
}

static void init_game(void) {
    pad.x = W/2.0f - PADDLE_W/2.0f;
    ball.x = W/2.0f; ball.y = H - 100.0f;
    ball.vx = 260.0f; ball.vy = -320.0f; ball.active = 1;
    score = 0; lives = 3; won = 0; lost = 0;
    init_bricks();
}

static void draw_rect_f(SDL_Renderer *ren, float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(ren, r, g, b, 255);
    SDL_Rect rect = {(int)x,(int)y,(int)w,(int)h};
    SDL_RenderFillRect(ren, &rect);
}

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window   *win = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    srand(1234);
    init_game();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    Uint32 prev = SDL_GetTicks();
    int running = 1;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) running = 0;
                if (e.key.keysym.sym == SDLK_r && (won||lost)) { init_game(); }
            }
        }

        Uint32 now = SDL_GetTicks();
        float  dt  = (now - prev) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        prev = now;

        if (!won && !lost) {
            /* Paddle movement */
            float pad_spd = 520.0f;
            if (keys[SDL_SCANCODE_LEFT]  || keys[SDL_SCANCODE_A]) pad.x -= pad_spd * dt;
            if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) pad.x += pad_spd * dt;
            if (pad.x < 0) pad.x = 0;
            if (pad.x + PADDLE_W > W) pad.x = W - PADDLE_W;

            /* Ball movement */
            ball.x += ball.vx * dt;
            ball.y += ball.vy * dt;

            /* Wall bounces */
            if (ball.x - BALL_R < 0)  { ball.x = BALL_R;    ball.vx =  fabsf(ball.vx); }
            if (ball.x + BALL_R > W)  { ball.x = W-BALL_R;  ball.vx = -fabsf(ball.vx); }
            if (ball.y - BALL_R < 0)  { ball.y = BALL_R;    ball.vy =  fabsf(ball.vy); }

            /* Paddle collision */
            if (ball.vy > 0 && ball.y + BALL_R >= H - 40 - PADDLE_H &&
                ball.x >= pad.x && ball.x <= pad.x + PADDLE_W) {
                ball.vy = -fabsf(ball.vy);
                float rel = (ball.x - (pad.x + PADDLE_W/2.0f)) / (PADDLE_W/2.0f);
                ball.vx = rel * 400.0f;
                ball.y  = H - 40 - PADDLE_H - BALL_R;
            }

            /* Lost ball */
            if (ball.y - BALL_R > H) {
                lives--;
                if (lives <= 0) { lost = 1; }
                else {
                    ball.x = W/2.0f; ball.y = H - 100.0f;
                    ball.vx = 260.0f * (rand()%2?1:-1); ball.vy = -320.0f;
                }
            }

            /* Brick collisions */
            int bricks_left = 0;
            for (int r=0;r<BRICK_ROWS;r++) for(int c=0;c<BRICK_COLS;c++) {
                if (!bricks[r][c].alive) continue;
                bricks_left++;
                float bx = BRICK_OFF_X + c*(BRICK_W+BRICK_PAD);
                float by = BRICK_OFF_Y + r*(BRICK_H+BRICK_PAD);
                if (ball.x+BALL_R > bx && ball.x-BALL_R < bx+BRICK_W &&
                    ball.y+BALL_R > by && ball.y-BALL_R < by+BRICK_H) {
                    bricks[r][c].alive = 0;
                    score += (BRICK_ROWS - r) * 10;
                    bricks_left--;
                    /* Determine which face was hit */
                    float ox = (ball.x < bx+BRICK_W/2) ? (bx - ball.x - BALL_R) : (ball.x - BALL_R - (bx+BRICK_W));
                    float oy = (ball.y < by+BRICK_H/2) ? (by - ball.y - BALL_R) : (ball.y - BALL_R - (by+BRICK_H));
                    if (fabsf(ox) < fabsf(oy)) ball.vx = -ball.vx;
                    else                        ball.vy = -ball.vy;
                }
            }
            if (bricks_left == 0) won = 1;
        }

        /* Render */
        SDL_SetRenderDrawColor(ren, 15, 15, 25, 255);
        SDL_RenderClear(ren);

        /* Bricks */
        for (int r=0;r<BRICK_ROWS;r++) for(int c=0;c<BRICK_COLS;c++) {
            if (!bricks[r][c].alive) continue;
            float bx = BRICK_OFF_X + c*(BRICK_W+BRICK_PAD);
            float by = BRICK_OFF_Y + r*(BRICK_H+BRICK_PAD);
            draw_rect_f(ren, bx, by, BRICK_W, BRICK_H, bricks[r][c].r, bricks[r][c].g, bricks[r][c].b);
        }
        /* Paddle */
        draw_rect_f(ren, pad.x, H-40-PADDLE_H, PADDLE_W, PADDLE_H, 200,200,255);
        /* Ball */
        draw_rect_f(ren, ball.x-BALL_R, ball.y-BALL_R, BALL_R*2, BALL_R*2, 255,255,255);

        /* Overlay messages */
        if (won || lost) {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
            SDL_Rect overlay = {W/2-150, H/2-40, 300, 80};
            SDL_RenderFillRect(ren, &overlay);
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("Final score: %d  Lives: %d  %s\n", score, lives, won?"YOU WIN!":lost?"GAME OVER":"");
    return 0;
}

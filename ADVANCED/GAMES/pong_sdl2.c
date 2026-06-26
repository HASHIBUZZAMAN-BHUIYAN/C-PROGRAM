/*
 * Pong — SDL2 Graphical Game
 * Player: W/S keys (left paddle). AI controls right paddle.
 * First to 7 points wins.
 *
 * Compile: see build.bat
 * Requires: SDL2.dll in same folder as .exe (copy from SDL2/x86_64-w64-mingw32/bin/)
 */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define PADDLE_W  12
#define PADDLE_H  90
#define BALL_SIZE  12
#define WIN_SCORE   7

typedef struct { float x, y, vx, vy; } Ball;
typedef struct { float x, y, speed;  } Paddle;

static void reset_ball(Ball *b, int serve_right) {
    b->x  = SCREEN_W / 2.0f;
    b->y  = SCREEN_H / 2.0f;
    b->vx = serve_right ? 300.0f : -300.0f;
    b->vy = (rand() % 2 ? 1 : -1) * (float)(150 + rand() % 100);
}

static void draw_rect(SDL_Renderer *r, int x, int y, int w, int h, Uint8 red, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(r, red, g, b, 255);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(r, &rect);
}

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window   *win = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Paddle player = { 20, SCREEN_H/2.0f - PADDLE_H/2.0f, 400 };
    Paddle ai     = { SCREEN_W - 20 - PADDLE_W, SCREEN_H/2.0f - PADDLE_H/2.0f, 280 };
    Ball   ball;
    int score_p = 0, score_ai = 0;
    srand(42);
    reset_ball(&ball, 1);

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    Uint32 prev = SDL_GetTicks();
    int running = 1;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) running = 0;
        }

        Uint32 now = SDL_GetTicks();
        float  dt  = (now - prev) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        prev = now;

        /* Player input */
        if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])   player.y -= player.speed * dt;
        if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) player.y += player.speed * dt;
        if (player.y < 0)                player.y = 0;
        if (player.y + PADDLE_H > SCREEN_H) player.y = SCREEN_H - PADDLE_H;

        /* Simple AI: track ball center */
        float ai_center = ai.y + PADDLE_H / 2.0f;
        if (ai_center < ball.y - 5) ai.y += ai.speed * dt;
        if (ai_center > ball.y + 5) ai.y -= ai.speed * dt;
        if (ai.y < 0)               ai.y = 0;
        if (ai.y + PADDLE_H > SCREEN_H) ai.y = SCREEN_H - PADDLE_H;

        /* Ball movement */
        ball.x += ball.vx * dt;
        ball.y += ball.vy * dt;

        /* Top/bottom bounce */
        if (ball.y <= 0)                  { ball.y = 0;                  ball.vy = fabsf(ball.vy); }
        if (ball.y + BALL_SIZE >= SCREEN_H) { ball.y = SCREEN_H-BALL_SIZE; ball.vy = -fabsf(ball.vy); }

        /* Paddle collisions */
        SDL_Rect br = {(int)ball.x, (int)ball.y, BALL_SIZE, BALL_SIZE};
        SDL_Rect pr = {(int)player.x, (int)player.y, PADDLE_W, PADDLE_H};
        SDL_Rect ar = {(int)ai.x,     (int)ai.y,     PADDLE_W, PADDLE_H};

        if (SDL_HasIntersection(&br, &pr) && ball.vx < 0) {
            ball.vx = fabsf(ball.vx) * 1.05f;
            float rel = (ball.y + BALL_SIZE/2.0f - (player.y + PADDLE_H/2.0f)) / (PADDLE_H/2.0f);
            ball.vy   = rel * 350.0f;
        }
        if (SDL_HasIntersection(&br, &ar) && ball.vx > 0) {
            ball.vx = -fabsf(ball.vx) * 1.05f;
            float rel = (ball.y + BALL_SIZE/2.0f - (ai.y + PADDLE_H/2.0f)) / (PADDLE_H/2.0f);
            ball.vy   = rel * 350.0f;
        }
        /* Clamp speed */
        if (fabsf(ball.vx) > 700) ball.vx = (ball.vx > 0 ? 1 : -1) * 700.0f;

        /* Scoring */
        if (ball.x < 0)          { score_ai++; reset_ball(&ball, 1);  }
        if (ball.x > SCREEN_W)   { score_p++;  reset_ball(&ball, 0);  }
        if (score_p >= WIN_SCORE || score_ai >= WIN_SCORE) { SDL_Delay(1500); running = 0; }

        /* Render */
        SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
        SDL_RenderClear(ren);

        /* Centre line */
        SDL_SetRenderDrawColor(ren, 60, 60, 60, 255);
        for (int y = 0; y < SCREEN_H; y += 20) {
            SDL_RenderDrawLine(ren, SCREEN_W/2, y, SCREEN_W/2, y+10);
        }

        draw_rect(ren, (int)player.x, (int)player.y, PADDLE_W, PADDLE_H, 200, 200, 255);
        draw_rect(ren, (int)ai.x,     (int)ai.y,     PADDLE_W, PADDLE_H, 255, 150, 150);
        draw_rect(ren, (int)ball.x,   (int)ball.y,   BALL_SIZE, BALL_SIZE, 255, 255, 255);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("Final score — Player: %d  AI: %d\n", score_p, score_ai);
    return 0;
}

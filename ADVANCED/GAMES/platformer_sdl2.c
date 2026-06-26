/*
 * Simple 2D Platformer — SDL2
 * Player is a colored rectangle (no sprite art needed).
 * Arrow keys / WASD to move. Space or W/Up to jump.
 * Reach the gold goal rectangle to win.
 *
 * Compile: see build.bat  |  SDL2.dll must be in the same folder.
 */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define W      800
#define H      500
#define TILE   40
#define GRAV  1200.0f

typedef struct { float x, y, vx, vy; int on_ground; } Player;
typedef struct { int x, y, w, h; } Rect;

#define MAX_PLAT 20
static Rect platforms[MAX_PLAT];
static int  nplats = 0;

static Rect goal;
static Player player;
static int won = 0;

static void add_plat(int x, int y, int w, int h) {
    if (nplats < MAX_PLAT) platforms[nplats++] = (Rect){x, y, w, h};
}

static void init_level(void) {
    nplats = 0;
    /* Ground */
    add_plat(0, H-TILE, W, TILE);
    /* Platforms */
    add_plat(100, H-120, 120, TILE);
    add_plat(280, H-190, 100, TILE);
    add_plat(420, H-260, 120, TILE);
    add_plat(580, H-200, 80,  TILE);
    add_plat(680, H-300, 100, TILE);
    add_plat(50,  H-320, 90,  TILE);
    add_plat(200, H-370, 110, TILE);
    add_plat(380, H-430, 140, TILE);
    /* Pit (no platform at x=320..410 ground level — keep it sparse) */

    goal = (Rect){730, H-340-30, 30, 30};

    player.x = 40; player.y = H - TILE - 36;
    player.vx = 0; player.vy = 0; player.on_ground = 0;
    won = 0;
}

static int rects_overlap(float ax, float ay, float aw, float ah,
                          float bx, float by, float bw, float bh) {
    return ax < bx+bw && ax+aw > bx && ay < by+bh && ay+ah > by;
}

static void draw_rect_rgb(SDL_Renderer *ren, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(ren, r, g, b, 255);
    SDL_Rect rc = {x, y, w, h};
    SDL_RenderFillRect(ren, &rc);
}

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window   *win = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    init_level();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    Uint32 prev = SDL_GetTicks();
    int running = 1;

#define PLAYER_W 24
#define PLAYER_H 36

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) running = 0;
                if (e.key.keysym.sym == SDLK_r) init_level();
                /* Jump */
                if ((e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_w ||
                     e.key.keysym.sym == SDLK_UP) && player.on_ground) {
                    player.vy  = -600.0f;
                    player.on_ground = 0;
                }
            }
        }

        Uint32 now = SDL_GetTicks();
        float  dt  = (now - prev) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        prev = now;

        if (!won) {
            /* Horizontal movement */
            float spd = 260.0f;
            player.vx = 0;
            if (keys[SDL_SCANCODE_LEFT]  || keys[SDL_SCANCODE_A]) player.vx = -spd;
            if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) player.vx =  spd;

            /* Gravity */
            player.vy += GRAV * dt;

            /* Move X */
            player.x += player.vx * dt;
            if (player.x < 0)             player.x = 0;
            if (player.x + PLAYER_W > W)  player.x = W - PLAYER_W;

            /* Move Y */
            player.y += player.vy * dt;
            player.on_ground = 0;

            /* Platform collisions */
            for (int i = 0; i < nplats; i++) {
                Rect *p = &platforms[i];
                if (rects_overlap(player.x, player.y, PLAYER_W, PLAYER_H,
                                  p->x, p->y, p->w, p->h)) {
                    /* Resolve from below (landing) */
                    if (player.vy > 0 && player.y + PLAYER_H - player.vy*dt <= p->y + 2) {
                        player.y = p->y - PLAYER_H;
                        player.vy = 0;
                        player.on_ground = 1;
                    } else if (player.vy < 0) {
                        player.y = p->y + p->h;
                        player.vy = 0;
                    }
                }
            }

            /* Fall below screen = respawn */
            if (player.y > H + 50) { player.x=40; player.y=H-TILE-PLAYER_H; player.vy=0; }

            /* Goal check */
            if (rects_overlap(player.x, player.y, PLAYER_W, PLAYER_H, goal.x, goal.y, goal.w, goal.h))
                won = 1;
        }

        /* Render */
        SDL_SetRenderDrawColor(ren, 40, 50, 80, 255);
        SDL_RenderClear(ren);

        /* Platforms */
        for (int i = 0; i < nplats; i++)
            draw_rect_rgb(ren, platforms[i].x, platforms[i].y, platforms[i].w, platforms[i].h, 120, 100, 60);

        /* Goal */
        draw_rect_rgb(ren, goal.x, goal.y, goal.w, goal.h, 255, 220, 50);

        /* Player */
        draw_rect_rgb(ren, (int)player.x, (int)player.y, PLAYER_W, PLAYER_H, 100, 200, 255);

        /* Win overlay */
        if (won) {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 160);
            SDL_Rect ov = {W/2-150, H/2-40, 300, 80};
            SDL_RenderFillRect(ren, &ov);
            SDL_SetRenderDrawColor(ren, 255, 220, 50, 255);
            SDL_Rect star = {W/2-10, H/2-10, 20, 20};
            SDL_RenderFillRect(ren, &star);
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("%s\n", won ? "You reached the goal! Well done!" : "Thanks for playing!");
    return 0;
}

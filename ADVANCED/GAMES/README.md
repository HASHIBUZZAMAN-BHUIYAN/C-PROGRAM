# ADVANCED/GAMES

## Terminal Games (no dependencies — just gcc)

| Game | Controls | Description |
|------|----------|-------------|
| `snake_terminal.c` | WASD / arrows, Q=quit | Classic snake with ANSI color |
| `tetris_terminal.c` | W=rotate, A/D=move, S=drop, Space=hard drop, Q=quit | Full Tetris with score/levels |

Build: `gcc snake_terminal.c -o snake_terminal.exe`

## SDL2 Graphical Games (requires SDL2.dll in same folder)

SDL2.dll is already copied here. For fresh builds, see `SDL2_SETUP.md` at the repo root.

| Game | Controls | Description |
|------|----------|-------------|
| `pong_sdl2.c` | W/S or Up/Down (player), AI opponent | Classic Pong, 7-point win |
| `breakout_sdl2.c` | Left/Right or A/D, R=restart | Break all bricks, 3 lives |
| `platformer_sdl2.c` | A/D=move, Space/W/Up=jump, R=reset | 2D platformer, reach the gold goal |

Build: see `build.bat`

## Note on SDL2 player/sprite visuals
The platformer uses colored rectangles as the player (no external sprite art).
This is intentional and clearly labeled — the physics and collision logic are complete.

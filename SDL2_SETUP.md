# SDL2 Setup Guide

## What's Installed
- **SDL2 version**: 2.32.8 (downloaded from github.com/libsdl-org/SDL releases)
- **Location**: `C:\Users\zen\Documents\GitHub\C-PROGRAM\SDL2\SDL2-2.32.8\x86_64-w64-mingw32`
- **SDL2.dll**: Already copied into `ADVANCED\GAMES\` for immediate use

## Directory Structure
```
SDL2\SDL2-2.32.8\x86_64-w64-mingw32\
+-- include\SDL2\    <- header files (#include <SDL2/SDL.h>)
+-- lib\             <- libSDL2.a, libSDL2main.a
+-- bin\SDL2.dll     <- runtime DLL (copy next to your .exe)
```

## Exact Compile Command
```bat
gcc mygame.c -o mygame.exe ^
    -I"C:\Users\zen\Documents\GitHub\C-PROGRAM\SDL2\SDL2-2.32.8\x86_64-w64-mingw32\include" ^
    -L"C:\Users\zen\Documents\GitHub\C-PROGRAM\SDL2\SDL2-2.32.8\x86_64-w64-mingw32\lib" ^
    -lmingw32 -lSDL2main -lSDL2 -mwindows -lm
```

## Key Points
1. **Link order matters**: -lmingw32 -lSDL2main -lSDL2 in that order.
2. **SDL2.dll must be next to your .exe** — copy it from SDL2\...\bin\SDL2.dll.
3. **Use #define SDL_MAIN_HANDLED** at the top of your .c file (before #include <SDL2/SDL.h>)
   OR ensure your main() has the signature int main(int argc, char *argv[]).
4. **-mwindows** suppresses the console window. Remove it during debugging to see printf output.

## Quick Test
Compile and run the included pong game:
```bat
cd ADVANCED\GAMES
build.bat
pong_sdl2.exe
```

## Installing SDL2_mixer (sound) — Optional
Not yet installed. To add sound support:
1. Download SDL2_mixer-devel-X.X.X-mingw.tar.gz from the SDL2_mixer releases page.
2. Extract alongside SDL2, copy the SDL2_mixer.dll next to your .exe.
3. Add -lSDL2_mixer to the compile command.

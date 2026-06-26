@echo off
SET GCC=C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe
SET SDL_INC=C:\Users\zen\Documents\GitHub\C-PROGRAM\SDL2\SDL2-2.32.8\x86_64-w64-mingw32\include
SET SDL_LIB=C:\Users\zen\Documents\GitHub\C-PROGRAM\SDL2\SDL2-2.32.8\x86_64-w64-mingw32\lib
echo Building GAMES...
%GCC% snake_terminal.c -o snake_terminal.exe -Wall -std=c11
%GCC% tetris_terminal.c -o tetris_terminal.exe -Wall -std=c11
%GCC% pong_sdl2.c -o pong_sdl2.exe -I"%SDL_INC%" -L"%SDL_LIB%" -lmingw32 -lSDL2main -lSDL2 -mwindows -lm
%GCC% breakout_sdl2.c -o breakout_sdl2.exe -I"%SDL_INC%" -L"%SDL_LIB%" -lmingw32 -lSDL2main -lSDL2 -mwindows -lm
%GCC% platformer_sdl2.c -o platformer_sdl2.exe -I"%SDL_INC%" -L"%SDL_LIB%" -lmingw32 -lSDL2main -lSDL2 -mwindows -lm
echo Done!


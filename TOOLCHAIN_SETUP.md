# Toolchain Setup

## Installed Toolchain
- **Compiler**: GCC 16.1.0 (WinLibs POSIX threads, UCRT runtime)
- **Package**: BrechtSanders.WinLibs.POSIX.UCRT
- **Install method**: winget install BrechtSanders.WinLibs.POSIX.UCRT
- **Location**: `C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin`

## Verify Installation
Open a new PowerShell or Command Prompt (not the one where you installed):
```
gcc --version
```
Expected output: gcc.exe (MinGW-W64 x86_64-ucrt-posix-seh, built by Brecht Sanders, r2) 16.1.0

If gcc is not found, open Environment Variables and confirm this is in your PATH:
`C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin`

## Compile + Run a Plain C File
```bat
gcc myfile.c -o myfile.exe -Wall -std=c11
myfile.exe
```
With math library (when using #include <math.h>):
```bat
gcc myfile.c -o myfile.exe -Wall -std=c11 -lm
myfile.exe
```
With multiple source files:
```bat
gcc main.c utils.c -o program.exe -Wall -std=c11
```

## Compile + Run an SDL2 File
See **SDL2_SETUP.md** for the full SDL2 compile command.
Short version:
```bat
gcc mygame.c -o mygame.exe ^
    -I"C:\Users\zen\Documents\GitHub\C-PROGRAM\SDL2\SDL2-2.32.8\x86_64-w64-mingw32\include" ^
    -L"C:\Users\zen\Documents\GitHub\C-PROGRAM\SDL2\SDL2-2.32.8\x86_64-w64-mingw32\lib" ^
    -lmingw32 -lSDL2main -lSDL2 -mwindows -lm
```
SDL2.dll must be in the same folder as the .exe.

## Using build.bat
Every project folder has a uild.bat with the correct compile command pre-filled.
Just run:
```bat
cd BEGINNER\day01
build.bat
lesson.exe
```

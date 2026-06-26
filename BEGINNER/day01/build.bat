@echo off
SET GCC=C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe
echo Compiling Day 01...
%GCC% lesson.c      -o lesson.exe      -Wall -Wextra -std=c11
%GCC% exercises.c   -o exercises.exe   -Wall -Wextra -std=c11
%GCC% solutions.c   -o solutions.exe   -Wall -Wextra -std=c11
%GCC% mini_project.c -o mini_project.exe -Wall -Wextra -std=c11
echo Done! Run: lesson.exe / exercises.exe / solutions.exe / mini_project.exe

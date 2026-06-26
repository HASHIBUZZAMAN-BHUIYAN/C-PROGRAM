@echo off
SET GCC=C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe
echo Compiling Day 13...
%GCC% lesson.c mathutils.c -o lesson.exe -Wall -std=c11
%GCC% exercises.c -o exercises.exe -Wall -std=c11
%GCC% solutions.c -o solutions.exe -Wall -std=c11
%GCC% mini_project.c mathutils.c -o mini_project.exe -Wall -std=c11 -lm
echo Done!


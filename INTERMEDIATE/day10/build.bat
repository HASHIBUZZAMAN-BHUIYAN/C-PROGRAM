@echo off
SET GCC=C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe
echo Compiling Int Day 10 Capstone...
%GCC% lesson.c -o capstone.exe -Wall -std=c11
%GCC% exercises.c -o exercises.exe -Wall -std=c11
echo Done! Run: capstone.exe


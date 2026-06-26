@echo off
SET GCC=C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe
echo Building ROBOTICS projects...
%GCC% pid_controller.c -o pid_controller.exe -Wall -std=c11 -lm
%GCC% kinematics_2d_arm.c -o kinematics_2d_arm.exe -Wall -std=c11 -lm
%GCC% pathfinding_grid_c.c -o pathfinding_grid_c.exe -Wall -std=c11
%GCC% sensor_fusion_simple.c -o sensor_fusion_simple.exe -Wall -std=c11 -lm
%GCC% realtime_scheduler_sim.c -o realtime_scheduler_sim.exe -Wall -std=c11
echo Done!


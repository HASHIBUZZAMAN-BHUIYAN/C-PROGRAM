@echo off
SET GCC=C:\Users\zen\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\gcc.exe
echo Building EMBEDDED projects...
%GCC% blink_led_sim.c -o blink_led_sim.exe -Wall -std=c11
%GCC% button_debounce_sim.c -o button_debounce_sim.exe -Wall -std=c11
%GCC% simple_rtos_scheduler.c -o simple_rtos_scheduler.exe -Wall -std=c11
%GCC% uart_protocol_sim.c -o uart_protocol_sim.exe -Wall -std=c11
%GCC% interrupt_simulation.c -o interrupt_simulation.exe -Wall -std=c11
echo Done!


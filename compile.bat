@echo off
chcp 437
g++ main.cpp -L./lib -lpdcurses -lws2_32 -I./include -o uno_win32 > log.txt 2>&1
type log.txt
pause
uno_win32
cls
echo [ Program Finished ]
pause
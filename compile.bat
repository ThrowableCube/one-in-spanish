@echo off
chcp 437
g++ main.cpp -lpdcurses -lws2_32 -o uno_win32 > log.txt 2>&1
type log.txt
pause
uno_win32
cls
echo [ Program Finished ]
pause
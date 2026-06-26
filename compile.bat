@echo off
chcp 437
g++ unogame_win32.cpp -L./lib -lpdcurses -I./include -o uno_win32 > log.txt 2>&1
type log.txt
pause
uno_win32
cls
echo [ Program Finished ]
pause

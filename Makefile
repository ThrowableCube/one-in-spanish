# HELP ME PLEASE
# I DESPERATELY NEED CONTRIBUTERS
# I DONT EVEN KNOW IF THIS WORKS
ifeq ($(OS),Windows_NT)
	LIBS = -lpdcurses -lws2_32
    TARGET = uno_win32.exe
else
    LIBS = -lncurses
    TARGET = uno_linux
endif

main: main.cpp
	g++ main.cpp -L./lib -I./include $(LIBS) -o $(TARGET)
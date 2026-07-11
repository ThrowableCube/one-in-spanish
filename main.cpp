#include "unocards.hpp"
#include "cursealias.hpp"

int main() {
    // no i have to sleep
    
    int ch = 0;
    srand(time(0));
    std::random_device rd;
    std::mt19937 g(rd());

    // go commit die
    // ur so mean waaaaa
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);

    std::vector<uno::card> thing = {};

    // somebodys gonna get confused by this so...
    for (int x = 0 ; x < 4 ; x++) { // this for cycles color
        thing.push_back({0, static_cast<uno::colors>(x), uno::types::none});
        for (int y = 0 ; y < 9 ; y++) { // this for generates number cards above 0
            for (int z = 0 ; z < 2 ; z++) { // this generates the card 2 times (TWO TIMES FROM FORSAKEN NO WAY)
                thing.push_back({(y + 1), static_cast<uno::colors>(x), uno::types::none});
            }
        }
    }
    // end of hell code

    std::string colorArray[4] = { // do we need this?
        // oh wait i dont have contributers no ones gonna answer this.
        "Red",
        "Blue",
        "Green",
        "Yellow"
    };

    uno::card currentCard; // default card.
    currentCard.number = 2;
    currentCard.color = uno::colors::green;
    currentCard.type = uno::types::none;

    uno::card lastCard = {3, uno::colors::green, uno::types::none};

    int selection = 0;
    int displayedLine = 0;
    int displayOffset = 0;
    bool notOOB = 0;
    bool alreadyDidIt = 0;
    bool notClose = 1;
    // im glad modern compilers removed the need for initialized values having to go on top of int main, makes it way easier to write C++

    // start of pdcurses
    // OUUU SHI VS CODE RECOGNIZES IT
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, 1);
    nodelay(stdscr, 1);

    WINDOW* cardWindow = newwin(14,14,1,1);
    box(cardWindow,ACS_VLINE,ACS_HLINE);

    WINDOW* debugWindow = newwin(14,34,1,16);
    box(debugWindow,ACS_VLINE,ACS_HLINE);

    //////////////////////////////////////////////////////////////////////////

    wattron(debugWindow, A_REVERSE);
    mvwprintw(debugWindow, 0, 2, " Debug ");
    wattroff(debugWindow, A_REVERSE);

    wattron(cardWindow, A_REVERSE);
    mvwprintw(cardWindow, 0, 2, " Hand ");
    wattroff(cardWindow, A_REVERSE);

    while (notClose) {
        refresh();
        for (int i = 0 ; i < 10 ; i++) {
            if ((i + displayOffset) >= thing.size()) {
                mvwprintw(cardWindow, (11 - i), 1, "  ");
            } else {
                if (i == selection) {
                    wattron(cardWindow, A_REVERSE);
                }
                mvwprintw(cardWindow, (11 - i), 1, printTLCard(thing.at((i + displayOffset))).c_str());
                wattroff(cardWindow, A_REVERSE);
            }
        }
        wrefresh(debugWindow);
        wrefresh(cardWindow);
        mvwprintw(debugWindow, 1, 1, "                      ");
	    mvwprintw(debugWindow, 2, 1, "                      ");
        mvwprintw(debugWindow, 1, 1, "Selection Value: %d", selection);
	    mvwprintw(debugWindow, 2, 1, "Line Offset: %d", displayOffset);

        mvwprintw(cardWindow, 12, 1, "PageDown");
        mvwprintw(cardWindow, 1, 1, "PageUp");
        ch = getch();
        switch (ch) {
            case KEY_NPAGE: // ok sahai punyaon
                displayOffset--;
                Sblink(cardWindow, 12, 1, "PageDown");
                break;
            case KEY_PPAGE:
                if (displayOffset < thing.size()) {
                    displayOffset++;
                    Sblink(cardWindow, 1, 1, "PageUp");
                }
                break;
            case KEY_DOWN:
                selection--;
                break;
            case KEY_UP:
                selection++;
                break;
            case '\n':
                notClose = 0;
                break;
        }
        mvwprintw(debugWindow, 12, 1, "                              "); // didnt wanna redraw the border
        if (selection > 9) {
            selection = 0;
        } else if (selection < 0) {
            selection = 9;
        }

        if (displayOffset < 0) {
            displayOffset = 0;
        }
    }

    endwin();
    printf("hi");
    return 0;
}
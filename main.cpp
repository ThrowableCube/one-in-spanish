#include "unocards.hpp"
#include "cursealias.hpp"

int main() {
    int hmc = 0;
    srand(time(0));
    std::vector<uno::card> thing = {};

    printf("a number, preferably between 1 and 10: ");
    scanf("%d", &hmc);

    for (int i = 0 ; i < hmc ; i++) {
        thing.push_back({(rand() % 10), static_cast<uno::colors>(rand() % 4), uno::types::none});
    }

    std::string colorArray[4] = {
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

    // start of pdcurses
    // OUUU SHI VS CODE RECOGNIZES IT
    initscr();
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    nodelay(stdscr, 1);
    int ch = 0;

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
            if (i >= thing.size()) {
                mvwprintw(cardWindow, (11 - i), 1, "  ");
            } else {
                if (i == selection) {
                    wattron(cardWindow, A_REVERSE);
                }
                mvwprintw(cardWindow, (11 - i), 1, printTLCard(thing.at(i)).c_str());
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
                displayOffset++;
                Sblink(cardWindow, 1, 1, "PageUp");
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
    getch();
    printf("hi");
    return 0;
}
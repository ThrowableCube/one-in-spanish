#include "unocards.hpp"

int main() {
    srand(time(0));
    std::vector<uno::card> thing = {};

    for (int i = 0 ; i < 5 ; i++) {
        thing.push_back({(rand() % 10), static_cast<uno::colors>(rand() % 4), uno::types::none});
    }

    std::string colorArray[4] = {
        "Red",
        "Blue",
        "Green",
        "Yellow"
    };

    uno::card currentCard; // why can't you be like your brother??? look below you!
    currentCard.number = 2;
    currentCard.color = uno::colors::green;
    currentCard.type = uno::types::none;

    uno::card lastCard = {3, uno::colors::green, uno::types::none};

    int selection = 0;
    int displayedLine = 0;
    int displayOffset = 0;
    bool notOOB = 0;

    // start of pdcurses
    // OUUU SHI VS CODE RECOGNIZES IT
    initscr();
    noecho();
    keypad(stdscr, 1);
    curs_set(0);
    int ch = 0;

    WINDOW* cardWindow = newwin(14,14,1,1);
    box(cardWindow,ACS_VLINE,ACS_HLINE);
    while (1) {
        wattron(cardWindow, A_REVERSE);
        mvwprintw(cardWindow, 0, 2, " Hand ");
        wattroff(cardWindow, A_REVERSE);
        mvwprintw(cardWindow, 12, 1, "Prev");
        mvwprintw(cardWindow, 1, 1, "Next");
        refresh();
        wrefresh(cardWindow);
        ch = getch();
        switch (ch) {
            case KEY_NPAGE:
                wattron(cardWindow, A_REVERSE);
                displayOffset--;
                mvwprintw(cardWindow, 12, 1, "Prev");
                refresh();
                wrefresh(cardWindow);
                napms(50);
                wattroff(cardWindow, A_REVERSE);
                mvwprintw(cardWindow, 12, 1, "Prev");
                refresh();
                wrefresh(cardWindow);
                break;
            case KEY_PPAGE:
                wattron(cardWindow, A_REVERSE);
                displayOffset++;
                mvwprintw(cardWindow, 1, 1, "Next");
                refresh();
                wrefresh(cardWindow);
                napms(50);
                wattroff(cardWindow, A_REVERSE);
                mvwprintw(cardWindow, 1, 1, "Next");
                refresh();
                wrefresh(cardWindow);
                break;
            case KEY_ENTER:
                break;
                
        }
    }

    getch();

    endwin();
    return 0;
}
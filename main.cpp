#include "unocards.hpp"
#include "cursealias.hpp"

int main() {
    // here come the tornado of shit code

    // no i have to sleep
    // ... this is awkward i updated the wrong file and i got confused on why my code changes arent working.
    
    int ch = 0;
    srand(time(0));
    std::random_device rd;
    std::mt19937 g(rd());

    // go commit die
    // ur so mean waaaaa

    std::vector<uno::player> players = {};
    std::vector<uno::card> deck = {};
    std::vector<uno::card> pile = {};

    players.push_back({"noName", 0, {}}); // what the fuck?

    // somebodys gonna get confused by this so...
    for (int x = 0 ; x < 4 ; x++) { // this cycles color
        deck.push_back({0, static_cast<uno::colors>(x), uno::types::none});
        for (int z = 0 ; z < 2 ; z++) { // this generates the card 2 times
            for (int y = 0 ; y < 9 ; y++) { // this for generates number cards above 0
                deck.push_back({(y + 1), static_cast<uno::colors>(x), uno::types::none});
            }

            deck.push_back({42, static_cast<uno::colors>(x), uno::types::draw});
            deck.push_back({42, static_cast<uno::colors>(x), uno::types::reverse});
            deck.push_back({42, static_cast<uno::colors>(x), uno::types::skip});
        }
    }

    for (int i = 0 ; i < 4 ; i++) {
        deck.push_back({69, static_cast<uno::colors>(4), uno::types::wild});
        deck.push_back({69, static_cast<uno::colors>(4), uno::types::wilddraw});
    }

    // end of hell code

    std::shuffle(deck.begin(), deck.end(), g);

    std::string colorArray[4] = { // do we need this?
        // oh wait i dont have contributers no ones gonna answer this.
        "Red",
        "Blue",
        "Green",
        "Yellow"
    };

    uno::card lastCard = {3, uno::colors::green, uno::types::none};

    int selection = 0;
    int displayedLine = 0;
    int displayOffset = 0;
    int result = 0;
    int currentPlayer = 0;
    int threshold = 50;
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

    if (has_colors() == 0) {
        printw("Your terminal doesn't support color.");
        refresh();
    } else {
        start_color();
        use_default_colors();
    }

    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_MAGENTA, -1);

    WINDOW* cardWindow = newwin(14,14,1,1);

    WINDOW* pileWindow = newwin(4,49,16,1);

    WINDOW* playerWindow = newwin(14,34,1,16);

    //////////////////////////////////////////////////////////////////////////

    winTitle(playerWindow, " Player ");

    winTitle(cardWindow, " Hand ");

    winTitle(pileWindow, " Discard Pile ");

    while (notClose) {
        refresh();
        mvwprintw(playerWindow, 12, 1, "                                ");
        mvwprintw(playerWindow, 12, 1, printCardFN(deck.at(selection + displayOffset)).c_str());
        for (int i = 0 ; i < 10 ; i++) {
            if ((i + displayOffset) >= deck.size()) {
                mvwprintw(cardWindow, (11 - i), 1, "  ");
            } else {
                if (i == selection) {
                    wattron(cardWindow, A_REVERSE);
                }
                wattron(cardWindow, COLOR_PAIR(getCardColorAsANSI(deck.at(i + displayOffset))));
                mvwprintw(cardWindow, (11 - i), 1, printTLCard(deck.at((i + displayOffset))).c_str());
                wattroff(cardWindow, COLOR_PAIR(getCardColorAsANSI(deck.at(i + displayOffset))));
                wattroff(cardWindow, A_REVERSE);
            }
        }

        wrefresh(playerWindow);
        wrefresh(cardWindow);
        wrefresh(pileWindow);
        mvwprintw(playerWindow, 1, 1, "                      ");
	    mvwprintw(playerWindow, 2, 1, "                      ");
        mvwprintw(playerWindow, 1, 1, "Player %d", currentPlayer + 1);
	    mvwprintw(playerWindow, 2, 1, "Cards: %d", players.at(currentPlayer).hand.size());

        mvwprintw(cardWindow, 12, 1, "PageDown");
        mvwprintw(cardWindow, 1, 1, "PageUp");

        wattron(playerWindow, COLOR_PAIR(getCardColorAsANSI(lastCard)));
        wattroff(playerWindow, COLOR_PAIR(getCardColorAsANSI(lastCard)));

        ch = getch();
        switch (ch) {
            case KEY_NPAGE: // ok sahai punyaon
                displayOffset -= 5;
                Sblink(cardWindow, 12, 1, "PageDown");
                break;
            case KEY_PPAGE:
                if (displayOffset < deck.size()) {
                    displayOffset += 5;
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
                result = discardCard(deck.at(selection + displayOffset), lastCard, 1);
                if (result) {
                    mvwprintw(playerWindow, 11, 1, "                                ");
                    mvwprintw(playerWindow, 11, 1, "Discard Result: %d", result);
                    pile.push_back(deck.at(selection + displayOffset));
                    deck.erase(deck.begin() + selection + displayOffset);
                } else { 
                    mvwprintw(playerWindow, 11, 1, "You cannot play this card.");
                }
                break;
        }
        if (selection > 9) {
            selection = 9;
            displayOffset++;
        } else if (selection < 0) {
            selection = 0;
            displayOffset--;
        } else if (selection > deck.size() - 1) {
            selection = deck.size() - 1;
        }

        if (displayOffset < 0) {
            displayOffset = 0;
        } else if (displayOffset > deck.size() - 10) {
            displayOffset = deck.size() - 10;
        }
    }

    endwin();
    printf("List was emptied or some other function broke the loop.\n");
    return 0;
}
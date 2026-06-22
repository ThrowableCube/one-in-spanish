#include "ansi_bs.hpp"
#include "unocards.hpp"

int main() {
    srand(time(0));
    vtInit();
    printf("\n\n");
    clrscr();
    std::vector<uno::card> thing = {};

    int howMuchCards;

    scanf("%d", &howMuchCards); // for testing.

    for (int i = 0 ; i < howMuchCards ; i++) {
        thing.push_back({(rand() % 10), static_cast<uno::colors>(rand() % 4), uno::types::none});
    }

    std::string colorArray[4] = {
        "Red",
        "Blue",
        "Green",
        "Yellow"
    };
    int ch;
    int selection = 3;
    enum keyArrow { // This is only for windows
        UP_ARROW = 72,
        DOWN_ARROW = 80,
        LEFT_ARROW = 75,
        RIGHT_ARROW = 77
    };

    uno::card currentCard; // why can't you be like your brother??? look below you!
    currentCard.number = 2;
    currentCard.color = uno::colors::green;
    currentCard.type = uno::types::none;

    uno::card lastCard = {3, uno::colors::green, uno::types::none};

    currentCard.color = static_cast<uno::colors>(selection);

    selection = 0;
    int displayedLine = 0;
    int displayOffset = 0;
    bool notOOB = 0;

    while (1) {
        if (thing.size() <= 0) {
            break;
        }

        for (int lines = 0; lines < 12; lines++) { // HEY IT FUCKING WORKS OKAY!?
            displayedLine = lines;
            displayedLine += (displayOffset * 10);
            
            if ((displayedLine - 1) >= thing.size()) {
                notOOB = 0;
            } else {
                notOOB = 1;
            }

            if (selection == lines) {
                if (notOOB) {
                    setColor(getCardColorAsANSI(thing.at(displayedLine - 1)),1,1);
                } else {
                    setColor(7,1,1);
                }
                setColor(0,0,0);
            } else {
                if (notOOB) {
                    setColor(getCardColorAsANSI(thing.at(displayedLine - 1)),1,0);
                } else {
                    setColor(7,1,0);
                }
                setColor(0,0,1);
            }
            if (lines == 0 || lines == 11) {
                switch (lines) {
                    case 0:
                        printf("previous");
                        break;
                    case 11:
                        printf("next");
                        break;
                }
            } else {
                //
                if ((displayedLine - 1) >= thing.size()) {
                    printf("  ");
                } else {
                    printTLCard(thing.at(displayedLine - 1));
                }

            }
            printf("\n");
            setColor(0,0,1);
            setColor(7,1,0);
        }

        int flflfr = 0; // hey wait why did i name this flflfr?
        int maxpage = 0;
        int tries = 0;
        while (flflfr <= thing.size() && tries < 255) {
            flflfr += 10;
            maxpage++;
            tries++;
        }

        printf("page: %d/", displayOffset + 1);
        printf("%d\n", maxpage);
        std::cout << "how much cards you have: " << thing.size() << "\n";
        printf("last discarded card: ");
        setColor(getCardColorAsANSI(lastCard),1,0);
        printTLCard(lastCard);

        ch = getch();

        if (ch == 0 || ch == 224) {
            ch = getch();
            switch (ch) {
                case UP_ARROW:
                    selection--;
                    break;
                case DOWN_ARROW:
                    selection++;
                    break;
            }
        } else if (ch==13) {
            if (selection > 10 || selection < 1) {
                switch (selection) {
                    case 0:
                        if (displayOffset > 0) { // fyi this checks if you're going to negative page
                            displayOffset--;
                        } else {
                            setColor(6,0,0);
                            printf("\a");
                        }
                        break;
                    case 11:
                        if (displayOffset < (maxpage - 1)) { // same as above but for max page
                            displayOffset++;
                        } else {
                            setColor(6,0,0);
                            printf("\a");
                        }
                        break;
                }
            } else if (notOOB) {
                discardCard(thing.at(displayedLine - 1), lastCard, 1, 1); // currently broken asf
            } else {
                printf("\a");
            }
        }

        if (selection < 0) {
            selection = 0;
        } else if (selection > 11) {
            selection = 11;
        }
        clrscr();
    }

    printf("\n\n");
    printf("%d", selection);
}

#include <cstdlib>
#include <ctime>
#include <vector>
#include <curses.h>
#include <stdio.h>
#include <iostream>
#pragma once

class uno {
    public:
        enum class colors {
            red = 0,
            blue,
            green,
            yellow
        };
        enum class types {
            none = 0,
            wild,
            draw,
            block,
            reverse,
            wilddraw
        };

        struct card {
            int number;
            colors color;
            types type;
        };
};

std::string printTLCard(uno::card card) {
    std::string rs;
    std::vector<char> letterColor = {'R', 'B', 'G', 'Y'};
    rs = std::to_string(letterColor.at(static_cast<int>(card.color)));
    rs += std::to_string(card.number);
    return rs;
}

int getCardColorAsANSI(uno::card card) { // Better, but still revise if possible.
    switch (card.color) {
        case uno::colors::red:
            return 1;
            break;
        case uno::colors::blue:
            return 4;
            break;
        case uno::colors::green:
            return 2;
            break;
        case uno::colors::yellow:
            return 3;
            break;
    }
    return 7;
}

int discardCard(uno::card discardingCard, uno::card &lastCard, bool mutate = 0) { // might need a rewrite.
    // HOLY SHIT I REMOVED THE PRINT AND PAUSE CODE AND IT LOOKS INFINITELY SMALLER.
    if (discardingCard.color == lastCard.color || discardingCard.type == uno::type::wild) { // checks for matching color or wildcard
        return 2;
    } else if (discardingCard.number == lastCard.number) {
	if (mutate) { // mutate means that it's allowed to change a value
            lastCard.color = discardingCard.color;
	}
        return 1;
    }
    return 0; // if none of the ifs ran
}
#include <cstdlib>
#include <ctime>
#include <vector>
#include "include/curses.h"
#include "include/asio.hpp"
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
#pragma once

asio::io_context io;

// class asioAlias {
//     public:
//         void wait_async(int seconds) {
//             asio::steady_timer t(io, asio::chrono::seconds(seconds));
//         }
// };

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
            skip,
            wilddraw
        };

        struct card {
            int number;
            colors color;
            types type;
        };

        struct player {
            std::string name;
            bool skipped;
            std::vector<card> hand;
        };
};

std::string printTLCard(uno::card card) {
    std::string rs;
    std::vector<std::string> letterColor = {"R", "B", "G", "Y"};
    rs = letterColor.at(static_cast<int>(card.color));
    rs += std::to_string(card.number);
    return rs; // changed back to std string
}

int getCardColorAsANSI(uno::card card) { // Better, but still revise if possible.
    switch (card.color) {
        case uno::colors::red:
            return 1;
        case uno::colors::blue:
            return 2;
        case uno::colors::green:
            return 3;
        case uno::colors::yellow:
            return 4;
        default:
            return 5;
    }
}

int discardCard(uno::card discardingCard, uno::card &lastCard, bool mutate = 0) { // might need a rewrite.
    // HOLY SHIT I REMOVED THE PRINT AND PAUSE CODE AND IT LOOKS INFINITELY SMALLER.
    // Yeah about that...

    // handling special cards
    if (discardingCard.type == uno::types::wild) {
        return 2; // YES DO IT HERE NOT THERE // yes sir ;-;
    } else if (discardingCard.type == uno::types::wilddraw) {
        return 3;
    }
    
    // handling special colored cards
    else if (discardingCard.type == uno::types::draw && discardingCard.color == lastCard.color) {
        return 4;
    } else if (discardingCard.type == uno::types::reverse && discardingCard.color == lastCard.color) {
        return 5; // function here...
    } else if (discardingCard.type == uno::types::skip && discardingCard.color == lastCard.color) {
        return 6;
    }

    // handling normal cards
    else if (discardingCard.color == lastCard.color) { // checks for matching color or wildcard
        return 1; // if it's two open the color picker! :D // FUCK NO. // you're so mean :'(
    } else if (discardingCard.number == lastCard.number) {
        if (mutate) {
            lastCard.color = discardingCard.color;
	    }
        return 1;
    }
    return 0; // if none of the ifs ran
}


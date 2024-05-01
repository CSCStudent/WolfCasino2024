#pragma once
#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <string>
#include "Casino.h"

// Card class definition
namespace S02902743
{
    class Card {
    public:
        std::string rank;
        std::string suit;

        Card(const std::string& rank, const std::string& suit);

        int getValue() const;

        friend std::ostream& operator<<(std::ostream& os, const Card& card);
    };

    // Deck class definition
    class Deck {
    public:
        std::vector<Card> cards;

        Deck();

        void build();
        void shuffle();
        Card draw();
    };

    // Hand class definition
    class Hand {
    public:
        std::vector<Card> cards;

        void addCard(const Card& card);
        int getValue() const;

        friend std::ostream& operator<<(std::ostream& os, const Hand& hand);
    };

    // BlackjackGame class definition
    class BlackjackGame : public CSC2034::Casino{
    public:
        Deck deck ;
        Hand playerHand;
        Hand dealerHand;

        BlackjackGame();

        void dealInitialCards();
        void playerHit();
        void dealerHit();
        bool isPlayerBusted() const;
        bool isDealerBusted() const;
        bool doesPlayerWin() const;
        static BlackjackGame* makeGame();
        void start();

        
    };

#endif // BLACKJACK_H
}
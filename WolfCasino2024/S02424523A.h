//in solution
#pragma once
#ifndef BACCARAT_H
#define BACCARAT_H
#include "Casino.h"
#include "S02424523B.h"
#include "S02424523D.h"
#include <iostream>
#include <ctime>

using namespace std;

//defined namespace for project
namespace S02424523
{
    class Baccarat : public CSC2034::Casino
    {
    public:
        //Constructor
        Baccarat();

        static Baccarat* makeGame();

        //This plays the game
        void start();

    private:
        Deck deck;
        Hand playerHand;
        Hand bankerHand;
        long wallet;
        void playHand(Deck& deck, Hand& player, Hand& banker);
        void initialDeal(Deck& deck, Hand& player, Hand& banker);
        void deal(Deck& deck, Hand& hand);
        void printHands(Hand& player, Hand& banker);
        long betResult(long& wallet, int betType, long bet, int winner);
        long makeBet(long& wallet);
        int tableResult(Hand player, Hand banker);
    };
}

#endif
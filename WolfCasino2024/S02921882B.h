//
//  Yahtzee.h
//  WolfCasino2024_xcode
//
//  Created by Parker Ellmann on 4/25/24.
//

#ifndef Yahtzee_h
#define Yahtzee_h
#include <map>
#include "Casino.h"
#include "S02921882A.h"


namespace S02921882
{
    class Yahtzee : public CSC2034::Casino {
    public:
        static const int NUM_DICE = 5;
        Yahtzee();
        static Yahtzee* makeGame();
        void start();
    private:
        const int NUM_CATEGORIES = 13;
        const string CATEGORIES[13] = {"Aces", "Twos", "Threes", "Fours", "Fives", "Sixes", "3 of a Kind", "4 of a Kind", "Full House", "Sm. Straight", "Lg. Straight", "Chance", "YAHTZEE"};
        const string SCORECARD[18] = {"Aces", "Twos", "Threes", "Fours", "Fives", "Sixes", "UPPER BNS", "UPPER TOTAL", "3 of a Kind", "4 of a Kind", "Full House", "Sm. Straight", "Lg. Straight", "Chance", "YAHTZEE", "YAHTZEE BNS", "LOWER TOTAL", "GRAND TOTAL"};
        map<string, int> scores;
        
        void displayScore(S02921882::Dice&);
        string getCategory();
        int ofKindTest(Dice&, int);
        int maxOfKind(Dice&);
        bool isFullHouseTest(Dice&);
        bool jokerRules(Dice&);
        int straightTest(Dice&);
        int sumOfDice(Dice&);
        bool scoringNonYahtzee(Dice&, string);
        bool scoringYahtzee(Dice&);
        void showDice(Dice&);
        string validateYesNoInput();
    };
}

#endif /* Yahtzee_h */

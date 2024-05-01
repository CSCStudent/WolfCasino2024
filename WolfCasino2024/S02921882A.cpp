//  Dice.cpp

#include <cstdlib>
#include <iostream>
#include "S02921882A.h"


namespace S02921882 {
    // Creates Dice object with parameter as the number of dice. Max 100 dice
    Dice::Dice(int num) {
        numDice = num;
        for (int index = 0; index < numDice; index++) {
            dice[index] = 0;
        }
    }

    // Destructor
    Dice :: ~Dice() {
    }

    // Returns value of specified die
    int Dice::getValue(int dieNum) const {
        if (dieNum <= numDice)
            return dice[dieNum - 1];
        else {
            std::cout << "--Dice::getValue()-- # of die out of range" << std::endl;
            return -1;
        }
    }

    // Randomizes value of specified die
    void Dice::roll(int dieNum) {
        if (dieNum <= numDice)
            dice[dieNum - 1] = (rand() % 6) + 1;
        else
            std::cout << "--Dice::roll()-- # of die out of range" << std::endl;
    }
}

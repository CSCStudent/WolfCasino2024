// Dice.h

#ifndef Dice_h
#define Dice_h

#include <stdio.h>
#include <string>

namespace S02921882 {
    class Dice {
    private:
        int numDice;
        int dice[100];
    public:
        Dice(int);
        ~Dice();
        int getValue(int) const;
        void roll(int dieNum);
    };
}
#endif /* Dice_h */

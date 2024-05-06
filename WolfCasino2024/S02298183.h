#pragma once
#include <ctime>
#include "Casino.h"

namespace S02298183
{
    class SquidGame : public CSC2034::Casino
    {
    public:
        SquidGame();
        static SquidGame *makeGame();
        void start();

    private:
        void clearConsole();
        void printSquidward();
        void printSquidwardBackwards();
        void printDollar();
        int countWs(const std::string &input);
        void printProgress(int totalWs, int lengthOfLevel);
        int lengthOfLevel;
        int turnsRemaining;
        int backLuckMultiplier;
    };

}

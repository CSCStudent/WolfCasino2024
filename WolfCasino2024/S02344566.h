#pragma once
#include <ctime>
#include "Casino.h"

//defined namespace for project
namespace S02344566
{
    class RockPaperScissorsGame : public CSC2034::Casino
    {
    public:
        //Constructor
        RockPaperScissorsGame();

        static RockPaperScissorsGame* makeGame();

        //This plays the game
        void start();


    private:
        char playerPlay;

        //Selects the computer's play
        char computerSelect();

        //finds the winner
        int findWinner(char,char);
    };
} //end of namespace

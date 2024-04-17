#pragma once
#include <ctime>
#include "Casino.h"

//defined namespace for project
namespace CSC2034
{
    class TicTacToeGame : public Casino
    {
    public:
        //Constructor
        TicTacToeGame();

        static TicTacToeGame* makeGame();

        //This plays the game
        void start();

    private:
        void run();

        //This stores the board state
        char board[3][3];
    };
} //end of namespace

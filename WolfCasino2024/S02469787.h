#pragma once
#include <ctime>
#include "Casino.h"

//defined namespace for project
namespace CSC2034
{
    class S02469787 : public Casino
    {
    public:
        //Constructor
        S02469787();

        static S02469787* makeGame();

        //This plays the game
        void start();

        //prints game state
        void print( );

        bool playerMove( int& );
        //check if anyone has won
        bool checkWinner(  );

    private:
        //This stores the board state
        char board[3][3];
    };
} //end of namespace

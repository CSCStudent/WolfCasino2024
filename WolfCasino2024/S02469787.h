#pragma once
#include <ctime>
#include "Casino.h"

//defined namespace for project
namespace S02469787 {
    class TicTacToe : public CSC2034::Casino {
    public:
        //Constructor
        TicTacToe();

        static TicTacToe* makeGame();

        //This plays the game
        void start();

        //prints game state
        void print();

        bool playerMove(int&);
        //check if anyone has won
        bool checkWinner();

    private:
        //This stores the board state
        char board[3][3];
    };
} //end of namespace


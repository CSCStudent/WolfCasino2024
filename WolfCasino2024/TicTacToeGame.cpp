#include <iostream>
#include <ctime>
#include "TicTacToeGame.h"

//defined namespace for project
namespace CSC2034
{
    //Constructor
    TicTacToeGame::TicTacToeGame()
    {

    }

    TicTacToeGame* TicTacToeGame::makeGame() {
        return new TicTacToeGame;
    }

    //The game!
    void TicTacToeGame::start() {

    }

} // end of namespace
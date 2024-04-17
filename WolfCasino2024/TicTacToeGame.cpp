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
        run();
    }


    void TicTacToeGame::run() {

    }



    int TicTacToeGame::getXCoord(char player)
    {
         return 0;
    }

    int TicTacToeGame::getYCoord(char player)
    {
        return 0;
    }

    bool TicTacToeGame::placeMarker(int x, int y, char currentPlayer)
    {
        return true;
    }

    bool TicTacToeGame::checkForVictory(char currentPlayer)
    {
         return false;
    }

    void TicTacToeGame::clearBoard()
    {
 
    }

    void TicTacToeGame::printBoard()
    {

    }

} // end of namespace
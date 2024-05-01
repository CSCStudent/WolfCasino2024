/*Nathan Rodarmel
* Professor: Robert Gilanyi
* CSC2034 Computer Science C++
* 30 April 2024
*
* CSC2034 Capstone Project
* Red vs Blue TicTacToe Game!
* Created by: Nathan Rodarmel
*
* Header Description: This header file contains the class definition for the TicTacToe game logic. The class contains the necessary
*                     methods to run the game, check for a win, check for a draw, and initialize the game board. The class also contains
*                     a factory method to create an instance of the TicTacToe game logic.
*/

#ifndef TICLOGIC_H
#define TICLOGIC_H   
#include "Casino.h"  // Include Casino header file

//defined namespace for project
namespace S02591408 {

    // Class definition for TicTacToe game logic
    class tttGameLogic : public CSC2034::Casino {

    public:
        static tttGameLogic* makeGame(); // Factory method to create an instance of TicLogic
        void start(); // Start the game
        void run(); // Run the TicTacToe game
        ~tttGameLogic(); // Destructor
        tttGameLogic(); // Constructor

    private:
        void initialize_board(); // Initialize the TicTacToe board
        void print_board(); // Print the TicTacToe board
        bool check_win(char marker); // Check if a player has won
        bool check_draw(); // Check if the game is a draw
        void player_move(char player); // Perform a player move

    };

}

#endif // TICLOGIC_H
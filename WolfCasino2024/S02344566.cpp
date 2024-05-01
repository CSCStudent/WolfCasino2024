#include <iostream>
#include <ctime>
#include "S02344566.h"

namespace S02344566
{
    //Constructor
    RockPaperScissorsGame::RockPaperScissorsGame()
    {

    }

    RockPaperScissorsGame* RockPaperScissorsGame::makeGame() {
        return new RockPaperScissorsGame;
    }

    //The game!
    void RockPaperScissorsGame::start() {
        int round = 1;
        int playerScore = 0;
        int computerScore = 0;
        while (round <= 3) {
            cout << "Round " << round << "...\n";
            cout << "Rock...\n";
            cout << "Paper...\n";
            cout << "Scissors...\n";
            cout << "Make your selection (r,p,s): ";
            cin >> playerPlay;
            cout << "SHOOT!\n";
            if (playerPlay == 'r')
                cout << "Player selected rock\n";
            else if (playerPlay == 'p')
                cout << "Player selected paper\n";
            else if (playerPlay == 's')
                cout << "Player selected scissors\n";
            cout << "Computer selected ";
            char comp = computerSelect();
            if (comp == 'r')
                cout << "rock\n";
            else if (comp == 'p')
                cout << "paper\n";
            else if (comp == 's')
                cout << "scissors\n";
            int win = findWinner(playerPlay, comp);
            if (win == 0) {
                cout << "Its a tie\n";
            }
            else if (win == 1) {
                cout << "Player wins round " << round << "\n";
                playerScore++;
                round++;
            }
            else if (win == 2) {
                cout << "Computer wins round " << round << "\n";
                computerScore++;
                round++;
            }
        }
        if (playerScore > computerScore)
            cout << "Player wins the game";
        else if (computerScore > playerScore)
            cout << "Computer wins the game\n";
    }

    char RockPaperScissorsGame::computerSelect() {
        char computerPlay[3] = { 'r','p','s' };
        int selection = rand() % 3;
        return computerPlay[selection];
    }

    int RockPaperScissorsGame::findWinner(char player, char comp) {
        if (player == 'r') {
            if (comp == 'r')
                return 0;
            else if (comp == 's')
                return 1;
            else if (comp == 'p')
                return 2;
        }
        if (player == 'p') {
            if (comp == 'p')
                return 0;
            else if (comp == 'r')
                return 1;
            else if (comp == 's')
                return 2;
        }
        if (player == 's') {
            if (comp == 's')
                return 0;
            else if (comp == 'p')
                return 1;
            else if (comp == 'r')
                return 2;
        }
    }
} // end of namespace
#include "S02710191A.h"
#include "S02710191A.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cctype>


namespace S02710191 {
    LiarsDice::LiarsDice()
    {
        
    }

    LiarsDice* LiarsDice::makeGame() {
        return new LiarsDice;
    }

    void LiarsDice::start() {
        
        bool testMode = false;
        bool playerTurn = true; // determines who bets first, player or house
        bool turnAfterHouseBet = false;
        int betNumberOnDice = 0;
        int betNumberOfDice = 0;
        bool validInput = true;
        
        cout << "Do you want to display opponent's hand to learn the game? (y/n)" << endl;
        do {
            char gameMode;
            cin >> gameMode;
            if (cin.fail()) {
                validInput = false;
                cout << "Invalid type input, try again." << endl;
                cin.clear();
                cin.ignore();
            }
            else if (gameMode == 'y') {
                testMode = true;
            }
        } while (!validInput);

        while (!playerHand.isEmpty() && !houseHand.isEmpty()) {
           
            cout << endl << "Your Hand:";
            playerHand.printHand();
            cout << endl;

            if (testMode) {
                cout << "Opponent Hand:";
                houseHand.printHand();
                cout << endl;
            }

            int playerNumberOnDiceBet;
            int playerNumberOfDiceBet;
            if (playerTurn) {
                cout << "Enter your bet." << endl;
                do {
                    
                    cout << "Number of dice:" << endl;
                    cin >> playerNumberOfDiceBet;

                    // validates data type
                    if (cin.fail()) {
                        validInput = false;
                        cout << "Invalid type input, try again." << endl;
                        cin.clear();
                        cin.ignore();
                    }
                    // the user has to increase the bet of either # of dice or # on dice
                    // checks for increase in # of dice
                    else if (!(playerNumberOfDiceBet >= betNumberOfDice)) {
                        cout << "Value is not more than current bet, try again." << endl;
                        validInput = false;
                        cin.clear();
                        cin.ignore();
                    }
                    else {
                        validInput = true;
                    }
                } while (!validInput);

                do {
                    cout << "Number on die:" << endl;
                    cin >> playerNumberOnDiceBet;

                    // validates data type
                    if (cin.fail()) {
                        validInput = false;
                        cout << "Invalid type input, try again." << endl;
                        cin.clear();
                        cin.ignore();
                    }
                    // checks if input is on the face of the die
                    else if (!((playerNumberOnDiceBet <= 6) && (playerNumberOnDiceBet >= 1))) {
                        cout << "Value is not on a die, try again." << endl;
                        validInput = false;
                        cin.clear();
                        cin.ignore();
                    }
                    // checks for increase of # on dice and if # of dice hasn't been increased
                    else if (!(playerNumberOnDiceBet > betNumberOnDice) && !(playerNumberOfDiceBet > betNumberOfDice)) {
                        cout << "Value is not more than current bet, try again." << endl;
                        validInput = false;
                        cin.clear();
                        cin.ignore();
                    }
                    else {
                        validInput = true;
                    }

                    betNumberOfDice = playerNumberOfDiceBet;
                    betNumberOnDice = playerNumberOnDiceBet;

                } while (!validInput);
            }
 
            // initialize player hand report
            int playerDiceSideCount[6] = { 0,0,0,0,0,0 };
            playerHand.highestQuantityDie(playerDiceSideCount);

            // initialize house hand report
            int houseDiceSideCount[6] = { 0,0,0,0,0,0 };
            houseHand.highestQuantityDie(houseDiceSideCount);

            // total game hand report
            int diceSideCount[6] = { 0,0,0,0,0,0 };
            houseHand.highestQuantityDie(diceSideCount);
            playerHand.highestQuantityDie(diceSideCount);

            // if the player bets more than the total # of dice on in the game, the house calls you a liar
            if (betNumberOfDice > (houseHand.size + playerHand.size) && playerTurn) {
                cout << endl << "House knows you're lying." << endl;
                playerHand.printHand();
                houseHand.printHand();
                cout << endl << "Total number of bet dice: " << diceSideCount[betNumberOnDice - 1] << endl;
                cout << "Number on die: " << betNumberOnDice << endl;
                playerHand.removeDie();
                houseHand.rerollHand();
                playerHand.rerollHand();
                playerTurn = false;
                betNumberOnDice = 0;
                betNumberOfDice = 0;
            }
            // if the player bets more than the total # of dice that could possibly be in the player hand
            // plus the number of that number in the house's hand, the house calls you a liar
            else if ((playerHand.size + houseDiceSideCount[betNumberOnDice-1] < betNumberOfDice) && playerTurn) {
                cout << endl << "House knows you're lying." << endl;
                playerHand.printHand();
                houseHand.printHand();
                cout << endl << "Total number of bet dice: " << diceSideCount[betNumberOnDice - 1] << endl;
                cout << "Number on die: " << betNumberOnDice << endl;
                playerHand.removeDie();
                houseHand.rerollHand();
                playerHand.rerollHand();
                playerTurn = false;
                turnAfterHouseBet = false;
                betNumberOnDice = 0;
                betNumberOfDice = 0;
            }
            else if (((playerHand.size + houseDiceSideCount[betNumberOnDice-1]) == betNumberOfDice) && playerTurn) {
                cout << endl << "House guesses you're lying." << endl;
                playerHand.printHand();
                houseHand.printHand();
                cout << endl << "Total number of bet dice: " << diceSideCount[betNumberOnDice - 1] << endl;
                cout << "Number on die: " << betNumberOnDice << endl;
                if (diceSideCount[betNumberOnDice - 1] >= betNumberOfDice) {
                    cout << "House guessed incorrectly." << endl;
                    playerHand.printHand();
                    houseHand.printHand();
                    houseHand.removeDie();
                    houseHand.rerollHand();
                    playerHand.rerollHand();
                    playerTurn = true;
                    turnAfterHouseBet = false;
                    betNumberOnDice = 0;
                    betNumberOfDice = 0;
                }
                else {
                    cout << "House guessed correctly." << endl;
                    playerHand.removeDie();
                    houseHand.rerollHand();
                    playerHand.rerollHand();
                    playerTurn = false;
                    betNumberOnDice = 0;
                    betNumberOfDice = 0;
                }
            }
            else if (!playerTurn && !turnAfterHouseBet) {
                int houseMostSide = 0;
                int houseIndexOfMostSide = 0;
                for (int i = 0; i < 7; i++) {
                    if (houseDiceSideCount[i] > houseMostSide) {
                        int randValue = (rand() % 3 + 1);
                        if (randValue == 1) {
                            houseMostSide = houseDiceSideCount[i] + 1; // 1/3 chance to bet above
                        }
                        else {
                            houseMostSide = houseDiceSideCount[i]; // how many
                        }
                        
                        houseIndexOfMostSide = i + 1; // what number
                    }
                }

                betNumberOnDice = houseIndexOfMostSide;
                betNumberOfDice = houseMostSide;
                cout << "House bet: " << endl;
                cout << "Number of dice: " << betNumberOfDice << endl;
                cout << "Number on dice: " << betNumberOnDice << endl;
                turnAfterHouseBet = true;

            }
            else {

                int houseMostSide = 0;
                int houseIndexOfMostSide = 0;
                for (int i = 0; i < 7; i++) {
                    if (houseDiceSideCount[i] > houseMostSide) {
                        houseMostSide = houseDiceSideCount[i];
                        houseIndexOfMostSide = i+1;
                    }
                }

                // house bet randomizer
                if (!turnAfterHouseBet) {
                    int randValue = (rand() % 2 + 1);
                    if (randValue == 1) {
                        betNumberOfDice += houseMostSide;
                    }
                    else {
                        if (betNumberOfDice <= (houseHand.size + playerHand.size)) {
                            if (betNumberOnDice > 6) {
                                betNumberOfDice += (rand() % houseMostSide + 1);
                            }
                            else {
                                betNumberOnDice += 1;
                            }
                        }
                        else {
                            betNumberOfDice += (rand() % houseMostSide + 1);
                        }
                    }

                    cout << "Number of dice: " << betNumberOfDice << endl;
                    cout << "Number on dice: " << betNumberOnDice << endl;

                    turnAfterHouseBet = false;
                }
                
                cout << "Is the house telling the truth? True or false (t/f): " << endl;
                char playerGuess;

                validInput = true;
                do {
                    cin >> playerGuess;
                    if (cin.fail()) {
                        validInput = false;
                        cout << "Invalid type input, try again." << endl;
                        cin.clear();
                        cin.ignore();
                    }
                    // if the player guesses the house is telling the truth, they bet again
                    else if (playerGuess == 't') {
                        cout << endl << "Current bet: " << endl;
                        cout << "Number of dice: " << betNumberOfDice << endl;
                        cout << "Number on dice: " << betNumberOnDice << endl;
                        continue;
                    }
                    // if the player guess the house is lying, the game checks the total number
                    // of the dice and checks if it is less than the bet
                    else if (playerGuess == 'f') {
                        cout << endl << "Total number of bet dice: " << diceSideCount[betNumberOnDice-1] << endl;
                        cout << "Number on dice: " << betNumberOnDice << endl;

                        // dice is more or equal to bet
                        if (betNumberOfDice <= diceSideCount[betNumberOnDice-1]) {
                            cout << "House was telling the truth." << endl;
                            cout << "Player Hand: ";
                            playerHand.printHand();
                            cout << "House Hand: ";
                            houseHand.printHand();
                            playerHand.removeDie();
                            houseHand.rerollHand();
                            playerHand.rerollHand();
                            playerTurn = false;
                            turnAfterHouseBet = false;
                            betNumberOnDice = 0;
                            betNumberOfDice = 0;
                        }
                        // dice is less than bet
                        else {
                            cout << endl << "House was lying." << endl;
                            cout << "Player Hand: ";
                            playerHand.printHand();
                            cout << "House Hand: ";
                            houseHand.printHand();
                            houseHand.removeDie();
                            houseHand.rerollHand();
                            playerHand.rerollHand();
                            playerTurn = true;
                            turnAfterHouseBet = false;
                            betNumberOnDice = 0;
                            betNumberOfDice = 0;
                        }
                    }
                } while (!validInput);
                

            }



        }
        if (playerHand.isEmpty()) {
            cout << "House wins." << endl;
        } 
        else if (houseHand.isEmpty()) {
            cout << "Player wins!" << endl;
        }
    }
}
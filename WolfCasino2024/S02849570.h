#pragma once
#include <ctime>
#include <vector>
#include <algorithm>
#include "Casino.h"

//defined namespace for project
namespace S02849570
{
    class Hangman : public CSC2034::Casino
    {
    public:
        //Constructor
        Hangman();

        static Hangman* makeGame();

        //This plays the game
        void start();

        static string pickWord();

        bool isCharInWord(char c);

        string getWordWithGuesses();

        static void printHangedMan(int);

    private:


        //This stores the board state
        vector<char> guesses;
        int triesLeft = 6;
        char guess = '\0';
        string word;
    };
} //end of namespace

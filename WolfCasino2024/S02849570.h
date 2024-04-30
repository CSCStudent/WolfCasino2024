#pragma once
#include <ctime>
#include <vector>
#include <algorithm>
#include "Casino.h"

//defined namespace for project
namespace CSC2034
{
    class S02849570 : public Casino
    {
    public:
        //Constructor
        S02849570();

        static S02849570* makeGame();

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

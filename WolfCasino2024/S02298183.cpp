// squidward source
// https://www.twitchquotes.com/copypastas/4777
// dollar art source
// https://emojicombos.com/dollar-sign-ascii-art

// squidgame.cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>
#include "S02298183.h"

namespace S02298183
{
    SquidGame::SquidGame() : lengthOfLevel(0), turnsRemaining(0), backLuckMultiplier(0)
    {
    }
    SquidGame *SquidGame::makeGame()
    {
        return new SquidGame;
    }

    void SquidGame::clearConsole()
    {
        const int numLines = 60;
        for (int i = 0; i < numLines; ++i)
        {
            std::cout << std::endl;
        }
    }

    void SquidGame::printSquidward()
    {
        std::vector<std::string> squidward = {
            "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠠⠤⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⣀⢤⡒⠉⠁⠀⠒⢂⡀⠀⠀⠀⠈⠉⣒⠤⣀⠀⠀⠀⠀",
            "⠀⠀⣠⠾⠅⠈⠀⠙⠀⠀⠀⠈⠀⠀⢀⣀⣓⡀⠉⠀⠬⠕⢄⠀⠀",
            "⠀⣰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡤⠶⢦⡀⠑⠀⠀⠀⠀⠈⢧⠀",
            "⠀⡇⠀⠀⠀⠀⠀⢤⣀⣀⣀⣀⡀⢀⣀⣀⠙⠀⠀⠀⠀⠀⠀⢸⡄",
            "⠀⢹⡀⠀⠀⠀⠀⡜⠁⠀⠀⠙⡴⠁⠀⠀⠱⡄⠀⠀⠀⠀⠀⣸⠀",
            "⠀⠀⠱⢄⡀⠀⢰⣁⣒⣒⣂⣰⣃⣀⣒⣒⣂⢣⠀⠀⠀⢀⡴⠁⠀",
            "⠀⠀⠀⠀⠙⠲⢼⡀⠀⠙⠀⢠⡇⠀⠛⠀⠀⣌⣀⡤⠖⠉⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⢸⡗⢄⣀⡠⠊⠈⢦⣀⣀⠔⡏⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⠈⡇⠀⢰⠁⠀⠀⠀⢣⠀⠀⣷⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⣠⠔⠊⠉⠁⡏⠀⠀⠀⠀⠘⡆⠤⠿⣄⣀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⣧⠸⠒⣚⡩⡇⠀⠀⠀⠀⠀⣏⣙⠒⢴⠈⡇⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠈⠋⠉⠀⠀⢳⡀⠀⠀⠀⣸⠁⠈⠉⠓⠚⠁⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠛⠛             "};
        for (const auto &line : squidward)
        {
            std::cout << line << std::endl;
        }
    }

    void SquidGame::printSquidwardBackwards()
    {
        std::vector<std::string> squidward = {
            "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠠⠤⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⣀⢤⡒⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⣒⠤⣀⠀⠀⠀⠀",
            "⠀⠀⣠⠾⠅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠬⠕⢄⠀⠀",
            "⠀⣰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀",
            "⠀⡇⠀⠀⠀               ⠀⠀⠀⠀⢸⡄",
            "⠀⢹⡀⠀                 ⠀⠀⠀⣸⠀",
            "⠀⠀⠱⢄⡀⠀                ⢀⡴⠁⠀",
            "⠀⠀⠀⠀⠙⠲⢼⡀⠀⠀⠀    ⠀⠀⠀⣌⣀⡤⠖⠉⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⢸⡗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡏⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⠀⠀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⣠⠔⠊⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⣄⣀⠀⠀⠀⠀⠀",
            "⠀⠀⠀⠀⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠈⠋⠉⠀⠀⢳⡀⠀⠀⠀⣸⠁⠈⠉⠓⠚⠁⠀⠀⠀⠀",
            "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠛⠛"};
        for (const auto &line : squidward)
        {
            std::cout << line << std::endl;
        }
    }

    void SquidGame::printDollar()
    {
        std::cout << R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣀⣀⣀⣄⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⣻⣿⡁⠀⠈⢹⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣵⣿⠁⠀⠀⢼⣀⣀⣀⡀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣠⠾⠛⠁⠀⠀⠀⠀⠀⠁⠉⠉⠉⠛⠲⣦⡀
⠀⠀⠀⠀⠀⣠⡞⠁⠀⠀⠀⣀⣤⣤⣤⣤⣤⣀⣀⠀⠀⠀⣼⠟
⠀⠀⠀⠀⣼⡟⠀⠀⠀⢰⣿⣭⣿⣿⣿⣭⣖⣫⠟⣛⠷⣾⠃⠀
⠀⠀⠀⢰⣿⡇⠀⠀⠀⠸⣾⡛⠀⠀⠀⠀⠉⠙⠛⠶⢾⠃⠀⠀
⠀⠀⠀⣸⡥⢿⡀⠀⠀⠀⠈⠙⠳⢦⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠻⣶⠋⡻⣦⡀⠀⠀⠀⠀⠀⠀⠉⠛⠳⢦⣄⠀⠀⠀⠀
⠀⠀⠀⠀⠻⣯⣠⠜⡹⠷⣦⣄⡀⠀⠀⠀⠀⠀⠀⠈⠻⣦⠀⠀
⠀⠀⠀⠀⠀⠈⠛⠾⣤⣖⣩⢜⡫⢟⣶⣤⣀⠀⠀⠀⠀⠘⣧⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠳⢯⣖⡩⠽⣷⠀⠀⠀⠀⢹⡀
⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡖⠊⣿⠀⠀⠀⠀⢸⠇
⠀⠀⣤⣶⣶⡟⠓⠶⢤⣄⣀⡀⠀⠀⣸⣷⡿⠋⠀⠀⠀⢀⣾⠀
⠀⣼⣛⣥⡟⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⣠⣾⡿⠀
⠘⢿⣥⠟⢷⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣾⣿⡟⠁⠀
⠀⠀⠈⠻⣯⣞⡩⠟⣻⠿⣻⢾⡆⠀⠀⠘⣟⣱⣿⠿⠋⠀⠀⠀
⠀⠀⠀⠀⠀⠉⠙⠛⠛⠻⣧⢼⡇⠀⠀⠀⣿⠋⠁⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡷⢺⣧⣤⣤⣤⣿⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣟⣡⣿⢛⣵⣷⠟⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀
    )" << std::endl;
    }

    int SquidGame::countWs(const std::string &input)
    {
        int count = 0;
        for (char c : input)
        {
            if (c == 'w')
            {
                count++;
            }
        }
        return count;
    }

    void SquidGame::printProgress(int totalWs, int lengthOfLevel)
    {
        std::cout << "start   ";
        std::cout << std::string(totalWs, 'w');
        std::cout << std::string(lengthOfLevel - totalWs, '-');
        std::cout << "   finish line\n";
    }

    void SquidGame::start()
    {

        int lengthOfLevel = 0;
        int turnsRemaining = 0;
        int backLuckMultiplier = 0;

        std::cout << "Welcome to Squid Game!\n";
        std::cout << "This is red light green light.\n";
        std::cout << "Each turn walk forward by entering 'w's.\n";
        std::cout << "The more 'w's the farther you will go.\n";
        std::cout << "But be careful!\n";
        std::cout << "If you get greedy and move too fast, Squidward may turn around!\n";
        std::cout << "Then it's game over!\n";
        std::cout << "The goal is to get the finish line before your turns run out.\n";
        std::cout << "And without Squidward catching you.\n";
        std::cout << "Winner gets 45,600,000,000$.\n";

        bool isNewGame = true;

        do
        {
            std::string difficultyLevel;

            srand(time(0));

            do
            {
                std::cout << "\nThe difficulty levels are 'easy' 'medium' 'expert'.\n";
                std::cout << "Please pick a difficulty: ";

                std::cin >> difficultyLevel;

                if (difficultyLevel == "easy" || difficultyLevel == "Easy" || difficultyLevel == "e" || difficultyLevel == "EASY")
                {
                    lengthOfLevel = 20;
                    turnsRemaining = 7;
                    backLuckMultiplier = 0;
                    break;
                }
                else if (difficultyLevel == "medium" || difficultyLevel == "Medium" || difficultyLevel == "m" || difficultyLevel == "MEDIUM")
                {
                    lengthOfLevel = 25;
                    turnsRemaining = 6;
                    backLuckMultiplier = 1;
                    break;
                }
                else if (difficultyLevel == "expert" || difficultyLevel == "Expert" || difficultyLevel == "ex" || difficultyLevel == "EXPERT")
                {
                    lengthOfLevel = 30;
                    turnsRemaining = 5;
                    backLuckMultiplier = 2;
                    break;
                }
                else
                {
                    std::cout << "Oops! I didn't understand that.\n";
                }
            } while (true);

            bool continueGame = true;
            int totalWs = 0;

            while (continueGame)
            {
                clearConsole();
                int badLuck = (rand() % 3) * backLuckMultiplier; // min 0, max 4
                int maxWs = (rand() % 6) + 5 - badLuck;          // min 5, max 10. min 3, max 8. min 1, max 6.
                printSquidwardBackwards();
                printProgress(totalWs, lengthOfLevel);
                std::cout << turnsRemaining << " turns remain...\n";
                // std::cout << "MaxWs: " << maxWs; // debug
                std::cout << "Enter some 'w's to move forward: ";
                std::string input;
                std::cin >> input;

                int wCount = countWs(input);
                totalWs += wCount;
                if (wCount > maxWs)
                {
                    clearConsole();
                    printSquidward();
                    std::cout << "Red Light! You moved while Squidward was looking! Game Over!\n";
                    continueGame = false;
                }
                else if (totalWs >= lengthOfLevel)
                {
                    clearConsole();
                    printDollar();
                    std::cout << "\nCongratulations! You passed the finish line!\n";
                    std::cout << "You win! The money's yours!\n\n";
                    continueGame = false;
                }
                else if (turnsRemaining <= 0)
                {
                    clearConsole();
                    printSquidward();
                    std::cout << "Time's up! Game Over!\n";
                    continueGame = false;
                }
                else
                {
                    turnsRemaining--;
                }
            }
            do
            {
                std::cout << "\nWould you like to play again?'.\n";
                std::cout << "Yes or no: ";

                std::string continueInput;
                std::cin >> continueInput;

                if (continueInput == "yes" || continueInput == "Yes" || continueInput == "y" || continueInput == "YES")
                {
                    isNewGame = true;
                    break;
                }
                else if (continueInput == "no" || continueInput == "No" || continueInput == "n" || continueInput == "NO")
                {
                    isNewGame = false;
                    break;
                }
                else
                {
                    std::cout << "Oops! I didn't understand that.\n";
                }
            } while (true);
        } while (isNewGame);

        std::cout << "\nThanks for playing!\n";
    }
};

// debug
// int main() {
//     squidgame::SquidGame game;
//     game.start();
//     return 0;
// }

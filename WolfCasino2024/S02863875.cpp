#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "S02863875.h"

// Note: please read first :: proper formate is a # don't include the 0 in front for single digits. Then color or high/low, EX red green black high low, then the amount you wish to bet 0 - 100
// Note: you can win even if you guess the wrong number it does not effect winning for basic black, red , green, high, low beting values.

namespace S02863875 {
    CSC2034::Casino* Roulette::makeGame() {
        return new Roulette();
    }
    Roulette::Roulette() {
        // Initialize balance to 0
        balance = 0;
    }
    void Roulette::start() {
        std::cout << "Welcome to the Roulette table!" << std::endl;
        std::cout << "Here are the numbers on the board:" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        for (int i = 0; i < 38; ++i) {
            if (i == 0) {
                std::cout << "\033[1;32m"; // Green color for 00
            }
            else if (i == 37) {
                std::cout << "\033[1;32m"; // Green color for 0
            }
            else {
                if (board[i].color == Color::RED)
                    std::cout << "\033[1;31m"; // Red color
                else if (board[i].color == Color::BLACK)
                    std::cout << "\033[1;34m"; // Blue color
            }
            std::cout << std::setw(2) << std::setfill('0') << i << " ";
            std::cout << "\033[0m "; // Reset color
            if ((i + 1) % 3 == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;

        // Game loop
        while (true) {
            std::cout << "Place your bets (e.g., 'number (can be any unless green), betType (color,high,low), amount bet (use spaces not commas, all three must be present)):" << std::endl;
            std::string bet;
            std::getline(std::cin, bet);

            // Parse the bet
            std::istringstream iss(bet);
            int betValue;
            std::string betType;
            int betAmount;
            iss >> betValue >> betType >> betAmount;

            // Process the bet
            if (isValidBet(betType, betValue, betAmount)) {
                int spinResult = spinWheel();
                if (isWinningBet(betType, betValue, spinResult)) {
                    int payout = calculatePayout(betType, betAmount, spinResult);
                    std::cout << "You win! Payout: " << payout << std::endl;
                    balance += payout;
                }
                else {
                    std::cout << "You lose!" << std::endl;
                    balance -= betAmount;
                }
            }
            else {
                std::cout << "Invalid bet!" << std::endl;
            }

            // Ask if the player wants to play again
            std::cout << "Play again? (y/n): ";
            char playAgain;
            std::cin >> playAgain;
            if (playAgain != 'y' && playAgain != 'Y') {
                break;
            }

            // Clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Thank you for playing Roulette!" << std::endl;
    }

    bool Roulette::isValidBet(const std::string& betType, int betValue, int betAmount) {
        // Convert betType to lowercase for case-insensitive comparison
        std::string lowercaseBetType = betType;
        std::transform(lowercaseBetType.begin(), lowercaseBetType.end(), lowercaseBetType.begin(), ::tolower);

        if (betAmount <= 0) {
            return false; // Bet amount must be positive
        }

        if (lowercaseBetType == "red" || lowercaseBetType == "black") {
            return true; // Bet on red or black is always valid
        }

        if (lowercaseBetType == "even" || lowercaseBetType == "odd") {
            return true; // Bet on even or odd is always valid
        }

        if (lowercaseBetType == "low" || lowercaseBetType == "high") {
            return true; // Bet on low (1-18) or high (19-36) is always valid
        }

        if (lowercaseBetType == "number") {
            // Bet on a specific number is valid if it's between 0 and 36
            return (betValue >= 0 && betValue <= 36);
        }

        return false; // Invalid bet type
    }

    bool Roulette::isWinningBet(const std::string& betType, int betValue, int spinResult) {
        if (betType == "red") {
            // Bet on red wins if the spin result is red (1-10, 19-28)
            return (isRed(spinResult));
        }

        if (betType == "black") {
            // Bet on black wins if the spin result is black (11-18, 29-36)
            return (!isRed(spinResult));
        }

        if (betType == "even") {
            // Bet on even wins if the spin result is even
            return (spinResult % 2 == 0);
        }

        if (betType == "odd") {
            // Bet on odd wins if the spin result is odd
            return (spinResult % 2 == 1);
        }

        if (betType == "low") {
            // Bet on low wins if the spin result is between 1 and 18
            return (spinResult >= 1 && spinResult <= 18);
        }

        if (betType == "high") {
            // Bet on high wins if the spin result is between 19 and 36
            return (spinResult >= 19 && spinResult <= 36);
        }

        if (betType == "number") {
            // Bet on a specific number wins if the spin result is that number
            return (spinResult == betValue);
        }

        return false; // Invalid bet type
    }

    int Roulette::calculatePayout(const std::string& betType, int betAmount, int spinResult) {
        if (isWinningBet(betType, betAmount, spinResult)) {
            // Calculate the payout based on the bet type
            if (betType == "red" || betType == "black") {
                return betAmount * 2; // Bet on red or black pays 1:1
            }

            if (betType == "even" || betType == "odd" || betType == "low" || betType == "high") {
                return betAmount * 2; // Bet on even, odd, low, or high pays 1:1
            }

            if (betType == "green") {
                return betAmount * 28; // Bet on green pays 28:1
            }

            if (betType == "number") {
                return betAmount * 36; // Bet on a specific number pays 35:1
            }
        }

        return 0; // No payout for losing bets
    }

    void Roulette::deposit(int amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited " << amount << ". Current balance: " << balance << std::endl;
        }
    }

    void Roulette::withdraw(int amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawn " << amount << ". Current balance: " << balance << std::endl;
        }
    }

    int Roulette::getBalance() const {
        return balance;
    }

    int Roulette::spinWheel() {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(nullptr)));

        // Generate a random number between 0 and 37
        return rand() % 38;
    }
}
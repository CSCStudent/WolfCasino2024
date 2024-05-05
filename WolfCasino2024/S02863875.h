#pragma once
#ifndef ROULETTE_H
#define ROULETTE_H

#include <string>
#include "Casino.h"

namespace S02863875 {
    enum class Color { GREEN, RED, BLACK };

    class Roulette : public CSC2034::Casino {
    public:
        Roulette();
        ~Roulette();

        static Casino* makeGame();
        void start() override;

        void deposit(int amount);
        void withdraw(int amount);
        int getBalance() const;

        bool isValidBet(const std::string& betType, int betValue, int betAmount);
        bool isWinningBet(const std::string& betType, int betValue, int spinResult);
        int calculatePayout(const std::string& betType, int betAmount, int spinResult);

    private:
        int balance;
        int spinWheel();

        static bool isRed(int number) {
            return ((number >= 1 && number <= 10) || (number >= 19 && number <= 28));
        }

        struct Number {
            int value;
            Color color;
        };
        Number board[38] = {
            {0, Color::GREEN}, {32, Color::RED}, {15, Color::BLACK}, {19, Color::RED}, {4, Color::BLACK}, {21, Color::RED}, {2, Color::BLACK}, {25, Color::RED}, {17, Color::BLACK}, {34, Color::RED}, {6, Color::BLACK}, {27, Color::RED},
            {13, Color::BLACK}, {36, Color::RED}, {11, Color::BLACK}, {30, Color::RED}, {8, Color::BLACK}, {23, Color::RED}, {10, Color::BLACK}, {5, Color::RED}, {24, Color::BLACK}, {16, Color::RED}, {33, Color::BLACK}, {1, Color::RED},
            {20, Color::BLACK}, {14, Color::RED}, {31, Color::BLACK}, {9, Color::RED}, {22, Color::BLACK}, {18, Color::RED}, {29, Color::BLACK}, {7, Color::RED}, {28, Color::BLACK}, {12, Color::RED}, {35, Color::BLACK}, {3, Color::RED},
            {26, Color::BLACK}
        };
    };
}

#endif // ROULETTE_H
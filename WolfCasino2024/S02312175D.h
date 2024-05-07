#ifndef PLAYER_TH
#define PLAYER_TH
#include <vector>
#include "S02312175A.h"

namespace S02312175 {
    class Player {
    public:
        Player();

        // Receive a card
        void receiveCard(const Card& card);

        // Get the player's hand
        const std::vector<Card>& getHand() const;

        // Get the player's current bet amount
        int getCurrentBet() const;

        // Get the player's total chips
        int getChips() const;

        // Add chips to the player's stack
        void addChips(int amount);

        // Bet a certain amount of chips
        void bet(int amount);

        // Reset the player's current bet amount
        void resetBet();

        // Check if the player has folded
        bool hasFolded() const;

        // Fold the player's hand
        void fold();

    private:
        std::vector<Card> hand_; // Player's hand
        int currentBet_; // Current bet amount
        int chips_; // Total chips
        bool folded_; // Whether the player has folded
    };
}
#endif // PLAYER_H

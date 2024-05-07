#ifndef GAME_TH
#define GAME_TH

#include <vector>
#include <map>
#include "S02312175B.h"
#include "S02312175D.h"
#include "Casino.h"


namespace S02312175 {
    class Game : public CSC2034::Casino {
    public:
        Game(int numPlayers);

        // returns game object
        static Game* makeGame();

        // Start the game
        void start();

    private:
        int numPlayers_; // Number of players in the game
        int activePlayers_;// Number of players who havent folded
        std::vector<Player> players_; // Vector of players
        Deck deck_; // Deck of cards
        std::vector<Card> communityCards_; // Community cards
        int currentBet_; // Current bet amount
        int pot_; // Total chips in the pot

        // Deal hole cards to each player
        void dealHoleCards();

        // Deal community cards
        void dealCommunityCards(int numCards);

        // Perform a betting round
        void bettingRound();

        // Determine the winner at the showdown
        void showdown();

        // Utility function to count occurrences of each rank in a hand
        std::map<Card::Rank, int> countRanks(const std::vector<Card>& hand);

        // Utility function to check if a hand contains a flush
        bool isFlush(const std::vector<Card>& hand);

        // Utility function to check if a hand contains a straight
        bool isStraight(const std::vector<Card>& hand);

        // Function to evaluate the rank of a hand
        int evaluateHandRank(const std::vector<Card>& hand);

        // Function to compare hands and determine the winner
        int compareHands(const std::vector<Card>& hand1, const std::vector<Card>& hand2);
        // Print the community cards
        void printCommunityCards() const;

        // Print players' hands
        void printPlayersHands() const;

        bool checkForWinnerAndAddPot();
    };
}
#endif // GAME_H


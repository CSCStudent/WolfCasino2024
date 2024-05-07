#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "S02312175C.h"

namespace S02312175 {
    std::map<Card::Rank, int> Game::countRanks(const std::vector<Card>& hand)
    {
        std::map<Card::Rank, int> rankCount;
        for (const auto& card : hand) {
            rankCount[card.getRank()]++;
        }
        return rankCount;
    }

    bool Game::isFlush(const std::vector<Card>& hand)
    {
        Card::Suit suit = hand[0].getSuit();
        for (const auto& card : hand) {
            if (card.getSuit() != suit) {
                return false;
            }
        }
        return true;
    }
    bool Game::isStraight(const std::vector<Card>& hand)
    {
        std::map<Card::Rank, int> rankCount = countRanks(hand);
        int straightCounter = 0;
        for (const auto& pair : rankCount) {
            if (pair.second > 0) {
                straightCounter++;
                if (straightCounter == 5) {
                    return true;
                }
            }
            else {
                straightCounter = 0;
            }
        }
        return false;
    }

    int Game::evaluateHandRank(const std::vector<Card>& hand)
    {
        if (isFlush(hand) && isStraight(hand)) {
            return 8; // Straight Flush
        }
        else if (isFlush(hand)) {
            return 5; // Flush
        }
        else if (isStraight(hand)) {
            return 4; // Straight
        }
        else {
            std::map<Card::Rank, int> rankCount = countRanks(hand);
            int maxCount = 0;
            for (const auto& pair : rankCount) {
                maxCount = std::max(maxCount, pair.second);
            }
            if (maxCount == 4) {
                return 7; // Four of a Kind
            }
            else if (maxCount == 3) {
                if (rankCount.size() == 2) {
                    return 6; // Full House
                }
                else {
                    return 3; // Three of a Kind
                }
            }
            else if (maxCount == 2) {
                if (rankCount.size() == 3) {
                    return 2; // Two Pair
                }
                else {
                    return 1; // One Pair
                }
            }
            else {
                return 0; // High Card
            }
        }
    }

    int Game::compareHands(const std::vector<Card>& hand1, const std::vector<Card>& hand2)
    {
        int rank1 = evaluateHandRank(hand1);
        int rank2 = evaluateHandRank(hand2);
        if (rank1 != rank2) {
            return rank1 > rank2 ? 1 : -1;
        }
        else {
            // For hands of the same rank, compare by high card
            std::map<Card::Rank, int> rankCount1 = countRanks(hand1);
            std::map<Card::Rank, int> rankCount2 = countRanks(hand2);
            for (auto iter1 = rankCount1.rbegin(), iter2 = rankCount2.rbegin(); iter1 != rankCount1.rend(); ++iter1, ++iter2) {
                if (iter1->first != iter2->first) {
                    return iter1->first > iter2->first ? 1 : -1;
                }
            }
            return 0; // Tie
        }
    }

    Game::Game(int numPlayers) : numPlayers_(numPlayers), currentBet_(0), pot_(0), deck_(), communityCards_() {
        players_.reserve(numPlayers_);
        for (int i = 0; i < numPlayers_; ++i) {
            players_.emplace_back();
        }
    }

    void Game::start() {
        activePlayers_ = numPlayers_;

        deck_.shuffle();
        dealHoleCards();

        std::cout << "Hole Cards Dealt" << std::endl;
        std::cout << std::endl;
        printPlayersHands();

        // First betting round
        bettingRound();
        if (checkForWinnerAndAddPot()) { exit(0); };

        // Deal flop
        dealCommunityCards(3);
        std::cout << "Flop Dealt" << std::endl;
        std::cout << std::endl;
        printCommunityCards();

        // Second betting round
        bettingRound();
        if (checkForWinnerAndAddPot()) { exit(0); };

        // Deal turn
        dealCommunityCards(1);
        std::cout << "Turn Dealt" << std::endl;
        std::cout << std::endl;
        printCommunityCards();

        // Third betting round
        bettingRound();
        if (checkForWinnerAndAddPot()) { exit(0); };

        // Deal river
        dealCommunityCards(1);
        std::cout << "River Dealt" << std::endl;
        std::cout << std::endl;
        printCommunityCards();

        // Final betting round
        bettingRound();
        if (checkForWinnerAndAddPot()) { exit(0); };

        showdown();
    }




    void Game::dealHoleCards() {
        for (int i = 0; i < 2; ++i) {
            for (auto& player : players_) {
                player.receiveCard(deck_.dealCard());
            }
        }
    }

    void Game::dealCommunityCards(int numCards) {
        for (int i = 0; i < numCards; ++i) {
            communityCards_.push_back(deck_.dealCard());
        }
    }

    void Game::bettingRound() {
        int currentBetIncrement = 100; // Placeholder for the minimum bet increment

        // Reset players' bets
        for (auto& player : players_) {
            player.resetBet();
        }

        int currentPlayerIndex = 0;
        int playersRemaining = numPlayers_;
        bool firstRound = (currentBet_ == 0);

        while (playersRemaining != 0 && activePlayers_ > 1) {
            Player& currentPlayer = players_[currentPlayerIndex];

            // Skip players who have folded or cannot match the current bet
            if (currentPlayer.hasFolded() || currentPlayer.getChips() < currentBet_ - currentPlayer.getCurrentBet()) {
                currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers_;
                continue;
            }

            std::cout << "Player " << (currentPlayerIndex + 1) << "'s turn." << std::endl;
            std::cout << "Current chips: " << currentPlayer.getChips() << std::endl;

            int betAmount;
            std::string action;

            // First round: players can check, bet, or fold
            if (currentBet_ == 0) {
                std::cout << "Current bet: " << currentBet_ << std::endl;
                std::cout << "Actions: (check, bet, fold)" << std::endl;
                std::cin >> action;
                if (action == "check") {
                    if (currentBet_ == 0) {
                        // Player checks, nothing happens
                        std::cout << "Player " << (currentPlayerIndex + 1) << " checks." << std::endl;
                        playersRemaining++;
                    }
                    else {
                        // Player cannot check, they must bet, call, or fold
                        std::cout << "Cannot check. Please bet, call, or fold." << std::endl;
                        continue;
                    }
                }
                else if (action == "bet") {
                    std::cout << "Enter bet amount: ";
                    std::cin >> betAmount;
                    if (betAmount < currentBet_) {
                        std::cout << "Bet amount must be at least the current bet." << std::endl;
                        continue;
                    }
                    currentPlayer.bet(betAmount);
                    currentBet_ = betAmount;
                    std::cout << "Player " << (currentPlayerIndex + 1) << " bets " << betAmount << "." << std::endl;
                }
                else if (action == "fold") {
                    std::cout << "Player " << (currentPlayerIndex + 1) << " folds." << std::endl;
                    currentPlayer.fold();
                    activePlayers_--;
                }
                else {
                    std::cout << "Invalid action. Please check, bet, or fold." << std::endl;
                    continue;
                }
                std::cout << std::endl;
            }
            else {
                // Subsequent rounds: players can fold, call, raise, or check
                std::cout << "Current bet: " << currentBet_ << std::endl;
                std::cout << "Actions: (fold, call, raise, check)" << std::endl;
                std::cin >> action;
                if (action == "fold") {
                    std::cout << "Player " << (currentPlayerIndex + 1) << " folds." << std::endl;
                    currentPlayer.fold();
                    activePlayers_--;
                }
                else if (action == "call") {
                    int callAmount = currentBet_ - currentPlayer.getCurrentBet();
                    currentPlayer.bet(callAmount);
                    std::cout << "Player " << (currentPlayerIndex + 1) << " calls " << callAmount << "." << std::endl;
                }
                else if (action == "raise") {
                    std::cout << "Enter raise amount: ";
                    std::cin >> betAmount;
                    if (betAmount < currentBet_ + currentBetIncrement) {
                        std::cout << "Raise amount must be at least " << currentBet_ + currentBetIncrement << "." << std::endl;
                        continue;
                    }
                    currentPlayer.bet(betAmount);
                    currentBet_ = betAmount;
                    playersRemaining = numPlayers_;
                    std::cout << "Player " << (currentPlayerIndex + 1) << " raises to " << betAmount << "." << std::endl;
                }
                else if (action == "check") {
                    if (currentBet_ == 0) {
                        // Player checks, nothing happens
                        std::cout << "Player " << (currentPlayerIndex + 1) << " checks." << std::endl;
                    }
                    else {
                        // Player cannot check, they must fold, call, or raise
                        std::cout << "Cannot check. Please fold, call, or raise." << std::endl;
                        continue;
                    }
                }
                else {
                    std::cout << "Invalid action. Please fold, call, raise, or check." << std::endl;
                    continue;
                }
                std::cout << std::endl;
            }

            // Move to the next player
            currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers_;
            playersRemaining--;
        }

        // Collect bets and add them to the pot
        for (auto& player : players_) {
            pot_ += player.getCurrentBet();
            player.resetBet();
        }
        currentBet_ = 0;
        std::cout << "The pot is: " << pot_;
        std::cout << std::endl;
    }

    void Game::showdown() {
        std::cout << "Showdown!" << std::endl;

        // Placeholder logic to determine the winner based on hand evaluation
        int winnerIndex = 0;
        int winnerRank = evaluateHandRank(players_[0].getHand());
        for (int i = 1; i < numPlayers_; ++i) {
            int rank = evaluateHandRank(players_[i].getHand());
            if (rank > winnerRank) {
                winnerIndex = i;
                winnerRank = rank;
            }
            else if (rank == winnerRank) {
                if (compareHands(players_[i].getHand(), players_[winnerIndex].getHand()) > 0) {
                    winnerIndex = i;
                }
            }
        }
        std::cout << "Player " << (winnerIndex + 1) << " wins the pot of " << pot_ << " chips!" << std::endl;
        players_[winnerIndex].addChips(pot_);
        pot_ = 0;
    }
    void Game::printCommunityCards() const {
        std::cout << "Community Cards: ";
        for (const auto& card : communityCards_) {
            std::cout << card.toString() << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    void Game::printPlayersHands() const {
        std::cout << "Players' Hands:" << std::endl;
        for (size_t i = 0; i < players_.size(); ++i) {
            std::cout << "Player " << (i + 1) << ": ";
            const auto& hand = players_[i].getHand();
            for (const auto& card : hand) {
                std::cout << card.toString() << " ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }
    bool Game::checkForWinnerAndAddPot() {
        int activePlayers = 0;
        Player* lastActivePlayer = nullptr;

        // Count active players and find the last active player
        for (auto& player : players_) {
            if (!player.hasFolded()) {
                activePlayers++;
                lastActivePlayer = &player;
            }
        }

        // If there's only one active player, add the pot to their chips
        if (activePlayers == 1 && lastActivePlayer != nullptr) {
            lastActivePlayer->addChips(pot_);
            std::cout << "Player " << (lastActivePlayer - &players_[0] + 1) << " wins the pot of " << pot_ << " chips!" << std::endl;
            pot_ = 0;
            return true;
        }
        return false;
    }
    Game* Game::makeGame() {
        int numPlayers;
        std::cout << "Enter the number of players: ";
        std::cin >> numPlayers;

        return new Game(numPlayers);

    }
}


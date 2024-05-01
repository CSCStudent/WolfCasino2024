#include "S02902743.h"

// Implement the functions for each class
namespace S02902743 {

    // Card class implementations
    Card::Card(const std::string& rank, const std::string& suit) : rank(rank), suit(suit) {}

    int Card::getValue() const {
        if (rank == "Jack" || rank == "Queen" || rank == "King") {
            return 10;
        }
        else if (rank == "Ace") {
            return 11;
        }
        else {
            return std::stoi(rank);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << card.rank << " of " << card.suit;
        return os;
    }

    // Deck class implementations
    Deck::Deck() {
        build();
    }

    void Deck::build() {
        std::string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        std::string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

        for (const auto& suit : suits) {
            for (const auto& rank : ranks) {
                cards.emplace_back(rank, suit);
            }
        }
    }

    void Deck::shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card Deck::draw() {
        if (cards.empty()) {
            throw std::runtime_error("Deck is empty");
        }
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

    // Hand class implementations
    void Hand::addCard(const Card& card) {
        cards.push_back(card);
    }

    int Hand::getValue() const {
        int value = 0;
        int aces = 0;

        for (const auto& card : cards) {
            value += card.getValue();
            if (card.rank == "Ace") {
                aces++;
            }
        }

        while (value > 21 && aces > 0) {
            value -= 10;
            aces--;
        }

        return value;
    }

    std::ostream& operator<<(std::ostream& os, const Hand& hand) {
        for (const auto& card : hand.cards) {
            os << card << ", ";
        }
        return os;
    }

    // BlackjackGame implementations
    BlackjackGame::BlackjackGame() {
        deck.shuffle();
    }

    void BlackjackGame::dealInitialCards() {
        for (int i = 0; i < 2; ++i) {
            playerHand.addCard(deck.draw());
            dealerHand.addCard(deck.draw());
        }
    }

    void BlackjackGame::playerHit() {
        playerHand.addCard(deck.draw());
    }

    void BlackjackGame::dealerHit() {
        dealerHand.addCard(deck.draw());
    }

    bool BlackjackGame::isPlayerBusted() const {
        return playerHand.getValue() > 21;
    }

    bool BlackjackGame::isDealerBusted() const {
        return dealerHand.getValue() > 21;
    }

    bool BlackjackGame::doesPlayerWin() const {
        if (isPlayerBusted()) {
            return false;
        }
        if (isDealerBusted()) {
            return true;
        }
        return playerHand.getValue() > dealerHand.getValue();
    }

    // Function to create a new game
    BlackjackGame* BlackjackGame::makeGame() {
        return new BlackjackGame();
    }

    void BlackjackGame::start() {
        std::string playAgain = "yes";  // Default to play again
        std::string choice;

        while (playAgain == "yes" || playAgain == "y") {  // While the player wants to play again
            // Reset the hands
            playerHand.cards.clear();
            dealerHand.cards.clear();

            // Deal the initial cards to player and dealer
            dealInitialCards();

            std::cout << "Initial Hands:\n";
            std::cout << "Player's Hand: " << playerHand << " (Value: " << playerHand.getValue() << ")\n";
            std::cout << "Dealer's Hand: " << dealerHand << " (Value: " << dealerHand.getValue() << ")\n";

            // Player's turn - let the player decide whether to hit or stay
            std::cout << "Player's Turn: Type 'hit' to take a card or 'stay' to end your turn.\n";

            while (true) {  // Continue until the player chooses to stay
                std::cout << "Player's choice: ";
                std::cin >> choice;  // Get player input

                if (choice == "hit") {  // Player chooses to hit
                    playerHit();
                    std::cout << "Player hits.\n";
                    std::cout << "Player's Hand: " << playerHand << " (Value: " << playerHand.getValue() << ")\n";

                    if (isPlayerBusted()) {  // Check if the player busted
                        std::cout << "Player busted! Dealer wins!\n";
                        break;  // Exit the loop and move to the end
                    }
                }
                else if (choice == "stay") {  // Player chooses to stay
                    std::cout << "Player stays.\n";
                    break;  // Exit the loop and move to the dealer's turn
                }
                else {
                    std::cout << "Invalid choice. Please type 'hit' or 'stay'.\n";
                }
            }

            // If the player hasn't busted, continue with the dealer's turn
            if (!isPlayerBusted()) {
                std::cout << "Dealer's Turn:\n";
                while (dealerHand.getValue() < 17) {  // Dealer hits until reaching or exceeding 17
                    std::cout << "Dealer hits.\n";
                    dealerHit();
                    std::cout << "Dealer's Hand: " << dealerHand << " (Value: " << dealerHand.getValue() << ")\n";
                }

                if (isDealerBusted()) {
                    std::cout << "Dealer busted! Player wins!\n";
                }
                else {
                    if (doesPlayerWin()) {
                        std::cout << "Player wins!\n";
                    }
                    else {
                        std::cout << "Dealer wins!\n";
                    }
                }
            }

            std::cout << "Final Hands:\n";
            std::cout << "Player's Hand: " << playerHand << " (Value: " << playerHand.getValue() << ")\n";
            std::cout << "Dealer's Hand: " << dealerHand << " (Value: " << dealerHand.getValue() << ")\n";

            // Ask the player if they want to play again
            std::cout << "Do you want to play again? (yes/no): ";
            std::cin >> playAgain;  // Capture the player's response
        }
    }



}  // namespace CSC2034





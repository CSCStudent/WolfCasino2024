#include "S02312175D.h"

namespace S02312175 {
    Player::Player() : currentBet_(0), chips_(1000), folded_(false) {}

    void Player::receiveCard(const Card& card) {
        hand_.push_back(card);
    }

    const std::vector<Card>& Player::getHand() const {
        return hand_;
    }

    int Player::getCurrentBet() const {
        return currentBet_;
    }

    int Player::getChips() const {
        return chips_;
    }

    void Player::addChips(int amount) {
        chips_ += amount;
    }

    void Player::bet(int amount) {
        if (amount > chips_) {
            // Can't bet more than what the player has
            currentBet_ += chips_;
            chips_ = 0;
        }
        else {
            currentBet_ += amount;
            chips_ -= amount;
        }
    }

    void Player::resetBet() {
        currentBet_ = 0;
    }

    bool Player::hasFolded() const {
        return folded_;
    }

    void Player::fold() {
        folded_ = true;
    }
}

#include <algorithm>
#include <chrono>
#include "S02312175B.h"

namespace S02312175 {
    Deck::Deck() : rng_(std::chrono::system_clock::now().time_since_epoch().count()) {
        for (int rank = static_cast<int>(Card::Rank::TWO); rank <= static_cast<int>(Card::Rank::ACE); ++rank) {
            for (int suit = static_cast<int>(Card::Suit::HEARTS); suit <= static_cast<int>(Card::Suit::SPADES); ++suit) {
                cards_.push_back(Card(static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit)));
            }
        }
    }

    void Deck::shuffle() {
        std::shuffle(cards_.begin(), cards_.end(), rng_);
    }

    Card Deck::dealCard() {
        if (isEmpty()) {
            throw std::out_of_range("Deck is empty");
        }
        Card dealtCard = cards_.back();
        cards_.pop_back();
        return dealtCard;
    }

    bool Deck::isEmpty() const {
        return cards_.empty();
    }
}

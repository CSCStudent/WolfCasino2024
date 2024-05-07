#ifndef DECK_TH
#define DECK_TH

#include "S02312175A.h"
#include <vector>
#include <random>

namespace S02312175 {
    class Deck {
    public:
        Deck();

        void shuffle();
        Card dealCard();
        bool isEmpty() const;

    private:
        std::vector<Card> cards_;
        std::mt19937 rng_; // Mersenne Twister random number generator
    };
}
#endif // DECK_H


#ifndef CARD_TH
#define CARD_TH

#include <iostream>
#include <string>

class Card {
public:
    enum class Rank {
        TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
    };

    enum class Suit {
        HEARTS, DIAMONDS, CLUBS, SPADES
    };

    Card(Rank rank, Suit suit);

    Rank getRank() const;
    Suit getSuit() const;
    std::string toString() const;

private:
    Rank rank_;
    Suit suit_;
};

std::ostream& operator<<(std::ostream& os, const Card& card);

#endif // CARD_H

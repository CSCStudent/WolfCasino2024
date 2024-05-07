#include "S02312175A.h"

Card::Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) {}

Card::Rank Card::getRank() const {
    return rank_;
}

Card::Suit Card::getSuit() const {
    return suit_;
}

std::string Card::toString() const {
    std::string rank_str;
    switch (rank_) {
    case Rank::TWO: rank_str = "2"; break;
    case Rank::THREE: rank_str = "3"; break;
    case Rank::FOUR: rank_str = "4"; break;
    case Rank::FIVE: rank_str = "5"; break;
    case Rank::SIX: rank_str = "6"; break;
    case Rank::SEVEN: rank_str = "7"; break;
    case Rank::EIGHT: rank_str = "8"; break;
    case Rank::NINE: rank_str = "9"; break;
    case Rank::TEN: rank_str = "10"; break;
    case Rank::JACK: rank_str = "J"; break;
    case Rank::QUEEN: rank_str = "Q"; break;
    case Rank::KING: rank_str = "K"; break;
    case Rank::ACE: rank_str = "A"; break;
    }

    std::string suit_str;
    switch (suit_) {
    case Suit::HEARTS: suit_str = "H"; break;
    case Suit::DIAMONDS: suit_str = "D"; break;
    case Suit::CLUBS: suit_str = "C"; break;
    case Suit::SPADES: suit_str = "S"; break;
    }

    return rank_str + suit_str;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.toString();
    return os;
}

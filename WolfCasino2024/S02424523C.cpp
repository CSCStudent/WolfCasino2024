//insolution
#include "S02424523C.h"

namespace S02424523 {
	Card::Card() {

	}
	Card::Card(int rank, int suit) {
		this->rank = rank;
		this->suit = suit;
	}
	Card::~Card() {

	}
	const array<string, 14> Card::Ranks = {
		"0", "Ace", "2", "3", "4", "5", "6","7", "8",
		"9", "10", "J", "Q", "K"
	};
	const array<string, 4> Card::Suits = {
		"Hearts", "Diamonds", "Clubs", "Spades"
	};
	int Card::getRank() const {
		return rank;
	}
	int Card::getSuit() const {
		return suit;
	}
	void Card::setRank(int newRank) {
		rank = newRank;
	}
	void Card::setSuit(int newSuit) {
		suit = newSuit;
	}
	int Card::compareTo(Card& oCard) {
		if (suit > oCard.suit) {
			return 1;
		}
		else if (this->suit < oCard.suit) {
			return -1;
		}
		if (rank > oCard.rank) {
			return 1;
		}
		else if (rank < oCard.rank) {
			return -1;
		}
		else {
			return 0;
		}
	}
	string Card::toString() {
		return Ranks[rank] + " of " + Suits[suit];
	}
}

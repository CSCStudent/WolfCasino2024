#include <string>
#include <random>
#include "S02977128C.h"

using namespace std;

namespace S02977128 {
	Card::Card() {
		this->rank = -1;
		this->suit = -1;
	}

	Card::Card(const Card& card) {
		this->rank = card.rank;
		this->suit = card.suit;
	}

	Card::Card(int rank, int suit) {
		this->rank = rank;
		this->suit = suit;
	}

	Card :: ~Card() {

	}

	string Card::cardString() {
		string str = "";
		str = str + ranks[this->rank] + " of " + suits[this->suit];
		return str;
	}

	int Card::getRank() const {
		return this->rank;
	}

	int Card::getSuit() const {
		return this->suit;
	}

	void Card::setRank(int rank) {
		this->rank = rank;
	}

	void Card::setSuit(int suit) {
		this->suit = suit;
	}

	void Card::copyCard(Card& source) {
		this->rank = source.rank;
		this->suit = source.suit;
	}

	string Card::rankToString(int rank) {
		return ranks[rank];
	}

	void Card :: operator=(const Card card) {
		rank = card.rank;
		suit = card.suit;
	}

	bool Card :: operator <(const Card card) {
		return (rank < card.rank);
	}

	bool Card :: operator >(const Card card) {
		return (rank > card.rank);
	}

	bool Card :: operator <=(const Card card) {
		return (rank <= card.rank);
	}

	bool Card :: operator >=(const Card card) {
		return (rank >= card.rank);
	}
}
#include <iostream>
#include "S01505380C.h"

using namespace std;

namespace S01505380 {

	string card::suits[5] = { "CLUBS", "DIAMONDS", "HEARTS", "SPADES", "ERROR" };
	string card::ranks[14] = { "2", "3", "4", "5", "6", "7",
							"8", "9", "10", "Jack", "Queen", "King", "Ace" , "ERROR" };

	card::card(int rank, int suit) {
		this->rank = rank;
		this->suit = suit;

	}

	bool card::isError() {
		return suit == 4 || rank == 13;

	}

	//compare the cards to eachother
	bool card::operator < (card otherCard) {
		return rank < otherCard.rank;
	}

	bool card::operator > (card otherCard) {
		return rank > otherCard.rank;
	}

	bool card::operator == (card otherCard) {
		return rank == otherCard.rank;
	}

	//overload the output to print the card
	ostream& operator << (ostream& output, card& myCard) {
		output << card::ranks[myCard.rank] << " of " << card::suits[myCard.suit];
		return output;
	}
}
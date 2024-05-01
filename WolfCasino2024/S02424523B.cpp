//in solution
#include "S02424523B.h"

/*learned keywords.push_back creates a new object then adds to the end of a vector
* while emplace_back essentially builds the new object in place, and doesnt need to move it
* into the vector.
* reserve will be used to allocate memory, in this case for our vector.
* in summary reserve will set aside memory for a vector and emplace_back will build each object in place.
* 
* Deck() uses Card constructor to create then allocate cards into a deck (vector).
*/

namespace S02424523 {
	Deck::Deck() {
		cards.reserve(52);

		for (int i = 1; i < 14; i++) {
			for (int j = 0; j < 4; j++) {
				cards.emplace_back(i, j);
			}
		}
	}
	void Deck::reset() {
		cards.clear();
		cards.reserve(52);

		for (int i = 1; i < 14; i++) {
			for (int j = 0; j < 4; j++) {
				cards.emplace_back(i, j);
			}
		}
	}
	//Deck(int numCards) reserves memory for cards.
	Deck::Deck(int numCards) {
		cards.reserve(numCards);
	}
	//Deck() destructor.
	Deck::~Deck() {

	}
	//shuffles the deck of cards.
	void Deck::shuffle() {
		int index = 0;
		Card temp;
		srand(time(NULL));

		for (int i = 0; i < cards.size(); i++) {
			index = rand() % cards.size();
			temp = cards[i];
			cards[i] = cards[index];
			cards[index] = temp;
		}
	}
	//sorts the deck of cards in ascending order of rank in a suit, then rank in next suit...
	void Deck::selectionSort() {
		for (int i = 0; i < cards.size() - 1; i++) {
			int bigIndex = 0;
			for (int j = 1; j < cards.size() - i; j++) {
				if (cards[j].compareTo(cards[bigIndex]) > 0) {
					bigIndex = j;
				}
			}
			swap(cards, bigIndex, cards.size() - i - 1);
		}
	}
	//swaps two cards in the deck.
	void Deck::swap(vector<Card>& cards, int index1, int index2) {
		Card temp;

		temp = cards[index1];
		cards[index1] = cards[index2];
		cards[index2] = temp;
	}
	//returns the deck of cards.
	const vector<Card>& Deck::getCards() const {
		return cards;
	}
	Card Deck::getCard() {
		Card card = cards.back();
		cards.pop_back();
		return card;
	}
	//sets the deck of cards to a new deck of cards.
	void Deck::setCards(const vector<Card>& cards) {
		this->cards = cards;
	}

	size_t Deck::getSize() {
		return cards.size();
	}
	//returns the deck of cards as a string.
	//double check the logic. It may not work as intended.
	string Deck::toString() {
		string str;
		int rank;
		int suit;
		for (size_t i = 0; i < cards.size(); ++i) {
			if (i > 0) {
				str += ", ";
			}
			rank = cards[i].getRank();
			suit = cards[i].getSuit();
			str += cards[i].toString();
		}
		return str;
	}
}

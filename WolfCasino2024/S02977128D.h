#ifndef DECK_GOFISH
#define DECK_GOFISH

#include <iostream>
#include <vector>
#include "S02977128C.h"

using namespace std;
namespace S02977128 {
	class Deck {
	private:
		vector<Card> cards;

	public:
		Deck();
		void shuffle();
		Card draw();
		vector<Card> getCards();
	};
}
#endif

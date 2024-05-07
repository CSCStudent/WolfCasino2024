#include <string>
#include <random>
#include "S02977128D.h"

using namespace std;

namespace S02977128 {
	Deck::Deck() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 13; j++) {
				cards.push_back(Card(j, i));
			}
		}
	}

	void Deck::shuffle() {
		for (int i = 0; i < cards.size(); i++) {
			int index = rand() % 52;
			Card temp;
			temp.copyCard(cards[i]);
			cards[i].copyCard(cards[index]);
			cards[index].copyCard(temp);
		}
	}

	Card Deck::draw() {
		Card top = cards.back();
		cards.pop_back();
		return top;
	}

	vector<Card> Deck::getCards() {
		return cards;
	}
}

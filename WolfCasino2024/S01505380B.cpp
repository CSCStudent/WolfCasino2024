#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<queue>
#include "S01505380B.h"

using namespace std;

namespace S01505380 {
	void deck::shuffle() {
		int random;
		//use the current time as the random number seed
		srand(time(NULL));
		//list of cards already added
		vector <card> randCards;
		for (int i = 0; i < 52; i++) {
			randCards.emplace_back(i % 13, i / 13);
		}
		//pull cards out and push them into the back of the deck
		while (randCards.size() > 0) {
			random = rand() % randCards.size();

			cards.push(randCards[random]);//push the cards from the random set

			randCards.erase(randCards.begin() + random); //delete the random card
		}

	}

	card deck::drawCard() {
		if (!cards.empty()) {
			card card = cards.front();

			cards.pop();
			return card;
		}
		else {
			card errorCard(4, 13);

			cout << "Deck empty";
			return errorCard;
		}
	}

	void deck::addCard(card newCard) {
		cards.push(newCard);

	}

	void deck::addToDeck(deck& otherDeck) {
		while (!otherDeck.cards.empty()) {
			cards.push(otherDeck.drawCard());

		}
	}

	bool deck::isEmpty() {
		return cards.empty();

	}

	int deck::deckSize() {

		return cards.size();
	}
}
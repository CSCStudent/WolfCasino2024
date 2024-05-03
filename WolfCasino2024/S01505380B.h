#pragma once
#include <iostream>
#include <queue>
#include "S01505380C.h"

using namespace std;
namespace S01505380 {

	class deck {

	public:
		void shuffle();
		void addCard(card);
		card drawCard();
		void addToDeck(deck&);
		bool isEmpty();
		int deckSize();

	private:
		queue <card> cards;

	};
}

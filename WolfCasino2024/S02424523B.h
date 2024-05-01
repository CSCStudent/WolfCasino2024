//in solution
#pragma once
#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include "S02424523C.h"
using namespace std;

namespace S02424523{
	class Deck {
	private:
		vector<Card> cards;
	public:
		Deck();
		Deck(int numCards);
		~Deck();

		void shuffle();
		void selectionSort();
		void swap(vector<Card>& cards, int index1, int index2);
		void reset();

		const vector<Card>& getCards() const;
		Card getCard();
		size_t getSize(); // return int or size_t?
		void setCards(const vector<Card>& cards);
		string toString();
	};
}
#endif

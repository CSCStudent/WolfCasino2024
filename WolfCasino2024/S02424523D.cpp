//in solution
#include "S02424523D.h"
//!!! need to make adjustments to hand size and reserve I think. if I am checking hand size in the game and
//! space is already reserved I think the hand will technically have a size which messes with game logic.
//! shrink_to_fit() may be useful to change the hand "size". however, I may want to instead check if space are empty
//! in the hand instead, but I am unsure if those data space are truly empty or if there is random data in there.

namespace S02424523 {
	Hand::Hand() {
		hand.reserve(3);
	}
	Hand::Hand(Card c1, Card c2, Card c3) {
		hand.push_back(c1);
		hand.push_back(c2);
		hand.push_back(c3);
	}
	Hand::~Hand() {

	}
	void Hand::addToHand(Card card) {
		hand.push_back(card);
	}
	void Hand::clearHand() {
		hand.clear();
		hand.shrink_to_fit();
	}
	int Hand::handTotal() {
		int sum = 0;
		for (Card card : hand) {
			if (card.getRank() > 9) {
				sum += 0;
			}
			else {
				sum += card.getRank();
			}
		}
		if (sum > 9) {
			sum = sum % 10;
		}
		return sum;
	}
	size_t Hand::handSize() {
		return hand.size();
	}
	Card Hand::getCard(int index) {
		Card card = hand[index];
		return card;
	}
	vector<Card> Hand::getHand() {
		return hand;
	}
	void Hand::setHand(vector<Card> hand) {
		this->hand = hand;
	}

	vector<Card>::iterator Hand::begin() {
		return hand.begin();
	}
	vector<Card>::iterator Hand::end() {
		return hand.end();
	}
	string Hand::toString(Hand hand) {

		string cardInHand = "";
		for (Card& card : hand) {  // Use const reference to avoid copying the card object
			cardInHand += card.toString() + " ";
		}
		cardInHand += "Total: " + to_string(hand.handTotal());
		return cardInHand;

	}
}

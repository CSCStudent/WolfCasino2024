#include "S02977128B.h"

using namespace std;

namespace S02977128 {
	Player::Player() {

	}


	Player :: ~Player() {

	}

	void Player::deal(Card card) {
		hand.push_back(card);
	}

	bool Player::inHand(int rank) {
		for (Card card : hand) {
			if (card.getRank() == rank) {
				return true;
			}
		}
		cout << "Card not in hand. Please select a card that is in your hand." << endl;
		return false;
	}

	Card Player::give(int index) {
		Card card = hand[index];
		hand.erase(hand.begin() + (index));
		return card;
	}

	void Player::take(Card card) {
		hand.push_back(card);
	}

	vector<Card> Player::getHand() {
		return hand;
	}

	int Player::getPoints() const {
		return points;
	}

	void Player::setPoints(int points) {
		this->points = points;
	}

	bool Player::haveSuit(int rank) {
		int count = 0;
		for (Card c : hand) {
			if (c.getRank() == rank) {
				count++;
			}
		}
		if (count == 4) {
			Card temp;
			temp.setRank(rank - 1);
			points++;
			cout << "This player has four " << (temp.rankToString(rank)) << "s and has gained a point!\n\n";
			clearCards(Card(rank, -1));
			return true;
		}
		return false;
	}

	string Player::showHand() {
		string str;
		for (Card c : hand) {
			str = str + c.cardString() + '\n';
		}
		return str;
	}

	void Player::sortHand() {
		sort(hand.begin(), hand.begin() + hand.size());
	}

	void Player::clearCards(Card card) {
		for (size_t i = hand.size() - 1; i > 0; i--) {
			if (hand[i].getRank() == card.getRank())
				hand.erase(hand.begin() + i);
		}
	}
}
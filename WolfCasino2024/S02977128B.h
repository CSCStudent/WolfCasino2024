#ifndef PLAYER_GOFISH
#define PLAYER_GOFISH

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "S02977128C.h"

using namespace std;
namespace S02977128 {
	class Player {
	private:
		vector<Card> hand;
		int points = 0;

	public:
		Player();
		~Player();
		vector<Card> getHand();
		int getPoints() const;
		void setPoints(int);
		void deal(Card);
		void take(Card);
		Card give(int);
//		Card give(Card);
		bool inHand(int);
		bool haveSuit(int);
		string showHand();
		void sortHand();
		void clearCards(Card);
	};
}
#endif

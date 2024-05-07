#ifndef CARD_GOFISH
#define CARD_GOFISH

#include <iostream>
#include <vector>
#include <string>

using namespace std;
namespace S02977128 {
	class Card {
	private:
		int rank;
		int suit;
		const string suits[4] = { "Hearts", "Diamonds", "Spades", "Clubs" };
		const string ranks[13] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

	public:
		Card();
		Card(const Card&);
		Card(int, int);
		~Card();
		int getRank() const;
		int getSuit() const;
		void setRank(int);
		void setSuit(int);
		string cardString();
		void copyCard(Card&);
		string rankToString(int);
		void operator = (const Card);
		bool operator < (const Card);
		bool operator > (const Card);
		bool operator <= (const Card);
		bool operator >= (const Card);
	};
}
#endif
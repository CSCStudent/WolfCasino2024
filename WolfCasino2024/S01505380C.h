#pragma once 
#include <string>

using namespace std;

namespace S01505380 {

	class card {
	private:

		int rank;
		int suit;

		//card 4,15 is an error card
		static string suits[5]; //to include the error card for the empty deck
		static string ranks[14];

	public:
		card(int, int);

		bool operator < (card);
		bool operator > (card);
		bool operator == (card);
		bool isError();

		friend ostream& operator << (ostream& output, card& myCard);

	};

}
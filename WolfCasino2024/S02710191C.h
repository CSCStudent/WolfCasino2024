#pragma once
#include <vector>
#include <iostream>
#include "S02710191B.h"

using namespace std;

namespace S02710191 {

	class DiceHand {
		private:

		public:
			vector<Die> hand;
			int size = 5;
			void removeDie(); // removes a single die from the hand vector
			bool isEmpty(); // checks if hand no longer has dice
			void printHand();
			void rerollHand(); // rerolls all dice in a hand
			int* highestQuantityDie(int dieSideCount[]); // creates an array of each dice total
			DiceHand();
			~DiceHand();

			//friend std::ostream& operator<< (std::ostream&, DiceHand&);
	};
}
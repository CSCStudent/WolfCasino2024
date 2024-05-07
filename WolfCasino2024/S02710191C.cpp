#include "S02710191C.h"
#include <iostream>
#include <ctime>
#include <chrono> 

using namespace std;

namespace S02710191 {
	DiceHand::DiceHand() {
		srand(std::chrono::system_clock::now().time_since_epoch().count());
		for (int i = 0; i < 5; i++) {
			hand.push_back(*new Die());
		}
	}

	DiceHand::~DiceHand() {

	}

	void DiceHand::removeDie() {
		size -= 1;
		hand.pop_back();
	}

	bool DiceHand::isEmpty() {
		return hand.empty();
	}

	void DiceHand::printHand() {
		for (Die die : hand) {
			cout << die.getValue() << " ";
		}
		cout << endl;
	}

	void DiceHand::rerollHand() {
		// iterates through hand and rerolls each value
		for (Die &die : hand) { 
			die.rollDie();
		}
	}

	

	int* DiceHand::highestQuantityDie(int dieSideCount[]) {
		
		// counts each die value
		for (Die die : hand) {
			if (die.getValue() == 1) {
				dieSideCount[0] += 1;
			}
			else if (die.getValue() == 2) {
				dieSideCount[1] += 1;
			}
			else if (die.getValue() == 3) {
				dieSideCount[2] += 1;
			}
			else if (die.getValue() == 4) {
				dieSideCount[3] += 1;
			}
			else if (die.getValue() == 5) {
				dieSideCount[4] += 1;
			}
			else if (die.getValue() == 6) {
				dieSideCount[5] += 1;
			}
		}

		return dieSideCount;
	}
}
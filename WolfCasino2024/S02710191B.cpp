#include <iostream>
#include <ctime>
#include <chrono> 
#include "S02710191C.h"

using namespace std;

namespace S02710191 {

	Die::Die() {
		value = (rand() % 6 + 1);
	}

	Die::~Die() {

	}

	// randomizes die value
	int Die::rollDie() {
		srand((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
		value = (rand() % 6 + 1);
		return value;
	}
	
	// returns value on die
	int Die::getValue() {
		return value;
	}
}
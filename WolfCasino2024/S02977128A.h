#pragma once
#include <thread>
#include <chrono>
#include <vector>
#include "Casino.h"
#include "S02977128B.h"
#include "S02977128D.h"

namespace S02977128 {
	class GoFish : public CSC2034::Casino {
	public:
		GoFish() {};
		void start();
		void deal(vector<Player>&,Deck&);
		bool play(vector<Player>&, int&, Deck&);
		void pointsCheck(vector<Player>&);
		static GoFish* makeGame();
	};
}
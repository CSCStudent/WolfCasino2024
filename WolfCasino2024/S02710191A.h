#pragma once
#include "Casino.h"
#include "S02710191C.h"

namespace S02710191 {

	class LiarsDice : public CSC2034::Casino {
	private:
		DiceHand playerHand;
		DiceHand houseHand;
	public:
		LiarsDice();
		~LiarsDice();
		static LiarsDice* makeGame();
		void start();
	};
}
//#endif
